#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_IDENTIFIER_LENGTH 100

// List of keywords (for simplicity, using a small subset)
const char *keywords[] = { "int", "float", "if", "else", "return", "while" };
const int keywordCount = sizeof(keywords) / sizeof(keywords[0]);

// List of operators
const char *operators[] = { "+", "-", "*", "/", "=", "==" };
const int operatorCount = sizeof(operators) / sizeof(operators[0]);

// Function to check if a word is a keyword
int isKeyword(char *word) {
    for (int i = 0; i < keywordCount; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a symbol is an operator
int isOperator(char *symbol) {
    for (int i = 0; i < operatorCount; i++) {
        if (strcmp(symbol, operators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Lexical analyzer function
void analyzeFile(FILE *file) {
    char ch;
    char buffer[MAX_IDENTIFIER_LENGTH];
    int index = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) {
            buffer[index++] = ch;
            while ((ch = fgetc(file)) != EOF && (isalpha(ch) || isdigit(ch))) {
                buffer[index++] = ch;
            }
            buffer[index] = '\0';
            if (isKeyword(buffer)) {
                printf("Keyword: %s\n", buffer);
            } else {
                printf("Identifier: %s\n", buffer);
            }
            index = 0;
            ungetc(ch, file);
        } else if (isspace(ch)) {
            continue;
        } else {
            char op[3] = { ch, '\0', '\0' };
            char next = fgetc(file);
            if (next != EOF) {
                op[1] = next;
                if (isOperator(op)) {
                    printf("Operator: %s\n", op);
                } else {
                    printf("Operator: %c\n", op[0]);
                    ungetc(next, file);
                }
            } else {
                printf("Operator: %c\n", op[0]);
            }
        }
    }
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Error opening file!\n");
        return 1;
    }

    analyzeFile(file);
    fclose(file);
    return 0;
}
