# Arduino Memory Game (Simon-Style)

## Overview
This project is a soldered Arduino Uno–based memory game inspired by classic Simon-style games.  
It uses **3 LEDs**, **3 push buttons**, and a **buzzer** to generate a random sequence that the player must repeat correctly. Each round adds a new step to the sequence, increasing difficulty over time.

When the player makes a mistake or completes all rounds, the game ends with a melody played through the buzzer.

---

## How the Game Works
1. The game starts when **Button 1** is pressed.
2. The Arduino generates a random LED sequence.
3. LEDs flash one by one to show the sequence.
4. The player must press the corresponding buttons in the correct order.
5. If the sequence is correct:
   - A new round starts
   - One more step is added to the sequence
6. If the player presses the wrong button:
   - The game ends
   - A melody is played
7. The maximum sequence length is **20 steps**.

![Game demo](game_demo.png)
[Project demo video (on youtube)](https://www.youtube.com/watch?v=UaOxY1Et8yw)

---

## Hardware Components
- Arduino Uno
- 3 LEDs
- 3 push buttons
- Piezo buzzer
- Current-limiting resistors for LEDs
- Pull-up resistors (internal, using INPUT_PULLUP)
- Soldered connections (no breadboard required)

---

## Pin Configuration

### LEDs
- LED 1 → Pin 13  
- LED 2 → Pin 8  
- LED 3 → Pin 7  

### Buttons (using internal pull-up resistors)
- Button 1 → Pin 4  
- Button 2 → Pin 3  
- Button 3 → Pin 2  

### Buzzer
- Buzzer → Pin 6  

---

## Software Behavior

### Startup
- LEDs turn on sequentially as a startup animation.

### Idle Mode
- LEDs cycle continuously while waiting for the game to start.

### Game Logic
- Random numbers (1–3) are generated and stored in an array.
- Each number corresponds to an LED and button.
- The sequence is displayed using timed LED flashes.
- Player input is checked step-by-step.
- Correct inputs trigger a short beep and LED feedback.
- Incorrect input immediately ends the game.

### End of Game
- A melody is played using the buzzer.
- All LEDs flash in sync with the music.
- Game state resets, ready for a new round.

---

## Melody
The buzzer plays a predefined melody at the end of the game using tone frequencies defined in `pitches.h`.  
LEDs turn on and off along with the music for visual feedback.

---

## Key Features
- Non-blocking LED animation using `millis()`
- Randomized gameplay
- Increasing difficulty
- Audio and visual feedback
- Fully soldered, standalone build

---

## Limitations and Improvements
Possible future enhancements:
- Score display (7-segment or LCD)
- Adjustable difficulty
- Sound feedback for incorrect input
- EEPROM-based high score storage
- More LEDs and buttons for increased complexity

---

## Notes
- Buttons use `INPUT_PULLUP`, so logic is **active LOW**
- Maximum sequence length is 20 steps
- Requires `pitches.h` for buzzer tones

---

## License
This project was built for learning and demonstration purposes.  
Feel free to modify and reuse for personal or educational projects.
