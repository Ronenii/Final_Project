//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

#include "concert_header.h"

/*Main*/
void main(int argc, char* argv[])
{
	int musician_count, instrument_count, concert_musicians_count; 
	char concert_input;
	InstrumentTree instrument_tree;

	buildInstrumentTree(&instrument_tree, "instruments.txt", &instrument_count);
	Musician** MusiciansGroup, *** MusiciansCollection, ** ConcertMusicians;

	MusiciansGroup = GetMusiciansFromFile("musicians.txt", instrument_tree,&musician_count);
	MusiciansCollection = createMusiciansCollection(MusiciansGroup, instrument_count, musician_count);

	concert_input = getchar();
	while (concert_input != '\n')
	{
		Concert* Concert = GetConcert(instrument_tree,&concert_input);
		ConcertMusicians = getMusiciansArrToConcert(Concert, MusiciansCollection, &concert_musicians_count);
		setAllMusiciansAvailable(ConcertMusicians, concert_musicians_count);
		printConcertDetails(Concert, ConcertMusicians, concert_musicians_count, instrument_tree);
		freeConcert(Concert);
		concert_input = getchar();
	}

	freeMusicians(MusiciansGroup, musician_count);//void printMusicians(Musician** musicians,int size)
	freeInstrumentTree(instrument_tree);
	printGoodbyeMessage();

}






















