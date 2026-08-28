#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::cout << "--- Isolated X11 Keyboard Polling Test ---" << std::endl;

    // 1. Establish connection to the X Server
    Display* dpy = XOpenDisplay(NULL);
    if (!dpy) {
        std::cerr << "CRITICAL ERROR: Could not connect to X Server (XOpenDisplay returned NULL)!" << std::endl;
        std::cerr << "Are you running a Wayland session without XWayland, or is DISPLAY env variable missing?" << std::endl;
        return 1;
    }
    std::cout << "Successfully connected to X Server display." << std::endl;

    // 2. Fetch the strict physical keycodes for space and lower-case 'w'
    // We will print these to verify X11's layout mapping is actually returning non-zero hardware indices.
    KeyCode space_kc = XKeysymToKeycode(dpy, XK_space);
    KeyCode w_kc     = XKeysymToKeycode(dpy, XK_w);

    std::cout << "Mapped Keysyms to System Keycodes -> [Space Code: " 
              << (int)space_kc << "] [ 'w' Code: " << (int)w_kc << "]" << std::endl;

    if (space_kc == 0 || w_kc == 0) {
        std::cerr << "ERROR: System failed to map character symbols to a physical keycode matrix." << std::endl;
        XCloseDisplay(dpy);
        return 1;
    }

    std::cout << "Starting loop. Hold down SPACEBAR or the 'W' key to test. Press Ctrl+C to exit.\n" << std::endl;

    char keys_matrix[32];

    while (true) {
        // Query the snapshot of the entire keyboard bitmap array from the X server
        XQueryKeymap(dpy, keys_matrix);

        // Map the single indices out of the 32-byte (256-bit) array
        // Formula: byte = keycode / 8 (keycode >> 3), bit = keycode % 8 (keycode & 7)
        bool space_pressed = (keys_matrix[space_kc >> 3] & (1 << (space_kc & 7))) != 0;
        bool w_pressed     = (keys_matrix[w_kc >> 3] & (1 << (w_kc & 7))) != 0;

        if (space_pressed) {
            std::cout << "[DETECTED] Spacebar is DOWN!" << std::endl;
        }
        if (w_pressed) {
            std::cout << "[DETECTED] 'W' Key is DOWN!" << std::endl;
        }

        // Throttle to 30ms to prevent spamming standard output streams
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }

    XCloseDisplay(dpy);
    return 0;
}
