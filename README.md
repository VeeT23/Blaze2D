# Blaze2D

Blaze2D is an open-source 2D graphic library that wraps SDL3. It is intended to promote convienence without compromizing flexibility.

Blaze2D's UI is organized in a heiarchy:

App -> Windows -> Containers -> Widgets

## App

The App class is the root of Blaze2D. It is responsible for managing the lifetime of SDL.

*Only one App object should be made per program.*

There are several important methods to the App class:

**update()**

Calls update() of all windows.

**render()**

Calls render() to all windows.

**get_input()**

Return the remaining input after propagating through the heiarchy.
Use for applications where menus/text boxes/UIs capture user input. 

(Use SDL_PollEvent() for raw user input.)

## Windows

The Window class extends SDL's windows; handling both SDL window and renderer initialization and destruction.