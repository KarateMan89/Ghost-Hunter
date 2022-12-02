#include "defs.h"

int main()
{
  BuildingType* bldg = (BuildingType*) calloc(1,sizeof(BuildingType));
  initBuilding(bldg);

  loadBuildingData(bldg);

  int choice = -1;
  while (choice != 0){
    printMenu(&choice);
    if(choice == 1){
      printRooms(&bldg->rooms);
    }
    else if(choice == 2){
      printGhosts(&bldg->ghosts, C_FALSE);
    }
    else if(choice == 3){
      printByLikelihood(&bldg->ghosts, C_FALSE);
    }
  }
  cleanupBuilding(bldg);
  free(bldg);
  return(0);
}
/*
 Function:   printMenu
  Purpose:   Prints the menu for the program.
      out:   Integer pointer that points to user's choice
   return:   None
*/
void printMenu(int *choice)
{
  int c = -1;
  int numOptions = 3;

  printf("\nMAIN MENU\n");
  printf("  (1) Print rooms\n");
  printf("  (2) Print ghosts\n");
  printf("  (3) Print ghosts by likelihood\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  scanf("%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }
  char a;
  while (c < 0 || c > numOptions) {
    printf("Invalid input. Please enter your selection: ");
    while((a = getchar()) != '\n' && a != EOF);
    scanf("%d", &c);
  }
  
  *choice = c;
}
