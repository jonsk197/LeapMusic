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

Download the [Leap SDK](https://developer.leapmotion.com/) and move, copy or link the folder named LeapSDK into the project directory, the following example is of symlinking:

```bash
ln -s ~/Path/To/SDK/LeapSDK ./

```

Then install the PortAudio library. On Ubuntu and other Debian derivatives it's:

```bash
sudo apt-get install libportaudio-dev
```
On MacOSX with homebrew it's:
```bash
brew install portaudio
```

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

3. The positioning of the fingers. Pressing the index finger against the thumb records a tone. Two fingers touch when the end position of their distal bones are about equal.
