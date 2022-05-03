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
Musician* getMusician(char* line, InstrumentTree tree);
