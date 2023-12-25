#include "parser/ast.h"
#include "shell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

extern int errno;

void handleCTRC(int signal);
void handleCommand(node_t *node);
void handlePipe(node_t *node);
void handleDetach(node_t *node);

void initialize(void){
    /* This code will be called once at startup */
    if (prompt)
        prompt = "vush$ ";
}

void run_command(node_t *node){
    /* Print parsed input for testing - comment this when running the tests! */
    //print_tree(node);
    struct sigaction signals;
    signals.sa_handler = &handleCTRC;
    sigaction(SIGINT, &signals, NULL);


switch(node->type) {
    case NODE_COMMAND:
        handleCommand(node);
        break;

    case NODE_PIPE:
        handlePipe(node);
        break;

    case NODE_REDIRECT:
        break;

    case NODE_SUBSHELL:
        break;

    case NODE_DETACH:
        handleDetach(node);
        break;

    case NODE_SEQUENCE:
        run_command(node->sequence.first);
        run_command(node->sequence.second);
        break;
    }
return;

    if (prompt)
        prompt = "vush$ ";
}

void handleCTRC(int signal){
    printf("%i", signal); 
}

void handleCommand(node_t *node){
    
    pid_t forkID;
    if(strcmp(node->command.program, "cd") == 0){
        chdir(node->command.argv[1]);
        return ;
    }
    else if(strcmp(node->command.program, "exit") == 0){
        exit(atoi(node->command.argv[1]));
    }
    else{
        forkID = fork();
        
        if(forkID == 0){
            if (execvp(node->command.program, node->command.argv) == -1)
            perror("No such file or directory");
            exit(-1);
        }
        else{
            waitpid(-1, &forkID, 0);
        }
    }
}

void handleDetach(node_t *node){
    
    pid_t forkID;
    forkID = fork();
    if(forkID == -1){
        perror("Detach fork error");
        exit(-1);
    }
    else if(forkID == 0){
        handleCommand(node->detach.child);
        exit(0);
    }
    
}

void handlePipe(node_t *node){
    
    int fd[2];
    pipe(fd);
    if(node->pipe.n_parts <= 1){
        printf("Error! \n");
        exit(-1);
    }

    pid_t forkID1 = fork();
    if(forkID1 == 0){
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        run_command(node->pipe.parts[0]);
        exit(0);
    }

    pid_t forkID2 = fork();
    if(forkID2 == 0){
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        run_command(node->pipe.parts[1]);
        exit(0);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(-1, &forkID2, 0);
    waitpid(-1, &forkID1, 0);
}