# cs302_robot_navigation
# Authors: Daniel Enriquez, Erik Marsh, Gage Christensen
Project specifications: https://www.autonomousrobotslab.com/uploads/5/8/4/4/58449511/cs302-bonus-assignment.pdf

Due Date: 12/6/19

This project simulates a drone that must use occupancy grid mapping to figure out it's surroundings.

## Installation instructions
Clone the repository into your computer with the following command:
```console
myusername:~$ git clone https://github.com/chrisgrob/cs302_robot_navigation
```
This program requires that the [boost](https://www.boost.org/doc/libs/1_66_0/more/getting_started/unix-variants.html) be installed somewhere on your computer After this you must specify the path where boost is installed (If you are a T.A. this will be done for you, and you can just make). This will be the folder in which the *contents* of boost are located (boost, docs, libs, more, etc.).

To specify this path, run the following:
```console
myusername:~$ export DEPENDENCY_PATH=~/path/to/my/dependencies
```
Alternatively, you may put the contents of the boost library into the headers/dependencies folder in your project.

Once this is done, you may compile the program by running make:
```console
myusername:~$ make
```
And you may run the program by running:
```console
myusername:~$ ./main
```

You may delete the compiled binaries and the program by running:
```console
make clean
```
