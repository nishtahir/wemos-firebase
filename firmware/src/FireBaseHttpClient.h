#ifndef FireBaseHttpClient_h
#define FireBaseHttpClient_h

#include "RestClient.h"

class FirebaseHttpClient : public RestClient {

    public :
        FirebaseHttpClient(const char* host, const char* token);
        FirebaseHttpClient(const char* host, const char* token, int port);

        int get(const char* path , String* response);
        int put(const char* path, const char* body, String* response);

    private :
        const char* token;
        String appendTokenToPath(const char* path);
};

#endif