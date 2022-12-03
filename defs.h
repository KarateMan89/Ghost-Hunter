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
char* devices[] = {
  [EMF] = "EMF",
  [TEMPERATURE] = "TEMPERATURE",
  [FINGERPRINTS] = "FINGERPRITNS",
  [SOUND] = "SOUND"
};
char* ghostNames[] = {
  [POLTERGEIST] = "POLTERGEIST",
  [BANSHEE] = "BANSHEE",
  [BULLIES] = "BULLIES",
  [PHANTOM] = "PHANTOM",
};


typedef struct {
	int id;
	EvidenceClassType evidenceType;
	float value;
} EvidenceType;

typedef struct EvidenceNode{
  EvidenceType* evidence;
  struct EvidenceNode* next;
} EvidenceNodeType;

typedef struct EvidenceList{
	EvidenceNodeType* head;
} EvidenceLinkedList;

typedef struct {
  	char name[MAX_STR];
	struct RoomList* connectedRooms;
	EvidenceLinkedList* evidence;
	struct Hunter* currHunters[MAX_HUNTERS];
	struct Ghost* ghost;
} RoomType;

typedef struct RoomNode{
	RoomType* room;
	struct RoomNode* next;
} RoomNodeType;

typedef struct RoomList{
	RoomNodeType* head;
	RoomNodeType* tail;
	int size;
} RoomLinkedList;

typedef struct Ghost{
	GhostClassType ghostType;
	RoomType* currRoom;
	int boredom;
	int evidenceID;
} GhostType;

typedef struct Hunter{
	char name[MAX_STR];
	int fear;
	int boredom;
	RoomType* currRoom;
	EvidenceClassType device;
	EvidenceLinkedList* notebook;
} HunterType;

typedef struct Building {
	 GhostType* theGhost;
	 RoomLinkedList MasterRooms; 
	 HunterType* hunters[MAX_HUNTERS];
} BuildingType;

void initBuilding(BuildingType* building);
void populateRooms(BuildingType* building);
void initRoomList(RoomLinkedList* rooms);
void initRoom(RoomType* room, char* name);
void printRooms(RoomLinkedList* building);
void printConnected(RoomLinkedList* roomList);
void initEvidence(int id, EvidenceClassType device, float value, EvidenceType** newEvidence);
void initGhost(GhostType** ghost, GhostClassType randomGhost, RoomType* startRoom, int id);
void loadGhost(BuildingType* building);
void moveGhost(GhostType* theGhost);
void addEvidence(EvidenceLinkedList* roomEvidenceList, EvidenceType* newEvidence);
void printRoomEvidence(EvidenceLinkedList* roomEvidence);
void addGhostEvidence(GhostType* theGhost);





int randInt(int, int);          // Generates a pseudorandom integer between the parameters
float randFloat(float, float);  // Generates a pseudorandom float between the parameters
void populateRooms(BuildingType*);   // Populates the building with sample data for rooms
