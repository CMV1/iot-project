#include "Particle.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306_RK.h" 

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(OLED_RESET);

int speakerPin = A5; 
int buttonPin = D2; 
bool soundPlaying = false; 

// --- NEW CLOUD VARIABLES ---
String cloudStatus = "Idle";
String lastEventDate = "None";
String eventnamed = "None";
int cloudSoundState = 0; 

void calendarHandler(const char *event, const char *data);

void setup() {
    Serial.begin(9600);
    delay(1000);

    // Register Cloud Variables
    Particle.variable("status", cloudStatus);
    Particle.variable("lastEvent", lastEventDate);
    Particle.variable("isSounding", cloudSoundState);
    Particle.variable("eventname", eventnamed);

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.display();

    pinMode(speakerPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLDOWN); 
    
    Particle.subscribe("hook-response/check_calendar", calendarHandler);
    Time.zone(-5);
}

void updateDisplay() {
    display.clearDisplay();
    display.setTextColor(WHITE);
    
    display.setTextSize(1);
    display.setCursor(10, 10);
    display.print(Time.format(Time.now(), "%I:%M:%S %p")); 

    display.setTextSize(1);
    display.setCursor(0, 45);
    if(soundPlaying) {
        display.print("ALARM ACTIVE!");
        cloudStatus = "ALARM ACTIVE"; // Update cloud string
        cloudSoundState = 1;          // Update cloud int
    } else {
        display.print("Status: Idle"); 
        cloudStatus = "Idle";         // Update cloud string
        cloudSoundState = 0;          // Update cloud int
    }

    display.display();
}

void loop() {
    static unsigned long lastUpdate = 0;
    if (millis() - lastUpdate > 500) {
        lastUpdate = millis();
        updateDisplay();
    }

    bool currentButtonState = digitalRead(buttonPin);
    if (currentButtonState == HIGH && soundPlaying) {
        noTone(speakerPin);
        soundPlaying = false;
        Serial.println("Sound stopped");
    }
    
    static unsigned long lastRequest = 0;
    if (millis() - lastRequest > 30000) {
        lastRequest = millis();
        Particle.publish("check_calendar", PRIVATE);
    }
}

void calendarHandler(const char *event, const char *data) {
    if (!data || strlen(data) == 0) {
        return;
    }

    String response = String(data);

    int nameIndex = -1;
    int itemsIndex = response.indexOf("\"items\"");
    if (itemsIndex != -1) {
        nameIndex = response.indexOf("\"summary\"", itemsIndex);
    }
    if (nameIndex == -1) {
        nameIndex = response.indexOf("\"summary\"");
    }
    if (nameIndex != -1) {
        int colonPos = response.indexOf(":", nameIndex);
        if (colonPos != -1) {
            int quoteStart = response.indexOf("\"", colonPos);
            if (quoteStart != -1) {
                int quoteEnd = response.indexOf("\"", quoteStart + 1);
                if (quoteEnd != -1) {
                    eventnamed = response.substring(quoteStart + 1, quoteEnd);
                }
            }
        }
    }

    int dateIndex = response.indexOf("\"start\":\"");
    if (dateIndex != -1) {
        int startPos = dateIndex + 9;
        int endPos = response.indexOf("\"", startPos);
        if (endPos != -1) {
            lastEventDate = response.substring(startPos, endPos); // Store for Cloud
            if (!soundPlaying) {
                tone(speakerPin, 700);
                soundPlaying = true;
            }
        }
    } else {
        int oldDateIndex = response.indexOf("\"Date\": \"");
        if (oldDateIndex != -1) {
            int startPos = oldDateIndex + 9;
            int endPos = response.indexOf("\"", startPos);
            if (endPos != -1) {
                lastEventDate = response.substring(startPos, endPos); // Store for Cloud
                if (!soundPlaying) {
                    tone(speakerPin, 700);
                    soundPlaying = true;
                }
            }
        }
    }
}