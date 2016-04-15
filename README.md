# YAGE (Yet Another Game Engine)

Authors: @harrygogonis and @goozie001

## Requirements

* Microsoft Visual Studio 2015 (sorry, will port to gcc later)

## Getting Started

* Clone the repository
* Open `YAGE.sln` file with visual studio
* Install dependancies:
	* `Tools > Nuget Package Manager > Package Manager Console`
	*  Type this into the the console: `Update-Package -Reinstall`
* Edit `main.cpp`
* Run the default startup project `F10`

## Documentation
If you are viewing this on Github, you can find our documentation here: 
[http://harrygogonis.github.io/YAGE](http://harrygogonis.github.io/YAGE)

## Screenshots
![Shadows](http://i.imgur.com/crVyjjA.png)
![Diablo](http://i.imgur.com/JOZFDyq.png)

## Viewport Controls

| Control           | Action                             |
|-------------------|------------------------------------|
| W                 | Moves the camera forward.          |
| S                 | Moves the camera backward.         |
| A                 | Moves the camera left.             |
| D                 | Moves the camera right.            |
| E                 | Moves the camera up.               |
| Q                 | Moves the camera down.             |
| Mouse Scroll DOWN | Zooms the camera out (raises FOV). |
| Mouse Scroll UP   | Zooms the camera in (lowers FOV).  |
| Mouse DRAG		| Rotates the camera around			 |

## 3rd Party Libraries
* [ASSIMP](http://www.assimp.org/)
* [SOIL](http://www.lonesock.net/soil.html)
* [Bullet](http://bulletphysics.org/wordpress/)
* [Freeglut](http://freeglut.sourceforge.net/)
* [OpenGL](https://www.opengl.org/)
* [GLM](http://glm.g-truc.net/0.9.7/index.html)

## Features
* Lighting system (Ambient, Point, Directional, Spotlight)
* Physics system (using bullet physics)
* Diffuse mapping
* Normal mapping
* Specular mapping
* Import scenes via .fbx, .obj, and more
* Game object builder
* Dynamic shadows
* Particle system

## Limitations
* Significant frame drop after ~500k polygons
* Shadows only supported w/ one directional light

## Future Features
* Animation
* Text rendering

## Helpful resources
* [in2gpu OpenGL Tutorial](http://in2gpu.com/opengl-3/)
* [OpenGL Documentation](https://www.opengl.org/sdk/docs/man/)
* [Red Book](http://www.amazon.com/OpenGL-Programming-Guide-Official-Learning/dp/0321335732)
* [OpenGL-Tutorial](http://www.opengl-tutorial.org/)
* [OGLDev](http://ogldev.atspace.co.uk/index.html)
