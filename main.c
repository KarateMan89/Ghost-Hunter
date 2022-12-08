#include "defs.h"


int main(int argc, char *argv[])
{   
    // Initialize a random seed for the random number generators
    printf("====START GAME====\n");
    srand(time(NULL));

    //create building
    BuildingType building;
    initBuilding(&building);
    //create and connect rooms
    populateRooms(&building);
    //load the ghost
    loadGhost(&building);
    //load the hunters
    printf("\nSELECT HUNTER NAMES\n\n");
    loadHunnters(&building);
    // create threads for hunters and ghost
    pthread_t h1, h2, h3, h4, gh;

    pthread_create(&gh, NULL, ghostFoo, building.theGhost);
    pthread_create(&h1, NULL, hunterFoo, building.hunters[0]);
    pthread_create(&h2, NULL, hunterFoo, building.hunters[1]);
    pthread_create(&h3, NULL, hunterFoo, building.hunters[2]);
    pthread_create(&h4, NULL, hunterFoo, building.hunters[3]);

    pthread_join(gh,NULL);
    pthread_join(h1,NULL);
    pthread_join(h2,NULL);
    pthread_join(h3,NULL);
    pthread_join(h4,NULL);

    printResults(&building);
    cleanBuilding(&building);
    return 0;
}

/*
Function: gameOver
Purpose: This function determines whether the game is over based on the state of the building and the hunters and ghost
in/out: The function takes in a pointer to a BuildingType structure representing the building and returns an integer indicating whether the game is over (1) or not (0)
in: The only parameter is a pointer to a BuildingType structure representing the building.
out: The function does not have any output parameters.
return: The function returns an integer indicating whether the game is over (1) or not (0)
*/
int gameOver(BuildingType* theBuilding){
    if(theBuilding->ghost_bored == 1){
        return 1;
    }else if(theBuilding->huntersScared + theBuilding->huntersBored >= 4){
        return 1;
    }else if(theBuilding->enoughEvidence >= 0){
        return 1;
    }
    return 0;
}

/*
Function: printResults
Purpose: This function prints the results of the game, including which hunter has won, which hunters have left the building due to boredom or fear, and whether the ghost has left the building
in/out: The function takes in a pointer to a BuildingType structure representing the building, and prints the results of the game to the console.
in: The only parameter is a pointer to a BuildingType structure representing the building.
out: The function outputs the results of the game to the console.
return: The function does not return a value.
*/
void printResults(BuildingType* theBuilding){
    printf("====GAME OVER====\n");
    if(theBuilding->ghost_bored == 1){
        printf("The ghost got bored and has left the building.\nThe game is a tie.\n");
    }
        for (int i = 0; i < 4;i++){
                if(theBuilding->hunters[i]->boredom<=0){
                    printf("%s left the building from boredom.\n",theBuilding->hunters[i]->name);
                }
                if(theBuilding->hunters[i]->fear>=100){
                    printf("%s ran away from the building in fear.\n", theBuilding->hunters[i]->name);
                }
        }
    if (theBuilding->huntersScared+theBuilding->huntersBored == 4){
        printf("All the hunters have left the building and the ghost has won.\n");
    }
    if(theBuilding->enoughEvidence > -1){
        printf("%s has found enough evidence and won the game for the hunters.\n", theBuilding->hunters[theBuilding->enoughEvidence]->name);
    }
}

/*
Function: hunterFoo
Purpose: This function is the thread function for a hunter. It updates the hunter's actions and checks if the game is over until the game is over.
in/out: The function takes in a void pointer to the hunter and returns 0 when the game is over.
in: The only parameter is a void pointer to the hunter.
out: The function does not have any output parameters.
return: The function returns 0 when the game is over.
*/
void* hunterFoo(void* h){
    HunterType* hunter = (HunterType*) h;
    int over = 0;
    while(over != 1){
        if(hunter->fear>=100||hunter->boredom<=0){
            break;
        }
        hunterControl(hunter, hunter->building);
        over = gameOver(hunter->building);
        usleep(25000);
    }
    return 0;
}

/*
Function: ghostFoo
Purpose: This function is the thread function for the ghost. It updates the ghost's actions and checks if the game is over until the game is over.
in/out: The function takes in a void pointer to the ghost and returns 0 when the game is over.
in: The only parameter is a void pointer to the ghost.
out: The function does not have any output parameters.
*/
void* ghostFoo(void* gh){
    GhostType* ghost = (GhostType*)gh;
    int over = 0;
    while(over != 1){
        ghostControl(ghost);
        over = gameOver(ghost->building);
        usleep(25000);
    }
    return 0;
}
/*
  Function:  randInt
  Purpose:   returns a pseudo randomly generated number,
             in the range min to (max - 1), inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [min, max-1)
*/
int randInt(int min, int max)
{
    return rand() % (max - min) + min;
}

/*
  Function:  randFloat
  Purpose:   returns a pseudo randomly generated number,
             in the range min to max, inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [0, max-1)
*/
float randFloat(float a, float b)
{
    // Get a percentage between rand() and the maximum
    float random = ((float)rand()) / (float)RAND_MAX;
    // Scale it to the range we want, and shift it
    return random * (b - a) + a;
}
