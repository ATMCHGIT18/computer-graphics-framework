#ifndef CHE_FRAMEWORK_GRAPHICS_HPP
#define CHE_FRAMEWORK_GRAPHICS_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

#if defined(__APPLE__)
#include <util.h>
#else
#include <pty.h>
#endif
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
// My libraries
#include <data_structures.hpp>
#include <terminal.hpp>
#include <pixel.hpp>
#include <window.hpp>
#include <che_algorithms.hpp>
#include <primitives.hpp>
#include <utils.hpp>

#define PIXEL_SIZE 1;

#endif