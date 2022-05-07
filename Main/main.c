//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

#include "concert_header.h"

/*Main*/
void main(int argc, char* argv[])
{
	InstrumentTree instrument_tree;
	Musician** musicians =NULL;
	buildInstrumentTree(&instrument_tree, "instruments.txt");

	musicians = GetMusiciansFromFile("musicians.txt", instrument_tree);

	printMusicians(musicians, 7);
}