#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4 // size of integer.
void error_handling(char* message);

int main(int argc, char* argv[])
{
	int sock;
	char opmsg[BUF_SIZE] = { 0, };
	int result, opnd_cnt, i;
	struct sockaddr_in serv_adr;

	/* You have to press like this */
	/* ./op_client <server_IP> <port> */
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	/* Creating Socket */
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		error_handling("socket() error");

	/* Socket address struct memory setting */
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]); // IP setting
	serv.adr.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("connect() error!");
	else
		puts("Connected........");


	/* getting operands */
	fputs("Operand count : ", stdout);
	scanf("%d", &opnd_cnt);
	opmsg[0] = (char)opnd_cnt; // This data structure will be used. Like paskal.

	for (i = 0; i < opnd_cnt; i++) {
		printf("Operand %d: ", i+1);
		scanf("%d", (int*)&opmsg[i * OPSZ + 1]); // We have to send 1 byte/ 4 bytes ..../ 4 bytes.
	}
	fgetc(stdin); // get '\n'

	/* getting operaotor */
	fputs("Operator: ", stdout);
	scanf("%c", &opmsg[opnd_cnt * OPSZ + 1]);
	


}