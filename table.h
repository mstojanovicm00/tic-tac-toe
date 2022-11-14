//
// Created by mihajlo-stojanovic on 12.11.22..
//

#ifndef TIC_TAC_TOE_TABLE_H
#define TIC_TAC_TOE_TABLE_H

enum table_check_message {
    NOTHING = 0,
    X_WON = 'X',
    O_WON = 'Y',
    DRAW = 'D'
};

struct table {
    char value[3][3];
    char turn;
};

struct table init();
int empty(struct table table, int row, int column);
char check(struct table table);
char change_turn(struct table* table);
void guess(struct table* table, int i, int j);
void draw(struct table table);
void print_message(enum table_check_message message);

#endif //TIC_TAC_TOE_TABLE_H
