#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define SKY_BLUE "\033[38;5;153m"
#define YELLOW "\033[33m"
#define END "\033[0m"

const char* words_list[] = {"lily", "valo", "best"};
const int words_count = 3;

void check_guess(const char* word, const char* guess, char* result) {
    int word_len = strlen(word);
    char* word_copy = strdup(word);
    char* guess_copy = strdup(guess);
    
    for (int i = 0; i < word_len; i++) {
        if (guess_copy[i] == word_copy[i]) {
            sprintf(result + strlen(result), "%s%c%s ", GREEN, guess_copy[i], END);
            word_copy[i] = '\0';
        } else {
            sprintf(result + strlen(result), "%c ", guess_copy[i]);
        }
    }
    
    for (int i = 0; i < word_len; i++) {
        if (strstr(result, GREEN) && result[strstr(result, GREEN) - result + 5] == guess_copy[i]) {
            continue;
        }
        
        for (int j = 0; j < word_len; j++) {
            if (word_copy[j] == guess_copy[i]) {
                char temp[20];
                sprintf(temp, "%s%c%s ", YELLOW, guess_copy[i], END);
                memmove(result + i * 8, temp, strlen(temp));
                word_copy[j] = '\0';
                break;
            }
        }
    }
    
    free(word_copy);
    free(guess_copy);
}

void game() {
    srand(time(NULL));
    const char* word = words_list[rand() % words_count];
    int attempts = 6;
    int word_len = strlen(word);
    
    printf("%s(!) Try to guess the %d-letter word. You have %d attempts.%s\n", BLUE, word_len, attempts, END);
    
    for (int attempt = 0; attempt < attempts; attempt++) {
        char guess[20];
        printf("%s(+) Enter your guess (attempt %d/%d): %s", GREEN, attempt + 1, attempts, END);
        fgets(guess, sizeof(guess), stdin);
        guess[strcspn(guess, "\n")] = '\0';
        
        for (int i = 0; guess[i]; i++) {
            guess[i] = tolower(guess[i]);
        }
        
        if (strlen(guess) != word_len) {
            printf("%s(!) The word must contain exactly %d letters.%s\n", BLUE, word_len, END);
            attempt--;
            continue;
        }
        
        if (strcmp(guess, word) == 0) {
            printf("%sCongratulations! You guessed the word: %s %s\n", SKY_BLUE, word, END);
            return;
        }
        
        char result[100] = "";
        check_guess(word, guess, result);
        printf("Feedback: %s\n", result);
        printf("%s(-) Try again.%s\n", RED, END);
    }
    
    printf("%sGame over! The correct word was: %s %s\n", SKY_BLUE, word, END);
}

int main() {
    game();
    return 0;
}
