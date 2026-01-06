#include "pitches.h"
int rounds[20];
int currentRound = 0;


int buzzerPIN = 6;

int ledPIN1 = 13;
int ledPIN2 = 8;
int ledPIN3 = 7;

int button1Pin = 4;
int button2Pin = 3;
int button3Pin = 2;

int button1State;
int button2State;
int button3State;


bool showLED = true;
int correctAnswer = 0;

unsigned long previousMillis = 0;                          // Tracks the last time an LED changed state
const int intervals[] = {100, 350, 100, 350, 100, 350};  // Durations for each step
int currentStep = 0;                                       // Tracks the current step in the sequence
bool ledState = LOW;                                       // Tracks whether the current LED is ON or OFF


int melody[] = {
  NOTE_E7, NOTE_E7, 0,NOTE_E7, 0, 
  NOTE_C7, NOTE_E7, 0, NOTE_G7, 0, 
  0,0, NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6, 0, 0, 
  NOTE_E6, 0, 0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 
  0, NOTE_F7, NOTE_G7, 0, 
  NOTE_E7, NOTE_C7, NOTE_D7, NOTE_B6, 0, 0,

};

int noteDurations = 12;

void setup() {
  randomSeed(analogRead(A0));

  pinMode(buzzerPIN, OUTPUT);

  pinMode(ledPIN1, OUTPUT);
  pinMode(ledPIN2, OUTPUT);
  pinMode(ledPIN3, OUTPUT);

  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);


  digitalWrite(ledPIN1, HIGH);
  delay(500);
  digitalWrite(ledPIN2, HIGH);
  delay(500);
  digitalWrite(ledPIN3, HIGH);
  delay(500);
  digitalWrite(ledPIN1, LOW);
  digitalWrite(ledPIN2, LOW);
  digitalWrite(ledPIN3, LOW);
  delay(500);
}


void loop() {

  unsigned long currentMillis = millis();  // Get the current time
  // Check if it's time to update the LEDs
  if (currentMillis - previousMillis >= intervals[currentStep]) {

    // Turn LEDs on or off based on the current step
    if (currentStep == 0) {
      digitalWrite(ledPIN1, HIGH);
    } else if (currentStep == 1) {
      digitalWrite(ledPIN1, LOW);
    } else if (currentStep == 2) {
      digitalWrite(ledPIN2, HIGH);
    } else if (currentStep == 3) {
      digitalWrite(ledPIN2, LOW);
    } else if (currentStep == 4) {
      digitalWrite(ledPIN3, HIGH);
    } else if (currentStep == 5) {
      digitalWrite(ledPIN3, LOW);
    }
    // Move to the next step
    currentStep++;
    if (currentStep >= 6) {
      currentStep = 0;  // Reset to the beginning of the sequence
    }
    previousMillis = currentMillis;  // Save the current time
  }

  button1State = digitalRead(button1Pin);

  if (button1State == LOW) {
    digitalWrite(ledPIN1, LOW);
    digitalWrite(ledPIN2, LOW);
    digitalWrite(ledPIN3, LOW);
    delay(750);
    while (true) {
      button1State = digitalRead(button1Pin);
      button2State = digitalRead(button2Pin);
      button3State = digitalRead(button3Pin);

      if (showLED == true) {
        if (currentRound < 20) {
          rounds[currentRound] = random(1, 4);
          currentRound++;
        }

        for (int i = 0; i < currentRound; i++) {
          if (rounds[i] == 1) {
            digitalWrite(ledPIN1, HIGH);
            delay(500);
            digitalWrite(ledPIN1, LOW);
          } else if (rounds[i] == 2) {
            digitalWrite(ledPIN2, HIGH);
            delay(500);
            digitalWrite(ledPIN2, LOW);
          } else if (rounds[i] == 3) {
            digitalWrite(ledPIN3, HIGH);
            delay(500);
            digitalWrite(ledPIN3, LOW);
          }
          delay(300);
        }
        showLED = false;
        correctAnswer = 0;
      }

      if (button1State == LOW) {
        if (rounds[correctAnswer] == 1) {
          digitalWrite(ledPIN1, HIGH);
          tone(buzzerPIN, 400, 50);
          delay(50);
          noTone(buzzerPIN);
          delay(400);
          digitalWrite(ledPIN1, LOW);
          correctAnswer++;
        } else {
          break;
        }
      }
      if (button2State == LOW) {
        if (rounds[correctAnswer] == 2) {
          digitalWrite(ledPIN2, HIGH);
          tone(buzzerPIN, 400, 50);
          delay(50);
          noTone(buzzerPIN);
          delay(400);
          digitalWrite(ledPIN2, LOW);
          correctAnswer++;
        } else {
          break;
        }
      }
      if (button3State == LOW) {
        if (rounds[correctAnswer] == 3) {
          digitalWrite(ledPIN3, HIGH);
          tone(buzzerPIN, 400, 50);
          delay(50);
          noTone(buzzerPIN);
          delay(400);
          digitalWrite(ledPIN3, LOW);
          correctAnswer++;
        } else {
          break;
        }
      }
      if (correctAnswer == currentRound) {
        delay(750);
        showLED = true;
      }
      if (currentRound >= 20) {
        break;
      }
    }
    music();
    delay(300);
  }
  showLED = true;
  currentRound = 0;
  correctAnswer = 0;
}


void music() {
  const int melodySize = sizeof(melody) / sizeof(melody[0]);  // Explicit size
  for (int thisNote = 0; thisNote < melodySize; thisNote++) {
    int noteDuration = 1000 / noteDurations;

    if (melody[thisNote] != 0) {  // If it's not a rest
      tone(buzzerPIN, melody[thisNote], noteDuration);
      // Turn on LEDs
      digitalWrite(ledPIN1, HIGH);
      digitalWrite(ledPIN2, HIGH);
      digitalWrite(ledPIN3, HIGH);
    } else {
      noTone(buzzerPIN);  // Stop any ongoing tone for a rest
      // Turn off LEDs
      digitalWrite(ledPIN1, LOW);
      digitalWrite(ledPIN2, LOW);
      digitalWrite(ledPIN3, LOW);
    }

    // Pause for note duration
    delay(noteDuration);

    // Ensure the tone and LEDs are turned off after each note
    noTone(buzzerPIN);
    digitalWrite(ledPIN1, LOW);
    digitalWrite(ledPIN2, LOW);
    digitalWrite(ledPIN3, LOW);

    // Pause between notes
    int pauseBetweenNotes = noteDuration * 0.30;
    delay(pauseBetweenNotes);
  }
}
