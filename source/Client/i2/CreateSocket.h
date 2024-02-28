#pragma once
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <inaddr.h>
#include <thread>
#pragma comment(lib, "ws2_32.lib")
const char SERVER_IP[] = "127.0.0.1"; //Local ip
const int SERVER_PORT_NUM = 8080; //Port
const int BUFFER_SIZE = 64; // Max buffer size

void CreateSocket(SOCKET&);