# cs302_robot_navigation
# Authors: Daniel Enriquez, Erik Marsh, Gage Christensen
Project specifications: https://www.autonomousrobotslab.com/uploads/5/8/4/4/58449511/cs302-bonus-assignment.pdf

Due Date: 12/6/19

This project simulates a drone that must use occupancy grid mapping to figure out its surroundings.

## Installation instructions
Clone the repository into your computer with the following command:
```console
git clone https://github.com/chrisgrob/cs302_robot_navigation
```
This program requires that the [boost](https://www.boost.org/doc/libs/1_66_0/more/getting_started/unix-variants.html) library be installed somewhere on your computer(if you are a T.A. do not worry about this as boost will be shipped with the repository, simply make the program).

Once boost is installed you must either specify the path where the *contents* of the library are (boost, doc, libs, etc.) **OR** you must place these contents into the /headers/dependencies folder in this project. To avoid being spammed with warnings that relate to the library and not this project, do not place boost into the /headers/include folder.

### Specifying the dependency path
To specify the path, run the following:
```console
echo ~/path/to/my/dependencies > config_path.txt
```
You may specify a new path by running the command again with a different path, and may unset the path by deleting config_path.txt.

### Compiling
To compile the program you may simply run make:
```console
make
```

### Running
You may run the program with:
```console
./main
```
This will output a 1000 by 1000 map with the probability of being taken for each cell.

### Uninstalling
You may delete the compiled binaries and the program by running:
```console
make clean
```
To uninstall the whole program simply delete the entire folder
