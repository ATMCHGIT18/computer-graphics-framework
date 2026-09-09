# Roadmap

This document tracks planned version, target dates, and features for this project.
Status legend:  🟡 Planned · 🔵 In Progress · 🟢 Done · 🔴 Delayed

---

## v0.1 - [1st September 2026]
**Status:** 🟢 Done
**Goal:** framework contains all basic mathematical rendering using terminal.

- [🟢] Windowing using terminal
- [🟢] Specialised pixel matrix for rendering
- [🟢] `Render` object and `Window` and `Image` object for rendering
- [🟢] Adding basic objects for holding color data of the screen `Matrix`,`Pixel`,`PixelMatrix`.

## v0.2 - [4th September 2026]
**Status:** 🟢 Done
**Goal:** Adding basic algorithms for line generation, triangle generation, and color filling

- [🟢] `algorithm.hpp` contains line generation , color filling algorithms
- [🟢] `Color` data structure to correspond to the modern APIs method of storing color data
- [🟢] expand `Render` object to support each type of `Matrix` as an input
- [🟢] `event.hpp` that supports the basic keyboard and mouse events across all platforms


## v0.3 - [15th September 2026]
**Status:**  🔵 In Progress
**Goal:** Support fully of 

- [🟢] `X11` compatibility for window creation instead of using terminal as window
- [🟢] `X11` event listening for keyboard and mouse movement event which more advanced than the `event.hpp` objects.
- [🔵] Compatibility of the whole framework on different machines


## v0.4 - [1st October 2026]
**Status:** 🟡 Planned
**Goal:** Fully compatible window option instead of working with terminal in all machines and have simple and basic animation system

- [🟡] Using other windowing options for MS Windows and MacOS instead of using terminal and cmd
- [🟡] Simple animation system
- [🟡] Introducing a sampling object for the more advanced operations which we will deal with in 3D space

## v0.5 - [Mid October 2026]
**Status:** 🟡 Planned
**Goal:** More advanced sampling systems and make the framework ready for 3D

- [🟡] Advanced sampling idea and algorithms
- [🟡] Start of making the framework compatible with 3D ( this will have another branch for itself)
- [🟡] Make a simple test animation.

## v0.6 - [Late October 2026]
**Status:** 🟡 Planned
**Goal:** Make Framework compatible with the 3D space,

- []
- []
- []

