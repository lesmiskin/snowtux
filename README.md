# Simple 3D Engine (by Les Miskin)
A simple, sparsely-featured 3D engine focused on code understandability.

## On the graphics API used
This engine uses an older API to handle it's 3D graphics, known as "OpenGL legacy". While this may seem like a bad idea
in terms of perpetuating outdated techniques, the decision to use this was based on ease of understanding by new 
programmers, as the modern style (used by OpenGL 3.1 and above) is significantly more complex. For more information, 
see: https://www.khronos.org/opengl/wiki/Legacy_OpenGL. The purpose of this engine is to provide an easy-to-learn base
for experimentation and hacking. Users who are interested in continuing their work in 3D graphics, whether they are 
planning to make a commercial game or continue their education, are encouraged to consult the modern approaches.

If someone is willing to provide an implementation of the engine using the modern OpenGL approach (sorry, but Vulkan is
going a bit far right now), then please feel free to fork the repo accordingly. If we can achieve a similar level of
clarity for the reader as with the current implementation, then I would dearly love to move the main codebase to it.

# Coding style
* No more than one logical or arithmetic expression per-line.
* Return statements should be on their own line, and not include an expression.
* Recommend maximum character limit of 120.
* Where an SDL alternative is available for a C function (e.g. SDL_GetTicks() vs. clock()), we prefer the C function.
  This is to increase understanding of C itself, and only use SDL when it's necessary.

# Comment policy
* When in doubt, add a comment.
* Important sections of code should be decorated with a header & description style.
* Use "own line" comments for single line statements and heading up code paragraphs.
* Use "right-aligned" comments for commentary on mid-code paragraph statements, or argument lists.
* Comments should be kept to a single line, in lowercase, and not end in a period.
* Omit comments for statements which call custom routines, which we can expect are already clearly-named.
* In contrast, provide an "own words" explanation when calling any library function, how ever clearly-named, to
  provide guidance to the reader.

# Todo
* Explanation of "long" and "float" (would be uncommom for modern beginners)