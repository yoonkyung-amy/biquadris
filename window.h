// Not tested; Xflush
#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#include "Color.h"

class Xwindow {
    Display *d;
    Window w;
    int s;
    GC gc;
    unsigned long colours[14];
    int width, height;

public:
    Xwindow(int width=900, int height=630);  // Constructor; displays the window.
    ~Xwindow();                              // Destructor; destroys the window.


    int to_int (Color t) const noexcept;

    // Draws a rectangle
    void fillRectangle(int x, int y, int width, int height, Color t);

    // Draws a string
    void drawString(int x, int y, std::string msg);


};

#endif
