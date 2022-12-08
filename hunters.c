#include "defs.h"

/*
Function: initHunter
Purpose: This function initializes a hunter with the given parameters
in/out: The function takes in several parameters specifying the hunter's properties (name, fear level, boredom level, current room, type of evidence device, and ID), and returns two pointers to allocated memory for the hunter's notebook and the HunterType structure representing the hunter.
in: The function takes in seven parameters: a string containing the hunter's name, an integer representing the hunter's fear level, an integer representing the hunter's boredom level, a pointer to a RoomType structure representing the hunter's current room, a value of the EvidenceClassType enumeration representing the type of evidence device the hunter has, a double pointer to an EvidenceLinkedList structure where the hunter's notebook will be stored, and a double pointer to a HunterType structure where the hunter will be stored.
out: The function does not have any output parameters.
return: The function returns two pointers to allocated memory for the hunter's notebook and the HunterType structure representing the hunter.
*/
void initHunter(char *name, int fear, int boredom, RoomType *currRoom, EvidenceClassType device, EvidenceLinkedList **notebook, HunterType **hunter, int id)
{
    *notebook = (EvidenceLinkedList *)calloc(1, sizeof(EvidenceLinkedList));
    (*notebook)->head = NULL;
    
    *hunter = (HunterType *)calloc(1, sizeof(HunterType));

    (*hunter)->id = id;
    strcpy((*hunter)->name, name);
    (*hunter)->boredom = boredom;
    (*hunter)->currRoom = currRoom;
    (*hunter)->device = device;
    (*hunter)->notebook = *notebook;
}

/*
Function: enoughEvidence
Purpose: This function determines whether a hunter has collected at least one piece of each of the three types of evidence required to capture the ghost (EMF readings, temperature readings, and sound recordings)
in/out: The function takes in a pointer to a HunterType structure representing the hunter, and returns an integer indicating whether the hunter has collected enough evidence (1) or not (0).
in: The only parameter is a pointer to a HunterType structure representing the hunter.
out: The function does not have any output parameters.
return: The function returns an integer indicating whether the hunter has collected enough evidence (1) or not (0). 
*/
int enoughEvidence(HunterType* theHunter){
    int emf=0;//0
    int temp=0;//1
    int finger=0;//2
    int sound=0;//3
    int counter=0;
    EvidenceNodeType* curr = theHunter->notebook->head;
    while(curr!=NULL){
        if(curr->evidence->evidenceType==0) emf++;
        else if(curr->evidence->evidenceType==1) temp++;
        else if(curr->evidence->evidenceType==2) finger++;
        else if(curr->evidence->evidenceType==3) sound++;
        curr = curr->next;
    }
    if(emf>=1) counter++;
    if(temp>=1) counter++;
    if(finger>=1) counter++;
    if(sound>=1) counter++;

    if(counter >=3) return 1;

    return 0;
}

/*
Function: enoughE
Purpose: This function determines whether a hunter has collected at least one piece of each of the three types of evidence required to capture the ghost (EMF readings, temperature readings, and sound recordings). If the hunter has collected enough evidence, the function sets the game_over flag in the BuildingType structure to 1 and records the hunter's ID in the enoughEvidence field.
in/out: The function takes in a pointer to a HunterType structure representing the hunter, and updates the game_over flag and enoughEvidence field in the BuildingType structure if the hunter has collected enough evidence.
in: The only parameter is a pointer to a HunterType structure representing the hunter.
out: The game_over flag and enoughEvidence field in the BuildingType structure are updated if the hunter has collected enough evidence.
return: The function always returns 0.
*/
int enoughE(HunterType* theHunter){
    int enough = enoughEvidence(theHunter);
    if(enough == 1){
        theHunter->building->game_over = 1;
        theHunter->building->enoughEvidence = theHunter->id;
    }
    return 0;
}

/*
Function: hunterscared
Purpose: This function determines whether a hunter is scared, and if so, increments the count of scared hunters in the building, removes the hunter from their current room, and prints a message indicating that the hunter has left
in/out: The function takes in a pointer to a HunterType structure representing the hunter, and updates the count of scared hunters in the building, the current room's array of hunters, and prints a message.
in: The only parameter is a pointer to a HunterType structure representing the hunter.
out: The count of scared hunters in the building, the current room's array of hunters, and a message are updated.
return: The function does not return a value.
*/
void hunterscared(HunterType* theHunter){
    if(theHunter->fear >= 100) {
        theHunter->building->huntersScared++;
        theHunter->currRoom->currHunters[theHunter->id] = NULL;
        printf("%s has ran away in fear.\n", theHunter->name);
    }
}

/*
Function: hunterBored
Purpose: This function determines whether a hunter is bored, and if so, increments the count of bored hunters in the building, removes the hunter from their current room, and prints a message indicating that the hunter has left
in/out: The function takes in a pointer to a HunterType structure representing the hunter, and updates the count of bored hunters in the building, the current room's array of hunters, and prints a message.
in: The only parameter is a pointer to a HunterType structure representing the hunter.
out: The count of bored hunters in the building, the current room's array of hunters, and a message are updated.
return: The function does not return a value. 
*/
void hunterBored(HunterType* theHunter){
    if(theHunter->boredom <= 0) {
        theHunter->building->huntersBored++;
        theHunter->currRoom->currHunters[theHunter->id] = NULL;
        printf("%s got bored and left.\n", theHunter->name);
    }
}

/*
Function: decreaseHunterBoredom
Purpose: This function decreases a hunter's boredom level by 1
in/out: The function takes in a pointer to a HunterType structure representing the hunter, and updates the hunter's boredom level.
in: The only parameter is a pointer to a HunterType structure representing the hunter.
out: The hunter's boredom level is decreased by 1.
return: The function does not return a value.
*/
void decreaseHunterBoredom(HunterType *theHunter)
{
    theHunter->boredom--;
}

/*
Function: resetHunterBoredom
Purpose: This function resets a hunter's boredom level to the maximum boredom level
in/out: The function takes in a pointer to a HunterType structure representing the hunter, and updates the hunter's boredom level.
in: The only parameter is a pointer to a HunterType structure representing the hunter.
out: The hunter's boredom level is reset to the maximum boredom level.
return: The function does not return a value.
*/
void resetHunterBoredom(HunterType *theHunter)
{
    theHunter->boredom = BOREDOM_MAX;
}

/*
Function: increaseHunterFear
Purpose: This function increases a hunter's fear level by 1
in/out: The function takes in a pointer to a HunterType structure representing the hunter, and updates the hunter's fear level.
in: The only parameter is a pointer to a HunterType structure representing the hunter.
out: The hunter's fear level is increased by 1.
return: The function does not return a value.
*/
void increaseHunterFear(HunterType *theHunter)
{
    theHunter->fear++;
}

/*
Function: hunterNear
Purpose: This function determines whether a hunter is alone in a room or not
in/out: The function takes in a pointer to a HunterType structure representing the hunter, and returns an integer indicating whether the hunter is alone in the room (1) or not (0).
in: The only parameter is a pointer to a HunterType structure representing the hunter.
out: The function does not have any output parameters.
return: The function returns an integer indicating whether the hunter is alone in the room (1) or not (0).
*/
int hunterNear(HunterType *theHunter)
{
    int isAlone = 0;
    for (int i = 0; i < 4; i++){
        if(theHunter->currRoom->currHunters[i]!=NULL){
            isAlone++;
            if(isAlone > 2) {return 0;}
        }
    }
    return 1;
}

/*
Function: ghostNear
Purpose: This function increases a hunter's fear level if they are in the same room as a ghost
in/out: The function takes in a pointer to a HunterType structure representing the hunter. The hunter's fear level is increased if they are in the same room as a ghost.
in: The only parameter is a pointer to a HunterType structure representing the hunter.
out: The hunter's fear level is increased if they are in the same room as a ghost.
return: The function does not return a value.
*/
void ghostNear(HunterType *theHunter)
{
    if (theHunter->currRoom->ghost != NULL)
    {
        increaseHunterFear(theHunter);
        resetHunterBoredom(theHunter);
    }
}

/*
Function: loadHunters
Purpose: This function prompts the user to enter the names of four hunters, and initializes the hunters with the entered names and other given parameters
in/out: The function takes in a pointer to a BuildingType structure, and updates the structure's array of hunters and the linked list of rooms with the newly initialized hunters.
in: The only parameter is a pointer to a BuildingType structure.
out: The BuildingType structure's array of hunters and the linked list of rooms are updated with the newly initialized hunters.
return: The function does not return a value.
*/
void loadHunnters(BuildingType *building)
{
    int counter = 0;
    while (counter < 4)
    {
        EvidenceLinkedList *notebook;
        HunterType *hunter;
        char name[MAX_STR] = {0};
        enterName(name, counter + 1);
        initHunter(name, FEAR_RATE, BOREDOM_MAX, building->MasterRooms.head->room, counter, &notebook, &hunter, counter);
        building->MasterRooms.head->next->room->currHunters[counter] = hunter;
        building->hunters[counter] = hunter;
        building->hunters[counter]->building = building;
        counter++;
    }
}

/*
Function: enterName
Purpose: This function prompts the user to enter the name of a hunter, and reads the user's input into a string
in/out: The function takes in a pointer to a string where the hunter's name will be stored, and an integer representing the hunter's index. The string is updated with the user's input.
in: The first parameter is a pointer to a string where the hunter's name will be stored. The second parameter is an integer representing the hunter's index.
out: The string is updated with the user's input.
return: The function does not return a value.
*/
void enterName(char *name, int x)
{
    while (1)
    {
        printf("Please enter the name of Hunter %d: ", x);
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;
        if (strlen(name) != 0)
        {
            break;
        }
    }
}

/*
Function: moveHunter
Purpose: This function moves a hunter from their current room to a randomly selected connected room, if that room is not already full
in/out: The function takes in a pointer to a HunterType structure representing the hunter to be moved, and an integer representing the hunter's index in the current room's array of hunters. The hunter's current room and the selected room's array of hunters are updated to reflect the hunter's movement.
in: The first parameter is a pointer to a HunterType structure representing the hunter to be moved. The second parameter is an integer representing the hunter's index in the current room's array of hunters.
out: The hunter's current room and the selected room's array of hunters are updated to reflect the hunter's movement.
return: The function does not return a value.
*/
void moveHunter(HunterType *theHunter, int x)
{   
    decreaseHunterBoredom(theHunter);
    int size = theHunter->currRoom->connectedRooms->size;
    int rand;
    if (size == 1)
    {
        rand = 0;
    }
    else
    {
        rand = randInt(0, size);
    }
    RoomNodeType *curr = theHunter->currRoom->connectedRooms->head;
    RoomType *prev = theHunter->currRoom;

    int counter = 0;
    while (curr != NULL && rand != counter)
    {
        curr = curr->next;
        counter++;
    }
    if(sem_trywait(&curr->room->mutexR) == 0){
        printf("%s moved from %s to %s.\n", theHunter->name, theHunter->currRoom->name, curr->room->name);
        
        theHunter->currRoom->currHunters[x] = NULL;
        theHunter->currRoom = curr->room;
        curr->room->currHunters[x] = theHunter;
        
        sem_post(&prev->mutexR);
    }
}

/*
Function: takeEvidence
Purpose: This function removes a piece of evidence from a linked list of evidence in a room, and adds it to another linked list of evidence in a hunter's notebook and a linked list of collected evidence in a building
in/out: The function takes in pointers to EvidenceLinkedList structures representing the room where the evidence is currently located, the hunter's notebook where the evidence will be moved, and a BuildingType structure containing a linked list of collected evidence. The linked lists are updated to reflect the removal and addition of the evidence.
in: The first parameter is a pointer to the EvidenceLinkedList structure representing the room where the evidence is currently located. The second parameter is a pointer to the EvidenceLinkedList structure representing the hunter's notebook where the evidence will be moved. The third parameter is an integer representing the ID of the evidence to be taken. The fourth parameter is a pointer to the BuildingType structure containing the linked list of collected evidence.
out: The linked lists are updated to reflect the removal and addition of the evidence.
return: The function does not return a value.
*/
void takeEvidence(EvidenceLinkedList *room, EvidenceLinkedList *hunter, int id, BuildingType* building)
{
    EvidenceNodeType *curr = room->head;
    EvidenceNodeType *prev = NULL;

    while (curr != NULL && curr->evidence->id != id)
    {
        prev = curr;
        curr = curr->next;
    }

    // If the item was not found, do nothing.
    if (curr == NULL) return;

    // Remove the item from the room's linked list.
    if (prev == NULL)
    {
        room->head = curr->next;
    }
    else
    {
        prev->next = curr->next;
    }

    // Allocate memory for a new node and add the item to the hunter's notebook.
    EvidenceNodeType *node = (EvidenceNodeType *)calloc(1, sizeof(EvidenceNodeType));
    node->evidence = curr->evidence;
    if(hunter->head == NULL){
        node->next = NULL;
    } else {
        node->next = hunter->head;
    }
    hunter->head = node;

    EvidenceNodeType *node1 = (EvidenceNodeType *)calloc(1, sizeof(EvidenceNodeType));
    node1->evidence = curr->evidence;
    if(building->collectedEvidence->head == NULL){
        node1->next = NULL;
    } else {
        node1->next = building->collectedEvidence->head;
    }
    building->collectedEvidence->head = node1;

    // Deallocate the memory for the original node.
    free(curr);
}

/*
Function: checkRoomEvidence
Purpose: This function allows a HunterType to collect evidence from a BuildingType if it is present in the current room.
in/out: The function takes in a pointer to a HunterType and a pointer to a BuildingType and returns nothing.
in: theHunter - a pointer to the HunterType that is collecting evidence 
    building - a pointer to the BuildingType from which the evidence is being collected
return: None
*/
void checkRoomEvidence(HunterType *theHunter, BuildingType* building)
{
    EvidenceNodeType *curr = theHunter->currRoom->evidence->head;
    int id;
    int found = 0;
    if (curr == NULL)
    {
        printf("%s ", theHunter->name);
        StandardEvidencePrint(1);
        decreaseHunterBoredom(theHunter);
    }
    else
    {
        while (curr != NULL)
        {
            if (curr->evidence->evidenceType == theHunter->device)
            {
                id = curr->evidence->id;
                if (curr->next == NULL)
                {
                    takeEvidence(theHunter->currRoom->evidence, theHunter->notebook, id, building);
                    found = 1;
                    break;
                }
                else
                {
                    curr = curr->next;
                    takeEvidence(theHunter->currRoom->evidence, theHunter->notebook, id, building);
                    found = 1;
                }
            }
            else
            {
                curr = curr->next;
            }
        }
        if (found == 0)
        {   
            printf("%s ", theHunter->name);
            StandardEvidencePrint(1);
            decreaseHunterBoredom(theHunter);
        }
        else
        {   
            switch (theHunter->device)
            {
            case 0:
                printf("%s has collected EMF evidence from the %s.\n", theHunter->name, theHunter->currRoom->name);
                break;
            case 1:
                printf("%s has collected TEMPERATURE evidence from the %s.\n", theHunter->name, theHunter->currRoom->name);
                break;
            case 2:
                printf("%s has collected FINGERPRINTS from the %s.\n", theHunter->name, theHunter->currRoom->name);
                break;
            case 3:
                printf("%s has collected SOUND evidence from the %s.\n", theHunter->name, theHunter->currRoom->name);
                break;
            }
            resetHunterBoredom(theHunter);
        }
    }
}

/*
Function: copyAllEvidence
Purpose: This function copies all of the evidence from one linked list to another
in/out: The function takes in two pointers to EvidenceLinkedList structures, and updates the second linked list with the evidence from the first
in: The first parameter is a pointer to the EvidenceLinkedList structure that contains the evidence to be copied. The second parameter is a pointer to the EvidenceLinkedList structure where the copied evidence will be stored.
out: The second linked list is updated with the evidence from the first.
return: The function does not return a value.
*/
void copyAllEvidence(EvidenceLinkedList *hunterS, EvidenceLinkedList *hunterR)
{
    EvidenceNodeType *hsCurr = hunterS->head;

    while (hsCurr != NULL)
    {
        EvidenceNodeType *new = (EvidenceNodeType *)calloc(1, sizeof(EvidenceNodeType));
        new->evidence = hsCurr->evidence;
        new->next = NULL;

        if (hunterR == NULL)
        {
            hunterR->head = new;
        }
        else
        {
            new->next = hunterR->head;
            hunterR->head = new;
        }
        hsCurr = hsCurr->next;
    }
}

/*
Function: copyEvidence
Purpose: This function copies a single piece of evidence from one linked list to another, if it is not already present in the second linked list
in/out: The function takes in a pointer to an EvidenceNodeType structure containing the evidence to be copied, and a pointer to the EvidenceLinkedList structure where the copied evidence will be stored. The second linked list is updated with the evidence from the first if it is not already present.
in: The first parameter is a pointer to an EvidenceNodeType structure containing the evidence to be copied. The second parameter is a pointer to the EvidenceLinkedList structure where the copied evidence will be stored.
out: The second linked list is updated with the evidence from the first if it is not already present.
return: The function does not return a value.
*/
void copyEvidence(EvidenceNodeType *evidenceNode, EvidenceLinkedList *hunterR)
{
    EvidenceNodeType *hrCurr = hunterR->head;
    int a = 0;
    while (hrCurr != NULL)
    {
        if (hrCurr->evidence->id == evidenceNode->evidence->id)
        {
            a = 1;
        }
        hrCurr = hrCurr->next;
    }

    if(a == 0){
        EvidenceNodeType *new = (EvidenceNodeType *)calloc(1, sizeof(EvidenceNodeType));
        new->evidence = evidenceNode->evidence;
        new->next = hunterR->head;
        hunterR->head = new;
        return;
    }
}

/*
Function: compareEvidence
Purpose: This function allows one HunterType to share its evidence with another HunterType.
in/out: The function takes in pointers to two HunterType objects and returns nothing.
in: hunterSending - a pointer to the HunterType that is sharing its evidence
    hunterReceiving - a pointer to the HunterType that is receiving the shared evidence
out: None
return: None

*/
void compareEvidence(HunterType *hunterSending, HunterType *hunterReceiving)
{
    decreaseHunterBoredom(hunterSending);
    EvidenceNodeType *hsCurr = hunterSending->notebook->head;
    
    int shared = 0;
    if(hunterSending->notebook!=NULL){
        if (hunterReceiving->notebook->head == NULL)
        {
            copyAllEvidence(hunterSending->notebook, hunterReceiving->notebook);
            shared = 1;
        }
        else
        {
            while (hsCurr != NULL)
            {
                copyEvidence(hsCurr, hunterReceiving->notebook);
                shared = 1;
                hsCurr = hsCurr->next;
            }
        }
        if (shared == 1)
        {
            printf("%s has shared GHOSTLY EVIDENCE with %s.\n", hunterSending->name, hunterReceiving->name);
        }
    } else {
        printf("%s has no evidence to share with %s.\n", hunterSending->name, hunterReceiving->name);
    }
}

/*
Function: hunterControl
Purpose: This function controls the actions of a HunterType in a BuildingType, such as moving, looking for evidence, or comparing evidence with other hunters.
in/out: The function takes in a pointer to a HunterType and a pointer to a BuildingType and returns nothing.
in: theHunter - a pointer to the HunterType whose actions are being controlled
    theBuilding - a pointer to the BuildingType in which the HunterType is located
out: None
return: None
*/
void hunterControl(HunterType *theHunter, BuildingType* theBuilding)
{

    /*
    0 is move
    1 is look for evidence
    2 is compare evidence
    */
    if(sem_trywait(&theHunter->currRoom->mutexR)==0){
        ghostNear(theHunter);
        int counter;
        int choice;
        int alone = hunterNear(theHunter);
        if (alone == 1)
        {
            choice = randInt(0, 2);
        }
        else
        {
            choice = randInt(0, 3);
        }
        if (choice == 0)
        {
            moveHunter(theHunter, theHunter->id);
        }
        else if (choice == 1)
        {
            checkRoomEvidence(theHunter,theBuilding);
        }
        else if (choice == 2)
        {
            if(theHunter->notebook->head!=NULL){
                int x = 0;
                while(x == 0){
                    counter = randInt(0, 4);
                    if(theHunter->currRoom->currHunters[counter] != NULL){
                        if (theHunter->currRoom->currHunters[counter]->id != theHunter->id){
                            x = 1;
                        }
                    }
                }
            compareEvidence(theHunter,theHunter->currRoom->currHunters[counter]);
            } else {
                printf("%s had no evidence to share.\n", theHunter->name);
            }
        }
        hunterscared(theHunter);
        hunterBored(theHunter);
        enoughE(theHunter);
        sem_post(&theHunter->currRoom->mutexR);
    }
}

/*
Function: cleanNotebook
Purpose: This function frees the memory allocated for the notebook of a HunterType.
in/out: The function takes in a double pointer to a HunterType and returns nothing.
in: hunter - a double pointer to the HunterType whose notebook is being cleaned
out: None
return: None
*/
void cleanNotebook(HunterType** hunter){
        EvidenceNodeType* curr = (*hunter)->notebook->head;
        EvidenceNodeType* next = NULL;
        while(curr != NULL){
            next = curr->next;
            free(curr);
            curr = next;
        }
        free((*hunter)->notebook);
}
