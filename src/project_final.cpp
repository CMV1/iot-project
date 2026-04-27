#include "Particle.h"
#include "HttpClient.h"  // Add via Particle Library Manager

HttpClient http;
http_header_t headers[] = {
    { "Content-Type", "application/json" },
    { "Authorization", "Bearer YOUR_ACCESS_TOKEN" }, // handled by middleware
    { NULL, NULL }
};

http_request_t request;
http_response_t response;

void setup() {
    Serial.begin(9600);
    waitFor(Serial.isConnected, 10000);
}

void loop() {
    checkTask();
    delay(60000); // Check every 60 seconds
}

void checkTask() {
    // If using middleware:
    request.hostname = "your-middleware.example.com";
    request.port = 443;
    request.path = "/check-task?taskId=YOUR_TASK_ID";

    http.get(request, response, headers);

    Serial.printlnf("Status: %d", response.status);
    Serial.printlnf("Body: %s", response.body.c_str());

    // Parse the response
    if (response.status == 200) {
        if (response.body.indexOf("\"status\":\"completed\"") >= 0) {
            Serial.println("Task is DONE!");
            // trigger LED, buzzer, etc.
        } else {
            Serial.println("Task still pending.");
        }
    }
}

