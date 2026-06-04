#include <Arduino.h>

// GPIO 2 is the built-in LED on ESP32 DevKitC v4
const int LED_PIN = 2;
const int BLINK_INTERVAL = 1000;  // 1 second

bool ledState = false;
unsigned long lastBlinkTime = 0;

void setup() {
    // Initialize serial communication at 115200 bps
    Serial.begin(115200);
    
    // Wait a bit for serial to be ready
    delay(100);
    
    // Initialize LED pin
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    ledState = false;
    
    // Output initialization message
    Serial.println("ESP32 Initialized.");
}

void loop() {
    unsigned long currentTime = millis();
    
    // Check if it's time to toggle the LED
    if (currentTime - lastBlinkTime >= BLINK_INTERVAL) {
        lastBlinkTime = currentTime;
        
        // Toggle LED
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState ? HIGH : LOW);
        
        // Output LED state to serial monitor
        if (ledState) {
            Serial.println("LED ON");
        } else {
            Serial.println("LED OFF");
        }
    }
}
