Contributors:
Ellis Yang
Danny Vang
Vallerey Luvsangombo


This project is the foundation for a modern task alarm. 
The function of this device is to alert the user to know when their task is due or upcoming
  How it works
    -The Photon is constantly requesting a task from google's API (This is within time reason)
    -photon request -> middle man -> Server  
    -The photon will request for the next and up comming task/calendar event, the middle man will activate asking the server for the time then information gets sent back to the photon.
      Since this is an example, we have sped up the code to run every 30 seconds to alert the user. 
It has a simple clock functionality, well it is a clock with an alarm



libraries--
  Photon - JsonParserGeneratorRK
  https://docs.particle.io/reference/device-os/libraries/j/JsonParserGeneratorRK/
    This is the bridge for the middleman to contact to google's API to allow request interaction between the photon ->>> middleman "the python script" ->>> online server;then back to photon

    Adafruit -
    https://docs.particle.io/reference/device-os/libraries/a/Adafruit_SSD1305_RK/
    https://docs.particle.io/reference/device-os/libraries/a/Adafruit_SSD1306/
      This is the to build the functionality for the onscreen OLED. 


    

  -----Applications
  Google cloud 
   Google Workspace
    Google calendar API 
      Its a REST API
  C++
    Particle Photon 2
  JSON 
    functionality:
      Request then pull
        To know what type of information to pull

  web stuff
    HTML
    CSS
    Javascript
      -this also pulls a new api token from google
List of Files

-Adafruit_GFX.cpp
-Adafruit_GFX.h
-Adafruit_SSD1306.cpp
-Adafruit_SSD1306.h
-Adafruit_SSD1306_RK.h
-JsonParserGeneratorRK.cpp
-JsonParserGeneratorRK.h
-calendar-webhook.json
-credentials.json
-handler.js
-index.html
-package.json
-project_final.cpp
-styles.css
-token.json



List of Components 
Particle Photon 2
1 button
1 OLED (type: SSD1306)
1 speaker (cvs 2308)
11 wires

https://cmv1.github.io/iot-project/src/index.html <---- go here for life github page
