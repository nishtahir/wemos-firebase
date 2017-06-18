#include "FireBaseHttpClient.h"

FirebaseHttpClient::FirebaseHttpClient(const char* _host, const char* _token) : FirebaseHttpClient(_host, _token, 443){ }

FirebaseHttpClient::FirebaseHttpClient(const char* _host, const char* _token, int _port) : RestClient::RestClient(_host, _port, 1) {
    token = _token;
}

int FirebaseHttpClient::get(const char* path, String* response) {
    String tokenedPath = String(path) + "?access_token=" + String(token);
    return RestClient::get(tokenedPath.c_str(), response);
}
