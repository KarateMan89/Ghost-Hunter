Ghost Hunter Game

Ghost Hunter is a simple game that simulates a group of hunters trying to capture a ghost in a haunted building. The game is implemented using C and pthreads for multithreading.

Building and Running the Game
To build the game, run the following command:

make

This will create an executable file called ghost-hunter. To run the game, use the following command:

./ghost-hunter

Gameplay
At the start of the game, the players are prompted to select names for the four hunters. The ghost is randomly placed in one of the rooms in the building. The game then begins, with the hunters and ghost taking turns to move and perform actions.

The ghost has 3 possible actions, it can either leave evidence in the current room, move to a different room or do nothing. The ghost leaves the game if it becomes bored.

The hunters have three possible actions: they can move to a different room, search the current room for evidence, or use their special device (EMF meter, thermal scanner, fingerprint kit, or audio recorder) to collect evidence. Each hunter has a different special device, and each type of evidence is only detectable by a specific device. If a hunter finds enough evidence (at least three different types), they win the game for the hunters. Hunters leave the game if they become bored or scared.

The game ends when the ghost leaves the building, all the hunters leave the building, or a hunter finds enough evidence to capture the ghost.

Code Structure
The code for the game is organized into the following files:

main.c: Contains the main function and the main game loop.
building.c: Contains functions for creating and managing the building.
ghost.c: Contains functions for controlling the ghost's actions.
hunters.c: Contains functions for controlling the hunters' actions.
evidence.c: Contains functions to manage evidence.
room.c: Contains functions to manage rooms.
