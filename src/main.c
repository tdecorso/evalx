#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "tds/da.h"

#define BUFFER_SIZE 256
#define TOKENS_CAPACITY 64

typedef enum {
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    END,
} tktype;

typedef struct {
    int data;
    tktype type;
} token;

typedef struct {
    token curr;
    size_t index;
} parser;

// Helper function to print single token in stdout
void token_print(token* t);

// Helper function to print all tokens in stdout
void print_tokens(da* tokens);

// Reads and null-terminates input string from stdin.
void read_input(char* buffer, size_t buffer_size);

// Returns true if input is not valid or user typed 'q'.
bool should_quit(char* buffer);

// Returns true if char is a plus sign
bool is_plus(char c);

// Returns true if char is a minus sign
bool is_minus(char c);

// Returns true if char is a star sign
bool is_mult(char c);

// Returns true if char is a slash sign
bool is_div(char c);

// Returns true if char is a left parenthesis
bool is_left_par(char c);

// Returns true if char is a right parenthesis
bool is_right_par(char c);

// Returns true if char is a white space
bool is_whitespace(char c);

// Reads series of digits from buffer and converts it into a token
bool tokenize_digits(const char* buffer, size_t* index, da* tokens);

// Processes input to produce array of tokens. Returns true if errors were found.
bool tokenize(const char* buffer, da* tokens);

// Updates parser with next token.
void parser_advance(parser* p, da* tokens);

// Makes parser advance if current token type matches expected.
void parser_consume(parser* p, da* tokens, tktype expected);

// Terms are multiplications or divisions of factors.
//     Returns true if errors were found.
bool parse_term(parser* p, da* tokens, int* result);

// Expressions are sums of terms.
//     Returns true if errors were found.
bool parse_expression(parser* p, da* tokens, int* result);

// Factors are either a number or expressions wrapped into parenthesis.
//     Returns true if errors were found.
bool parse_factor(parser* p, da* tokens, int *result);

// Parses tokens and prints the result. Returns true if errors were found.
bool parse(da* tokens);

int main(void) {
    char buffer[BUFFER_SIZE];
    da* tokens = da_alloc(sizeof(token), TOKENS_CAPACITY);

    while (1) {
        printf("  > ");

        read_input(buffer, sizeof(buffer));

        if (should_quit(buffer)) break;

        if (tokenize(buffer, tokens)) {
            printf("  > Error: syntax not valid.\n");
            continue;
        }

        if (parse(tokens)) {
            printf("  > Error: syntax not valid.\n");
            continue;
        }
    }

    return 0;
}

void read_input(char* buffer, size_t buffer_size) {
    buffer = fgets(buffer, buffer_size, stdin);
    if (buffer) buffer[strcspn(buffer, "\n")] = '\0';
}

bool should_quit(char* buffer) {
    if (!buffer) return true;
    if (strcmp(buffer, "q") == 0) return true;
    return false;
}

bool tokenize_digits(const char* buffer, size_t* index, da* tokens) {
    char c = buffer[*index];
    char dbuff[64];
    size_t j = 0;
    do {
        dbuff[j++] = c;
        c = buffer[++(*index)];
        if (j == 64) return true;
    } while (isdigit(c));

    dbuff[j] = '\0';
    int value = atoi(dbuff);
    token t = {value, NUMBER};
    da_append(tokens, &t);
    return false;
}

bool tokenize(const char* buffer, da* tokens) {
    tokens->count = 0;
    size_t i = 0;
    while (buffer[i] != '\0') {
        if (is_whitespace(buffer[i])) {
            i++;
            continue;
        }
        else if (isdigit(buffer[i])) {
            if (tokenize_digits(buffer, &i, tokens)) return true; 
        }

        else if (is_plus(buffer[i])) {
            token t = {0, PLUS};
            da_append(tokens, &t);
            i++;
        }
        else if (is_minus(buffer[i])) {
            token t = {0, MINUS};
            da_append(tokens, &t);
            i++;
        }
        else if (is_mult(buffer[i])) {
            token t = {0, MULTIPLY};
            da_append(tokens, &t);
            i++;
        }
        else if (is_div(buffer[i])) {
            token t = {0, DIVIDE};
            da_append(tokens, &t);
            i++;
        }
        else if (is_left_par(buffer[i])) {
            token t = {0, LPAREN};
            da_append(tokens, &t);
            i++;
        }
        else if (is_right_par(buffer[i])) {
            token t = {0, RPAREN};
            da_append(tokens, &t);
            i++;
        }
        else return true;
    }

    token end = {0, END};
    da_append(tokens, &end);
    return false;
}

bool is_plus(char c) {
    return c == '+';
}

bool is_minus(char c) {
    return c == '-';
}

bool is_mult(char c) {
    return c == '*';
}

bool is_div(char c) {
    return c == '/';
}

bool is_whitespace(char c) {
    return c == ' ' || c == '\t';
}

bool is_left_par(char c) {
    return c == '(';
}

bool is_right_par(char c) {
    return c == ')';
}

void token_print(token* t) {
    switch (t->type) {
    case NUMBER:
        printf("NUMBER(%d)\n", t->data);
        break;
    case PLUS:
        printf("PLUS\n");
        break;
    case MINUS:
        printf("MINUS\n");
        break;
    case MULTIPLY:
        printf("MULTIPLY\n");
        break;
    case DIVIDE:
        printf("DIVIDE\n");
        break;
    case LPAREN:
        printf("(\n");
        break;
    case RPAREN:
        printf(")\n");
        break;
    default:
        break;
    }
}

void print_tokens(da* tokens) {
    for (size_t i = 0; i < tokens->count; ++i) {
        token t;
        da_get(tokens, i, &t);
        token_print(&t);
    }
}

void parser_advance(parser* p, da* tokens) {
    da_get(tokens, p->index, &p->curr);
    p->index++;
}

void parser_consume(parser* p, da* tokens, tktype expected) {
    if (p->curr.type == expected) {
        parser_advance(p, tokens);
    }
}

bool parse_factor(parser* p, da* tokens, int *result) {
    if (p->curr.type == NUMBER) {
        *result = p->curr.data;
        parser_consume(p, tokens, NUMBER);
        return false;
    }
    else if (p->curr.type == LPAREN) {
        parser_consume(p, tokens, LPAREN);
        if (parse_expression(p, tokens, result)) return true;
        if (p->curr.type != RPAREN) return true;
        parser_consume(p, tokens, RPAREN);
        return false;
    }
    return true;
}

bool parse_term(parser* p, da* tokens, int* result) {

    if (parse_factor(p, tokens, result)) return true;

    bool is_mult = p->curr.type == MULTIPLY;
    bool is_div = p->curr.type == DIVIDE;
    while (is_mult || is_div) {
        if (is_mult) {
            parser_consume(p, tokens, MULTIPLY);
            int value;
            if (parse_factor(p, tokens, &value)) return true;
            *result *= value;
        }
        if (is_div) {
            parser_consume(p, tokens, DIVIDE);
            int value;
            if (parse_factor(p, tokens, &value)) return true;
            if (value == 0) return true;
            *result /= value;
        }
    
        is_mult = p->curr.type == MULTIPLY;
        is_div = p->curr.type == DIVIDE;
    }
    return false;
}

bool parse_expression(parser* p, da* tokens, int* result) {

    if (parse_term(p, tokens, result)) return true;

    bool is_add = p->curr.type == PLUS;
    bool is_sub = p->curr.type == MINUS;

    while (is_add || is_sub) {
        if (is_add) {
            parser_consume(p, tokens, PLUS);
            int value = p->curr.data;
            if (parse_term(p, tokens, &value)) return true;
            *result += value;
        }
        if (is_sub) {
            parser_consume(p, tokens, MINUS);
            int value = p->curr.data;
            if (parse_term(p, tokens, &value)) return true;
            *result -= value;
        }
    
        is_add = p->curr.type == PLUS;
        is_sub = p->curr.type == MINUS;
    }
    return false;
}

bool parse(da* tokens) {
    if (tokens->count == 0) return true;
    
    parser p = {{0}, 0};
    parser_advance(&p, tokens);

    int result = p.curr.data;

    if (parse_expression(&p, tokens, &result)) return true;

    if (p.curr.type == END) {
        printf("  > Result: %d\n", result);
        return false;
    }

    return true;
}
