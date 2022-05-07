//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

/*Instruments header*/
#include "instrument_header.h"

#pragma once
/*Constants*/


/*Structs*/
typedef struct 
{
	unsigned short insId;
	float price;
}MPI;

typedef struct 
{
	MPI mpi_data;

	MPI* next;
}MPIListNode;

typedef struct 
{
	MPIListNode* head;
	MPIListNode* tail;
}MPIList;

typedef struct 
{
	char** name;
	MPIList instruments;
}Musician;

/*Function refrences*/
void GetMusiciansFromFile(Musician** musicians, char* file_name, InstrumentTree tree);
Musician* getMusician(char* line, InstrumentTree tree);
void addStringToName(char** name, char* token, int* name_index);
MPIListNode* createNewMPIListNode(MPIListNode* next, unsigned short insID, char* price);
void createNewMPIList(MPIList* instruments);
bool MPIListIsEmpty(MPIList* lst);
void insertMPIDataToEndList(MPIList* lst, unsigned short insID, char* price);

