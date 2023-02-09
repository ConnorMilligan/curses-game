#include "window.h"

Window::Window(int x, int y, int width, int height) {
    this->position.x = x;
    this->position.y = y;

    this->dimensions.width = width;
    this->dimensions.height = height;

    this->win = newwin(x, y, width, height);
    box(this->win, '~', '~');
}

void Window::draw() {
    touchwin(this->win);
    wrefresh(this->win);
    getch();

    touchwin(stdscr);
    refresh();
}