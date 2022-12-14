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

## Expected Result
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
In the example above, 9 lines (laps) were necessary to move the 12 ants from start to end.

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
The size of the map must be specified as below:
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

## Viewer
A unique visualisator "Visu-Hex" has been developed for this project.  
This program has the particularity to be created with the Python language.  

The following packages must be installed on your system before to use the visualisator:  
- python3
- pip3

If necessary, you can use the "Homebrew" package manager to install them.  
Homebrew was originally designed to simplify the installation process on MacOs (indeed, there is a majority of Mac at 42).  
The use of Homebrew is facultative as you can install "python" and "pip3" on your own way, depending of your OS.  
```
brew install python
brew install pip3
```

Then, use the python3 official package manager "pip3" to install the "pygame" module:
```
pip3 install pygame
```

You can now combine the "Visu-Hex" with the "lem-in" program:

```
./lem-in < maps/valid/subject7 | python3 src/visu/visu-hex.py -py3
```

**Tips:**  
- Use [SPACE] key to see the ants moving in live!
- Hold the Left-Click (Mouse) on a room to change its position.
- Use [F] key to enable the Newton mode, reorganizing automatically the nodes in live with a funny effect!
- Use [S] key to enable the score, displaying the number of laps in live!
- Use the Scroll Wheel Mouse to change the size of the rooms.

## 3rd-party Viewer
A special option has been implemented to make our program compatible with external graph viewer.  

Use the '-v' option to generate a ".DOT" file, compatible for example with "Graphviz":  
```
./lem-in -v < maps/valid/subject7
```

Graphviz needs to be installed on your system:
```
brew install graphviz
```

- with small map, use "neato" to maintain the original position of the rooms:
```
make neato
```

- with big map, use "sfdp" to position automatically the rooms:
```
make sfdp
```

## MAN (complete user manual)
```
./lem-in -h
```

## Screenshots
Complete output for the example above  
![Capture d’écran du 2022-11-25 18-24-30](https://user-images.githubusercontent.com/52746061/204032877-06f854d4-a0e2-4eda-88ed-6286ce5cea8e.png)  
Using "Visu-Hex" viewer for the example above (rooms placed manually)  
![Capture d’écran du 2022-11-25 22-52-02](https://user-images.githubusercontent.com/52746061/204058410-64525f2c-f73a-4473-839d-1b8273677f58.png)  
Using "Visu-Hex" viewer for the example above (Newton mode enabled)  
![Capture d’écran du 2022-11-26 00-16-48](https://user-images.githubusercontent.com/52746061/204062627-ef93284b-8bec-49a3-b92b-89aded5085a7.png)  
Using "Graphviz" viewer for the example above (neato)  
![neato-subject7](https://user-images.githubusercontent.com/52746061/204062210-c243ea72-f919-457a-9f5f-4148e02c7ff7.png)  
Using "Graphviz" viewer for the example above (sfdp)  
![sfdp-subject7](https://user-images.githubusercontent.com/52746061/204062428-e2da07d5-9c04-4605-9146-65ad7a97529d.png)  
Using "Visu-Hex" viewer with a map generated randomly (size flow-thousand)  
![capture2](https://user-images.githubusercontent.com/52746061/204062920-acbe1bb9-8838-427f-af70-9695c59e4d7f.png)  
Using "Visu-Hex" viewer with a map generated randomly (size flow-thousand, Newton mode enabled)  
![capture1](https://user-images.githubusercontent.com/52746061/204061826-e853f51d-c8a7-41de-9bec-e176bdeced0f.png)  
Using "Graphviz" viewer with a map generated randomly (size flow-thousand, sfdp)  
![capture3](https://user-images.githubusercontent.com/52746061/204063433-2e0e51d0-df08-4780-adeb-5d122bafa667.png)

## Notes
To reach the highest level of optimization required in term of number of lines (laps), I had to implement a BFS algorithm.  
For a same map (as in the example above), the best combination of paths can change in function of the number of ants.  
To handle such cases, I also had to implement a Superposition algorithm which consist of comparing the results of various BFS using different initial settings, for example with a increased minimal flow.

## Keywords
Graph theory  
Breadth-First Search algorithm (BFS)
