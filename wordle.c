#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define SKY_BLUE "\033[38;5;153m"
#define END "\033[0m"

void wordle_game() {
    const char *words_list[] = {"lily", "valo", "best"};
    int word_count = sizeof(words_list) / sizeof(words_list[0]);
    
    srand(time(NULL));
    const char *word = words_list[rand() % word_count];
    int word_length = strlen(word);
    int attempts = 6;
    char user_input[10];
    
    for (int i = 0; i < attempts; i++) {
        printf(GREEN "(+) Enter your guess: " END);
        if (scanf("%9s", user_input) != 1) {
            printf(RED "(-) Error reading input." END "\n");
            while (getchar() != '\n');
            continue;
        }
        
        if (strlen(user_input) != word_length) {
            printf(BLUE "(!) The word must contains only %d letters. " END "\n", word_length);
            i--;
            continue;
        }
        
        if (strcmp(user_input, word) != 0) {
            printf(RED "(-) Nice try." END "\n");
            continue;
        } else {
            printf(SKY_BLUE "Game over! The correct word was: %s " END "\n", word);
            return;
        }
    }
    
    printf(RED "Game over! You didn't guess the word. The correct word was: %s" END "\n", word);
}

int main() {
    wordle_game();
    return 0;
}
