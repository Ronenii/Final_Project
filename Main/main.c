//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

#include "concert_header.h"

/*Main*/
void main(int argc, char* argv[])
{
	int musician_count, instrument_count, concert_musicians_count; 
	InstrumentTree instrument_tree;

	buildInstrumentTree(&instrument_tree, "instruments.txt", &instrument_count);
	Musician** MusiciansGroup, *** MusiciansCollection, ** ConcertMusicians;

	MusiciansGroup = GetMusiciansFromFile("musicians.txt", instrument_tree,&musician_count);
	MusiciansCollection = createMusiciansCollection(MusiciansGroup, instrument_count, musician_count);

	printWelcomeMessege();
	Concert* Concert = GetConcert(instrument_tree);
	while (Concert != NULL)
	{
		ConcertMusicians = getMusiciansArrToConcert(Concert, MusiciansCollection, &concert_musicians_count);
		setAllMusiciansAvailable(MusiciansGroup, musician_count);
		printConcertDetails(Concert, ConcertMusicians, concert_musicians_count, instrument_tree);
		freeConcert(Concert);
		Concert = GetConcert(instrument_tree);
	}
	freeMusicians(MusiciansGroup, musician_count);//void printMusicians(Musician** musicians,int size)
	freeInstrumentTree(instrument_tree);
	printGoodbyeMessage();

}






















