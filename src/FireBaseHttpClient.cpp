#include "FireBaseHttpClient.h"

FirebaseHttpClient::FirebaseHttpClient(const char* _host, const char* _token) : FirebaseHttpClient(_host, _token, 443){ }

FirebaseHttpClient::FirebaseHttpClient(const char* _host, const char* _token, int _port) : RestClient::RestClient(_host, _port, 1) {
    token = _token;
}

int FirebaseHttpClient::get(const char* path, String* response) {
    return RestClient::get(appendTokenToPath(path).c_str(), response);
}

int FirebaseHttpClient::put(const char* path, const char* body, String* response) {
    return RestClient::put(appendTokenToPath(path).c_str(), body, response);
}

String FirebaseHttpClient::appendTokenToPath(const char* path) {
    return String(path) + "?access_token=" + String(token);
}