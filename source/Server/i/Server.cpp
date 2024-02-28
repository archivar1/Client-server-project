
#include "Server.h"

void main()
{
	
	SOCKET ServSock;
	SOCKET ClientConn;
	CreateSocket(ServSock, ClientConn);
	while (true) {
		HandleClientConn(ClientConn);
		closesocket(ServSock);
		closesocket(ServSock);
		closesocket(ClientConn);
		WSACleanup();
		std::cout << "Trying to reconnect" << std::endl;
		CreateSocket(ServSock, ClientConn);
	}

	closesocket(ServSock);
	WSACleanup();

}