This project is the foundation for a modern task alarm. 
The function of this device is to alert the user to know when their task is due or upcoming
  How it works
    -The Photon is constantly requesting a task from google's API (This is within time reason)
    -photon request -> middle man -> Server  
    -When time is around 1 hour, the middle man will activate asking the server for the time then information gets sent back to the photon. 

libraries--
  Photon - HttpClient
  https://docs.particle.io/reference/device-os/libraries/h/HttpClient/
    This is the request and servers to send resources via a client-server aka the protocal for communication. 

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
    Python
      Flask lib
        used for backend server communication, mainly used for automated sending 

  web stuff
    HTML
    CSS
    Javascript



  

    
    ----self notes---Ellis
    
    Add libraries
    // particle library add HttpClient
    // particle library add JsonParserGeneratorRK
      --thoughts
        I couldn't think between whether if I should've used python or javascript, but since python has more user support and guides, I followed through with python.
        
