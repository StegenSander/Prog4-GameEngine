https://github.com/StegenSander/Prog4-GameEngine
# Minigin
 GameEngine for Dae::Prog4

Minigin started as a very minimal framework, but over the course of 12 weeks I have turned Minigin in my own 2D engine.
Minigin now contains:
	- Controllable scenes: change and reset scenes at runtime + each scene has its own input
	- Input manager with Keyboard and up to 4 controllers support
	- Component system: every object is built up from 1 Gameobject and a combination of components
		Default components are:
		- TextureComponent (Renders Textures)
		- TextComponent (Renders Text)
		- ButtonComponent (Calls a function on click)
		- SpawnerComponent (Takes care of object spawning 
			for if you need a certain amount of object of the same type alive at all times)
	- GameObjects and Components can be destroyed during runtime
	- Binary Parsing: All POD's and Strings are supported
	- SDL2 Audio: for simple .wav audio (runs on a seperate thread)
	- Imgui Support (not used in demo project)
	- Observer Pattern: use Subject and Listener Classes to detach components from eachother and use a 1 to many way of function calls
	- Everything uses smartpointers to avoid memory leaks

