cmake_minimum_required(VERSION 3.27)


project(Server)

add_executable (Server
	i/Server.cpp
	i/CreateSocket.cpp
	i/HandleClientConn.cpp
	i/Server.h)



