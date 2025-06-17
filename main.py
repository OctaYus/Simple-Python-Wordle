import random


class Colors:
    """Class to define ANSI color codes for terminal output"""

    def __init__(self):
        """Initialize color codes"""
        self.GREEN = "\033[32m"
        self.RED = "\033[31m"
        self.BLUE = "\033[34m"
        self.SKY_BLUE = "\033[38;5;153m"
        self.END = "\033[0m"


color = Colors()


class Wordle:
    def __init__(self):
        self.words_list = ["lily", "valo", "best"]
        self.word = random.choice(self.words_list)
        self.attempts = 6

    def game(self):
        try:
            word = self.word
            attempts = self.attempts

            for _ in range(attempts):
                user_input = input(f"{color.GREEN}(+) Enter your guess: {color.END}")
                if len(user_input) != len(word):
                    print(f"{color.BLUE}(!) The word must contains only {len(word)} letters. {color.END}")
                if not user_input == word:
                    print(f"{color.RED}(-) Nice try.{color.END}")
                    continue

                else:
                    print(
                        f"{color.SKY_BLUE}Game over! The correct word was: {word} {color.END}"
                    )
                    return

        except Exception as e:
            print(f"{color.RED}(-) Error occurred: {e} {color.RED}")


def main():
    wordle = Wordle()
    wordle.game()


if __name__ == "__main__":
    main()

