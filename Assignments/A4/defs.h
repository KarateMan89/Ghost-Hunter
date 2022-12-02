#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#define C_TRUE     1
#define C_FALSE    0
 
#define MAX_ARR  128
#define MAX_STR   32
 
#define NEXT_ROOM_ID    9001
#define NEXT_GHOST_ID  810310

typedef enum { POLTERGEIST, WRAITH, PHANTOM, BULLIES, OTHER } GhostEnumType;

typedef struct {
  int id;
  char name[MAX_STR];
  struct GhostList *ghosts;
} RoomType;
 
typedef struct {
  int id;
  GhostEnumType ghostType;
  RoomType* room;
  float likelihood;
} GhostType;
 
/*** Define the RoomArrayType here ***/
typedef struct{
  int size;
  RoomType* elements[MAX_ARR];
} RoomArrayType;
 
/*** Define the NodeType here ***/
typedef struct Node{
  GhostType* data;
  struct Node* next;
} NodeType;
 
/*** Complete the GhostListType here ***/
typedef struct GhostList {
  NodeType* head;
  NodeType* tail;
} GhostListType;

/*** Complete the BuildingType here ***/
typedef struct Building {
  GhostListType ghosts;
  RoomArrayType rooms;
} BuildingType;


//ghost.c
void initGhostList(GhostListType* list);
void initGhost(int id, GhostEnumType gt, RoomType* r, float like, GhostType** ghost);
void printGhost(GhostType* ghost);
void printGhosts(GhostListType* list, int ends);
void printByLikelihood(GhostListType* origList, int ends);
void addGhostByLikelihood(GhostListType* list, GhostType* ghost);
void cleanupGhostData(GhostListType* list);
void cleanupGhostList(GhostListType* list);


//room.c
void initRoomArray(RoomArrayType* arr);
void initRoom(int id, char *name, RoomType **room);
void addRoom(RoomArrayType* arr, RoomType* r);
void printRoom(RoomType* room); // added by me 
void printRooms(RoomArrayType* arr);
void cleanupRoomArray(RoomArrayType* arr);

//building.c
void initBuilding(BuildingType* b);
void loadBuildingData(BuildingType *building);
void cleanupBuilding(BuildingType* b);

//main.c
void printMenu(int*);
