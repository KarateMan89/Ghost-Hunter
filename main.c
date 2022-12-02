#include "defs.h"

int main(int argc, char *argv[])
{
    // Initialize a random seed for the random number generators
    srand(time(NULL));

    BuildingType building;
    initBuilding(&building);
    populateRooms(&building);
    printRooms(&building.MasterRooms);
    loadGhost(&building);

    moveGhost(building.theGhost);
    moveGhost(building.theGhost);
    moveGhost(building.theGhost);
    for (int i = 0; i < 10;i++){
        addGhostEvidence(building.theGhost);}
    moveGhost(building.theGhost);
    moveGhost(building.theGhost);
    moveGhost(building.theGhost);



    return 0;
}

void printRooms(RoomLinkedList* roomList){
    RoomNodeType *curr = roomList->head; 
    while(curr !=NULL){
        printf("-------------------%s----SIZE:%d------------\n", curr->room->name, curr->room->connectedRooms->size);
        printConnected(curr->room->connectedRooms);
        curr = curr->next;
    }
}
void printConnected(RoomLinkedList* roomList){
    RoomNodeType* curr = roomList->head; 
    while(curr !=NULL){
        printf("%s\n",curr->room->name);
        curr = curr->next;
    }
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
float randFloat(float a, float b) {
    // Get a percentage between rand() and the maximum
    float random = ((float) rand()) / (float) RAND_MAX;
    // Scale it to the range we want, and shift it
    return random * (b - a) + a;
}

/*=======================================================================================================
                                             BUILDING.C
=======================================================================================================*/
void initBuilding(BuildingType* building){
    initRoomList(&building->MasterRooms);
}

void appendRoom(RoomLinkedList* list, RoomNodeType* new){
    if(list->head == NULL){
        list->head = new;
        list->tail = new;
    } else {
        list->tail->next = new;
        list->tail = new;
    }
}

void connectRooms(RoomType *x, RoomType* y){
    RoomNodeType* new = calloc(1,sizeof(RoomNodeType));
    new->room = y;

    // only connects the VAN to the HALLWAY
    if(x->connectedRooms->head==NULL){
        x->connectedRooms->head = new;
        x->connectedRooms->size++;
        if(y->connectedRooms->head ==NULL){
            RoomNodeType* previousRoom = calloc(1,sizeof(RoomNodeType));
            previousRoom->room = x;
            y->connectedRooms->head=previousRoom;
            y->connectedRooms->size++;
        }
    // when adding the first room to a room other than the VAN
    } else if (x->connectedRooms->tail == NULL){
        x->connectedRooms->head->next = new;
        x->connectedRooms->tail = new;
        x->connectedRooms->size++;
        if(y->connectedRooms->head ==NULL){
            RoomNodeType* previousRoom = calloc(1,sizeof(RoomNodeType));
            previousRoom->room = x;
            y->connectedRooms->head=previousRoom;
            y->connectedRooms->size++;
        }
    // when adding to the tail
    } else {
        x->connectedRooms->tail->next = new;
        x->connectedRooms->tail = new;
        x->connectedRooms->size++;
        if(y->connectedRooms->head ==NULL){
            RoomNodeType* previousRoom = calloc(1,sizeof(RoomNodeType));
            previousRoom->room = x;
            y->connectedRooms->head=previousRoom;
            y->connectedRooms->size++;
        }
    }
}

void populateRooms(BuildingType* building) {
    // First, create each room. Perhaps you want to include more data 
    // in the init parameters?
    RoomType* van = calloc(1, sizeof(RoomType));
    initRoom(van, "Van");
    RoomType* hallway = calloc(1, sizeof(RoomType));
    initRoom(hallway, "Hallway");
    RoomType* master_bedroom = calloc(1, sizeof(RoomType));
    initRoom(master_bedroom, "Master Bedroom");
    RoomType* boys_bedroom = calloc(1, sizeof(RoomType));
    initRoom(boys_bedroom, "Boy's Bedroom");
    RoomType* bathroom = calloc(1, sizeof(RoomType));
    initRoom(bathroom, "Bathroom");
    RoomType* basement = calloc(1, sizeof(RoomType));
    initRoom(basement, "Basement");
    RoomType* basement_hallway = calloc(1, sizeof(RoomType));
    initRoom(basement_hallway, "Basement Hallway");
    RoomType* right_storage_room = calloc(1, sizeof(RoomType));
    initRoom(right_storage_room, "Right Storage Room");
    RoomType* left_storage_room = calloc(1, sizeof(RoomType));
    initRoom(left_storage_room, "Left Storage Room");
    RoomType* kitchen = calloc(1, sizeof(RoomType));
    initRoom(kitchen, "Kitchen");
    RoomType* living_room = calloc(1, sizeof(RoomType));
    initRoom(living_room, "Living Room");
    RoomType* garage = calloc(1, sizeof(RoomType));
    initRoom(garage, "Garage");
    RoomType* utility_room = calloc(1, sizeof(RoomType));
    initRoom(utility_room, "Utility Room");

    // Now create a linked list of rooms using RoomNodeType in the Building
    RoomNodeType* van_node = calloc(1, sizeof(RoomNodeType));
    van_node->room = van;
    RoomNodeType* hallway_node = calloc(1, sizeof(RoomNodeType));
    hallway_node->room = hallway;
    RoomNodeType* master_bedroom_node = calloc(1, sizeof(RoomNodeType));
    master_bedroom_node->room = master_bedroom;
    RoomNodeType* boys_bedroom_node = calloc(1, sizeof(RoomNodeType));
    boys_bedroom_node->room = boys_bedroom;
    RoomNodeType* bathroom_node = calloc(1, sizeof(RoomNodeType));
    bathroom_node->room = bathroom;
    RoomNodeType* basement_node = calloc(1, sizeof(RoomNodeType));
    basement_node->room = basement;
    RoomNodeType* basement_hallway_node = calloc(1, sizeof(RoomNodeType));
    basement_hallway_node->room = basement_hallway;
    RoomNodeType* right_storage_room_node = calloc(1, sizeof(RoomNodeType));
    right_storage_room_node->room = right_storage_room;
    RoomNodeType* left_storage_room_node = calloc(1, sizeof(RoomNodeType));
    left_storage_room_node->room = left_storage_room;
    RoomNodeType* kitchen_node = calloc(1, sizeof(RoomNodeType));
    kitchen_node->room = kitchen;
    RoomNodeType* living_room_node = calloc(1, sizeof(RoomNodeType));
    living_room_node->room = living_room;
    RoomNodeType* garage_node = calloc(1, sizeof(RoomNodeType));
    garage_node->room = garage;
    RoomNodeType* utility_room_node = calloc(1, sizeof(RoomNodeType));
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

void loadGhost(BuildingType* building){
    GhostType* ghost;
    int randomGhostType = randInt(0,4);
    int randomRoom = randInt(0,12);

    //chooose a random room for the ghost to start
    int counter = 0;
    RoomNodeType* curr = (&building->MasterRooms)->head->next;
    while(curr->next !=NULL && counter != randomRoom){
        curr = curr->next;
        counter++;
    }
    RoomType* rD = curr->room;
    
    //create the ghost
    initGhost(&ghost, randomGhostType, rD, EVIDENCE_ID);
    building->theGhost = ghost;
}

/*=======================================================================================================
                                             ROOM.C
=======================================================================================================*/
// initRoom(boys_bedroom, "Boy's Bedroom");
void initRoomList(RoomLinkedList* roomList){
    roomList->head = NULL;
    roomList->tail = NULL;
    roomList->size = 0;
}
void initRoom(RoomType *room,char* name){
    strcpy(room->name, name);

    RoomLinkedList* roomList = (RoomLinkedList*) calloc (1, sizeof(RoomLinkedList));
    room->connectedRooms = roomList;
    room->connectedRooms->head = NULL;
    room->connectedRooms->tail = NULL;

    EvidenceLinkedList* eList = (EvidenceLinkedList*) calloc (1, sizeof(EvidenceLinkedList));
    room->evidence = eList;
    room->evidence->head = NULL;

    // made this a double pointer because we want to store a pointer to a pointer of
    // the actual ghost, we dont want to allocate new memory to store a new GhostType structure
    // GhostType** noGhost = (GhostType**) calloc(1,sizeof(GhostType*));
    // room->ghost = noGhost;
}

/*=======================================================================================================
                                             GHOST.C
=======================================================================================================*/
void initGhost(GhostType** ghost, GhostClassType randomGhost, RoomType* startRoom, int id){
    *ghost = (GhostType*) calloc (1,sizeof(GhostType));
    (*ghost)->ghostType = randomGhost;
    (*ghost)->currRoom = startRoom;
    (*ghost)->boredom = BOREDOM_MAX;
    (*ghost)->evidenceID = EVIDENCE_ID;
}

void addEvidence(EvidenceLinkedList* roomEvidenceList, EvidenceType* newEvidence){
    EvidenceNodeType* newEvidenceNode = (EvidenceNodeType*) calloc (1,sizeof(EvidenceNodeType));
    newEvidenceNode->evidence = newEvidence;
    
    newEvidenceNode->next = roomEvidenceList->head;
    roomEvidenceList->head = newEvidenceNode;
}

void addGhostEvidence(GhostType* theGhost){
    /*
        calaute type of evidence
        calc valuse of evidence
    */
    int type = randInt(0, 2);
    int value;
    switch (theGhost->ghostType)
    {
    case 0: //Leaves ghostly EMF, TEMPERATURE, and FINGERPRINTS
        switch (type)
        {
        case 0: //EMF
            value = randFloat(4.70, 5.00);
            if(value<4.90){
                return;
            }
            break;
        case 1: //TEMP
            value = randFloat(-10.00, 1.00);
            if(value>0.00){
                return;
            }
            break;
        case 2: //FINGER
            value = randInt(0, 1);
            if(value == 0){
                return ;
            }
            break;
        }
        break;
    case 1: //Leaves ghostly EMF, TEMPERATURE, and SOUND
        switch (type)
        {
        case 0: //EMF
            value = randFloat(4.70, 5.00);
            if(value<4.90){
                return;
            }
            break;
        case 1: //TEMP
            value = randFloat(-10.00, 1.00);
            if(value>0.00){
                return;
            }
            break;
        case 2: //SOUND
            value = randFloat(65.00, 75.00);
            if(value<70.00){
                return;
            }
            break;
        }
        break;
    case 2: //Leaves ghostly EMF, FINGERPRINTS, and SOUND
        switch (type)
        {
        case 0: //EMF
            value = randFloat(4.70, 5.00);
            if(value<4.90){
                return;
            }
            break;
        case 1: //FINGER
            value = randInt(0, 1);
            if(value == 0){
                return ;
            }
            break;
        case 2: //SOUND
            value = randFloat(65.00, 75.00);
            if(value<70.00){
                return;
            }
            break;
        }
        break;
    case 3: //Leaves ghostly TEMPERATURE, FINGERPRINTS, and SOUND
        switch (type)
        {
        case 0: //TEMP
            value = randFloat(-10.00, 1.00);
            if(value>0.00){
                return;
            }
            break;
        case 1: //FINGER
            value = randInt(0, 1);
            if(value == 0){
                return;
            }
            break;
        case 2: //SOUND
            value = randFloat(65.00, 75.00);
            if(value<70.00){
                return;
            }
            break;
        }
        break;
    }
    
    //initializes EvidenceType and Adds to the back of the room LinkedListEvidence
    EvidenceType* newEvidence;
    initEvidence(theGhost->evidenceID, type, value, &newEvidence);
    theGhost->evidenceID ++;
    addEvidence(theGhost->currRoom->evidence, newEvidence);
}

void moveGhost(GhostType* theGhost){
    int size = theGhost->currRoom->connectedRooms->size;
    int rand;
    if(size==1){
        rand = 0;
    }else{
        rand = randInt(0,size-1);
    }
    RoomNodeType* curr = theGhost->currRoom->connectedRooms->head;

    int counter = 0;
    while(curr != NULL && rand != counter){
        curr = curr->next;
        counter++;
    }

    theGhost->currRoom = curr->room;
}


/*=======================================================================================================
                                             HUNTERS.C
=======================================================================================================*/


/*=======================================================================================================
                                             EVIDENCE.C
=======================================================================================================*/

void initEvidence(int id, EvidenceClassType device, float value, EvidenceType** newEvidence){
    *newEvidence = (EvidenceType*) calloc (1,sizeof(EvidenceType));
    (*newEvidence)->id = id;
    (*newEvidence)->evidenceType = device;
    (*newEvidence)->value = value;
}