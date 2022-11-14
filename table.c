//
// Created by mihajlo-stojanovic on 12.11.22..
//

#include "table.h"

#include <stdio.h>

struct table init() {
    struct table table;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            table.value[i][j] = '0' + i * 3 + j + 1;
        }
    }
    table.turn = 'X';
    return table;
}

int empty(struct table table, int row, int column) {
    char letter = table.value[row][column];
    return letter != 'X' && letter != 'O';
}

static char check_row(struct table table, int row) {
    char default_value = table.value[row][0];
    for (int i = 1; i < 3; ++i) {
        if (table.value[row][i] != default_value)
            return NOTHING;
    }
    return default_value;
}
static char check_column(struct table table, int column) {
    char default_value = table.value[0][column];
    for (int i = 1; i < 3; ++i) {
        if (table.value[i][column] != default_value)
            return NOTHING;
    }
    return default_value;
}
static char check_main(struct table table) {
    char default_value = table.value[0][0];
    if (table.value[1][1] != default_value)
        return NOTHING;
    if (table.value[2][2] != default_value)
        return NOTHING;
    return default_value;
}
static char check_additional(struct table table) {
    char default_value = table.value[0][2];
    if (table.value[1][1] != default_value)
        return NOTHING;
    if (table.value[2][0] != default_value)
        return NOTHING;
    return default_value;
}
char check(struct table table) {
    for (int i = 0; i < 3; ++i) {
        char winner = check_row(table, i);
        if (winner)
            return winner;
        winner = check_column(table, i);
        if (winner)
            return winner;
    }
    char winner = check_main(table);
    if (winner)
        return winner;
    winner = check_additional(table);
    if (winner)
        return winner;
    return NOTHING;
}

char change_turn(struct table* table) {
    return (table->turn == 'X') ? (table->turn = 'O') : (table->turn = 'X');
}

void guess(struct table* table, int i, int j) {
    table->value[i][j] = table->turn;
}

#define DIMENSION 13
void draw(struct table table) {
    int _i = 0, _j = 0;
    for (int i = 1; i <= DIMENSION; ++i) {
        for (int j = 1; j <= DIMENSION; ++j) {
            if (i % 4 == 1) {
                printf("-");
                continue;
            }
            if (j % 4 == 1) {
                printf("|");
                continue;
            }
            if (i % 4 == 3 && j % 4 == 3) {
                putchar(table.value[_i][_j]);
                _i += (_j = (_j + 1) % 3) % 3 == 0;
                continue;
            }
            printf(" ");
        }
        printf("\n");
    }
}

void print_message(enum table_check_message message) {
    switch (message) {
        case X_WON:
            printf("X won\n");
            break;
        case O_WON:
            printf("O won\n");
            break;
        case DRAW:
            printf("It's a draw\n");
            break;
        default:
            printf("There was some error in this game\n");
    }
}