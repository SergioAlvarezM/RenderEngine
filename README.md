# RenderEngine

Simple render engine to simplify the work with OpenGL.

# How to use

To use this render in user mode you only have to modify the Setup.h file. In this file there is the functions that will be running inside the Engine and that will be called in each frame and at the beggining of the engine. These two functions have all the parameters needed from the Engine.

This file already have a small code showing how to use it.

If you need help to know how the engine works below is a small explanation of every class. Also the .h files of each class are commented with explanations of the methods.

There is also a makefile that has inside the most important commands for the project like compile, generate documentation, and other things, run in the console _make_ to show the help message.

# Structure of the Engine

## Camera Class

The class that manage the camera and all its movements. Also is the one that generates the View matrix that will be
used in the Shaders.

## Render Class

Is the one that manage all the drawing in the screen and the main interaction with OpenGL. (it doesn't mean that the other
classes don't interact with OpenGL).

## EventHandler Class

Is the one that manage the events that happens in the program. This is the one in charge of calling the other classes
classes method when an event ocurs.

## Scene Class

Is the one in charge of place the objects in the world and have all the positions ready to give them to the render.
(not yet implemented).

## Shader Class

The class that is in charge of all the things that are related to the shaders, from compile to declare uniforms.

#Things to do

- Object class (inherit from model)
- Triangulation class (inherit from object or model)
- Change the drawAxis method in scene to only use one model and not three
