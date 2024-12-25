#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "uds/uds.h"

void power();

int main(int argc, char* argv[]){
	if(argc != 2){
		fprintf(stderr, "Wrong argument count.\n");
		return 1;
	}

	if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0){
		printf("Usage:\n-h\t\tshow this massage and exit.\noff\t\tsend 'off' to daemon and turn off the PC.\nreboot\t\tsend 'reboot' to daemon and reboot the PC.\nzzz\t\tsend 'zzz' to daemon and suspend the PC.\n");
		return 0;
	}
	else if(strcmp(argv[1], "poweroff") == 0){
		power("poweroff");
	}
	else if(strcmp(argv[1], "reboot") == 0){
		power("reboot");
	}
	else if(strcmp(argv[1], "zzz") == 0){
		power("zzz");
	}
	else{
		fprintf(stderr, "Unknown argument. Use '-h' to see usage.\n");
		return 1;
	}

	return 0;
}

void power(char* arg){
	int sockfd = uds_client_init("/tmp/power.sock");
	send(sockfd, arg, strlen(arg), 0);
	close(sockfd);
}
