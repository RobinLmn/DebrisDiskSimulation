# Debris Disk Simulation

A debris disk is a collection of dust particles orbiting a solar system older than 10Myrs. These dust particles are the remnants of planetesimal collisions within the solar system, collisions that lead to planet formation according to the core accretion model.

Since the debris are the results of planet formation, and since the dust particles are gravitationally perturbed by the solar system, analyzing a debris disk can give crucial information on the presence of exoplanets within the system.

In this project, 3-dimensional rendering techniques are used to visualize the morphologies of a debris disk orbiting a solar system composed of a single planet, with a possibly eccentric orbit. Building up on the work of Lee & Chiang (2016), a more performant and practical tool is presented to understand the various shapes of a debris disk at different viewing angles, in both scattered light and thermal emission.

<p float="left">
<img alt="alt_text" width="400px" src="https://github.com/RobinLmn/DebrisDiskSimulation/blob/main/Documents/Media/Final%20Report/DebrisDisks/disk_morphologies.png" />

<img alt="alt_text" width="400px" src="https://github.com/RobinLmn/DebrisDiskSimulation/blob/main/Documents/Media/Final%20Report/DebrisDisks/disk_morphologies_thermal.png" />
  
</p>

## Packaging

The latest release can be downloaded [here](https://github.com/RobinLmn/DebrisDiskSimulation/releases/latest). For now, there is only a windows version.

## Downloading the code source

1. Clone the repository to your device.
2. Download Visual Studio 2019 or more
3. Run the file 'GenerateProject.bat'.
4. Launch 'DebrisDisk.sln'. This will launch Visual Studio and the source code.

There are three configurations: 'Debug', 'Profile' and 'Release'. Generally, 'Release' should be chosen for better performances. For debugging purposes, 'Debug' can be used. The 'Profile' configuration is used to measure the program's performances with the Tracy profiler.

5. Select 'Release' next to 'x64' instead of 'Debug'
6. Launch the program by clicking 'Local Windows Debugger'. This will launch the tool. 

## Using the tool

Every parameter is defined in the '.config' file under the 'Content' directory. In this file, enter all the parameters associated with the simulation, like the size of the window, the parameters of the star, and the path to the file containing the orbits. Evering line starting by '#' is a comment and will not be read.

In the tool, you can zoom in and zoom out using the arrow keys. You can rotate around by using WASD or moving the mouse and right clicking at the same time.

The tool has two windows. The first one is a 'Photo Mode' to take a screenshot saved at 'DebrisDiskSimulation\DebrisDisk\Content\Screenshots'. The second window is to manually enter certain parameters, like the control speed, the disk rendering, or the viewing angles.

## Navigating the source code

The solution 'DebrisDisk' contains 5 projects: 'DebrisDisk', 'glad', 'GLFW', 'ImGui' and 'tracy'. The source code of the project is situated in the 'DebrisDisk' project. The other projects are third party tools and utilities.

The 'DebrisDisk' project has 3 modules: 'Engine', 'Renderer', 'Systems'. The Renderer is what draws the disk on the screen. The Systems are what define the debris disk, the position of every particule, their color, etc. Finally, the Engine links the two together. The Engine also controls the window layout and the UI ('Editor').

DebrisDisk.cpp and DebrisDisk.h are the most interesting files for the physics of the project. It defines a 'SDebrisDisk' class which goal is to populate a list of 'Particles' that the renderer will draw. This is done in th SDebrisDisk::Init() function. First, it loads the orbits from the file specified in the configuration file. Then, it converts every orbits to particles in the 'OrbitToParticle' method.

## Contributing

Feel free to submit pull requests, or to open an issue to report a bug.
