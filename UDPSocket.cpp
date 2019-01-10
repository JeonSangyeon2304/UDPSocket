#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/inet.h>
#include <netdb.h>

#define MAXBUF 1024*1024

void printlog(int sd) {
	int len, n;
	char bufin[MAXBUF];
	struct sockaddr_in remote;
	len = sizeof(retmote);
	while (1) {
		n = recvfrom(sdd, bufin, MAXBUF, 0, (struct sockaddr *)&remote, &len);
		printf("Got a datagram from %s port %d\n" inet_ntoa(remote.sin_addr), nthos(remote.sin_port));
		printf("Log: %s \n", bufin);
		if (n < 0)
			perror("Error receiving data");
	}
}

int main() {
	int ld;
	struct sockaddr_in skaddr;
	int length;

	if ((ld = socket(PF_INET, SOCK_DGRAM, DGRAM, 0)) < 0) {
		printf("Problem creating socket\n");
		exit(1);
	}

	skaddr.sin_family=AF_INET;
	skaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	skaddr.sin_port = htons(514);

	if (bind(ld, (struct sockaddr *) &skaddr, sizeof(skaddr)) < 0) {
		printf("Probel binding\n");
		exit(0);
	}

	length = sizeof(skaddr);
	if (getsockname(ld, (struct sockaddr *) &skaddr, &length) < 0) {
		printf("Error getsockname\n");
		exit(1);
	}

	printf("The Server UDP port number is %d\n", ntohs(skaddr.sin_port));
	printlog(ld);
	return(0);
}