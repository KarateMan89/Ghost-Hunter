#include "defs.h"

//this simplifies ghost types
char* ghostNames[] = {
  [POLTERGEIST] = "POLTERGEIST",
  [WRAITH] = "WRAITH",
  [PHANTOM] = "PHANTOM",
  [BULLIES] = "BULLIES",
  [OTHER] = "OTHER",
  [7] = "UKNOWN"
};

/*
 Function:   initGhostList
  Purpose:   Initializes both fields of the given list parameter to NULL.
      out:   GhostListType pointer
   return:   None
*/
void initGhostList(GhostListType* list){
  list->head = NULL;
  list->tail = NULL;
}

/*
 Function:   initGhost
  Purpose:   Dynamically allocates memory for a GhostType structure, initializes its fields to the
             given parameters, and “returns” this new structure using the ghost parameter
       in:   int for id.
       in:   GhostEnumType(int) for ghost type.
       in:   RoomType pointer for room.
       in:   Flaot for likelihood.
      out:   GhostType double pointer.
   return:   None
*/
void initGhost(int id, GhostEnumType gt, RoomType* r, float like, GhostType** ghost){
  *ghost = (GhostType*) calloc(1,sizeof(GhostType));
  (*ghost)->id = id;
  (*ghost)->ghostType = gt;
  (*ghost)->room = r;
  (*ghost)->likelihood = like;
}

/*
 Function:   addGhost
  Purpose:   Adds a GhostType directly at the back of the given LinkedList.
   in/out:   GhostListType pointer for the head and tail of the list.
       in:   GhostType pointer for ghost to be added to the LinkedList.
   return:   None
*/
void addGhost(GhostListType* list, GhostType* ghost){
  //allocate memory in the heap for a new node
  NodeType* new = (NodeType*) calloc(1,sizeof(NodeType));
  new->data = ghost;
  new->next = NULL;

  //if linked list is empty
  if(list->head == NULL){
    list->head = new;
    list->tail = new;
  } else {
    list->tail->next = new;
    list->tail = new;
  }
}

/*
 Function:   addGhostByLikelihood
  Purpose:   Adds the ghost to the given list, directly in its correct place, in descending order by likelihood.
   in/out:   GhostListType pointer for the head and tail of the list.
       in:   GhostType pointer for ghost to be added to the LinkedList.
   return:   None
*/
void addGhostByLikelihood(GhostListType* list, GhostType* ghost){
  NodeType* curr = list->head;
	NodeType* prev = NULL;
	NodeType* new = NULL;

  if(list->head == NULL || list->tail->data->likelihood > ghost->likelihood){
    addGhost(list,ghost);
    return;
  }
  //find the insertion point
	while(curr != NULL){
		if(curr->data->likelihood < ghost->likelihood){break;}
		prev = curr;
		curr = curr->next;
	}
  //if found create new node
  new = (NodeType*) calloc(1,sizeof(NodeType));
  new->data = ghost;

  if(prev == NULL){
    list->head = new;
  } else {
    prev->next = new;
  }
  new->next = curr;
}

/*
 Function:   printGhost
  Purpose:   Prints to the screen every field of the given ghost.
       in:   GhostType pointer for ghost to be printed.
   return:   None
*/
void printGhost(GhostType* ghost){
  if(ghost == NULL){printf("GHOST YOU ARE TRYING TO PRINT IS NULL\n");return;}
  char* roomName = calloc (32, sizeof(char));
  char* ghostType = calloc(32,sizeof(char));

  if (ghost->room != NULL){
    strcpy(roomName, ghost->room->name);
  } else {
    strcpy(roomName, "UKNOWN");
  }
  if(ghost->ghostType < 0 || ghost->ghostType > 4){
    strcpy(ghostType, ghostNames[7]);
  } else {
    strcpy(ghostType, ghostNames[ghost->ghostType]);
  }

  printf("| %8d | %11s | %32s | %10.1f |\n", ghost->id, ghostType, roomName, ghost->likelihood);
  printf("--------------------------------------------------------------------------\n");

  free(roomName);
  free(ghostType);
}

/*
 Function:   printGhosts
  Purpose:   Prints every ghost in the given list to the screen, using an existing function. If the ends parameter is set to C_TRUE, then the two
             ghosts at the head and tail of the linked list are printed out a second time, after all the ghosts have been output. 
             If the ends parameter is set to C_FALSE, then the head and tail are not printed a second time at the end.
       in:   GhostListType pointer for the list to be printed.
       in:   int for boolean to be checked.
   return:   None
*/
void printGhosts(GhostListType* list, int ends){
  printf("==========================================================================\n");
  printf("| GHOST ID |    TYPE     |               ROOM               | LIKELIHOOD |\n");
  printf("==========================================================================\n");

  if(list->head == NULL){
    printf("+++++++++++++++++++++++++++++GHOST LIST EMPTY+++++++++++++++++++++++++++++\n");
    return;
  }
  NodeType* curr = list->head;
  while (curr != NULL){
    printGhost(curr->data);
    curr = curr->next;
  }
  if(ends == C_TRUE){
    printGhost(list->head->data);
    printGhost(list->tail->data);
  }
}

/*
 Function:   printByLikelihood
  Purpose:   Prints every ghost in the given list to the screen, in decreasing order by likelihood, reuses an existing function.
       in:   GhostListType pointer for the list to be printed.
       in:   int for boolean to be checked.
   return:   None
*/
void printByLikelihood(GhostListType* origList, int ends){
  GhostListType* temp = (GhostListType*) calloc(1,sizeof(GhostListType));
  initGhostList(temp);
  NodeType* curr = origList->head;

  while(curr != NULL){
    addGhostByLikelihood(temp,curr->data);
		curr = curr->next;
  }

  printGhosts(temp, ends);

  cleanupGhostList(temp);
  free(temp);
}

/*
 Function:   cleanupGhostData
  Purpose:   Traverses the given list and deallocates its data only.
       in:   GhostListType pointer for the list to be cleaned. (only in parameter cause we are not actually changing anything in GhostListType)
   return:   None
*/
void cleanupGhostData(GhostListType* list){
  NodeType* curr = list->head;
	NodeType* next = NULL;

  	while(curr != NULL){
		  next = curr->next;
      free(curr->data);
		  curr = next;
    }
}

/*
 Function:   cleanupGhostList
  Purpose:   Traverses the given list and deallocates its nodes only.
   in/out:   GhostListType pointer for the list to be cleaned.
   return:   None
*/
void cleanupGhostList(GhostListType* list){
  NodeType* curr = list->head;
	NodeType* next = NULL;

    while(curr != NULL){
		  next = curr->next;
      free(curr);
		  curr = next;
    }
}