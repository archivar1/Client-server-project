#include "Server.h"
void HandleClientConn(SOCKET ClientConn)
{
	std::vector <char> servBuff(BUFFER_SIZE);	// Buffers for sending and receiving data
	int packet_size = 0;
	std::string sendbuf;



	while (true) {
		// Receiving packet from client. Program is waiting (system pause) until receive
		packet_size = recv(ClientConn, servBuff.data(), servBuff.size(), 0);
		if (packet_size == SOCKET_ERROR)
		{
			std::cout << "Error receiving data from client. Error # " << WSAGetLastError() << std::endl;
			break;
		}
		else
		{
			std::cout << "Client's message: " << servBuff.data() << std::endl;
			if (servBuff.size() >= 2 && std::stoi(servBuff.data()) % 32 == 0 && std::stoi(servBuff.data()) != 0)
			{
				std::cout << "data Accept" << std::endl;
				sendbuf = "Accept";
				packet_size = send(ClientConn, sendbuf.c_str(), sizeof(sendbuf), 0);
			}
			else
			{
				std::cout << "Error, data decline" << std::endl;
				sendbuf = "Decline";
				packet_size = send(ClientConn, sendbuf.c_str(), sizeof(sendbuf), 0);
			}

		}
		if (packet_size == SOCKET_ERROR)
		{
			std::cout << "Can't send message to Client. Error # " << WSAGetLastError() << std::endl;
			break;
		}

	}

	closesocket(ClientConn);
}