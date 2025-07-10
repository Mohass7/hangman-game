# HangC++ — A Terminal Hangman Game in C++

I built this game because I used to enjoy playing Hangman myself. I wanted to create my own version using C++ as a way to apply what I’ve learned and improve my programming skills through a fun project. 

HangC++ is a terminal-based word guessing game inspired by Hangman. The player tries to guess a hidden word by entering one letter at a time. The game features a clean interface, random word categories, and input validation — all built using modern C++.

## Game Rules

- The computer selects a **random word** from one of three categories: animals, countries, or food.
- The word is represented by underscores (`_`), one for each letter.
- The player guesses one lowercase letter at a time.
- If the letter exists in the word, it's revealed in all correct positions.
- If the guess is incorrect, the player loses a life (represented as `+` symbols).
- The game ends when:
  - The word is fully guessed (win)
  - The player runs out of lives (lose)

## Features

- Input validation (only lowercase a-z letters accepted)
- Repeated guesses are caught and ignored
- Random word selection from themed word banks
- Configurable number of attempts (default is 6)
- Encapsulated game logic using a C++ class

## Tech Stack

- Language: **C++17**
- Standard Library: `iostream`, `vector`, `string_view`, `limits`
- Custom `Random.h` utility for random number generation
