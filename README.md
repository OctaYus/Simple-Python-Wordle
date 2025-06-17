# Simple Python Wordle

A minimal command-line Wordle-style game written in Python.

## How It Works

- The game randomly selects a word from a small built-in list.
- You have 6 attempts to guess the correct word.
- If your guess is incorrect, you're prompted to try again.
- The game ends when you guess the correct word or run out of attempts.


## Example

```
(+) Enter your guess: test
(-) Nice try.
(+) Enter your guess: lily
Game over! The correct word was: lily
````

## Getting Started

1. Clone the repository:

```bash
git clone https://github.com/OctaYus/Simple-Python-Wordle.git
cd Simple-Python-Wordle
````

2. Run the game:

```bash
python3 main.py
```

Requires Python 3.6 or higher.

## Customization

* You can edit the `self.words_list` in the `Wordle` class to add or replace words.
* The game checks for full word matches only (no letter-by-letter hints yet).

## To-Do

* Add feedback for correct letters in correct/wrong positions.
* Load word list from an external file.
* Expand to support standard 5-letter Wordle words.

## License

This project is licensed under the MIT License.

