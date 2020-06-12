#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char* message);

int main(int argc, char* argv[])
{
	int serv_sock, clnt_sock; /* Socket Descriptor */
	char message[BUF_SIZE];
	int str_len, i;

	struct sockaddr_in serv_adr;
	struct sockaddr_in clnt_adr;
	socklen_t clnt_adr_sz;

	/* ./echo_server <port> */
	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	/* get server socket */
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1)
		error_handling("socket() error");

	/* socket address setting to use */
	memset(&serv_adr, 0, sizeof(serv_adr)); // make dump to zero
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	/* binding */
	if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_sock))
		error_handling("bind() error");


	/* ready to get connection signal */
	if (listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	/* get five times acception */
	clnt_adr_sz = sizeof(clnt_adr);
	for (i = 0; i < 5; i++) {
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_size);
		if (clnt_sock == -1) /* exception */
			error_handling("accept() error");
		else {
			printf("Connected client %d \n", i+1 );

			while ((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
				write(clnt_sock, message, str_len);

			printf("Server read count : %d\n",str_len);
			close(clnt_sock);
		}
	}

	close(serv_sock);
	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}