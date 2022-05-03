//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

#include "concert_header.h"

/*Main*/
void main(int argc, char* argv[])
{
	InstrumentTree instrument_tree;

	buildInstrumentTree(&instrument_tree, "instruments.txt");

	Concert c1 = getConcert(instrument_tree);
	printConcertDetails(c1);

}