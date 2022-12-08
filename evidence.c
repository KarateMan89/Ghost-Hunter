#include "defs.h"
/*
Function: initEvidence
Purpose: This function initializes the fields of an EvidenceType with the specified values.
in/out: The function takes in an integer, an EvidenceClassType, a float, and a double pointer to an EvidenceType and returns nothing.
in: id - the identifier for the EvidenceType
    device - the type of device used to collect the evidence
    value - the value of the evidence
    newEvidence - a double pointer to the EvidenceType that is being initialized
out: None
return: None

*/
void initEvidence(int id, EvidenceClassType device, float value, EvidenceType **newEvidence)
{
    *newEvidence = (EvidenceType *)calloc(1, sizeof(EvidenceType));
    (*newEvidence)->id = id;
    (*newEvidence)->evidenceType = device;
    (*newEvidence)->value = value;
}

/*
Function: addEvidence
Purpose: This function adds an EvidenceType to the linked list of evidence for a room.
in/out: The function takes in a pointer to an EvidenceLinkedList and a pointer to an EvidenceType and returns nothing.
in: roomEvidenceList - a pointer to the EvidenceLinkedList for the room where the evidence is being added
    newEvidence - a pointer to the EvidenceType that is being added to the room
out: None
return: None
*/
void addEvidence(EvidenceLinkedList *roomEvidenceList, EvidenceType *newEvidence)
{
    EvidenceNodeType *newEvidenceNode = (EvidenceNodeType *)calloc(1, sizeof(EvidenceNodeType));
    newEvidenceNode->evidence = newEvidence;
    newEvidenceNode->next = NULL;

    if (roomEvidenceList->head == NULL)
    {
        roomEvidenceList->head = newEvidenceNode;
        roomEvidenceList->head->next = NULL;
    }
    else
    {
        newEvidenceNode->next = roomEvidenceList->head;
        roomEvidenceList->head = newEvidenceNode;
    }
}

/*
Function: printRoomEvidence
Purpose: This function prints the evidence in a room's EvidenceLinkedList.
in/out: The function takes in a pointer to an EvidenceLinkedList and returns nothing.
in: roomEvidence - a pointer to the EvidenceLinkedList for the room whose evidence is being printed
out: None
return: None

*/
void printRoomEvidence(EvidenceLinkedList *roomEvidence)
{
    EvidenceNodeType *curr = roomEvidence->head;
    while (curr != NULL)
    {
        printf("EVIDENCE ID: %d DEVICE: %d VALUE: %f\n", curr->evidence->id, curr->evidence->evidenceType, curr->evidence->value);
        curr = curr->next;
    }
}
