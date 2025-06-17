import random


class Colors:
    def __init__(self):
        self.GREEN = "\033[32m"
        self.RED = "\033[31m"
        self.BLUE = "\033[34m"
        self.SKY_BLUE = "\033[38;5;153m"
        self.YELLOW = "\033[33m"
        self.END = "\033[0m"


color = Colors()


class Wordle:
    def __init__(self):
        self.words_list = ["lily", "valo", "best"]
        self.word = random.choice(self.words_list)
        self.attempts = 6

    def check_guess(self, guess):
        result = []
        word_letters = list(self.word)
        guess_letters = list(guess)
        
        for i in range(len(guess_letters)):
            if guess_letters[i] == word_letters[i]:
                result.append(f"{color.GREEN}{guess_letters[i]}{color.END}")
                word_letters[i] = None
            else:
                result.append(guess_letters[i])
        
        for i in range(len(result)):
            if isinstance(result[i], str) and color.GREEN in result[i]:
                continue
            letter = guess_letters[i]
            if letter in word_letters:
                result[i] = f"{color.YELLOW}{letter}{color.END}"
                word_letters[word_letters.index(letter)] = None
            else:
                result[i] = letter
        
        return " ".join(result)

    def game(self):
        try:
            word = self.word
            attempts = self.attempts

            print(f"{color.BLUE}(!) Try to guess the {len(word)}-letter word. You have {attempts} attempts.{color.END}")
            
            for attempt in range(attempts):
                user_input = input(f"{color.GREEN}(+) Enter your guess (attempt {attempt + 1}/{attempts}): {color.END}").lower()
                
                if len(user_input) != len(word):
                    print(f"{color.BLUE}(!) The word must contain exactly {len(word)} letters.{color.END}")
                    continue
                
                if user_input == word:
                    print(f"{color.SKY_BLUE}Congratulations! You guessed the word: {word} {color.END}")
                    return
                
                feedback = self.check_guess(user_input)
                print(f"Feedback: {feedback}")
                print(f"{color.RED}(-) Try again.{color.END}")

            print(f"{color.SKY_BLUE}Game over! The correct word was: {word} {color.END}")

        except Exception as e:
            print(f"{color.RED}(-) Error occurred: {e} {color.END}")


def main():
    wordle = Wordle()
    wordle.game()


if __name__ == "__main__":
    main()
