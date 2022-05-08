//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

#include "concert_header.h"

/*Main*/
void main(int argc, char* argv[])
{
	int musician_count;
	InstrumentTree instrument_tree;
	buildInstrumentTree(&instrument_tree, "instruments.txt");
	Musician** MusiciansGroup =NULL;
	MusiciansGroup = GetMusiciansFromFile("musicians.txt", instrument_tree,&musician_count);

	Concert* concert_input = GetConcert(instrument_tree);
	printConcertDetails(concert_input);

	freeMusicians(MusiciansGroup, musician_count);
	freeInstrumentTree(instrument_tree);
}