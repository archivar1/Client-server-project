#include "Server.h"
void CreateSocket(SOCKET& ServSock, SOCKET& ClientConn)
{
	
	int erStat; //Ñheck error
	in_addr ip_to_num;
	erStat = inet_pton(AF_INET, IP_SERV, &ip_to_num);

	if (erStat <= 0)
	{
		std::cerr << "Error in IP translation to special numeric format" << std::endl;
		return;
	}


	// WinSock initialization
	WSADATA wsData;
	WORD DLLVersion = MAKEWORD(2, 2);

	if (WSAStartup(DLLVersion, &wsData) != 0)
	{
		std::cerr << "Error WinSock version initializaion #" << WSAGetLastError() << std::endl;
		return;
	}
	else
		std::cout << "WinSock initialization is OK" << std::endl;

	// Server socket initialization
	ServSock = socket(AF_INET, SOCK_STREAM, 0);

	if (ServSock == INVALID_SOCKET)
	{
		std::cerr << "Error initialization socket # " << WSAGetLastError() << std::endl;
		closesocket(ServSock);
		WSACleanup();
		return;
	}
	else
		std::cout << "Server socket initialization is OK" << std::endl;

	// Server socket binding
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr = ip_to_num;
	addr.sin_port = htons(PORT_NUM);

	erStat = bind(ServSock, (sockaddr*)&addr, sizeof(addr));

	if (erStat != 0)
	{
		std::cerr << "Error Socket binding to server info. Error # " << WSAGetLastError() << std::endl;
		closesocket(ServSock);
		WSACleanup();
		return;
	}
	else
		std::cout << "Binding socket to Server info is OK" << std::endl;

	//Starting to listen to any Clients
	erStat = listen(ServSock, SOMAXCONN);

	if (erStat != 0)
	{
		std::cerr << "Can't start to listen to. Error # " << WSAGetLastError() << std::endl;
		closesocket(ServSock);
		WSACleanup();
		return;
	}
	else
	{
		std::cout << "Listening.." << std::endl;
	}

	//Client socket creation and acception in case of connection
	sockaddr_in clientInfo;
	SOCKET Connections[100];
	int clientInfo_size = sizeof(clientInfo);
	for (int i=0; i<100; i++)
	{
		ClientConn = accept(ServSock, (sockaddr*)&clientInfo, &clientInfo_size);

		if (erStat != 0)
		{
			std::cerr << "Client detected, but can't connect to a client. Error # " << WSAGetLastError() << std::endl;
			closesocket(ServSock);
			closesocket(ClientConn);
			WSACleanup();
			return;
		}
		else
		{
			std::cout << "Connection to a client established successfully" << std::endl;
			char clientIP[22];
			inet_ntop(AF_INET, &clientInfo.sin_addr, clientIP, INET_ADDRSTRLEN);

			std::cout << "Client connected with IP address " << clientIP << std::endl;


		}
		Connections[i] = ClientConn;
		std::thread(HandleClientConn, Connections[i]).detach();
	}
}