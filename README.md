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
It has a simple clock functionality


libraries--
  Photon - JsonParserGeneratorRK
  https://docs.particle.io/reference/device-os/libraries/j/JsonParserGeneratorRK/
    This is the bridge for the middleman to contact to google's API to allow request interaction between the photon ->>> middleman "the python script" ->>> online server;then back to photon

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


    ----self notes---Ellis
    
    Add libraries
    // particle library add HttpClient
    // particle library add JsonParserGeneratorRK
      <!-- --thoughts
        I couldn't think between whether if I should've used python or javascript, but since python has more user support and guides, I followed through with python.
         --> This is obsolete it was faster using photon
         