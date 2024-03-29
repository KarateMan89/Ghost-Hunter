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
	sem_t mutexR;
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
	int actualEvidence;
	struct Building *building;
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
	struct Building* building;
} HunterType;

typedef struct Building
{
	GhostType *theGhost;
	RoomLinkedList MasterRooms;
	HunterType *hunters[MAX_HUNTERS];
	EvidenceLinkedList* collectedEvidence;
	int game_over;
	int ghost_bored;
	int huntersBored;
	int huntersScared;
	int enoughEvidence;
} BuildingType;


void populateRooms(BuildingType *);
void initRoomList(RoomLinkedList *);
void initRoom(RoomType *, char *);
void initBuilding(BuildingType *);
void printRooms(RoomLinkedList *);
void printConnected(RoomLinkedList *);
void initEvidence(int , EvidenceClassType , float , EvidenceType **);
void initGhost(GhostType **, GhostClassType , RoomType *, int );
void loadGhost(BuildingType *building);
void moveGhost(GhostType *theGhost);
void addEvidence(EvidenceLinkedList *roomEvidenceList, EvidenceType *newEvidence);
void printRoomEvidence(EvidenceLinkedList *roomEvidence);
void addGhostEvidence(GhostType *theGhost);
void* hunterFoo(void*);
void* ghostFoo(void*);
void appendRoom(RoomLinkedList *list, RoomNodeType *new);
void connectRooms(RoomType *x, RoomType *y);
void cleanBuildingRoomList(RoomLinkedList MasterRooms);
void cleanBuilding(BuildingType* building);
void StandardEvidencePrint(int x);
int ghostAlone(GhostType *theGhost);
void ghostControl(GhostType *theGhost);
void cleanRoomList(RoomType* room);
void initHunter(char *name, int fear, int boredom, RoomType *currRoom, EvidenceClassType device, EvidenceLinkedList **notebook, HunterType **hunter, int id);
int enoughEvidence(HunterType* theHunter);
void hunterscared(HunterType* theHunter);
void hunterBored(HunterType* theHunter);
void decreaseHunterBoredom(HunterType *theHunter);
void resetHunterBoredom(HunterType *theHunter);
void increaseHunterFear(HunterType *theHunter);
int hunterNear(HunterType *theHunter);
void ghostNear(HunterType *theHunter);
void loadHunnters(BuildingType *building);
void enterName(char *name, int x);
void moveHunter(HunterType *theHunter, int x);
void takeEvidence(EvidenceLinkedList *room, EvidenceLinkedList *hunter, int id, BuildingType *theBuilding);
void checkRoomEvidence(HunterType *theHunter, BuildingType* building);
void copyAllEvidence(EvidenceLinkedList *hunterS, EvidenceLinkedList *hunterR);
void copyEvidence(EvidenceNodeType *evidenceNode, EvidenceLinkedList *hunterR);
void compareEvidence(HunterType *hunterSending, HunterType *hunterReceiving);
void hunterControl(HunterType *theHunter, BuildingType* theBuilding);
void cleanNotebook(HunterType** hunter);
void printResults(BuildingType *theBuilding);
int gameOver(BuildingType*);
int randInt(int, int);				// Generates a pseudorandom integer between the parameters
float randFloat(float, float);		// Generates a pseudorandom float between the parameters
int enoughE(HunterType *theHunter);
