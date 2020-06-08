#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char* message);

int main(int argc, char* argv[])
{
	int serv_sock;
	int clnt_sock;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	char message[] = "Hello Mr bully";

	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	/* Creating Socket : socket() */
	/* IPv4 Setting, TCP Setting */
	if ((serv_sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		error_handling("socket() error");

	/* sockaddr setting */
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	/* Binding : bind() */
	/* binding socket, reference of socket address, size */
	if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind() error");

	/* Listen : listen() */
	/* server socket, number of queue ready to connect */
	if (listen(serv_sock, 5) == -1)
		error_handling("listen() error");
	clnt_addr_size = sizeof(clnt_addr);

	/* Accepting connection : accept() */
	/* server socket, client sockaddr, size */
	/* Server program just get the connecting signal. */
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	if (clnt_sock == -1)
		error_handling("accept() error");

	/* Sending message to client */
	/* like file descriptor, data, size */
	write(clnt_sock, message, sizeof(message));
	

	/* close socket descriptor */
	close(clnt_sock);
	close(serv_sock);

}
void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}