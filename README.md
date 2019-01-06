# Simple 3D Engine (by Les Miskin)
A simple, sparsely-featured 3D engine focused on code understandability. 

# Coding style
* No more than one logical or arithmetic expression per-line.
* Return statements should be on their own line, and not include an expression.
* Inline comments are lowercase, fit on a single line, and have no trailing period.
* Noteworthy sections of code are denoted with a heading style, with a single line comment below. Additional prose
  should be placed in `tour.txt` to keep the code itself readable.
* Author's discretion as to whether comments should be above or on the right of a statement (generally above is 
  preferred for readability).
* Recommend maximum character limit of 120.
* Where an SDL alternative is available for a C function (e.g. SDL_GetTicks() vs. clock()), we prefer the C function.
  This is to increase understanding of C itself, and only use SDL when it's necessary.

# Todo
* Explanation of "long" and "float" (would be uncommom for modern beginners)