godot-raknet-example
====================

This is a simple demonstration of using a custom C++ module for the Godot game
engine which connects to another peer on the network using the RakNet networking
library.

All it does is to initiate a connection between two RakNet peers.

## Usage
Clone the repository somewhere on your computer. After cloning, be sure to clone
the RakNet repository too which is included as a submodule. Within the directory
of the repository run:

```
git submodule init
git submodule update
```

Assuming you already have the source code of the Godot engine on your computer,
you can now copy the `gdraknet` folder and paste it under the `modules` in the
Godot engine's root directory.

Just compile the Godot engine as usual and you are good to go.

**Please note**, I have only tested this on GNU/Linux. Not sure if it will work
on other platforms.

You can check the example project for Godot which is included under the
`example\_project` directory.

You can learn more about using custom C++ modules with Godot from the following
link:
https://github.com/okamstudio/godot/wiki/custom\_modules
