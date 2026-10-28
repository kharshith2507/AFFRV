#include "BluetoothSerial.h"
#include "DHT.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` or select proper board
settings.
#endif

BluetoothSerial SerialBT;

const int buz = 26;   // Buzzer pin
const int m1 = 19;    // Motor driver pin 1
const int m2 = 21;    // Motor driver pin 2
const int m3 = 22;    // Motor driver pin 3
const int m4 = 23;    // Motor driver pin 4
const int wp = 25;    // Water pump pin (PWM capable)

// Sensor Pins
const int fire = 15;      // Digital/Analog input-only pin
const int fire1 = 4;      // Digital/Analog input-only pin
const int fire2 = 17;     // Digital pin
const int DHTPIN = 16;    // Digital pin for DHT11
const int gasPin = 32;    // VP (Analog input pin for Gas Sensor)

// Define DHT type
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Thresholds
const int gasThreshold = 2000; // Adjust based on your gas sensor calibration (0-4095 range)

int md = 0; // Mode: 0 = Automatic, 1 = Manual
char incomingCommand = ' ';

void setup() {
  Serial.begin(115200);

  // Initialize Bluetooth device name
  SerialBT.begin("ESP32_Fire_Robot");
  Serial.println("Bluetooth device active. Pair with 'ESP32_Fire_Robot'.");

  // Initialize sensors
  dht.begin();

  pinMode(fire, INPUT);
  pinMode(fire1, INPUT);
  pinMode(fire2, INPUT);
  pinMode(gasPin, INPUT);

  pinMode(buz, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(wp, OUTPUT);

  digitalWrite(wp, LOW);
  digitalWrite(buz, LOW);
}

void loop() {
  // Read Flame Sensors (Active LOW)
  int fval = digitalRead(fire);
  int f1val = digitalRead(fire1);
  int f2val = digitalRead(fire2);

    // Read Gas Sensor (Analog)
    int gasValue = analogRead(gasPin);

    // Read DHT11 Temperature & Humidity
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature(); // Celsius

  // Print all sensor statuses to Serial Monitor & Bluetooth Terminal
    String sensorStatus = "F1: " + String(fval) + " | F2: " + String(f1val) + " | F3: " + String(f2val) +
                        " | Gas: " + String(gasValue) +
                        " | Temp: " + String(isnan(temperature) ? 0.0 : temperature) +
                        "C | Hum: " + String(isnan(humidity) ? 0.0 : humidity) + "%";
    Serial.println(sensorStatus);

    // Check Bluetooth commands for Mode Switching / Control
    if (SerialBT.available() > 0) {
      incomingCommand = SerialBT.read();

        if (incomingCommand == '1') {
          md = 0;
          SerialBT.println("Mode: Automatic");
        }
        else if (incomingCommand == '2') {
          md = 1;
          SerialBT.println("Mode: Manual");
          stopMotors();
        }
    }

    // ==================== AUTOMATIC MODE ====================
    if (md == 0) {

        if (fval == 0 ) {
          digitalWrite(buz, HIGH);
          digitalWrite(m1, HIGH); digitalWrite(m2, LOW);
          digitalWrite(m3, HIGH); digitalWrite(m4, LOW);
          delay(2000);
          stopMotors();
          digitalWrite(wp, 1);
          delay(2000);
          digitalWrite(wp, LOW);
          digitalWrite(buz, LOW);
        }
        else if (f1val == 0) {
          digitalWrite(buz, HIGH);
          digitalWrite(m1, LOW); digitalWrite(m2, HIGH);
          digitalWrite(m3, HIGH); digitalWrite(m4, LOW);
          delay(2000);
          stopMotors();
          digitalWrite(wp, 1);
          delay(2000);
          digitalWrite(wp, LOW);
          digitalWrite(buz, LOW);
        }
        else if (f2val == 0) {
          digitalWrite(buz, HIGH);
          digitalWrite(m1, 1); digitalWrite(m2, 0);
          digitalWrite(m3, LOW); digitalWrite(m4, HIGH);
          delay(2000);
          stopMotors();
          digitalWrite(wp, 1);
          delay(2000);
          digitalWrite(wp, LOW);
          digitalWrite(buz, LOW);
        }
        else {
          digitalWrite(buz, LOW);
          digitalWrite(wp, LOW);
          stopMotors();
        }
    }

    // ==================== MANUAL MODE ====================
    if (md == 1) {
      if (incomingCommand == '3') {
        digitalWrite(m1, HIGH); digitalWrite(m2, LOW);
        digitalWrite(m3, HIGH); digitalWrite(m4, LOW);
      }
      else if (incomingCommand == '4') {
        digitalWrite(m1, LOW); digitalWrite(m2, HIGH);
        digitalWrite(m3, LOW); digitalWrite(m4, HIGH);
      }
      else if (incomingCommand == '5') {
        digitalWrite(m1, LOW); digitalWrite(m2, HIGH);
        digitalWrite(m3, HIGH); digitalWrite(m4, LOW);
      }
      else if (incomingCommand == '6') {
        digitalWrite(m1, HIGH); digitalWrite(m2, LOW);
        digitalWrite(m3, LOW); digitalWrite(m4, HIGH);
      }
      else if (incomingCommand == '7') {
        stopMotors();
      }
      else if (incomingCommand == '8') {
        digitalWrite(wp, 1);
      }
      else if (incomingCommand == '9') {
        digitalWrite(wp, LOW);
      }
    }

    delay(100);
}

void stopMotors() {
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
}
