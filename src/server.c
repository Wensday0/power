#include <grp.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "fork_exec/fork_exec.h"
#include "uds/uds.h"


typedef struct{
	char* path;
	char* args[2];
} command;

int main(){
	command reboot = {"/sbin/reboot", {"reboot", NULL}};
	command poweroff = {"/sbin/poweroff", {"poweroff", NULL}};
	command zzz = {"/sbin/zzz", };

	freopen("/dev/null", "r", stdin);
//	freopen("/dev/null", "w", stdout);
	freopen("/dev/null", "w", stderr);

	int sockfd = uds_server_init("/tmp/power.sock");

	chmod("/tmp/power.sock", 0771);

	struct group* grp = getgrnam("power");
	chown("/tmp/power.sock", -1, grp->gr_gid);

	char buffer[9];
	while(1){
		uds_server_read(sockfd, buffer, sizeof(buffer)/sizeof(buffer[1]));

		if(strcmp(buffer, "zzz") == 0)
			fork_exec(zzz.path, zzz.args);
		if(strcmp(buffer, "poweroff") == 0)
			fork_exec(poweroff.path, poweroff.args);
		if(strcmp(buffer, "reboot") == 0)
			fork_exec(reboot.path, reboot.args);
		else printf("%s\n",buffer);
	}
}
