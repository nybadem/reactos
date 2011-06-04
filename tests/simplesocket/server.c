#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>

#define PORT 		54321
#define DIRSIZE 	8192

int main()
{
	char     dir[DIRSIZE];
	int 	 sd, sd_current, cc, fromlen, tolen;
	int 	 addrlen;
	struct   sockaddr_in sin;
	struct   sockaddr_in pin;
	
	WORD version = MAKEWORD(1,1);
	WSADATA wsaData;

	WSAStartup(version, &wsaData);
 
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("socket error\n");
		exit(1);
	}

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(PORT);

	if (bind(sd, (struct sockaddr *) &sin, sizeof(sin)) == -1)
	{
		printf("bind");
		exit(1);
	}

	if (listen(sd, 5) == -1)
	{
		printf("listen error\n");
		exit(1);
	}

	addrlen = sizeof(pin); 
	if ((sd_current = accept(sd, (struct sockaddr *)  &pin, &addrlen)) == -1)
	{
		printf("accept error\n");
		exit(1);
	}

	if (recv(sd_current, dir, sizeof(dir), 0) == -1)
	{
		printf("recv error\n");
		exit(1);
	}

	printf("Message from client: %s\n", dir);
    
	if (send(sd_current, dir, strlen(dir), 0) == -1)
	{
		printf("send error\n");
		exit(1);
	}

	close(sd_current);
	close(sd);

	Sleep(1000);
	
	return 0;
}
 