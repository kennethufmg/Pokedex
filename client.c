#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void usage(int argc, char **argv) {
	printf("usage: %s <server IP> <server port>\n", argv[0]);
	printf("example: %s 127.0.0.1 51511\n", argv[0]);
	exit(EXIT_FAILURE);
}

#define BUFSZ 1024

int main(int argc, char **argv) {
	if (argc < 3) {
		usage(argc, argv);
	}

	struct sockaddr_storage storage;
	if (0 != addrparse(argv[1], argv[2], &storage)) {
		usage(argc, argv);
	}

	int s;
	s = socket(storage.ss_family, SOCK_STREAM, 0);
	if (s == -1) {
		logexit("socket");
	}
	struct sockaddr *addr = (struct sockaddr *)(&storage);
	if (0 != connect(s, addr, sizeof(storage))) {
		logexit("connect");
	}

	char addrstr[BUFSZ];
	addrtostr(addr, addrstr, BUFSZ);

	char Envia[BUFSZ],Recebe[BUFSZ];
	
	while(1) {

		memset(Envia, 0, BUFSZ);
		printf(">> ");
		fgets(Envia, BUFSZ-1, stdin);
		size_t count = send(s, Envia, strlen(Envia)+1, 0); //ENVIA

		if (count != strlen(Envia)+1) {
			logexit("send");
		}
		
		//memset(Recebe, 0, BUFSZ);
		count = recv(s, Recebe, BUFSZ, 0);//RECEBE
		printf("<< %s\n", Recebe);

	}
	close(s);

	exit(EXIT_SUCCESS);
}