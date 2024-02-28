#pragma once
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <inaddr.h>
#include <stdio.h>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include <condition_variable>
#include <chrono>
#include <algorithm>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
static string buffer;
static mutex buffer_mutex;
static condition_variable buffer_cv;
void InputDataThread();
void DataProcessThread(SOCKET);