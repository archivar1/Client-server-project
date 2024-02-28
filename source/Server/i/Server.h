#pragma once
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <inaddr.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <thread>
#include <condition_variable>
#include <algorithm>
#pragma comment(lib, "ws2_32.lib")

//Key constants
const char IP_SERV[] = "127.0.0.1";
const int PORT_NUM = 8080;
const int BUFFER_SIZE = 64;

void CreateSocket(SOCKET&, SOCKET&);
void HandleClientConn(SOCKET);