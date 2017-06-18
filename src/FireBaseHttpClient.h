#ifndef FireBaseHttpClient_h
#define FireBaseHttpClient_h

#include "RestClient.h"

class FirebaseHttpClient : public RestClient {

    public :
        FirebaseHttpClient(const char* host, const char* token);
        FirebaseHttpClient(const char* host, const char* token, int port);

        int get(const char*, String*);

    private :
        const char* token;
};

#endif