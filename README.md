# Terminal Computer Graphics

A lightweight, terminal-based graphics framework and game engine(need to be completed), written in C++.

## Why this exists

Most graphics/game frameworks (SFML, SDL, OpenGL-based engines, etc.) come with a lot of setup overhead, dependencies, and abstraction — which is great for building real games, but makes them a poor fit for something else entirely: **learning and testing graphics algorithms in isolation.**

If you want to see how line rasterization, shape filling, or point-in-triangle tests actually work, step by step, you shouldn't need a windowing system, a build pipeline, and a dozen dependencies just to plot some pixels.

This project takes a different approach: render everything directly into the terminal, using nothing but ANSI escape codes and true-color output. No external graphics libraries, no GPU drivers, no windowing toolkit — just a terminal window and a pixel buffer.

It serves two purposes at once:

1. **A minimal sandbox for learning graphics algorithms** — small, inspectable, and easy to reason about, since there's no framework noise between your algorithm and the screen.
2. **A framework (and eventually engine) for building terminal-based games** — for developers who want to create real, playable terminal games without fighting a general-purpose engine that wasn't designed with terminals in mind.

## Core building blocks

- **`Pixel` / `PixelMatrix` / `Color` / `Point2D`** — a flat RGBA(RGB) pixel buffer with clear/set/blend operations and small 2D point data structure.
- **`TerminalLauncher`** — spawns and owns a real terminal emulator process (currently Alacritty) as the visual output window. (need help tp expand the idea)
- **`Window`** — ties a `PixelMatrix` to a `TerminalWindow` and handles rendering the buffer to the screen.
- **`Image`** — core idea of creating spirits which supports smapling
- **`Renderer`** — a simple renderer object which handles the rendering images to the window.
- **`Primitive`** — handles the creation and drawing of simple primitive shapes like `Line2D`, `Triangle`, `Rectangle`, `Circle`.

## Status

This project is under active development. Core pixel buffer, window, and terminal-launch logic are being built and tested first; rasterization algorithms and game-engine features (input handling, game loop utilities, etc.) come next.

## Documentation

Full documentation, design notes, and usage guides live in the project wiki:

👉 [Project Wiki](https://github.com/ATMCHGIT18/graphics-framework/wiki)

## License

Licensed under the [Apache License 2.0](LICENSE).
