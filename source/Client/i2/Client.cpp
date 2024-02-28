
#include "CreateSocket.h"
#include "ThreadFoo.h"


void main()
{
	SOCKET ClientSock;
	CreateSocket(ClientSock);

	while (true) {
		std::thread t1(InputDataThread);
		std::thread t2(DataProcessThread, ClientSock);
		t1.join();
		t2.join();
	}

	closesocket(ClientSock);
	WSACleanup();

	

}