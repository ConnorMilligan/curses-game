#include <curses.h>
//#include <sdl2/pdcsdl.h>

int main(int argc, char **argv) {
    wchar_t smile = L'\u00AF';
    
    initscr();
    
    addstr("Hello, world!\n");
    addch(smile);

    getch();
    //pdc_fwidth = 12;
    getch();


    endwin();
    return 0;
}
