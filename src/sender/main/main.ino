#define SEG_A 9
#define SEG_B 8
#define SEG_C 2
#define SEG_D 4
#define SEG_E 3
#define SEG_F 6
#define SEG_G 5

#define YELLOW 11
#define RED 7
#define BLUE 12
#define BUTTON 10

unsigned long lastTime;
unsigned long lastButtonPress = 0;

bool isOn = false;
int senderState = 0;
void setup() {
  Serial.begin(9600);

  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  static bool lastButtonState = HIGH;
  static unsigned long lastDebounceTime = 0;
  static unsigned long lastTime = 0;
  const unsigned long debounceDelay = 75;
  const unsigned long buttonDelay = 200;
  int buttonState = digitalRead(BUTTON);

  if (buttonState != lastButtonState) {
    lastDebounceTime = millis();
  }


  if ((millis() - lastDebounceTime) > debounceDelay) 
  {
    if (buttonState == LOW && (millis() - lastButtonPress) > buttonDelay) 
    {
      isOn = !isOn;
      lastButtonPress = millis();
    }
  }
  lastButtonState = buttonState;

  if (isOn) 
  {
    unsigned long elapsedTime = millis() - lastTime;

    if (elapsedTime >= 0 && elapsedTime < 3000) 
    {
      updateSenderState(senderState, 1, 40);
      digitalWrite(RED, HIGH);
      digitalWrite(YELLOW, LOW);
      digitalWrite(BLUE, LOW);

      if (elapsedTime < 1000) 
      {
        three();
      } 
      else if (elapsedTime < 2000) 
      {
        two();  
      } 
      else 
      {
        one();  
      }
    } 
    else if (elapsedTime >= 3000 && elapsedTime < 5000) 
    {
      updateSenderState(senderState, 2, 65);
      digitalWrite(RED, LOW);
      digitalWrite(YELLOW, HIGH);
      digitalWrite(BLUE, LOW);

      if (elapsedTime < 4000) 
      {
        two();
      } 
      else 
      {
        one();
      }
    }
    else if (elapsedTime >= 5000 && elapsedTime < 9000) 
    {
      updateSenderState(senderState, 3, 20);

      digitalWrite(RED, LOW);
      digitalWrite(YELLOW, LOW);
      digitalWrite(BLUE, HIGH);

      if (elapsedTime < 6000)
      {
        three();
      }
      else if (elapsedTime < 7000)
      {
        two();
      }
      else {
        one();
      }
    }
    else if (elapsedTime >= 9000)
    {
      lastTime += 9000;  
    }
    else
    {
      lastTime = millis();
    }
  }
  else
  {
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(BLUE, LOW);

    digitalWrite(SEG_A, LOW);
    digitalWrite(SEG_B, LOW);
    digitalWrite(SEG_G, LOW);
    digitalWrite(SEG_E, LOW);
    digitalWrite(SEG_D, LOW);
    digitalWrite(SEG_F, LOW);
    digitalWrite(SEG_C, LOW);
  }
}

void updateSenderState(int &oldState, int newState, int transmitData) {
  if (oldState != newState) {
    oldState = newState;
    Serial.println(transmitData);
  }
}

void one() {
  digitalWrite(SEG_A, LOW);
  digitalWrite(SEG_B, HIGH);
  digitalWrite(SEG_G, LOW);
  digitalWrite(SEG_E, LOW);
  digitalWrite(SEG_D, LOW);
  digitalWrite(SEG_F, LOW);
  digitalWrite(SEG_C, HIGH);
}

void two() {
  digitalWrite(SEG_A, HIGH);
  digitalWrite(SEG_B, HIGH);
  digitalWrite(SEG_G, HIGH);
  digitalWrite(SEG_E, HIGH);
  digitalWrite(SEG_D, HIGH);
  digitalWrite(SEG_F, LOW);
  digitalWrite(SEG_C, LOW);
}

void three() {
  digitalWrite(SEG_A, HIGH);
  digitalWrite(SEG_B, HIGH);
  digitalWrite(SEG_G, HIGH);
  digitalWrite(SEG_E, LOW);
  digitalWrite(SEG_D, HIGH);
  digitalWrite(SEG_F, LOW);
  digitalWrite(SEG_C, HIGH);
}

void four() {
  digitalWrite(SEG_A, LOW);
  digitalWrite(SEG_B, HIGH);
  digitalWrite(SEG_G, HIGH);
  digitalWrite(SEG_E, LOW);
  digitalWrite(SEG_D, LOW);
  digitalWrite(SEG_F, HIGH);
  digitalWrite(SEG_C, HIGH);
}

void five() {
  digitalWrite(SEG_A, HIGH);
  digitalWrite(SEG_B, LOW);
  digitalWrite(SEG_G, HIGH);
  digitalWrite(SEG_E, LOW);
  digitalWrite(SEG_D, HIGH);
  digitalWrite(SEG_F, HIGH);
  digitalWrite(SEG_C, HIGH);
}
