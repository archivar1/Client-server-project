cmake_minimum_required(VERSION 3.27)


project(Client)

add_executable (Client
	i2/Client.cpp
	i2/CreateSocket.cpp
	i2/ThreadFoo.cpp
	i2/CreateSocket.h
	i2/ThreadFoo.h)


