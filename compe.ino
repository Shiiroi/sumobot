const int irSensorPin = A0; // Analog pin A0 for IR sensor
const int qtrPin = A2;     // Pin to which the analog sensor is connected
const int threshold = 512; // Threshold value for analog-to-digital conversion
const int prox = 40;       // Max distance seen

// Motors
#define leftSpeed 5
#define leftMotor1 6
#define leftMotor2 7
#define rightMotor1 8
#define rightMotor2 9
#define rightSpeed 10

bool first = true;
float distanceIR; // SharpIR Value
int qtr;          // qtr value

unsigned long previousMillis = 0;
const long interval = 500; // Interval for actions in milliseconds

void setup() {
    Serial.begin(9600); // Initialize serial communication with a baud rate of 9600
    pinMode(leftSpeed, OUTPUT);
    pinMode(leftMotor1, OUTPUT);
    pinMode(leftMotor2, OUTPUT);
    pinMode(rightMotor1, OUTPUT);
    pinMode(rightMotor2, OUTPUT);
    pinMode(rightSpeed, OUTPUT);
    delay(5000);
}

void loop() {
    unsigned long currentMillis = millis();

    distanceIR = sharpIR();
    qtr = qtrCheck();
    Serial.println("cm");
    Serial.println(distanceIR);

    if (qtr >= threshold) {
        while (qtr >= threshold) {
            tornado();
            distanceIR = sharpIR();
            qtr = qtrCheck();
            if (distanceIR <= prox) {
                Serial.println("detected");
                Stop();
                delay(150);
                break;
            }
            if (qtr < threshold) {
                Serial.println("on white");
                break;
            }
        }
    } else if (qtr <= threshold) {
        goBack();
        delay(250);
        if (currentMillis - previousMillis >= interval) {
            rotate();
            previousMillis = currentMillis;
        }
    }
    else{
      tornado();
    }

  if (distanceIR <= prox) {
        while (qtr >= threshold) {
            Serial.println("attack");
            attack();
            qtr = qtrCheck();
            distanceIR = sharpIR();
            if (qtr <= threshold) {
                Serial.println("on white");
                break;
            }
            if (distanceIR > prox) {
                Serial.println("scan");
                break;
            }
        }
    }
    else{
      tornado();
    }


    // Add more non-blocking logic here
}

// FUNCTIONS
void tornado() {
    analogWrite(leftSpeed, 70);
    analogWrite(rightSpeed, 70);
    digitalWrite(leftMotor1, 1);
    digitalWrite(leftMotor2, 0);
    digitalWrite(rightMotor1, 1);
    digitalWrite(rightMotor2, 0);
    Serial.println("scanning");
    if (qtr <= threshold || distanceIR <= prox) {
        return; 
    }
}

void attack() {
  while(distanceIR <= prox){
      if (distanceIR <= 15) {
        analogWrite(leftSpeed, 255);
    analogWrite(rightSpeed, 255);
    digitalWrite(leftMotor1, 0);
    digitalWrite(leftMotor2, 1);
    digitalWrite(rightMotor1, 1);
    digitalWrite(rightMotor2, 0);
    delay(100);
    distanceIR = sharpIR();
    qtr = qtrCheck();
  } else if (distanceIR <= 30) {
    analogWrite(leftSpeed, 130);
    analogWrite(rightSpeed, 130);
    digitalWrite(leftMotor1, 0);
    digitalWrite(leftMotor2, 1);
    digitalWrite(rightMotor1, 1);
    digitalWrite(rightMotor2, 0);
    delay(100);
    distanceIR = sharpIR();
    qtr = qtrCheck();
  } else if (distanceIR <= prox ) {
        analogWrite(leftSpeed, 90);
    analogWrite(rightSpeed, 90);
    digitalWrite(leftMotor1, 0);
    digitalWrite(leftMotor2, 1);
    digitalWrite(rightMotor1, 1);
    digitalWrite(rightMotor2, 0);
    delay(100);
    distanceIR = sharpIR();
    qtr = qtrCheck();
  } 

    distanceIR = sharpIR();
    qtr = qtrCheck();
    
    if (qtr <= threshold || distanceIR > prox) {
        return;
    }
  }
}

int sharpIR() {
    int irVal = analogRead(irSensorPin); // Read the analog sensor value
    float voltage = irVal * (5.0 / 1023.0); // Convert the analog value to voltage (5V is the reference voltage)
    // Calculate distance using a typical Sharp IR sensor equation
    // For GP2Y0A21YK0F, the typical equation is Distance (cm) = 10 / (Voltage * 0.0048828125)
    float distanceIR = 29.998 * pow(voltage, -1.173);
        Serial.println("cm");
    Serial.println(distanceIR);
    return distanceIR;
}
int qtrCheck() {
    int qtrVal = analogRead(qtrPin); // Read the analog sensor value (0-1023)
    Serial.println(qtrVal);
    return qtrVal;
}
void goBack() {
    analogWrite(leftSpeed, 200);
    analogWrite(rightSpeed, 200);
    digitalWrite(leftMotor1, 1);
    digitalWrite(leftMotor2, 0);
    digitalWrite(rightMotor1, 0);
    digitalWrite(rightMotor2, 1);
    Serial.println("back");
}
void rotate() {
    analogWrite(leftSpeed, 120);
    analogWrite(rightSpeed, 120);
    digitalWrite(leftMotor1, 1);
    digitalWrite(leftMotor2, 0);
    digitalWrite(rightMotor1, 1);
    digitalWrite(rightMotor2, 0);
    Serial.println("rotate");
}
void Stop() {
    analogWrite(leftSpeed, 0);
    analogWrite(rightSpeed, 0);
    digitalWrite(leftMotor1, 0);
    digitalWrite(leftMotor2, 0);
    digitalWrite(rightMotor1, 0);
    digitalWrite(rightMotor2, 0);
}

void last() {
  while(qtr <= threshold){
      if (distanceIR <= 15) {
        analogWrite(leftSpeed, 255);
    analogWrite(rightSpeed, 255);
    digitalWrite(leftMotor1, 0);
    digitalWrite(leftMotor2, 1);
    digitalWrite(rightMotor1, 1);
    digitalWrite(rightMotor2, 0);
    delay(100);
    distanceIR = sharpIR();
    qtr = qtrCheck();
  } else if (distanceIR <= 30) {
    analogWrite(leftSpeed, 180);
    analogWrite(rightSpeed, 180);
    digitalWrite(leftMotor1, 0);
    digitalWrite(leftMotor2, 1);
    digitalWrite(rightMotor1, 1);
    digitalWrite(rightMotor2, 0);
    delay(100);
    distanceIR = sharpIR();
    qtr = qtrCheck();
  } else if (distanceIR <= prox) {
        analogWrite(leftSpeed, 130);
    analogWrite(rightSpeed, 130);
    digitalWrite(leftMotor1, 0);
    digitalWrite(leftMotor2, 1);
    digitalWrite(rightMotor1, 1);
    digitalWrite(rightMotor2, 0);
    delay(100);
    distanceIR = sharpIR();
    qtr = qtrCheck();
  } 

    distanceIR = sharpIR();
    qtr = qtrCheck();
    
    if (qtr <= threshold) {
        return;
    }
  }
}
