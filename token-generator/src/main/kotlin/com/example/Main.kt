package com.example

import java.util.Arrays
import com.google.api.client.googleapis.auth.oauth2.GoogleCredential
import java.io.FileInputStream



fun main(args: Array<String>) {
    val googleCred = GoogleCredential.fromStream(FileInputStream("service_account.json"))
    val scoped = googleCred.createScoped(
            Arrays.asList(
                    "https://www.googleapis.com/auth/firebase.database",
                    "https://www.googleapis.com/auth/userinfo.email"
            )
    )
    scoped.refreshToken()
    val token = scoped.accessToken
    println("Token: $token")
}