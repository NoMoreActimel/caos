#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void free_cmds(char** cmds, int sz) {
    for (int i = 0; i != sz; ++i) {
        free(cmds[i]);
    }
    free(cmds);
}

int mysystem(const char *cmd) {
    size_t cmd_sz = strlen(cmd);
    if (cmd_sz == 0) {
        return -1;
    }

    bool in_token = false;
    int cnt_tokens = 0;
    for (size_t i = 0; i != cmd_sz; ++i) {
        if (cmd[i] != ' ') {
            if (!in_token) {
                in_token = true;
                cnt_tokens++;
            }
        } else if (in_token) {
            in_token = false;
        }
    }

    if (cnt_tokens == 0) {
        return -1;
    }

    char** cmds = malloc((cnt_tokens + 1) * sizeof(char*));
    int token_ind = 0;

    in_token = false;
    int token_start = 0;
    for (int i = 0; i != cmd_sz; ++i) {
        if (cmd[i] != ' ') {
            if (!in_token) {
                in_token = true;
                token_start = i;
            }
        } else {
            if (in_token) {
                in_token = false;
                cmds[token_ind] = malloc((i + 1 - token_start) * sizeof(char));
                for (int j = 0; j != i - token_start; ++j) {
                    cmds[token_ind][j] = cmd[token_start + j];
                }
                cmds[token_ind][i - token_start] = '\0';
                token_ind++;
            }
        }
    }
    if (in_token) {
        cmds[token_ind] = malloc((cmd_sz + 1 - token_start) * sizeof(char));
        for (int j = 0; j != cmd_sz - token_start; ++j) {
            cmds[token_ind][j] = cmd[token_start + j];
        }
        cmds[token_ind][cmd_sz - token_start] = '\0';
    }

    cmds[cnt_tokens] = NULL;

    int pid, status;

    if ((pid = fork()) == 0) {
        execvp(cmds[0], cmds);
        _exit(1);        
    } else if (pid < 0) {
        free_cmds(cmds, cnt_tokens + 1);
        return -1;
    } else {
        waitpid(pid, &status, 0);
        free_cmds(cmds, cnt_tokens + 1);

        if (WIFSIGNALED(status)) {
            return 1024 + WTERMSIG(status);
        } else if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            return -1;    
        }
    }
}