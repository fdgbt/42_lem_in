# 42_Lem_in
This project aims to simulate the course of an ants colony using Graph theory.  
All the ants must move from point A to point B as fast as possible.  
They must consider all differents tubes (paths) and rooms (nodes) inside the colony (network) and intelligently selecting the best options that should avoid any traffic jams.  
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
Quickest way means the solution with the least number of lines.

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
number_of_ants
the_rooms
the_links

Lx-y Lz-w Lr-o [...]
```
- x, z, r represents the ants' numbers (going from 1 to number_of_ants) and y, w, o represents the rooms’ names.

## Screenshots
![Capture d’écran du 2022-11-25 18-24-30](https://user-images.githubusercontent.com/52746061/204032877-06f854d4-a0e2-4eda-88ed-6286ce5cea8e.png)


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

## Viewer

## MAN (complete user manual)


## Notes

## Keywords
Graph theory  
Depth-first search algorithm (DFS)
