#ifndef NETWORK_H
#define NETWORK_H

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <string>

#include <curl/curl.h>
#include <curl/easy.h>
#pragma comment(lib, "winmm.lib")

#include <iostream>

class cNetwork {
protected:


public:
	DWORD a;
	

public:
	//static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
	std::string postRequest(std::string data);

};
#endif