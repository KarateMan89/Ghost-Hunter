#include "defs.h"
/*
Function: initBuilding
Purpose: Initialize a building by initializing its MasterRooms and collectedEvidence lists, and creating a mutex for synchronization.
in/out: building - a pointer to the BuildingType object to be initialized.
return: none
*/
void initBuilding(BuildingType *building)
{
    initRoomList(&building->MasterRooms);
    EvidenceLinkedList* collectedEvidence = (EvidenceLinkedList*) calloc(1,sizeof(EvidenceLinkedList));
    collectedEvidence->head = NULL;
    building->collectedEvidence = collectedEvidence;
    building->ghost_bored = 0;
    building->game_over = 0;
    building->huntersBored = 0;
    building->huntersScared = 0;
    building->enoughEvidence = -1;
}
/*
Function: appendRoom
Purpose: This function appends a new node to a linked list of rooms.
in/out: The linked list and the new node are passed by reference and can be modified by the function.
return: The function does not return anything. It modifies the linked list and the new node in place.
*/
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

/*
Function: connectRooms
Purpose: This function connects two rooms together by adding a RoomNodeType structure to the linked list of each room.
In/Out: This function takes two pointers to RoomType structures as input and modifies their connected rooms linked lists.
Return: None
*/
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


/*
Function: populateRooms
Purpose: Initialize and populate a linked list of rooms within a BuildingType struct
in/out:
in: pointer to a BuildingType struct to populate
out: none
return: none
*/
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
/*
Function: cleanBuildingRoomList
Purpose: This function cleans up the memory associated with a given list of rooms in a building by freeing the memory allocated to each room and its linked list of connected rooms.
In/Out: This function takes a RoomLinkedList structure as input and frees the memory associated with the rooms and their connected rooms linked lists.
In: A RoomLinkedList structure, MasterRooms, containing a list of rooms in a building.
Out: The memory associated with the rooms and their connected rooms linked lists in MasterRooms is freed.
Return: None.
*/
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

/*
Function: cleanBuildingEvidence
Purpose: This function cleans up the memory occupied by a linked list of evidence collected from a building.
in/out: The linked list of evidence is passed by reference and can be modified by the function.
return: The function does not return anything. It modifies the linked list in place.
*/
void cleanBuildingEvidence(EvidenceLinkedList* collectedEvidence){
        EvidenceNodeType* curr = collectedEvidence->head;
        EvidenceNodeType* next = NULL;
        while(curr != NULL){
            next = curr->next;
            free(curr->evidence);
            free(curr);
            curr = next;
        }
        free(collectedEvidence);
}
/*
Function: cleanBuilding
Purpose: Clean up and free memory for a BuildingType struct and its contained data
in/out: pointer to a BuildingType struct to clean up
return: none
*/
void cleanBuilding(BuildingType* building){
    for (int i = 0; i < 4; i++){
        cleanNotebook(&(building->hunters[i]));
        free(building->hunters[i]);
    }
    cleanBuildingRoomList(building->MasterRooms);
    free(building->theGhost);
    cleanBuildingEvidence(building->collectedEvidence);
}
