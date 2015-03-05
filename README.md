Leap Music
==========

A musical instrument built using the Leap Motion v2.


Installation
============

Download the source code of the project with git:
```bash
git clone <repo url>
cd leapMusic
```

Dependencies
------------

Download the [Leap SDK](https://developer.leapmotion.com/) and move, copy or link the folder named LeapSDK into the project directory, the following example is of symlinking:

```bash
ln -s ~/Path/To/SDK/LeapSDK ./

```

Then install the PortAudio, PortMIDI, FreeGLUT and GLEW libraries.

### Ubuntu, Mint and other Debian derivatives


```bash
sudo apt-get install libportaudio-dev libportmidi-dev freeglut3-dev libglew-dev
```


### On MacOSX with homebrew

```bash
brew install portaudio homebrew/X11/freeglut glew
```

Unfortunately portmidi isn't packaged for homebrew which means you will have to download, build and install it on your own.


Building
--------

Now you're ready to build the project:

``` bash
cd build
cmake ..
make
```

If you don't want to compile the project with make you can specify the type of project files CMake should generate with the -G flag. Use ```cmake --help``` to see which generators are available.


Interaction
===========
1. An open hand with the palm facing downwards indicates idleness, nothing happens.

2. A hand turned up side down opens the context menu.

2. Absolute position of the palm of the hand. This is the position used to modify the tone and also to navigate menus. This information is trivially retrieved from the SDK.

3. Closing the hand and only pointing with the index finger plays a note.

4. Closing the fingers completely into a fist records the sound.


Developer notes
===============
If you are working on shaders or models, note that CMake won't copy these folders into the destination directory if the project was up to date, i.e. nothing had to be compiled. So you have to modify a _source code_ file for the models and shaders to be copied.
