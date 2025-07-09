#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>

#include "window.h"
#include "Color.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Xwindow Constructor" << std::endl;
#endif

    d = XOpenDisplay(NULL);
    if (d == NULL) {
        cerr << "Cannot open display" << endl;
        exit(1);
    }
    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                            BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapRaised(d, w);

    Pixmap pix = XCreatePixmap(d,w,width,
                               height,DefaultDepth(d,DefaultScreen(d)));
    gc = XCreateGC(d, pix, 0,(XGCValues *)0);

    XFlush(d);
    XFlush(d);

    // Set up colours.
    XColor xcolour;
    Colormap cmap;

    char color_vals[15][15]={"white", "black", "red", "green", "blue",
                             "orange", "yellow", "brown", "maroon", "purple",
                             "dimgray", "gray", "whitesmoke", "darkseagreen", "cyan"};

    cmap=DefaultColormap(d,DefaultScreen(d));

    for(int i=0; i < 15; ++i) {
        XParseColor(d,cmap,color_vals[i],&xcolour);
        XAllocColor(d,cmap,&xcolour);
        colours[i]=xcolour.pixel;
    }

    int black = to_int(Color::Black);
    XSetForeground(d,gc,colours[black]);

    // Make window non-resizeable.
    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
    hints.height = hints.base_height = hints.min_height = hints.max_height = height;
    hints.width = hints.base_width = hints.min_width = hints.max_width = width;
    XSetNormalHints(d, w, &hints);

    XSynchronize(d,True);

    usleep(1000);
}

Xwindow::~Xwindow() {
#if DEBUG_LEVEL > 0
    #include <iostream>
    std::cout << "Xwindow Destructor" << std::endl;
#endif
    XFreeGC(d, gc);
    XCloseDisplay(d);
}

int Xwindow::to_int (Color t) const noexcept {
    return static_cast<int>(t);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, Color t) {
    int colorType = to_int(t);
    XSetForeground(d, gc, colours[colorType]);
    XFillRectangle(d, w, gc, x, y, width, height);
    int black = to_int(Color::Black);
    XSetForeground(d, gc, colours[black]);
    XFlush(d);
}

void Xwindow::drawString(int x, int y, string msg) {
    XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
    XFlush(d);
}
