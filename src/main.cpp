#include <curses.h>

#include "window.h"

int main(int argc, char **argv) {    
    initscr();
    
    addstr("Hello, world!\n");

    Window myWin(1, 1, 20, 20);
    getch();
    myWin.draw();

    endwin();
    return 0;
}
