#include "defs.h"

/*
TO DO

make it so the ghost can not go to the van
win conditions
multi threading

*/
int main(int argc, char *argv[])
{ 
    srand(time(NULL));
    // srand(2);

    //create building
    BuildingType building;
    initBuilding(&building);
    //create and connect rooms
    populateRooms(&building);
    //load the ghost
    loadGhost(&building);
    //load the hunters
    loadHunnters(&building);

    int x = 1;
    int over = 0;
    for(int i = 0; i < 10000; i++){
        // for(int y = 0; y < 4; y++){
        //     if(strcmp(building.hunters[y]->currRoom->name,"Basement") == 0){
        //         printf("==================IM IN THE BASEMENT===================\n");
        //     }
        //     if(strcmp(building.hunters[y]->currRoom->name,"Garage") == 0){
        //         printf("==================IM IN THE GARAGE===================\n");
        //     }
        //     if(strcmp(building.hunters[y]->currRoom->name,"Kitchen") == 0){
        //         printf("==================IM IN THE KITCHEN===================\n");
        //     }
        // }
        printf("TURN: %d\n", i);
        // for (int x = 0; x < 102;x++){
        //     increaseHunterFear(building.hunters[0]);
        // }
        ghostControl(building.theGhost);
        if(building.hunters[0] != NULL)
            hunterControl(building.hunters[0]);
        if(building.hunters[1] != NULL)
            hunterControl(building.hunters[1]);
        if(building.hunters[2] != NULL)
            hunterControl(building.hunters[2]);
        if(building.hunters[3] != NULL)
            hunterControl(building.hunters[3]);
        over = endersGame(&building);
        if(over == 1){
            break;
        }
    }
    cleanBuilding(&building);
    /*
    +++++++++++++++++++++++++MAIN CONTROL FLOW+++++++++++++++++++++++++++++++++++++++
    */ 
    // // Initialize a random seed for the random number generators
    // srand(time(NULL));
    // // srand(3);
    // //create building
    // BuildingType building;
    // initBuilding(&building);
    // //create and connect rooms
    // populateRooms(&building);
    // //load the ghost
    // loadGhost(&building);
    // //load the hunters
    // loadHunnters(&building);
    // // create threads for hunters and ghost
    // pthread_t h1, h2, h3, h4, gh;

    // GhostType* ghost = building.theGhost;
    // HunterType* hunterOne = building.hunters[0];
    // HunterType* hunterTwo = building.hunters[1];
    // HunterType* hunterThree = building.hunters[2];
    // HunterType* hunterFour = building.hunters[3];
    
    // int huntersGone = 0;
    // int ghostGone = 0;
    // int ghostDiscovered = 0;
    // while(!huntersGone && !ghostGone && !ghostDiscovered){
    //     pthread_create(&gh, NULL, ghostFoo, ghost);
    //     // if(building.hunters[0] != NULL)
    //         pthread_create(&h1, NULL, hunterFoo, hunterOne);
    //     // if(building.hunters[1] != NULL)
    //         pthread_create(&h2, NULL, hunterFoo, hunterTwo);
    //     // if(building.hunters[2] != NULL)
    //         pthread_create(&h3, NULL, hunterFoo, hunterThree);
    //     // if(building.hunters[3] != NULL)
    //         pthread_create(&h4, NULL, hunterFoo, hunterFour);

    //     pthread_join(gh,NULL);
    //     pthread_join(h1,NULL);
    //     pthread_join(h2,NULL);
    //     pthread_join(h3,NULL);
    //     pthread_join(h4,NULL);

    //     // if(1) huntersGone = 1;
    //     // if(1) ghostGone = 1;
    //     // if(1) ghostDiscovered = 1;
    //     // Sleep(1.5);
    // }
/*
+++++++++++++++++++++++++MAIN CONTROL FLOW END+++++++++++++++++++++++++++++++++++++
*/

    // srand(time(NULL));

    // BuildingType building;
    // initBuilding(&building);
    // populateRooms(&building);
    // printRooms(&building.MasterRooms);
    // loadGhost(&building);
    // loadHunnters(&building);
    // int counter = 0;
    // while (counter < 4)
    // {
    //     printf("Hunter %d: %s\n", counter, building.hunters[counter]);
    //     printf("Location: %s\n", building.hunters[counter]->currRoom->name);
    //     counter++;
    // }
    // moveHunter(building.hunters[1], 1);
    // moveHunter(building.hunters[0], 0);
    // while (building.theGhost->currRoom != building.hunters[0]->currRoom)
    // {
    //     moveGhost(building.theGhost);
    // }
    // printf("Hunter %d: %s\n", 1, building.hunters[0]);
    // printf("Location: %s\n", building.hunters[0]->currRoom->name);
    // EvidenceLinkedList *test = building.MasterRooms.head->next->room->evidence;
    // EvidenceType *adding;
    // for (int i = 0; i < 20; i++)
    // {
    //     addGhostEvidence(building.theGhost);
    // }
    // checkRoomEvidence(building.hunters[0]);
    // checkRoomEvidence(building.hunters[1]);
    // compareEvidence(building.hunters[0], building.hunters[1]);
    // compareEvidence(building.hunters[1], building.hunters[0]);
    // printf("Hunter 0:\n");
    // printRoomEvidence(building.hunters[0]->notebook);
    // printf("==================================================\nHunter 1:\n");
    // printRoomEvidence(building.hunters[1]->notebook);

    // moveGhost(building.theGhost);
    // moveGhost(building.theGhost);
    // moveGhost(building.theGhost);
    // for (int i = 0; i < 10;i++){
    //     addGhostEvidence(building.theGhost);}
    // printRoomEvidence(building.theGhost->currRoom->evidence);
    // moveGhost(building.theGhost);
    // moveGhost(building.theGhost);
    // moveGhost(building.theGhost);
    // RoomNodeType* curr = (&building.MasterRooms)->head;
    // while(curr != NULL){
    //     printf("------------------------------------------------------------------\n%s\n", curr->room->name);
    //     printRoomEvidence(curr->room->evidence);
    //     curr = curr->next;
    // }
    return 0;
}

void* hunterFoo(void* h){
    HunterType* hunter = (HunterType*) h;
    
    if(sem_wait(&hunter->mutex) < 0){
        printf("Semaphore wait error.\n");
        exit(1);
    }
    hunterControl(hunter);
    if(sem_post(&hunter->mutex) < 0){
        printf("Semaphore wait error.\n");
        exit(1);
    }
    return 0;
}

void* ghostFoo(void* gh){
    GhostType* ghost = (GhostType*) gh;

    if(sem_wait(&ghost->mutex) < 0){
        printf("Semaphore wait error.\n");
        exit(1);
    }
    ghostControl(ghost);
    if(sem_post(&ghost->mutex) < 0){
        printf("Semaphore wait error.\n");
        exit(1);
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

 int endersGame(BuildingType* building){
    if(building->theGhost->boredom == 0){
        printf("The ghost got bored and has left the building.\nThe is a tie.");
        return 1;
    }
    // we need a way to check if a hunter has all the evidence.
    // array of evidence type if there are 3 types of evidence present they win
    else{

        int count = 0;
        for (int i = 0; i < 4;i++){
            if(building->hunters[i]!=NULL){
                hunterBored(&building->hunters[i]);
            }
            if(building->hunters[i]==NULL){
                count++;
            }
        }
        if (count == 4){
            printf("All the hunters have left.\nThe ghost wins.");
            return 1;
        } 

        count = 0;
        for (int i = 0; i < 4;i++){
            if(building->hunters[i]!=NULL){
                hunterscared(&building->hunters[i]);
            }
            if(building->hunters[i]==NULL){
                count++;
            }
        }
        if (count == 4){
            printf("All the hunters have left.\nThe ghost wins.");
            return 1;
        } 
    }
    int enoughE = 0;
    for(int j = 0; j < 4; j++){
        if(building->hunters[j]!=NULL && building->hunters[j]->notebook!=NULL){
            enoughE = enoughEvidence(building->hunters[j]);
        }
        if(enoughE == 1){
            printf("The hunters have collected enough evidence and have won.");
            return 1;
        }
    }
    return 0;
 }

/*=======================================================================================================
                                             BUILDING.C
=======================================================================================================*/
void initBuilding(BuildingType *building)
{
    initRoomList(&building->MasterRooms);
    sem_t mutex;
    if(sem_init(&mutex,0,1) < 0){
        printf("Semaphore initialization error.");
        exit(1);
    }
    building->mutex = mutex;
}

void appendRoom(RoomLinkedList *list, RoomNodeType *new)
{
    if (list->head == NULL)
    {
        list->head = new;
        list->tail = new;
    }
    else
    {
        list->tail->next = new;
        list->tail = new;
    }
}

void connectRooms(RoomType *x, RoomType *y)
{
    // Allocate memory for a new RoomNodeType structure to link x and y
    RoomNodeType *new = calloc(1, sizeof(RoomNodeType));
    new->room = y;

    // only connects the VAN to the HALLWAY
    if (x->connectedRooms->head == NULL)
    {
        // If the linked list of x is empty, add the new RoomNodeType as the first element
        x->connectedRooms->head = new;
        x->connectedRooms->size++;
        // If the linked list of y is also empty, add a new RoomNodeType to the linked list of y
        if (y->connectedRooms->head == NULL)
        {
            RoomNodeType *previousRoom = calloc(1, sizeof(RoomNodeType));
            previousRoom->room = x;
            y->connectedRooms->head = previousRoom;
            y->connectedRooms->size++;
        }
        // when adding the first room to a room other than the VAN
    }
    else if (x->connectedRooms->tail == NULL)
    {
        // If the linked list of x is not empty but its tail is NULL,
        // add the new RoomNodeType as the second element in the linked list of x
        x->connectedRooms->head->next = new;
        x->connectedRooms->tail = new;
        x->connectedRooms->size++;
        // If the linked list of y is empty, add a new RoomNodeType to the linked list of y
        if (y->connectedRooms->head == NULL)
        {
            RoomNodeType *previousRoom = calloc(1, sizeof(RoomNodeType));
            previousRoom->room = x;
            y->connectedRooms->head = previousRoom;
            y->connectedRooms->size++;
        }
        // when adding to the tail
    }
    else
    {
        // If the linked list of x is not empty and its tail is not NULL,
        // add the new RoomNodeType to the end of the linked list of x
        x->connectedRooms->tail->next = new;
        x->connectedRooms->tail = new;
        x->connectedRooms->size++;
        // If the linked list of y is empty, add a new RoomNodeType to the linked list of y
        if (y->connectedRooms->head == NULL)
        {
            RoomNodeType *previousRoom = calloc(1, sizeof(RoomNodeType));
            previousRoom->room = x;
            y->connectedRooms->head = previousRoom;
            y->connectedRooms->size++;
        }
    }
}

void populateRooms(BuildingType *building)
{


    RoomType *van = calloc(1, sizeof(RoomType));
    initRoom(van, "Van");
    RoomType *hallway = calloc(1, sizeof(RoomType));
    initRoom(hallway, "Hallway");
    RoomType *master_bedroom = calloc(1, sizeof(RoomType));
    initRoom(master_bedroom, "Master Bedroom");
    RoomType *boys_bedroom = calloc(1, sizeof(RoomType));
    initRoom(boys_bedroom, "Boy's Bedroom");
    RoomType *bathroom = calloc(1, sizeof(RoomType));
    initRoom(bathroom, "Bathroom");
    RoomType *basement = calloc(1, sizeof(RoomType));
    initRoom(basement, "Basement");
    RoomType *basement_hallway = calloc(1, sizeof(RoomType));
    initRoom(basement_hallway, "Basement Hallway");
    RoomType *right_storage_room = calloc(1, sizeof(RoomType));
    initRoom(right_storage_room, "Right Storage Room");
    RoomType *left_storage_room = calloc(1, sizeof(RoomType));
    initRoom(left_storage_room, "Left Storage Room");
    RoomType *kitchen = calloc(1, sizeof(RoomType));
    initRoom(kitchen, "Kitchen");
    RoomType *living_room = calloc(1, sizeof(RoomType));
    initRoom(living_room, "Living Room");
    RoomType *garage = calloc(1, sizeof(RoomType));
    initRoom(garage, "Garage");
    RoomType *utility_room = calloc(1, sizeof(RoomType));
    initRoom(utility_room, "Utility Room");

    // Now create a linked list of rooms using RoomNodeType in the Building
    RoomNodeType *van_node = calloc(1, sizeof(RoomNodeType));
    van_node->room = van;
    RoomNodeType *hallway_node = calloc(1, sizeof(RoomNodeType));
    hallway_node->room = hallway;
    RoomNodeType *master_bedroom_node = calloc(1, sizeof(RoomNodeType));
    master_bedroom_node->room = master_bedroom;
    RoomNodeType *boys_bedroom_node = calloc(1, sizeof(RoomNodeType));
    boys_bedroom_node->room = boys_bedroom;
    RoomNodeType *bathroom_node = calloc(1, sizeof(RoomNodeType));
    bathroom_node->room = bathroom;
    RoomNodeType *basement_node = calloc(1, sizeof(RoomNodeType));
    basement_node->room = basement;
    RoomNodeType *basement_hallway_node = calloc(1, sizeof(RoomNodeType));
    basement_hallway_node->room = basement_hallway;
    RoomNodeType *right_storage_room_node = calloc(1, sizeof(RoomNodeType));
    right_storage_room_node->room = right_storage_room;
    RoomNodeType *left_storage_room_node = calloc(1, sizeof(RoomNodeType));
    left_storage_room_node->room = left_storage_room;
    RoomNodeType *kitchen_node = calloc(1, sizeof(RoomNodeType));
    kitchen_node->room = kitchen;
    RoomNodeType *living_room_node = calloc(1, sizeof(RoomNodeType));
    living_room_node->room = living_room;
    RoomNodeType *garage_node = calloc(1, sizeof(RoomNodeType));
    garage_node->room = garage;
    RoomNodeType *utility_room_node = calloc(1, sizeof(RoomNodeType));
    utility_room_node->room = utility_room;

    // Building->MasterRooms might be a linked list structre, or maybe just a node.
    // initRoomList(&building->MasterRooms);
    appendRoom(&building->MasterRooms, van_node);
    appendRoom(&building->MasterRooms, hallway_node);
    appendRoom(&building->MasterRooms, master_bedroom_node);
    appendRoom(&building->MasterRooms, boys_bedroom_node);
    appendRoom(&building->MasterRooms, bathroom_node);
    appendRoom(&building->MasterRooms, basement_node);
    appendRoom(&building->MasterRooms, basement_hallway_node);
    appendRoom(&building->MasterRooms, right_storage_room_node);
    appendRoom(&building->MasterRooms, left_storage_room_node);
    appendRoom(&building->MasterRooms, kitchen_node);
    appendRoom(&building->MasterRooms, living_room_node);
    appendRoom(&building->MasterRooms, garage_node);
    appendRoom(&building->MasterRooms, utility_room_node);

    // Now connect the rooms. It is possible you do not need a separate
    // function for this, but it is provided to give you a starting point.
    connectRooms(van, hallway);
    connectRooms(hallway, master_bedroom);
    connectRooms(hallway, boys_bedroom);
    connectRooms(hallway, bathroom);
    connectRooms(hallway, kitchen);
    connectRooms(hallway, basement);
    connectRooms(basement, basement_hallway);
    connectRooms(basement_hallway, right_storage_room);
    connectRooms(basement_hallway, left_storage_room);
    connectRooms(kitchen, living_room);
    connectRooms(kitchen, garage);
    connectRooms(garage, utility_room);
}

void cleanBuildingRoomList(RoomLinkedList MasterRooms){
    RoomNodeType *curr = MasterRooms.head;
    RoomNodeType *nextRoom = NULL;
    while (curr != NULL){
        nextRoom = curr->next;
        cleanRoomList(curr->room);
        free(curr->room);
        free(curr);
        curr = nextRoom;
    }
    
}

void cleanBuilding(BuildingType* building){
    for (int i = 0; i < 4; i++){
        if(building->hunters[i] != NULL){
            cleanNotebook(&(building->hunters[i]));
            free(building->hunters[i]);
        }
        else{
            free(building->hunters[i]);
        }
    }
    cleanBuildingRoomList(building->MasterRooms);
    free(building->theGhost);
}
/*=======================================================================================================
                                             ROOM.C
=======================================================================================================*/
// initRoom(boys_bedroom, "Boy's Bedroom");
void initRoomList(RoomLinkedList *roomList)
{
    roomList->head = NULL;
    roomList->tail = NULL;
    roomList->size = 0;
}

void initRoom(RoomType *room, char *name)
{
    strcpy(room->name, name);

    RoomLinkedList *roomList = (RoomLinkedList *)calloc(1, sizeof(RoomLinkedList));
    room->connectedRooms = roomList;
    room->connectedRooms->head = NULL;
    room->connectedRooms->tail = NULL;
    room->connectedRooms->size = EVIDENCE_ID;

    EvidenceLinkedList *eList = (EvidenceLinkedList *)calloc(1, sizeof(EvidenceLinkedList));
    room->evidence = eList;
    room->evidence->head = NULL;

    // made this a double pointer because we want to store a pointer to a pointer of
    // the actual ghost, we dont want to allocate new memory to store a new GhostType structure
    // GhostType** noGhost = (GhostType**) calloc(1,sizeof(GhostType*));
    // room->ghost = noGhost;
}

void printRooms(RoomLinkedList *roomList)
{
    RoomNodeType *curr = roomList->head;
    while (curr != NULL)
    {
        printf("-------------------%s----SIZE:%d------------\n", curr->room->name, curr->room->connectedRooms->size);
        printConnected(curr->room->connectedRooms);
        curr = curr->next;
    }
}

void printConnected(RoomLinkedList *roomList)
{
    RoomNodeType *curr = roomList->head;
    while (curr != NULL)
    {
        printf("%s\n", curr->room->name);
        curr = curr->next;
    }
}

/*=======================================================================================================
                                             GHOST.C
=======================================================================================================*/
void initGhost(GhostType **ghost, GhostClassType randomGhost, RoomType *startRoom, int id)
{
    *ghost = (GhostType *)calloc(1, sizeof(GhostType));
    (*ghost)->ghostType = randomGhost;
    (*ghost)->currRoom = startRoom;
    (*ghost)->boredom = BOREDOM_MAX;
    (*ghost)->evidenceID = EVIDENCE_ID;
}

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
    // reference to mutex in building
    building->theGhost->mutex = building->mutex;
}

void StandardEvidencePrint(int x)
{
    if (x == 0)
    {
        printf("The ghost has left standard evidence.\n");
    }
    else
    {
        printf("has collected standard evidence.\n");
    }
}

void addGhostEvidence(GhostType *theGhost)
{
    /*
        calaute type of evidence
        calc valuse of evidence
    */
    int type = randInt(0, 3);
    int value;
    switch (theGhost->ghostType)
    {
    case 0: // Leaves ghostly EMF, TEMPERATURE, and FINGERPRINTS
        switch (type)
        {
        case 0: // EMF
            type = 0;
            value = randFloat(4.70, 5.00);
            if (value < 4.90)
            {   
                StandardEvidencePrint(0);
                return;
            }
            break;
        case 1: // TEMP
            type = 1;
            value = randFloat(-10.00, 1.00);
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
            value = randFloat(4.70, 5.00);
            if (value < 4.90)
            {
                StandardEvidencePrint(0);
                return;
            }
            break;
        case 1: // TEMP
            type = 1;
            value = randFloat(-10.00, 1.00);
            if (value > 0.00)
            {
                StandardEvidencePrint(0);
                return;
            }
            break;
        case 2: // SOUND
            type = 3;
            value = randFloat(65.00, 75.00);
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
            value = randFloat(4.70, 5.00);
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
            value = randFloat(65.00, 75.00);
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
            value = randFloat(-10.00, 1.00);
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
            value = randFloat(65.00, 75.00);
            if (value < 70.00)
            {
                StandardEvidencePrint(0);
                return;
            }
            break;
        }
        break;
    }

    // initializes EvidenceType and Adds to the back of the room LinkedListEvidence
    EvidenceType *newEvidence;
    initEvidence(theGhost->evidenceID, type, value, &newEvidence);
    theGhost->evidenceID++;
    addEvidence(theGhost->currRoom->evidence, newEvidence);
}

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

int ghostAlone(GhostType *theGhost)
{
    for (int i = 0; i < 4; i++)
    {
        if (theGhost->currRoom->currHunters[i] != NULL)
        {
            return 1;
        }
    }
    return 0;
}

void moveGhost(GhostType *theGhost)
{
    int size = theGhost->currRoom->connectedRooms->size;
    int rand;
    if (size == 1)
    {
        rand = 0;
    }
    else
    {
        rand = randInt(0, size - 1);
    }
    RoomNodeType *curr = theGhost->currRoom->connectedRooms->head;

    int counter = 0;
    while (curr != NULL && rand != counter)
    {
        curr = curr->next;
        counter++;
    }
    if(strcmp(curr->room->name,"Van") == 0){
        curr = curr->next->next;
    }
    printf("The Ghost has moved from %s to ",theGhost->currRoom->name);
    theGhost->currRoom->ghost = NULL;
    theGhost->currRoom = curr->room;
    theGhost->currRoom->ghost = theGhost;
    printf("%s.\n", theGhost->currRoom->name);

}

void ghostControl(GhostType *theGhost)
{
    /*
    //0 do nothing
    //1 leave evidence
    //2 move
    */
    int choice;
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
}

void cleanRoomList(RoomType* room){
    EvidenceNodeType* currEv = room->evidence->head;
    EvidenceNodeType* nextEv = NULL;
    while(currEv != NULL){
        nextEv = currEv->next;
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


/*=======================================================================================================
                                             HUNTERS.C
=======================================================================================================*/
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

int enoughEvidence(HunterType* theHunter){
    int emf=0;//0
    int temp=0;//1
    int finger=0;//2
    int sound=0;//3
    int counter=0;
    EvidenceNodeType* curr = theHunter->notebook->head;
    while(curr!=NULL){
        if(curr->evidence->evidenceType==0){
            emf++;
        }else if(curr->evidence->evidenceType==1){
            temp++;
        }else if(curr->evidence->evidenceType==2){
            finger++;
        }else if(curr->evidence->evidenceType==3){
            sound++;
        }
        curr = curr->next;
    }
    if(emf>=1){
        counter++;
    }
    if(temp>=1){
        counter++;
    }
    if(finger>=1){
        counter++;
    }
    if(sound>=1){
        counter++;
    }
    if(counter >=3){
        printf("%s has found enough evidence and won the game.\n", theHunter->name);
        return 1;
    }
    return 0;
}

void hunterscared(HunterType** theHunter){
    if((*theHunter)->fear >=100){
        printf("%s has ran away in fear.\n",(*theHunter)->name);
        (*theHunter)->currRoom->currHunters[(*theHunter)->id] = NULL;
        cleanNotebook(theHunter);

        *theHunter = NULL;
    }
}

void hunterBored(HunterType** theHunter){
    if((*theHunter)->boredom>=100){
        printf("%s got bored and left.\n",(*theHunter)->name);
        (*theHunter)->currRoom->currHunters[(*theHunter)->id] = NULL;
        cleanNotebook(theHunter);
        *theHunter = NULL;
    }
}

void decreaseHunterBoredom(HunterType *theHunter)
{
    theHunter->boredom--;
}

void resetHunterBoredom(HunterType *theHunter)
{
    theHunter->boredom = BOREDOM_MAX;
}

void increaseHunterFear(HunterType *theHunter)
{
    theHunter->fear++;
}

int hunterNear(HunterType *theHunter)
{
    int isAlone = 0;
    for (int i = 0; i < 4; i++){
        if(theHunter->currRoom->currHunters[i]!=NULL){
            isAlone++;
        }
    }
    if(isAlone>2){
        return 0;
    }
    return 1;
}

void ghostNear(HunterType *theHunter)
{
    if (theHunter->currRoom->ghost != NULL)
    {
        increaseHunterFear(theHunter);
        resetHunterBoredom(theHunter);
    }
}

void loadHunnters(BuildingType *building)
{
    /* do some for loop or while loop
     user validation as well ( maybe a separate function)
     and create all our hunters the parameter of this function is
     the buildings array starting address*/

    int counter = 0;
    while (counter < 4)
    {
        EvidenceLinkedList *notebook;
        HunterType *hunter;
        char name[MAX_STR] = {0};
        enterName(name, counter + 1);
        initHunter(name, FEAR_RATE, BOREDOM_MAX, building->MasterRooms.head->room, counter, &notebook, &hunter, counter);
        building->MasterRooms.head->room->currHunters[counter] = hunter;
        building->hunters[counter] = hunter;
        building->hunters[counter]->mutex = building->mutex;
        counter++;
    }
}

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

    int counter = 0;
    while (curr != NULL && rand != counter)
    {
        curr = curr->next;
        counter++;
    }
    printf("%s moved from %s to %s\n", theHunter->name, theHunter->currRoom->name, curr->room->name);
    theHunter->currRoom->currHunters[x] = NULL;
    theHunter->currRoom = curr->room;
    curr->room->currHunters[x] = theHunter;
}

void takeEvidence(EvidenceLinkedList *room, EvidenceLinkedList *hunter, int id)
{
    EvidenceNodeType *curr = room->head;
    EvidenceNodeType *prev = NULL;
    while (curr != NULL)
    {
        if (curr->evidence->id != id)
        {
            prev = curr;
            curr = curr->next;
        }
        else
        {
            if (curr->next == NULL)
            {
                // if notebook is empty
                if (hunter->head == NULL)
                {
                    if (prev == NULL)
                    {
                        room->head = NULL;
                        hunter->head = curr;
                        hunter->head->next = NULL;
                    }
                    else if (prev == room->head)
                    {
                        prev->next = NULL;
                        room->head = prev;
                        hunter->head = curr;
                        hunter->head->next = NULL;
                    }
                    else
                    {
                        prev->next = NULL;
                        hunter->head = curr;
                        hunter->head->next = NULL;
                    }
                }
                else
                {
                    if (prev == NULL)
                    {
                        room->head = NULL;
                        curr->next = hunter->head;
                        hunter->head = curr;
                    }
                    else if (prev == room->head)
                    {
                        prev->next = NULL;
                        curr->next = hunter->head;
                        hunter->head = curr;
                        room->head->next = NULL;
                    }
                    else
                    {
                        prev->next = NULL;
                        curr->next = hunter->head;
                        hunter->head = curr;
                    }
                }
            }
            else if (hunter->head == NULL)
            {
                if (prev == NULL)
                {
                    room->head = curr->next;
                    hunter->head = curr;
                    hunter->head->next = NULL;
                }
                else
                {
                    prev->next = curr->next;
                    hunter->head = curr;
                    hunter->head->next = NULL;
                }
            }
            else
            {
                if (prev == NULL)
                {
                    room->head = curr->next;
                    curr->next = hunter->head;
                    hunter->head = curr;
                }
                else
                {
                    prev->next = curr->next;
                    curr->next = hunter->head;
                    hunter->head = curr;
                }
            }
            break;
        }
    }
}

void checkRoomEvidence(HunterType *theHunter)
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
                    takeEvidence(theHunter->currRoom->evidence, theHunter->notebook, id);
                    found = 1;
                    break;
                }
                else
                {
                    curr = curr->next;
                    takeEvidence(theHunter->currRoom->evidence, theHunter->notebook, id);
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
            printf("%s has collected %s evidence from the %s.\n", theHunter->name, devices[theHunter->device], theHunter->currRoom->name);
            resetHunterBoredom(theHunter);
        }
    }
}

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

void compareEvidence(HunterType *hunterSending, HunterType *hunterReceiving)
{
    decreaseHunterBoredom(hunterSending);
    EvidenceNodeType *hsCurr = hunterSending->notebook->head;
    
    int shared = 0;
    if(hunterSending->notebook!=NULL){
        
    
    if (hunterReceiving->notebook == NULL)
    {
        copyAllEvidence(hunterSending->notebook, hunterReceiving->notebook);
        shared = 1;
    }
    else
    {
        EvidenceNodeType *hrCurr = hunterReceiving->notebook->head;
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
    }}
    else
    {
        printf("%s has no evidence to share with %s.\n", hunterSending->name, hunterReceiving->name);
    }
}

void hunterControl(HunterType *theHunter)
{

    /*
    0 is move
    1 is look for evidence
    2 is compare evidence
    */
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
        checkRoomEvidence(theHunter);
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
            printf("%s had nothing to share.\n", theHunter->name);
        }
    }
}

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
// void addEvidenceTypes(HunterType* theHunter){
//     int contains = 0;
//     for (int i = 0; i < 3;i++){
//         if(theHunter->types[i]==!NULL&&contains==0){
//             theHunter->types[i] = theHunter->notebook->head->evidence->evidenceType;
//         }
//     } 
// }

/*=======================================================================================================
                                             EVIDENCE.C
=======================================================================================================*/

void initEvidence(int id, EvidenceClassType device, float value, EvidenceType **newEvidence)
{
    *newEvidence = (EvidenceType *)calloc(1, sizeof(EvidenceType));
    (*newEvidence)->id = id;
    (*newEvidence)->evidenceType = device;
    (*newEvidence)->value = value;
}

void addEvidence(EvidenceLinkedList *roomEvidenceList, EvidenceType *newEvidence)
{
    EvidenceNodeType *newEvidenceNode = (EvidenceNodeType *)calloc(1, sizeof(EvidenceNodeType));
    newEvidenceNode->evidence = newEvidence;

    if (roomEvidenceList->head == NULL)
    {
        roomEvidenceList->head = newEvidenceNode;
        roomEvidenceList->head->next = NULL;
    }
    else
    {
        newEvidenceNode->next = roomEvidenceList->head;
        roomEvidenceList->head = newEvidenceNode;
    }
}

void printRoomEvidence(EvidenceLinkedList *roomEvidence)
{
    EvidenceNodeType *curr = roomEvidence->head;
    while (curr != NULL)
    {
        printf("EVIDENCE ID: %d DEVICE: %d VALUE: %f\n", curr->evidence->id, curr->evidence->evidenceType, curr->evidence->value);
        curr = curr->next;
    }
}
