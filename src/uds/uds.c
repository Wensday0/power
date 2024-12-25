#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include "uds.h"

int uds_server_init(const char* socket_path){
	struct sockaddr_un addr;
	memset(&addr, 0, sizeof(struct sockaddr_un));

	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);

	int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sockfd < 0){
		return -1;
	}

	unlink(socket_path);

	int rc;

	rc = bind(sockfd, (const struct sockaddr *)&addr, sizeof(addr));
	if(rc < 0){
		close(sockfd);
		return -1;
	}

	rc = listen(sockfd, 5);
	if(rc < 0){
		close(sockfd);
		return -1;
	}

	return sockfd;
}

int uds_client_init(const char* socket_path){
	struct sockaddr_un addr;
	memset(&addr, 0, sizeof(struct sockaddr_un));

	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);

	int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sockfd < 0) {
		return -1;
	}

	int rc = connect(sockfd, (const struct sockaddr *)&addr, sizeof(addr));
	if (rc < 0) {
		close(sockfd);
		return -1;
	}

	return sockfd;
}

int uds_server_read(int server_sock, char* buffer, int len) {
	struct sockaddr_un client_addr;
	socklen_t client_len = sizeof(client_addr);

	int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len);
	if (client_sock < 0) {
		return -1;
	}

	ssize_t bytes_read = read(client_sock, buffer, len - 1);
	buffer[bytes_read] = '\0';


	close(client_sock);
	return 0;
}
