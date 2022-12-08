#include "defs.h"

/*
Function: initGhost
Purpose: Initialize a ghost with a given ghost type, starting room, and evidence ID.
in/out:
- ghost: GhostType** - a pointer to a pointer to a GhostType instance that will be initialized
- randomGhost: GhostClassType - the type of ghost to initialize (e.g. Poltergeist, Specter)
- startRoom: RoomType* - the starting room for the ghost
- id: int - the evidence ID for the ghost

return: void

*/
void initGhost(GhostType **ghost, GhostClassType randomGhost, RoomType *startRoom, int id)
{
    *ghost = (GhostType *)calloc(1, sizeof(GhostType));
    (*ghost)->ghostType = randomGhost;
    (*ghost)->currRoom = startRoom;
    (*ghost)->boredom = BOREDOM_MAX;
    (*ghost)->evidenceID = EVIDENCE_ID;
    (*ghost)->actualEvidence = 0;
}

/*
Function: loadGhost
Purpose: Create a ghost in a random room in a given building.
in/out:
- building: BuildingType* - a pointer to a BuildingType instance representing the building in which the ghost will be created

return: void

*/
void loadGhost(BuildingType *building)
{
    GhostType *ghost;
    int randomGhostType = randInt(0, 4);
    int randomRoom = randInt(1, 12);

    // chooose a random room for the ghost to start
    int counter = 0;
    RoomNodeType *curr = (&building->MasterRooms)->head->next;
    while (curr->next != NULL && counter != randomRoom)
    {
        curr = curr->next;
        counter++;
    }
    RoomType *rD = curr->room;

    // create the ghost
    initGhost(&ghost, randomGhostType, rD, EVIDENCE_ID);
    ghost->currRoom->ghost = ghost;
    building->theGhost = ghost;
    building->theGhost->building = building;
    switch (ghost->ghostType)
    {
    case 0:
        printf("The Ghost is a POLTERGEIST and starts in room %s.\n", building->theGhost->currRoom->name);
        break;
    case 1:
        printf("The Ghost is a BANSHEE and starts in room %s.\n", building->theGhost->currRoom->name);
        break;
    case 2:
        printf("The Ghost is a BULLIES and starts in room %s.\n", building->theGhost->currRoom->name);
        break;     
    case 3:
        printf("The Ghost is a PHANTOM and starts in room %s.\n", building->theGhost->currRoom->name);
        break;    
    }
}

/*
Function: ghostBored
Purpose: Check if the ghost is bored and update the game state accordingly.
in/out:
- theGhost: GhostType* - a pointer to a GhostType instance representing the ghost

return: int - 1 if the ghost is bored, 0 otherwise

*/
int ghostBored(GhostType* theGhost){
    if(theGhost->boredom == 0){
        theGhost->building->ghost_bored = 1;
        return 1;
    }
    return 0;
}



void StandardEvidencePrint(int x)
{
    if (x == 0)
    {
        printf("The Ghost has left standard evidence.\n");
    }
    else
    {
        printf("has collected standard evidence.\n");
    }
}

/*
Function: addGhostEvidence
Purpose:   Adds ghost evidence to a room
in/out:   
in: GhostType*
out:  
return:  none
*/
void addGhostEvidence(GhostType *theGhost)
{
        int type = randInt(0, 3);
        int value;
        switch (theGhost->ghostType)
        {
        case 0: // Leaves ghostly EMF, TEMPERATURE, and FINGERPRINTS
            switch (type)
            {
            case 0: // EMF
                type = 0;
                value = randFloat(4.70, 6.00);
                if (value < 4.90)
                {   
                    StandardEvidencePrint(0);
                    return;
                }
                break;
            case 1: // TEMP
                type = 1;
                value = randFloat(-10.00, 2.00);
                if (value > 0.00)
                {
                    StandardEvidencePrint(0);
                    return;
                }
                break;
            case 2: // FINGER
                type = 2;
                value = randInt(0, 2);
                if (value == 0)
                {
                    StandardEvidencePrint(0);
                    return;
                }
                break;
            }
            break;
        case 1: // Leaves ghostly EMF, TEMPERATURE, and SOUND
            switch (type)
            {
            case 0: // EMF
                type = 0;
                value = randFloat(4.70, 6.00);
                if (value < 4.90)
                {
                    StandardEvidencePrint(0);
                    return;
                }
                break;
            case 1: // TEMP
                type = 1;
                value = randFloat(-10.00, 2.00);
                if (value > 0.00)
                {
                    StandardEvidencePrint(0);
                    return;
                }
                break;
            case 2: // SOUND
                type = 3;
                value = randFloat(65.00, 76.00);
                if (value < 70.00)
                {
                    StandardEvidencePrint(0);
                    return;
                }
                break;
            }
            break;
        case 2: // Leaves ghostly EMF, FINGERPRINTS, and SOUND
            switch (type)
            {
            case 0: // EMF
                type = 0;
                value = randFloat(4.70, 6.00);
                if (value < 4.90)
                {
                    StandardEvidencePrint(0);
                    return;
                }
                break;
            case 1: // FINGER
                type = 2;
                value = randInt(0, 2);
                if (value == 0)
                {
                    StandardEvidencePrint(0);
                    return;
                }
                break;
            case 2: // SOUND
                type = 3;
                value = randFloat(65.00, 76.00);
                if (value < 70.00)
                {
                    StandardEvidencePrint(0);
                    return;
                }
                break;
            }
            break;
        case 3: // Leaves ghostly TEMPERATURE, FINGERPRINTS, and SOUND
            switch (type)
            {
            case 0: // TEMP
                type = 1;
                value = randFloat(-10.00, 2.00);
                if (value > 0.00)
                {
                    StandardEvidencePrint(0);
                    return;
                }
                break;
            case 1: // FINGER
                type = 2;
                value = randInt(0, 2);
                if (value == 0)
                {
                    StandardEvidencePrint(0);
                    return;
                }
                break;
            case 2: // SOUND
                type = 3;
                value = randFloat(65.00, 76.00);
                if (value < 70.00)
                {
                    StandardEvidencePrint(0);
                    return;
                }
                break;
            }
            break;
        }
        theGhost->actualEvidence++;
        // initializes EvidenceType and Adds to the back of the room LinkedListEvidence
        EvidenceType *newEvidence;
        
        initEvidence(theGhost->evidenceID, type, value, &newEvidence);
        switch (newEvidence->evidenceType)
        {
        case 0:
            printf("The Ghost has left EMF ghostly evidence in %s.\n",theGhost->currRoom->name);
            break;
        
        case 1:
            printf("The Ghost has left TEMPERATURE ghostly evidence in %s.\n",theGhost->currRoom->name);
            break;
        case 2:
            printf("The Ghost has left FINGERPRINTS ghostly evidence in %s.\n",theGhost->currRoom->name);
            break;
        case 3:
            printf("The Ghost has left SOUND ghostly evidence in %s.\n",theGhost->currRoom->name);
            break;
        }
        theGhost->evidenceID++;
        addEvidence(theGhost->currRoom->evidence, newEvidence);
}

/*
Function: adjustGhostBoredom
Purpose: adjusts ghosts boredome
in/out:   GhotType pointer 
return: none
*/
void adjustGhostBoredom(GhostType *theGhost)
{
    int alone = ghostAlone(theGhost); 
    if (alone == 1)
    {
        theGhost->boredom = BOREDOM_MAX;
    }
    else
    {
        theGhost->boredom--;
    }
}

/*
Function:   ghostAlone
Purpose:   checks if ghost is alone
in: GhostType pointer
return: none
*/
int ghostAlone(GhostType *theGhost)
{   
    for (int i = 0; i < 4; i++)
    {
        if (theGhost->currRoom->currHunters[i] != NULL)
            {return 1;}
    }
    return 0;
}

/*
Function:   moveGhost
Purpose:   moves ghost from one room to another
in/out:   GhostType pointer
return: none
*/
void moveGhost(GhostType *theGhost)
{           
    int size = theGhost->currRoom->connectedRooms->size;
    int rand = randInt(0, size);

    RoomNodeType *curr = theGhost->currRoom->connectedRooms->head;
    RoomType *prev = theGhost->currRoom;
    int counter = 0;
    while (curr != NULL && rand != counter)
    {
        curr = curr->next;
        counter++;
    }
    if(sem_trywait(&curr->room->mutexR) == 0){

        printf("The Ghost has moved from %s to ",theGhost->currRoom->name);
        theGhost->currRoom->ghost = NULL;

        theGhost->currRoom = curr->room;
        theGhost->currRoom->ghost = theGhost;
        printf("%s.\n", theGhost->currRoom->name);

        sem_post(&prev->mutexR);
    }
}

/*
Function:   ghostControl
Purpose:   main function for decisions of ghost
in/out:  ghostype pointer 
return: none
*/
void ghostControl(GhostType *theGhost)
{
    /*
    //0 do nothing
    //1 leave evidence
    //2 move
    */
    if(sem_trywait(&theGhost->currRoom->mutexR) == 0){
        int choice;
        int bored;
        int alone = ghostAlone(theGhost);
        if (alone == 1)
        {
            choice = randInt(0, 2);
        }
        else
        {
            choice = randInt(0, 3);
        }
        if (choice == 1)
        {
            addGhostEvidence(theGhost); 
        }
        else if (choice == 2)
        {
            moveGhost(theGhost);
        }
        adjustGhostBoredom(theGhost);
        bored = ghostBored(theGhost);
        sem_post(&theGhost->currRoom->mutexR);
    }
}

/*
Function:    cleanRoomList
Purpose:  cleans linked list of evidence in room
in/out:   RoomType pointer
return: none
*/
void cleanRoomList(RoomType* room){
    EvidenceNodeType* currEv = room->evidence->head;
    EvidenceNodeType* nextEv = NULL;
    while(currEv != NULL){
        nextEv = currEv->next;
        free(currEv->evidence);
        free(currEv);
        currEv = nextEv;
    }
    free(room->evidence);

    RoomNodeType* currR = room->connectedRooms->head;
    RoomNodeType* nextR = NULL;
    while(currR != NULL){
        nextR = currR->next;
        free(currR);
        currR = nextR;
    }
    free(room->connectedRooms);
}
