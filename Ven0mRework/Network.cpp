#include "Network.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::string cNetwork::postRequest(std::string data) {
	CURL *curl;
	CURLcode res;
	const char *postthis = data.c_str();
	std::string readBuffer;
	curl = curl_easy_init();
	if (curl) {
		std::string url = "http://420.69.420.69/license.php";
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postthis);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			std::cout << "Network Error!\n\n";
			exit(1);
		}
		curl_easy_cleanup(curl);
	}
	return readBuffer;
}

