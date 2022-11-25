# 42_lem_in
This project aims to simulate the course of an ants colony using Graph theory.  
All the ants must move from point A to point B as fast as possible.  
They must consider all differents tubes (paths) and rooms (nodes) inside the colony (network) and intelligently select the best options that should avoid any traffic jams.  
Indeed, at each simulation lap, ants can move from a room to another using its connected tubes, but each room can contain only one ant at a time.

## Example
![Screenshot 2022-11-25 at 17-22-43 lem-in en pdf](https://user-images.githubusercontent.com/52746061/204024652-6456b5bd-e4c1-4a85-9fff-e72a1ee069c9.png)

The program receive the data describing the ant farm from the standard output in the following format:
- number_of_ants
- the_rooms
- ##commands
- the_links
- #comments

The commands "##start" signals the ant farm’s entrance and "##end" its exit.

```
#comment
12
3 2 2
##start
start 4 0
##end
end 4 6
4 0 4
1 4 2
2 4 4
5 8 2
6 8 4
start-1
3-4
#another comment
2-4
1-5
6-5
end-6
1-2
2-end
3-start
```

## Expected Results
The objective of this project is to find the quickest way to get N ants across the farm.  
Quickest way means the solution with the least number of lines (each lines is resulting from a simulation lap).

At the beginning of the simulation, all the ants are in the room ##start.  
The goal is to bring them to the room ##end with as few turns as possible.  
To be the first to arrive, ants will need to take the shortest path (and that isn’t necessarily the simplest).  
They will also need to avoid traffic jams as well as walking all over their fellow ants.  

Contraints:
- Each room can only contain one ant at a time (except at ##start and ##end which can contain as many ants as necessary).  
- All the ants are in the room ##start at the beginning of the game.
- At each turn, each ant can move only once and through a tube (the room at the receiving end must be empty).  
- At each turn, the program only display on the standard output the ants that moved, respecting the format requested :  
```
Lx-y Lz-w Lr-o [...]
```
- x, z, r represents the ants' numbers (going from 1 to number_of_ants) and y, w, o represents the rooms’ names.

Example:
```
L1-3 L2-1 
L1-4 L3-3 L2-5 L4-1 
L1-2 L3-4 L5-3 L2-6 L4-5 L6-1 
L1-end L3-2 L5-4 L7-3 L2-end L4-6 L6-5 L8-1 
L3-end L5-2 L7-4 L9-3 L4-end L6-6 L8-5 L10-1 
L5-end L7-2 L9-4 L11-3 L6-end L8-6 L10-5 L12-1 
L7-end L9-2 L11-4 L8-end L10-6 L12-5 
L9-end L11-2 L10-end L12-6 
L11-end L12-end 
```

To conclude, the number of lines determines the number of laps taken by the simulation to transfert all the ants from the start room to the end room.  
In the example above, 9 lines (laps) were necessary.

## Install
Create or update the "lem-in" program from sources.

```
make
```

## Reinstall
Recompile completely the program.

```
make re
```

## Clean
Delete object files created during installation.

```
make clean
```

## Uninstall
Delete object files but also the compiled program.  
It will not affect the source code.

```
make fclean
```

## Usage

```
./lem-in < maps/valid/subject7
```

## Map Generator
A map generator is included in the "maps" folder.  
It is an independant program, provided by 42, to generate random map.  
The size of the map must be specified:
- --flow-one
- --flow-ten
- --flow-thousand
- --big
- --big-superposition 

Example:
```
./maps/generator_linux --flow-ten
```
Both programs can be combined to use automatically the random map:
```
./maps/generator_linux --big | ./lem-in
```

## External Viewer
A unique visualisator "Visu-Hex" has been developed for this project.
This program has the particularity to be created with the Python language.  

The following packages must be installed on your system before to use the visualisator: 
- python (python3)
- pip3

If necessary, you can use the "Homebrew" package manager to install them.  
Homebrew was originally designed to simplify the installation process on MacOs (indeed, there is a majority of Mac at 42).
The use of Homebrew is facultative as you can install "python" and "pip3" on your own way, depending of your OS.
```
brew install python
brew install pip3
pip3 install pygame
```

Then, use the python3 official package manager "pip3" to install the "pygame" module:
```
pip3 install pygame
```

Now, you can combine the "Visu-Hex" with "lem-in" program:

```
./lem-in < maps/valid/subject7 | python3 src/visu/visu-hex.py -py3
```

Tip: keep the Left-Click (Mouse) on a room to change its position in live.

## 3rd-party Viewer

## MAN (complete user manual)
```
./lem-in -h
```

## Screenshots
![Capture d’écran du 2022-11-25 18-24-30](https://user-images.githubusercontent.com/52746061/204032877-06f854d4-a0e2-4eda-88ed-6286ce5cea8e.png)

## Notes

## Keywords
Graph theory  
Depth-first search algorithm (DFS)
