




int CURRENT_POS;


int pins[] = {0, 15, 2, 4, 5, 18, 19, 21, 22};
int clockSpeed = 34;
int reversePin = 26;
int forwardPin = 33;
int randomPin = 25;
int pulsePin = 32;
int sequenceMode = 1;
// pulseDirection = forward 1, backward 0
int pulseDirection = 1;


void setup() {

  Serial.begin(115200);
  pinMode(reversePin, INPUT_PULLUP);
  pinMode(forwardPin, INPUT_PULLUP);
  pinMode(pulsePin, INPUT_PULLUP);
  pinMode(randomPin, INPUT_PULLUP);


  for (int i = 0; i < (sizeof(pins) / sizeof(pins[0])); i++)
  {

    pinMode(pins[i], OUTPUT);
  };


  attachInterrupt(reversePin, reverse, FALLING);
  attachInterrupt(forwardPin, forward, FALLING);
  attachInterrupt(pulsePin, pulse, FALLING);
  attachInterrupt(randomPin, rndom, FALLING);


  if (sequenceMode == 0) {
    CURRENT_POS = 8;
  }
  else CURRENT_POS = 1;

}
void forward() {

  sequenceMode = 1;
}
void reverse() {

  sequenceMode = 0;
}
void pulse() {
  sequenceMode = 2;
}
void rndom() {
  sequenceMode = 3;
}


void loop() {
  if (sequenceMode == 0) {
    revSequence();
  }
  if (sequenceMode == 1) {
    fwdSequence();
  }
  if (sequenceMode == 2) {
    pulseSequence();
  }

  if (sequenceMode == 3) {
    randSequence();
  }



}

void fwdSequence() {
  if (CURRENT_POS > 9  ) {
    CURRENT_POS = 0;
  };

  outputPin();
  delay(analogRead(clockSpeed));
  digitalWrite(pins[CURRENT_POS], LOW);
  CURRENT_POS = CURRENT_POS + 1;







  if (CURRENT_POS == 9  ) {
    CURRENT_POS = 0;
  };



}
void revSequence() {
  if (CURRENT_POS < 1  ) {
    CURRENT_POS = 9;
  };
  CURRENT_POS = CURRENT_POS - 1;


  outputPin();
  delay(analogRead(clockSpeed));
  digitalWrite(pins[CURRENT_POS], LOW);
  if (CURRENT_POS == 1 ) {
    CURRENT_POS = 9 ;

  };
}


void pulseSequence() {
  if (CURRENT_POS < 1  ) {
    CURRENT_POS = 9;
  };
  if (CURRENT_POS > 9  ) {
    CURRENT_POS = 0;
  };

  if (pulseDirection == 0) {
    CURRENT_POS = CURRENT_POS - 1;
  }



  outputPin();
  delay(analogRead(clockSpeed));
  digitalWrite(pins[CURRENT_POS], LOW);
  if (pulseDirection == 1) {
    CURRENT_POS = CURRENT_POS + 1;
  }


  if (CURRENT_POS == 1 ) {
    pulseDirection = 1;

  };
  if (CURRENT_POS == 9 ) {
    pulseDirection = 0;

  };

}


void randSequence() {
  CURRENT_POS = random(1, sizeof(pins) / sizeof(pins[0]) );
  outputPin();
  delay(analogRead(clockSpeed));
  digitalWrite(pins[CURRENT_POS], LOW);
}




void outputPin() {

  digitalWrite(pins[CURRENT_POS], HIGH);
}
