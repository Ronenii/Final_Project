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
	int name_length;
	MPIList instruments;
	bool availability;
}Musician;

/*Function refrences*/
Musician*** createMusiciansCollection(Musician** MusicianGroup, int size, int musician_count);
Musician** getMusiciansByInstrument(Musician** MusicianGroup, int musician_count, int insID);
Musician* getMusician(char* line, InstrumentTree tree);
MPIListNode* createNewMPIListNode(MPIListNode* next, unsigned short insID, char* price);
Musician** GetMusiciansFromFile(char* file_name, InstrumentTree tree, int* count);

void addStringToName(char** name, char* token, int* name_index);
void createNewMPIList(MPIList* instruments);
void insertMPIDataToEndList(MPIList* lst, unsigned short insID, char* price);
void set_musician(Musician* musician, char** name, int name_length, MPIList instrument_list);
void freeMusicians(Musician** musicians, int musicians_size);
void freeMusician(Musician* musician);
void freeName(char** name, int name_size);
void freeMPIList(MPIList instrument_list);

bool MPIListIsEmpty(MPIList* lst);
bool playsInstrument(Musician* musician, int insID);

