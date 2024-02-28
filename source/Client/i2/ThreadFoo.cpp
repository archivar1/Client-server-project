#include "ThreadFoo.h"
#include "CreateSocket.h"
void InputDataThread()
{
	char input[BUFFER_SIZE];
	while (true)
	{

		std::cout << "Enter the line \n";
		std::cin >> input;

		//Check the line
		if (std::strlen(input) <= BUFFER_SIZE && std::all_of(input, input + std::strlen(input), ::isdigit))
		{
			std::string str_input(input);
			//Sort
			std::sort(str_input.rbegin(), str_input.rend());
			//Replace
			for (int i = 0; i < str_input.length(); i++)
			{
				if ((str_input[i]) % 2 == 0)
				{
					str_input.replace(i, 1, "KB");
					i++;
				}

			}

			//Send data to buffer
			std::unique_lock<std::mutex> lock(buffer_mutex);
			buffer = str_input;
			buffer_cv.notify_one();
		}
		else
		{
			std::cout << "Error, wrong line\n";
		}
	}

}

void DataProcessThread(SOCKET sock)
{
	std::vector <char>servBuff(BUFFER_SIZE);
	int sum = 0;
	while (true)
	{
		//Waiting for data
		std::unique_lock<std::mutex> ulock(buffer_mutex);
		buffer_cv.wait(ulock, [] {return !buffer.empty(); });

		//Work on data
		std::string data = buffer;
		buffer.clear();
		ulock.unlock();
		std::cout << "Data " << data.data() << std::endl;

		for (int i = 0; i < data.size(); i++)
		{
			if (isdigit(data[i]))
			{
				sum += data[i] - '0';
			}
		}
		std::cout << "Sum " << sum << std::endl;
		std::string str = std::to_string(sum);

		int packet_size = send(sock, str.c_str(), sizeof(str), 0);
		if (packet_size == SOCKET_ERROR) {
			std::cerr << "Can't send message or receive message, Error # " << WSAGetLastError() << std::endl;
			sum = 0;
			closesocket(sock);
			WSACleanup();
			std::cerr << "Trying to recconect " << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(5));
			CreateSocket(sock);
			continue;
		}
		packet_size = recv(sock, servBuff.data(), servBuff.size(), 0);
		if (packet_size == SOCKET_ERROR) {
			std::cerr << "Can't send message or receive message, Error # " << WSAGetLastError() << std::endl;
			sum = 0;
			closesocket(sock);
			WSACleanup();
			std::cerr << "Trying to recconect " << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(5));
			CreateSocket(sock);
			continue;
		}

		else
			std::cout << "Server message: " << servBuff.data() << std::endl;
		sum = 0;
		buffer.clear();

	}

}