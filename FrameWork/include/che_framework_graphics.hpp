#ifndef CHE_FRAMEWORK_GRAPHICS_HPP
#define CHE_FRAMEWORK_GRAPHICS_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <array>
#include <algorithm>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

#if defined(__APPLE__)
#include <util.h>
#else

#if defined(__APPLE__)
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#undef Window
#undef index
#endif

#include <thread>
#include <chrono>
#include <pty.h>
#endif
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// My libraries
#include <data_structures.hpp>
#include <terminal.hpp>
#include <pixel.hpp>
#include <che_algorithms.hpp>
#include <event.hpp>
#include <window.hpp>
#include <primitives.hpp>
#include <utils.hpp>

#define PIXEL_SIZE 1;

#endif