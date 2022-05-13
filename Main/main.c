//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

#include "concert_header.h"

/*Main*/
void main(int argc, char* argv[])
{
	int musician_count, instrument_count;
	InstrumentTree instrument_tree;

	buildInstrumentTree(&instrument_tree, "instruments.txt", &instrument_count);
	Musician** MusiciansGroup, *** MusiciansCollection, ** ConcertMusicians;

	MusiciansGroup = GetMusiciansFromFile("musicians.txt", instrument_tree,&musician_count);

	MusiciansCollection = createMusiciansCollection(MusiciansGroup, instrument_count, musician_count);

	Concert* Concert = GetConcert(instrument_tree);
	ConcertMusicians = getMusiciansArrToConcert(Concert, *MusiciansCollection);

	freeConcert(Concert);
	freeMusicians(MusiciansGroup, musician_count);
	freeInstrumentTree(instrument_tree);
}