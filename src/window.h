#ifndef WINDOW_H
#define WINDOW_H

#include <curses.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int width;
    int height;
} Dimension;

class Window {
    private:
        Point position;
        Dimension dimensions;
        WINDOW *win;
    public:
        Window(int x, int y, int width, int height);
        
        void draw();
};




#endif