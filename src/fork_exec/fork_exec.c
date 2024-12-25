#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "fork_exec.h"

void fork_exec(char* path, char* args[]) {
	pid_t pid = fork();

	if (pid == 0){
		execv(path, args);
		printf("exec");
		exit(1);
	}
	else if (pid < 0) {
		exit(1);
	}

	wait(NULL);
}
