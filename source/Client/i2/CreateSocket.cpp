
#include "CreateSocket.h"
void CreateSocket(SOCKET& ClientSock)
{

	int erStat; // Check for errors
	in_addr ip_to_num;
	inet_pton(AF_INET, SERVER_IP, &ip_to_num);


	// WinSock initialization
	WSADATA wsData;
	erStat = WSAStartup(MAKEWORD(2, 2), &wsData);

	if (erStat != 0) {
		std::cerr << "Error WinSock version initializaion #" << WSAGetLastError() << std::endl;
		return;
	}
	else
		std::cout << "WinSock initialization is OK" << std::endl;

	// Socket initialization
	ClientSock = socket(AF_INET, SOCK_STREAM, 0);

	if (ClientSock == INVALID_SOCKET) {
		std::cerr << "Error initialization socket # " << WSAGetLastError() << std::endl;
		closesocket(ClientSock);
		WSACleanup();
	}
	else
		std::cout << "Client socket initialization is OK" << std::endl;

	// Establishing a connection to Server
	sockaddr_in servInfo;
	servInfo.sin_family = AF_INET;
	servInfo.sin_addr = ip_to_num;
	servInfo.sin_port = htons(SERVER_PORT_NUM);

	erStat = connect(ClientSock, (sockaddr*)&servInfo, sizeof(servInfo));

	if (erStat != 0) {
		std::cerr << "Connection to Server is FAILED. Error # " << WSAGetLastError() << std::endl;
		closesocket(ClientSock);
		WSACleanup();
		std::cerr << "Trying to recconect " << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		CreateSocket(ClientSock);

	}
	else
		std::cout << "Connection established SUCCESSFULLY. Ready to send a message to Server" << std::endl;
}