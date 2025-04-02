# Debris Disk Simulation

A real-time visualization tool for simulating and analyzing debris disks around solar systems.

<p float="center">
<img alt="alt_text" width="400px" src="https://github.com/RobinLmn/DebrisDiskSimulation/blob/main/docs/images/tool_window.png" />
</p>

## Download

### Latest Release

- Windows: [v1.0.0](https://github.com/robinlmn/DebrisDiskSimulation/releases/latest)
- Mac: _Do you need this? Shoot me an email_
- Linux: _Do you need this? Shoot me an email_

### Previous Releases
- Windows: [v0.0.0](https://github.com/robinlmn/DebrisDiskSimulation/releases/tag/v0.0.0)

## Guide

### Getting Started


1. Download the latest release from the [releases page](https://github.com/robinlmn/DebrisDiskSimulation/releases/latest)
2. Extract the ZIP file to your preferred location
3. Run `DebrisDiskSimulation.exe`

### Visualizing a debris disk

1. **File > New** allows you to create a new debris disk to visualize from its orbits.
    a. **Star Properties** allow you to specify the mass, radius and temperature of the system's star.
    b. **Dust Properties** allow you to specify the fixed radiation of each particle and the number of particles per orbit.
        i. **Orbits File** is the file containing the disk's orbits. Each orbit has the format `a e I Omega omega Beta\n`. See `content/dust_orbits` for examples.
    c. **Save Location** is the path where the debris disk will be saved. This will create a `.sim` file that can later be re-opened with **File > Open**.

2. **File > Open** allows you to reopen a debris disk that was created through **File > New**. Generally a `.sim` file.

3. **File > Export** will save the debris disk as a `.png` image.

### Scenes

Every debris disk vizualized through **File > New** or **File > Open** will be listed in the **Scenes** window, on the right. Double clicking an item will open the debris disk. This way, you can quickly cycle through multiple debris disk.

### Properties

1. **Debris Disk**
i. **Thermal Radiation**: Whether to render the disk in scattered light (off) or in thermal radiation (on)
ii. **Intensity**: multiplier applied to the intensity each dust particle, scaling them on the colormap.
iii. **Offset**: amount added to the intensity of each dust particle, offseting them on the colormap.
iv. **Dust Contribution**: the additive parameter used to blend dust particles in the same pixel.

2. **Camera**
i. **Distance**: the distance of the camera from the center of the solar system.
ii. **Altitude**: alt angle of the camera, always facing the system's star.
iii. **Azimuth**: az angle of the camera, always facing the system's star.
iv. **Sensitivity**: mouse sensitivity, when used to control the camera.
v. **Speed**: keyboard sensitivity, when used to control the camera.

### Camera Controls

- **Mouse**: right click and hold to rotate the camera around the debris disk. The camera will always face the center of the system
- **Keyboard**: `W` and `D` control the camera's alt angle, and `A` and `S` control the camera's azimuth angle. `Arrow Up` and `Arrow Down` control the distance from the disk

## What is a debris disk?

A debris disk is a collection of dust particles orbiting a solar system older than 10Myrs. These dust particles are the remnants of planetesimal collisions within the solar system, collisions that lead to planet formation according to the core accretion model.

Since the debris are the results of planet formation, and since the dust particles are gravitationally perturbed by the solar system, analyzing a debris disk can give crucial information on the presence of exoplanets within the system.

In this project, 3-dimensional rendering techniques are used to visualize the morphologies of a debris disk orbiting a solar system composed of a single planet, with a possibly eccentric orbit. Building up on the work of Lee & Chiang (2016), a more performant and practical tool is presented to understand the various shapes of a debris disk at different viewing angles, in both scattered light and thermal emission.

<p float="left">
<img alt="alt_text" width="400px" src="https://github.com/RobinLmn/DebrisDiskSimulation/blob/main/docs/media/final_report/images/disk_morphologies.png" />

<img alt="alt_text" width="400px" src="https://github.com/RobinLmn/DebrisDiskSimulation/blob/main/docs/media/final_report/images/disk_morphologies_thermal.png" />

</p>

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
