//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

/*Instruments header*/


#pragma once
/*Constants*/


/*Structs*/
typedef struct MusicianPriceInstrument
{
	unsigned short insId;
	float price;
}MPI;

typedef struct ListNodeOfMPI
{
	MPI mpi_data;
	MPI* next;
}MPIListNode;

typedef struct mpiList
{
	MPIListNode* head;
	MPIListNode* tail;
}MPIList;
typedef struct musician
{
	char** name;
	MPIList instruments;
}Musician;

/*Function refrences*/