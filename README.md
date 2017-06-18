# wemos-firebase Sample

Project that connects to the firebase realtime databse using the
Esp8266 powered Wemos D1 mini. 

# Structure

There are 3 parts to this project.

1. `firmware` - This is the embedded firmware that runs on the wemos. It's compiled using PlatformIO.
    To build this correctly, you will need to fillout the appropriate fields in the `platformio.ini` build flags.

```
build_flags = -DSSID_NAME=\"Your SSID here \" 
              -DSSID_PASSWORD=\"Your wifi password here\"
              -DFIREBASE_HOST=\"path to your firebase host here\"
              -DFIREBASE_AUTH_TOKEN=\"Generated access token here\"
              -DHTTP_DEBUG # Optional if you want to enable http debug logging
```
2. `token-generator` - This is to generate firebase access tokens to communicate with your db. You will need to add a 
`service_account.json` file to the root directory of the project. This can be exported from your firebase settings. You can build and run the project using -  
```
../gradlew assemble && java -jar build/libs/token-generator-1.0-SNAPSHOT.jar
```

This will print an access token in the terminal.

3. `mobile-app` - Companion app to display values obtained from firebase. Build and deploy using Android Studio.

# Setup

You will need to provide
1. Wifi credentials
2. Firebase hostname and acess token

Simply add the appropriate values in the `platformio.ini` config file and build
the project using


Afterwhich you can upload to your device and enjoy.