    const int VAL_PROBE = 1; // Analog pin 2
    const int MOISTURE_LEVEL = 250; // the value after the LED goes ON
     
    const int sensorPin = A0;    // pin that the sensor is attached to
    const int ledPin = 8;        // pin that the LED is attached to

// variables:
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value

    void setup() {
        Serial.begin(9600);
        
        
        pinMode(13, OUTPUT);
        digitalWrite(13, HIGH);

  // calibrate during the first five seconds
        while (millis() < 5000) {
        sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
        }
  // signal the end of the calibration period
  digitalWrite(13, LOW);
        
        
    }
     
  
    void loop() {
        int moisture = analogRead(VAL_PROBE);
     
        Serial.println(moisture);
     
        if(moisture > MOISTURE_LEVEL) {
          digitalWrite(11,LOW);
          digitalWrite(10,HIGH);
        } 
        
        else   {
            digitalWrite(10,LOW);
            digitalWrite(11,HIGH);
        }
        // read the sensor:
  sensorValue = analogRead(sensorPin);

  // apply the calibration to the sensor reading
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);

  // in case the sensor value is outside the range seen during calibration
  sensorValue = constrain(sensorValue, 0, 255);

  // fade the LED using the calibrated value:
  analogWrite(ledPin, sensorValue);
        
        
        
        
        delay(100);
    }
