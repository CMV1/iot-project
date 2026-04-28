#include "Particle.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306_RK.h" // Use the RK version for Photon 2 stability

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

// FIXED CONSTRUCTOR: This tells the Photon to use I2C (Wire)
Adafruit_SSD1306 display(OLED_RESET);

int speakerPin = A5; 
int buttonPin = D2; 
bool soundPlaying = false; 



void calendarHandler(const char *event, const char *data);


void setup() {
    Serial.begin(9600);
    
    // Give the hardware a second to settle
    delay(1000);

    // Initialize display with I2C address 0x3C
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

    display.clearDisplay();
    display.setTextColor(WHITE);
    display.display();

    pinMode(speakerPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLDOWN); // Pull-down so button reads LOW when pressed
    
    Particle.subscribe("hook-response/check_calendar", calendarHandler);
    Time.zone(-5);
}

void updateDisplay() {
    display.clearDisplay();
    display.setTextColor(WHITE);
    
    // Display Time
    display.setTextSize(1);
    display.setCursor(10, 10);
    display.print(Time.format(Time.now(), "%I:%M:%S %p")); 

    // Display Status
    display.setTextSize(1);
    display.setCursor(0, 45);
    if(soundPlaying) {
        display.print("ALARM ACTIVE!");
    } else {
        display.print("Status: Idle"); 
    }

    display.display();
}

void loop() {
    // Limit display updates so we don't overwhelm the processor
    static unsigned long lastUpdate = 0;
    if (millis() - lastUpdate > 500) {
        lastUpdate = millis();
        updateDisplay();
    }

    // Debounce button: check if LOW (pressed) for debounce time
    static unsigned long lastButtonPress = 0;
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
        Serial.println("Handler triggered, but data is empty.");
        return;
    }

    String response = String(data);
    
    // Debug: see exactly what Google sent back
    Serial.println("Raw Data received: " + response);

    // Look for the "Date" key
    int dateIndex = response.indexOf("\"Date\": \"");
    
    if (dateIndex != -1) {
        int startPos = dateIndex + 8;
        int endPos = response.indexOf("\"", startPos);
        
        if (endPos != -1) {
            String eventDate = response.substring(startPos, endPos);
            Serial.print("Success!");
            Serial.println(eventDate);
            // Start playing sound continuously until button is pressed
            if (!soundPlaying) {
                tone(speakerPin, 700); // Play continuous tone at 700 Hz
                soundPlaying = true;
                Serial.println("Sound started - press button to stop");
            
            }
        }
    } else {
        Serial.println("Waiting for an upcoming event to be added to the calendar...");
    }
}