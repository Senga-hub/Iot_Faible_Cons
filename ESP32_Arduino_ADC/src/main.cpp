// See https://docs.espressif.com/projects/arduino-esp32/en/latest/api/adc.html
// Example of using ADC on ESP32 with Arduino framework
#include <Arduino.h>
#include <driver/adc.h>
// 1.4.2.2 Input
int button_Count = 0;
int previous_State = HIGH;  // Assuming button is not pressed at start (pull-up resistor)
// const unsigned long debounce_Delay = 30; // Used for debounce
// unsigned long last_Change_Time = 0; // Used for debounce
// int stable_State = HIGH;  // Used for debounce
volatile bool button_Flag = false;

// 1.5.2.2
int value = 0;   // the sensor value
int valueMin = 4095;  // minimum sensor value
int valueMax = 0;     // maximum sensor value

void handleButtonInterrupt() {
    button_Flag = true;
}

void setup() {
    Serial.begin(115200);
    // Configure ADC on GPIO 36 (ADC1_CH0)
    analogSetPinAttenuation(36, (adc_attenuation_t)ADC_ATTEN_DB_12);  // Set attenuation to 12dB (max ~3.1V)
    analogSetWidth(12);                                               // Set ADC resolution to 12 bits (0-4095)
    pinMode(2, OUTPUT);  // Set GPIO 2 as output for LED
    /* 
    pinMode(2, OUTPUT_0); // Output UpDown to apply resistor
    */
   pinMode(34, INPUT);  // Set GPIO 34 as input
   attachInterrupt(digitalPinToInterrupt(34), handleButtonInterrupt, RISING);  

   /*
       // LED signal beginning of calibration
    digitalWrite(2, HIGH);
    while (millis() < 5000) {
        // Wait for 5 seconds before starting the ADC readings
        // Read raw ADC value (0-4095)
        int value = analogRead(36);

        if (value < valueMin) {
            valueMin = value;  // Update minimum value
        }

        if (value > valueMax) {
            valueMax = value;  // Update maximum value
        }
        
    }
    // LED signal end of calibration
    digitalWrite(2, LOW);
    */


}



void loop() {
    

    //1.3.2.2
    //Comment the println when terminal screenshot is not needed in order to keep temporal precision   
    //Serial.println("[Binome 01 - MANZANAS & AGNES] Hello Arduino World!");



   
    
    /*
    delay(2000);  // Wait 2 second
    */
    
    //1.4.2.1 Input
    /*
    digitalWrite(2, HIGH);
    delay(50);  // N * 50 ms = 1 * 50 ms
    digitalWrite(2, LOW);
    delay(1950);  
    */
    /*
    //1.4.2.2 Input
    // In this case on morse unit would be 50 ms as described by 50 * N ms = 50 * 1 ms = 50 ms
    //But this timing is to fast so we will mutliply it by 10 to be readable
    // SOS = ... --- ...
    int Morse_Unit = 500;
    // S = 3 dots = 3 * 50 ms = 150 ms 
    for (int i = 0; i < 3; i++) {
        digitalWrite(2, HIGH);
        delay(Morse_Unit);  // N * 50 ms = 1 * 50 ms
        digitalWrite(2, LOW);
        if (i < 2)  // Avoid delay after the last dot
            delay(Morse_Unit);
    }
    delay (3* Morse_Unit);  // Inter-letter space (3 units)
    // O = 3 dashes = 3 * 150 ms = 450 ms
    for (int i = 0; i < 3; i++) {
        digitalWrite(2, HIGH);
        delay(3 * Morse_Unit);  // N * 50 ms = 3 * 50 ms
        digitalWrite(2, LOW);
        if (i < 2)  // Avoid delay after the last dash
            delay(Morse_Unit);
    }
    delay (3 * Morse_Unit);  // Inter-letter space (3 units)
    // S = 3 dots = 3 * 50 ms = 150 ms
    for (int i = 0; i < 3; i++) {
        digitalWrite(2, HIGH);
        delay(Morse_Unit);  // N * 50 ms = 1 * 50 ms
        digitalWrite(2, LOW);
        if (i < 2)  // Avoid delay after the last dot
            delay(Morse_Unit);
    }
    delay (7 * Morse_Unit);  // Inter-Word space (7 units)
    */

    /*
    ////1.4.2.2.1 Output

    /* 
    AI use

    I had issue due to the mechanical effect of the button
    So i asked IA to help me debug, it suggested me to use a debounce technique 
    Using the card Timestamp
    */

    /*
    int current_state = digitalRead(34);

    if (current_state != previous_State) {
        last_Change_Time = millis();
    }

    if (millis() - last_Change_Time > debounce_Delay) {
        // Check for debounce
        if (current_state != stable_State) {
            // the initial code
            if (stable_State == LOW && current_state == HIGH) {
                button_Count++;
                Serial.println("[Binome 01 - MANZANAS & AGNES] Button Count: " + String(button_Count));
            }
            stable_State = current_state;
        }
    }

    previous_State = current_state;
    */

    /*

     ////1.4.2.2.2 Output
    if (button_Flag) {
    button_Count++;
    Serial.println("[Binome 01 - MANZANAS & AGNES] Button Count: " + String(button_Count));
    button_Flag = false; 
    }
    */

    /*
    //1.5.2
    int value = analogRead(36);
    value = constrain(value, valueMin, valueMax);  // Constrain the value to the calibrated range
    value = map(value, valueMin, valueMax, 0, 255);

    Serial.println("[Binome 01 - MANZANAS & AGNES] Hello Arduino World!");
    Serial.println(value);
    delay(1000);
    */

    //1.5.3

    int value = analogRead(36);
    Serial.println("Value: " + String(value));

    // Convert raw value to millivolts (150-3100mV with 11dB or 12dB attenuation with ESP32)
    float voltage = (float)value * (3100.0 - 150.0) / 4095.0 + 150.0;

    // Directly read voltage in millivolts
    float direct_voltage = analogReadMilliVolts(36);
    float temperature = (direct_voltage - 500.0) / 10.0;  // Convert voltage to temperature (example conversion)


    // Print calculated and direct millivolt values
    Serial.println("[Binome 01 - MANZANAS & AGNES] Hello Arduino World!");
    Serial.println("Température: " + String(temperature) + " degrés Celsius");
    delay(1000);  // Wait 1 second
} 
