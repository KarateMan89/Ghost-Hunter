#include "defs.h"

int main(int argc, char *argv[])
{
    // Initialize a random seed for the random number generators
    srand(time(NULL));

    // You may change this code; this is for demonstration purposes
    BuildingType building;
    initBuilding(&building);
    populateRooms(&building);
    printrooms(&building.MasterRooms);

    return 0;
}
void printrooms(RoomLinkedList* b){
    RoomNodeType *u =b->head; 
    while(u !=NULL){
    printf("-------------------%s----------------\n",u->room->name);
    printconnected(u->room->ConnectedRooms);
    u=u->next;
}}
void printconnected(RoomLinkedList* b){
    RoomNodeType *u =b->head; 
    while(u !=NULL){printf("%s\n",u->room->name);u=u->next;
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
    // GhostType* ghost = (GhostType*) calloc(1,sizeof(GhostType));
    // building->theGhost = ghost;
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
    if(x->ConnectedRooms->head==NULL){
        x->ConnectedRooms->head = new;
        x->ConnectedRooms->tail = new;
        if(y->ConnectedRooms->head ==NULL){
            RoomNodeType* newa = calloc(1,sizeof(RoomNodeType));
            newa->room = x;
            y->ConnectedRooms->head=newa;
            y->ConnectedRooms->tail=newa;
        }
    }else{
        x->ConnectedRooms->tail->next = new;
        x->ConnectedRooms->tail = new;
        if(y->ConnectedRooms->head ==NULL){
            RoomNodeType* newa = calloc(1,sizeof(RoomNodeType));
            newa->room = x;
            y->ConnectedRooms->head=newa;
            y->ConnectedRooms->tail=newa;
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
    initRoomList(&building->MasterRooms);

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

/*=======================================================================================================
                                             ROOM.C
=======================================================================================================*/
// initRoom(boys_bedroom, "Boy's Bedroom");
initRoomList(RoomLinkedList* roomList){
    roomList->head = NULL;
    roomList->tail = NULL;
}
void initRoom(RoomType *room,char* name){
    strcpy(room->name, name);

    RoomLinkedList* roomList = (RoomLinkedList*) calloc (1, sizeof(RoomLinkedList));
    room->ConnectedRooms = roomList;

    // EvidenceLinkedList* eList = (EvidenceLinkedList*) calloc (1, sizeof(EvidenceLinkedList));
    // room->evidence = eList;

    // made this a double pointer because we want to store a pointer to a pointer of
    // the actual ghost, we dont want to allocate new memory to store a new GhostType structure
    // GhostType** noGhost = (GhostType**) calloc(1,sizeof(GhostType*));
    // room->ghost = noGhost;
}