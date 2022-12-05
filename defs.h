#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_STR 64
#define FEAR_RATE 1
#define MAX_FEAR 100
#define MAX_HUNTERS 4
#define USLEEP_TIME 50000
#define BOREDOM_MAX 99
#define EVIDENCE_ID 0

#define C_TRUE 1
#define C_FALSE 0

// You may rename these types if you wish
typedef enum
{
	EMF,
	TEMPERATURE,
	FINGERPRINTS,
	SOUND
} EvidenceClassType;
typedef enum
{
	POLTERGEIST,
	BANSHEE,
	BULLIES,
	PHANTOM
} GhostClassType;
char *devices[] = {
	[EMF] = "EMF",
	[TEMPERATURE] = "TEMPERATURE",
	[FINGERPRINTS] = "FINGERPRITNS",
	[SOUND] = "SOUND"};
char *ghostNames[] = {
	[POLTERGEIST] = "POLTERGEIST",
	[BANSHEE] = "BANSHEE",
	[BULLIES] = "BULLIES",
	[PHANTOM] = "PHANTOM",
};

typedef struct
{
	int id;
	EvidenceClassType evidenceType;
	float value;
} EvidenceType;

typedef struct EvidenceNode
{
	EvidenceType *evidence;
	struct EvidenceNode *next;
} EvidenceNodeType;

typedef struct EvidenceList
{
	EvidenceNodeType *head;
} EvidenceLinkedList;

typedef struct
{
	char name[MAX_STR];
	struct RoomList *connectedRooms;
	EvidenceLinkedList *evidence;
	struct Hunter *currHunters[MAX_HUNTERS];
	struct Ghost *ghost;
} RoomType;

typedef struct RoomNode
{
	RoomType *room;
	struct RoomNode *next;
} RoomNodeType;

typedef struct RoomList
{
	RoomNodeType *head;
	RoomNodeType *tail;
	int size;
} RoomLinkedList;

typedef struct Ghost
{
	GhostClassType ghostType;
	RoomType *currRoom;
	int boredom;
	int evidenceID;
	sem_t mutex;
} GhostType;

typedef struct Hunter
{
	char name[MAX_STR];
	int id;
	int fear;
	int boredom;
	RoomType *currRoom;
	EvidenceClassType device;
	EvidenceLinkedList *notebook;
	sem_t mutex;
} HunterType;

typedef struct Building
{
	GhostType *theGhost;
	RoomLinkedList MasterRooms;
	HunterType *hunters[MAX_HUNTERS];
	sem_t mutex;
} BuildingType;

void initBuilding(BuildingType *building);
void populateRooms(BuildingType *building);
void initRoomList(RoomLinkedList *rooms);
void initRoom(RoomType *room, char *name);
void printRooms(RoomLinkedList *building);
void printConnected(RoomLinkedList *roomList);
void initEvidence(int id, EvidenceClassType device, float value, EvidenceType **newEvidence);
void initGhost(GhostType **ghost, GhostClassType randomGhost, RoomType *startRoom, int id);
void loadGhost(BuildingType *building);
void moveGhost(GhostType *theGhost);
void addEvidence(EvidenceLinkedList *roomEvidenceList, EvidenceType *newEvidence);
void printRoomEvidence(EvidenceLinkedList *roomEvidence);
void addGhostEvidence(GhostType *theGhost);
void* hunterFoo(void* hunter);
void* ghostFoo(void* ghost);
void appendRoom(RoomLinkedList *list, RoomNodeType *new);
void connectRooms(RoomType *x, RoomType *y);
void cleanBuildingRoomList(RoomLinkedList MasterRooms);
void cleanBuilding(BuildingType* building);
void StandardEvidencePrint(int x);
void addGhostEvidence(GhostType *theGhost);
int ghostAlone(GhostType *theGhost);
void ghostControl(GhostType *theGhost);
void cleanRoomList(RoomType* room);
void initHunter(char *name, int fear, int boredom, RoomType *currRoom, EvidenceClassType device, EvidenceLinkedList **notebook, HunterType **hunter, int id);
int enoughEvidence(HunterType* theHunter);
void hunterscared(HunterType** theHunter);
void hunterBored(HunterType** theHunter);
void decreaseHunterBoredom(HunterType *theHunter);
void resetHunterBoredom(HunterType *theHunter);
void increaseHunterFear(HunterType *theHunter);
int hunterNear(HunterType *theHunter);
void ghostNear(HunterType *theHunter);
void loadHunnters(BuildingType *building);
void enterName(char *name, int x);
void moveHunter(HunterType *theHunter, int x);
void takeEvidence(EvidenceLinkedList *room, EvidenceLinkedList *hunter, int id);
void checkRoomEvidence(HunterType *theHunter);
void copyAllEvidence(EvidenceLinkedList *hunterS, EvidenceLinkedList *hunterR);
void copyEvidence(EvidenceNodeType *evidenceNode, EvidenceLinkedList *hunterR);
void compareEvidence(HunterType *hunterSending, HunterType *hunterReceiving);
void hunterControl(HunterType *theHunter);
void cleanNotebook(HunterType** hunter);
void initEvidence(int id, EvidenceClassType device, float value, EvidenceType **newEvidence);
void addEvidence(EvidenceLinkedList *roomEvidenceList, EvidenceType *newEvidence);
void printRoomEvidence(EvidenceLinkedList *roomEvidence);
 int endersGame(BuildingType* building);





int randInt(int, int);				// Generates a pseudorandom integer between the parameters
float randFloat(float, float);		// Generates a pseudorandom float between the parameters
void populateRooms(BuildingType *); // Populates the building with sample data for rooms
