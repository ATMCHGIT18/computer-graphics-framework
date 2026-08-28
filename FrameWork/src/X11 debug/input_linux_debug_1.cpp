#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    // 1. Initialize Display connection
    Display* dpy = XOpenDisplay(NULL);
    if (!dpy) return 1;

    int screen = DefaultScreen(dpy);
    
    // 2. Create the Window
    Window win = XCreateSimpleWindow(
        dpy, RootWindow(dpy, screen), 
        10, 10, 400, 400, 1,
        BlackPixel(dpy, screen), WhitePixel(dpy, screen)
    );

    // 3. Ask for Keyboard events AND Window Drawing (Exposure) events
    XSelectInput(dpy, win, KeyPressMask | KeyReleaseMask | ExposureMask);
    XMapWindow(dpy, win);

    // 4. Create a Graphics Context (GC) - Needed for drawing instructions
    GC gc = XCreateGC(dpy, win, 0, NULL);

    // Define colors using hex codes
    unsigned long color_blue  = 0x0000FF;
    unsigned long color_red   = 0xFF0000;
    unsigned long current_color = color_blue;

    bool running = true;
    XEvent event;

    std::cout << "Window is ready. Focus the window and press Space to toggle colors, or Esc to exit.\n";

    // --- NON-BLOCKING ENGINE LOOP ---
    while (running) {
        // Look for OS inputs without freezing your code execution
        while (XPending(dpy)) {
            XNextEvent(dpy, &event);

            KeySym sym = XLookupKeysym(&event.xkey, 0);

            if (event.type == KeyPress) {
                if (sym == XK_space) {
                    // Change drawing color dynamically when Space is pressed
                    current_color = (current_color == color_blue) ? color_red : color_blue;
                    std::cout << "[RENDER UPDATE] Color switched!" << std::endl;
                }
                if (sym == XK_Escape) {
                    running = false;
                }
            }
        }

        // --- RENDER SECTION ---
        // 1. Set the active drawing color
        XSetForeground(dpy, gc, current_color);

        // 2. Draw natively onto the window (XDrawRectangle, XFillRectangle, XDrawLine, etc.)
        // Arguments: display, window, graphics_context, x, y, width, height
        XFillRectangle(dpy, win, gc, 100, 100, 200, 200);

        // 3. Flush updates to make sure the graphics server renders it instantly
        XFlush(dpy);

        // Throttle to keep CPU usage low
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    // Clean up hardware handles
    XFreeGC(dpy, gc);
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
    return 0;
}
