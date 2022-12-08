#include "defs.h"

/*
Function: initRoomList
Purpose: Initialize a RoomLinkedList struct with NULL head and tail pointers and a size of 0
in/out:
in: pointer to a RoomLinkedList struct to initialize
out: none
return: none 
*/
void initRoomList(RoomLinkedList *roomList)
{
    roomList->head = NULL;
    roomList->tail = NULL;
    roomList->size = 0;
}

/*
Function: initRoom
Purpose: Initialize a RoomType struct with the given name and set up linked lists for connected rooms and evidence
in/out: pointer to a RoomType struct to initialize, char array containing the name of the room
return: none
*/
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
    sem_t mutexR;
    sem_init(&mutexR, 0 , 1);
    room->mutexR = mutexR;
}

/*
Function: printRooms
Purpose: This function prints the list of rooms in a given roomList, along with the name and size of each room's connected rooms linked list.
In: This function takes a pointer to a RoomLinkedList structure as input and prints the contents of the linked list to the standard output.
Return: None.
*/
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
/*
Function: printConnected
Purpose: Print the names of the rooms in a linked list of rooms
in/out:
in: pointer to a RoomLinkedList struct containing the linked list of rooms
return: none
*/
void printConnected(RoomLinkedList *roomList)
{
    RoomNodeType *curr = roomList->head;
    while (curr != NULL)
    {
        printf("%s\n", curr->room->name);
        curr = curr->next;
    }
}
