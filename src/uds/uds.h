#ifndef UDS
#define UDS

	int uds_server_init(const char* socket_path);
	int uds_server_read(int server_sock, char* buffer, int len);

	int uds_client_init(const char* socket_path);

#endif
