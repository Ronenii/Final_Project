//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

/*Instruments header*/


#pragma once
/*Constants*/


/*Structs*/
typedef struct
{
	unsigned short insId;
	float price;
} MusicianPriceInstrument;
typedef struct
{
	char** name;
	MPIList instruments;
} Musician;

/*Function refrences*/