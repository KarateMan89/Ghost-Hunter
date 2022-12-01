#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_STR            64
#define FEAR_RATE           1
#define MAX_FEAR          100
#define MAX_HUNTERS         4
#define USLEEP_TIME     50000
#define BOREDOM_MAX        99
#define EVIDENCE_ID         0

#define C_TRUE 1
#define C_FALSE 0

// You may rename these types if you wish
typedef enum { EMF, TEMPERATURE, FINGERPRINTS, SOUND } EvidenceClassType;
typedef enum { POLTERGEIST, BANSHEE, BULLIES, PHANTOM } GhostClassType;

typedef struct {
  	char name[MAX_STR];
	struct RoomList* connectedRooms;
	// EvidenceLinkedList* evidence;
	// HunterType* currHunters[MAX_HUNTERS];
	// struct GhostType* ghost;
} RoomType;

typedef struct RoomNode{
	RoomType* room;
	struct RoomNode* next;
} RoomNodeType;

typedef struct RoomList{
	RoomNodeType* head;
	RoomNodeType* tail;
} RoomLinkedList;

typedef struct Building {
	//  GhostType theGhost; // statically allocated
	 RoomLinkedList MasterRooms; // contains head and tail of all rooms
	//  HunterType hunters[MAX_HUNTERS];
} BuildingType;

void initBuilding(BuildingType* building);
void populateRooms(BuildingType* building);
void initRoomList(RoomLinkedList* rooms);
void initRoom(RoomType* room, char* name);
void printRooms(RoomLinkedList* building);
void printConnected(RoomLinkedList* roomList);



/*
typedef struct {
	int id;
	EvidenceClassType evidenceType;
	float value;
} EvidenceType;

typedef struct EvidenceNode{
  EvidenceType* data;
  struct EvidenceNode* next;
} EvidenceNodeType;

typedef struct EvidenceList{
	EvidenceNodeType* head;
	EvidenceNodeType* tail;
} EvidenceLinkedList;

//==Ghost
typedef struct {
  EvidenceType *elements;
  int capacity;
  int size;
} NotebookType;
//==Hunter
typedef struct Hunter{
	char name[MAX_STR];
	int fear;
	int boredom;
	struct RoomType* currRoom;
	EvidenceClassType device;
	NotebookType* notebookList;
} HunterType;

typedef struct {
	GhostClassType ghostType;
	RoomType* currRoom;
	int boredom;
} GhostType;
*/








int randInt(int, int);          // Generates a pseudorandom integer between the parameters
float randFloat(float, float);  // Generates a pseudorandom float between the parameters

void populateRooms(BuildingType*);   // Populates the building with sample data for rooms
