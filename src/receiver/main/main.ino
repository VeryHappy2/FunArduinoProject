#include <Servo.h>

#define SERVO 7
#define BUZZER 4

Servo servo;

void setup()
{
  Serial.begin(9600);
  servo.attach(SERVO);
  pinMode(BUZZER, OUTPUT);
}

void loop()
{
  int receivedData = -1;

  if (Serial.available() > 0) {
    receivedData = Serial.parseInt();
    Serial.print("Received: ");
    Serial.println(receivedData);
    if (receivedData >= 1 && receivedData <= 180)
    {
      servo.write(receivedData);
      tone(BUZZER, 400, 10); 
      delay(200);
      tone(BUZZER, 600, 10);
      delay(200);
      tone(BUZZER, 1000, 10); 
      delay(200);
      tone(BUZZER, 1200, 10); 

      delay(200);
      tone(BUZZER, 1500, 10); 
      delay(200);
      tone(BUZZER, 600, 10);  
    }
  }
}