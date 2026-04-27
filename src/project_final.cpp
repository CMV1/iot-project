#include "Particle.h"
#include "HttpClient.h"
#include "JsonParserGeneratorRK.h"
JsonParser parser;

HttpClient http;
http_header_t headers[] = {
    { "Content-Type", "application/json" },
    { "Authorization", "Bearer YOUR_ACCESS_TOKEN" },
    { NULL, NULL }
};

http_request_t request;
http_response_t response;

void checkCalendar() {
    request.hostname = "www.googleapis.com";
    request.port = 443;
    request.path = "/calendar/v3/calendars/c_3fe405c6ca6b844a9a8fd605ae2327d226d49c93757f85bd1ecd42fc9c322d54@group.calendar.google.com/events"
                   "?timeMin=2026-04-26T00:00:00Z"
                   "&timeMax=2026-04-26T23:59:59Z"
                   "&singleEvents=true"
                   "&key=AIzaSyAk8ncBzJtL6fx-SmAn8ZRB_ZlfuzjRQyo";

    http.get(request, response, headers);

    Serial.printlnf("Status: %d", response.status);
    Serial.println(response.body);

    parser.addString(response.body);

if (parser.parse()) {
    const JsonParserGeneratorRK::jsmntok_t *itemsArray;
    if (parser.getValueTokenByKey(parser.getOuterObject(), "items", itemsArray)) {

        const JsonParserGeneratorRK::jsmntok_t *firstItem;
        if (parser.getValueTokenByIndex(itemsArray, 0, firstItem)) {

            String summary;
            if (parser.getValueByKey(firstItem, "summary", summary)) {
                Serial.printlnf("Event: %s", summary.c_str());
            } else {
                Serial.println("No summary found.");
            }
        } else {
            Serial.println("No events today.");
        }
    } else {
        Serial.println("No items array in response.");
    }
} else {
    Serial.println("Failed to parse JSON response.");
}
}

void setup() {
    Serial.begin(9600);
    waitFor(Serial.isConnected, 5000);
}

void loop() {
    checkCalendar();
    delay(60000);
}