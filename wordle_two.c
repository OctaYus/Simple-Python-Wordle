#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

// Color definitions
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"
#define COLOR_BLUE "\033[34m"
#define COLOR_SKY_BLUE "\033[38;5;153m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BOLD "\033[1m"
#define COLOR_UNDERLINE "\033[4m"
#define COLOR_GRAY "\033[90m"
#define COLOR_END "\033[0m"

// Game configuration
#define MAX_WORD_LENGTH 20
#define MAX_ATTEMPTS 6
#define DEFAULT_WORD_COUNT 3

// Function prototypes
void print_banner();
void print_colored(const char* color, const char* text);
char* to_lowercase(char* str);
bool is_word_in_list(const char* word, char** word_list, int word_count);
void play_game(char* target_word, int word_length);

// Default words
const char* default_words[] = {"lily", "valo", "best"};

int main(int argc, char* argv[]) {
    // Initialize random number generator
    srand(time(NULL));

    print_banner();

    char** word_list = NULL;
    int word_count = 0;

    // Use default words if no wordlist provided
    if (argc < 2) {
        print_colored(COLOR_RED, "(i) No wordlist provided. Using default wordlist.\n");
        word_count = DEFAULT_WORD_COUNT;
        word_list = malloc(word_count * sizeof(char*));
        for (int i = 0; i < word_count; i++) {
            word_list[i] = strdup(default_words[i]);
        }
    } else {
        // Try to read words from file
        FILE* file = fopen(argv[1], "r");
        if (file == NULL) {
            print_colored(COLOR_YELLOW, "(i) Wordlist file not found. Creating with default words.\n");
            
            // Create the file with default words
            file = fopen(argv[1], "w");
            if (file == NULL) {
                print_colored(COLOR_RED, "(!) Failed to create wordlist file.\n");
                return 1;
            }
            
            for (int i = 0; i < DEFAULT_WORD_COUNT; i++) {
                fprintf(file, "%s\n", default_words[i]);
            }
            fclose(file);
            
            // Now read it back
            file = fopen(argv[1], "r");
            if (file == NULL) {
                print_colored(COLOR_RED, "(!) Failed to open created wordlist file.\n");
                return 1;
            }
        }

        // Count lines in file
        char buffer[MAX_WORD_LENGTH];
        while (fgets(buffer, MAX_WORD_LENGTH, file) != NULL) {
            if (strlen(buffer) > 1) {  // Skip empty lines
                word_count++;
            }
        }
        
        // Allocate memory for word list
        word_list = malloc(word_count * sizeof(char*));
        rewind(file);
        
        // Read words into array
        int index = 0;
        while (fgets(buffer, MAX_WORD_LENGTH, file) != NULL && index < word_count) {
            buffer[strcspn(buffer, "\n")] = 0;  // Remove newline
            if (strlen(buffer) > 0) {
                word_list[index] = strdup(buffer);
                index++;
            }
        }
        fclose(file);

        if (word_count == 0) {
            print_colored(COLOR_RED, "(!) Wordlist is empty. Using default list.\n");
            word_count = DEFAULT_WORD_COUNT;
            word_list = realloc(word_list, word_count * sizeof(char*));
            for (int i = 0; i < word_count; i++) {
                word_list[i] = strdup(default_words[i]);
            }
        }
    }

    // Select random word
    int random_index = rand() % word_count;
    char* target_word = strdup(word_list[random_index]);
    int word_length = strlen(target_word);

    // Start the game
    play_game(target_word, word_length);

    // Clean up
    for (int i = 0; i < word_count; i++) {
        free(word_list[i]);
    }
    free(word_list);
    free(target_word);

    return 0;
}

void print_banner() {
    printf(
        COLOR_SKY_BLUE
        "\n"
        " _       __               ____ \n"
        "| |     / /___  _________/ / /__ \n"
        "| | /| / / __ \\/ ___/ __  / / _ \\\n"
        "| |/ |/ / /_/ / /  / /_/ / /  __/\n"
        "|__/|__/\\____/_/   \\__,_/_/\\___/ \n"
        "                                 \n"
        COLOR_END
    );
}

void print_colored(const char* color, const char* text) {
    printf("%s%s%s", color, text, COLOR_END);
}

char* to_lowercase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

bool is_word_in_list(const char* word, char** word_list, int word_count) {
    for (int i = 0; i < word_count; i++) {
        if (strcmp(word, word_list[i]) == 0) {
            return true;
        }
    }
    return false;
}

void play_game(char* target_word, int word_length) {
    int attempts = MAX_ATTEMPTS;
    char guess[MAX_WORD_LENGTH];
    bool guessed_correctly = false;

    printf(COLOR_BLUE "(!) Try to guess the %d-letter word. You have %d attempts.\n" COLOR_END, word_length, attempts);
    printf(COLOR_BLUE "Legend: " COLOR_GREEN "Correct position" COLOR_END " | " 
           COLOR_YELLOW "Wrong position" COLOR_END " | " COLOR_GRAY "Not in word" COLOR_END "\n\n");

    for (int attempt = 0; attempt < attempts; attempt++) {
        printf(COLOR_GREEN "(+) Enter your guess (attempt %d/%d): " COLOR_END, attempt + 1, attempts);
        fgets(guess, MAX_WORD_LENGTH, stdin);
        guess[strcspn(guess, "\n")] = 0;  // Remove newline
        
        // Convert to lowercase
        to_lowercase(guess);

        if (strlen(guess) != word_length) {
            printf(COLOR_BLUE "(!) The word must contain exactly %d letters.\n" COLOR_END, word_length);
            attempt--;  // Don't count this invalid attempt
            continue;
        }

        if (strcmp(guess, target_word) == 0) {
            guessed_correctly = true;
            printf(
                COLOR_BOLD COLOR_SKY_BLUE "\nCongratulations! You guessed the word correctly: "
                COLOR_UNDERLINE COLOR_GREEN "%s" COLOR_END "\n\n",
                target_word
            );
            break;
        }

        // Prepare feedback
        char feedback[MAX_WORD_LENGTH * 10];  // Extra space for color codes
        feedback[0] = '\0';
        
        char word_copy[MAX_WORD_LENGTH];
        strcpy(word_copy, target_word);

        // First pass: mark correct positions (green)
        bool correct_positions[MAX_WORD_LENGTH] = {false};
        for (int i = 0; i < word_length; i++) {
            if (guess[i] == word_copy[i]) {
                correct_positions[i] = true;
                word_copy[i] = '*';  // Mark as used
            }
        }

        // Second pass: check remaining letters
        for (int i = 0; i < word_length; i++) {
            if (correct_positions[i]) {
                // Correct position - green
                strcat(feedback, COLOR_BOLD COLOR_GREEN);
                strncat(feedback, &guess[i], 1);
                strcat(feedback, COLOR_END " ");
            } else {
                // Check if letter exists elsewhere in word
                bool found = false;
                for (int j = 0; j < word_length; j++) {
                    if (word_copy[j] == guess[i]) {
                        found = true;
                        word_copy[j] = '*';  // Mark as used
                        break;
                    }
                }

                if (found) {
                    // Correct letter, wrong position - yellow
                    strcat(feedback, COLOR_YELLOW);
                    strncat(feedback, &guess[i], 1);
                    strcat(feedback, COLOR_END " ");
                } else {
                    // Letter not in word - gray
                    strcat(feedback, COLOR_GRAY);
                    strncat(feedback, &guess[i], 1);
                    strcat(feedback, COLOR_END " ");
                }
            }
        }

        printf("Feedback: %s\n", feedback);
        printf(COLOR_RED "(-) Try again.\n\n" COLOR_END);
    }

    if (!guessed_correctly) {
        printf(COLOR_SKY_BLUE "Game over! The correct word was: " COLOR_BOLD COLOR_GREEN "%s" COLOR_END "\n", target_word);
    }
}
