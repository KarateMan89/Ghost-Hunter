#include "defs.h"

/*
 Function:   initRoomArray
  Purpose:   Initializes the fields of the given RoomArrayType structure. In this case only size.
      out:   RoomArrayType pointer.
   return:   None
*/
void initRoomArray(RoomArrayType* arr){
  arr->size = 0;
}

/*
 Function:   initRoom
  Purpose:   Initializes the fields of the given RoomType structure. Initializes a new GhostListType as one of the fields.
       in:   int for room id.
       in:   char pointer for room name
      out:   RoomType double pointer.
   return:   None
*/
void initRoom(int id, char *name, RoomType **room){
  GhostListType* ghosts = (GhostListType*) calloc(1,sizeof(GhostListType));
  initGhostList(ghosts);
  RoomType* newRoom = (RoomType*) calloc(1,sizeof(RoomType));
  newRoom->id = id;
  strcpy((newRoom->name), name);
  newRoom->ghosts = ghosts;

  *room = newRoom;
}

/*
 Function:   addRoom
  Purpose:   Adds the room r to the back of the array structure in parameter arr.
       in:   RoomType pointer for room to be added.
   in/out:   RoomArrayType double pointer for list.
   return:   None
*/
void addRoom(RoomArrayType* arr, RoomType* r){
  if(arr->size == MAX_ARR){return;}
  arr->elements[arr->size] = r;
  arr->size++;
}

/*
 Function:   printRoom
  Purpose:   Prints the room specified in the room pointer parameter.
       in:   RoomType pointer for room to be printed.
   return:   None
*/
void printRoom(RoomType* room){
  printf("==========================================================================\n");
  printf("|          %32s ( %5d )                    |\n",room->name, room->id);
  printGhosts(room->ghosts, C_FALSE);
  printf("\n\n");
}

/*
 Function:   printRooms
  Purpose:   Prints the rooms in the specified RoomTypeArray pointer arr.
       in:   RoomArrayType pointer for list to be printed.
   return:   None
*/
void printRooms(RoomArrayType* arr){
  if(arr->size == 0){
    printf("ROOM ARRAY IS EMPTY!\n");
    return;
  }
  for(int i = 0; i < arr->size; i++){
    printRoom(arr->elements[i]);
  }
}

/*
 Function:   cleanupRoomArray
  Purpose:   Deallocates the dynamically allocated memory in the given room collection. 
             This includes each room, and each room’s ghosts list and its nodes.
   in/out:   RoomArrayType pointer for the list to be cleaned.
   return:   None
*/
void cleanupRoomArray(RoomArrayType* arr){
  for (int i = 0; i < arr->size; i++){
    cleanupGhostList((arr->elements[i])->ghosts);
    free((arr->elements[i])->ghosts);
    free(arr->elements[i]);
  }
}