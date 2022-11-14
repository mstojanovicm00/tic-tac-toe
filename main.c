#include <stdio.h>

#include "table.h"

enum table_check_message play(struct table table) {
    int draw_not = 0;
    enum table_check_message message;
    int turns = 0;
    do {
        if (draw_not)
            draw_not = 0;
        else
            draw(table);
        printf("Insert a number where you want to insert your sign: ");
        int num;
        scanf("%d", &num);
        int row = (num - 1) / 3;
        int column = (num - 1) % 3;
        if (!empty(table, row, column)) {
            printf("The place you want to insert your sign is already occupied\n");
            printf("Try again!\n");
            draw_not = 1;
            continue;
        }
        guess(&table, row, column);
        printf("Value at (%d, %d) is %c\n", row, column, table.value[row][column]);
        change_turn(&table);
        message = check(table);
        if (++turns == 9)
            return DRAW;
    } while (!message);
    draw(table);
    return message;
}

int main() {
    print_message(play(init()));
    return 0;
}
