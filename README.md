# cmwade-vcs
Charlotte's solo project for 324

VCS (short for Visual Character System) is an sdl-based audio/visual/input system designed to provide the basic functionality of ncurses, plus some extras. It is designed to merge the simplicity and ease-of-use of ascii-art graphics with the capabilities of modern graphics and audio systems.

##### Features
* SDL window which renders an array of 8x8 ASCII characters in its own thread, in a style much like ncurses.
* Character foreground and background colors configurable by RGB; no more memorizing color codes
* Keyboard reading handled through SDL
* Basic support for playing one-off audio sounds as well as looping a track
* (stretch goal) Shaders allow you to overlay effects on the background and foreground color layers, rendered on a 1/8 character size grid
