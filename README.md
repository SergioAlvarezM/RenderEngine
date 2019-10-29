# RenderEngine
 Simple render engine to simplify the work with OpenGL.
 
 
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

- Writte a better readme with examples and better explanatons.
- Scene class
- Object class
- Triangulation class