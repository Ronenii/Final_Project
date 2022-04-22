//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

/*Instrument functions*/

#include "instrument_header.h"

/*Functions*/

//Recieves a string and an int, assigns it to a new TreeNode and returns it.
TreeNode* createNewInstrument(char* name, unsigned short insID)
{
	TreeNode* instrument = NULL;
	instrument->insId = insID;
	instrument->instrument = name;
	instrument->left = instrument->right = NULL;

	return instrument;
}

//Adds a given new instrument into a given tree
//o(n) = n (n is the tree size)
void insertInstrumentToTree(InstrumentTree* instrument_tree, TreeNode* instrument)
{
	insertInstrumentToTreeRec(instrument_tree->root, instrument);
}

void insertInstrumentToTreeRec(TreeNode* current_tree_node, TreeNode* instrument)
{
	if (current_tree_node == NULL) //If the tree is empty then the root is set to be the instrument
	{
		current_tree_node = instrument;
		return;
	}

	
	if (*(current_tree_node->instrument) < *(instrument->instrument)) //Selection of where to send the instrument based on it's first letter
		insertInstrumentToTreeRec(current_tree_node->right, instrument);

	else if (*(current_tree_node->instrument) > *(instrument->instrument))
		insertInstrumentToTreeRec(current_tree_node->left, instrument);

	else //If the first letters match, runs through both strings until their chars at the char_index aren't equal
	{
		int char_index = 0;
		while (current_tree_node->instrument[char_index] == instrument->instrument[char_index])
			char_index++;
		if (current_tree_node->instrument[char_index] < instrument->instrument[char_index])
			insertInstrumentToTreeRec(current_tree_node->right, instrument);
		else
			insertInstrumentToTreeRec(current_tree_node->left, instrument);
	}
}

//Recieves a string array(names of all instruments), creates a new tree node for each instrument and inserts it into the instrument tree
//o(n) = n^2 (n is instruments_size)
void buildInstrumentTree(InstrumentTree * instrument_tree,char ** instruments, int instruments_size)
{
	TreeNode* new_instrument;
	for (int instrument_index = 0; instrument_index < instruments_size; instrument_index++)
	{
		new_instrument = createNewInstrument(instruments[instrument_index], instrument_index); //the instrument is assigned a name and an id based on it's index in the list
		insertInstrumentToTree(instrument_tree, new_instrument);
	}
}



int findInsId(InstrumentTree tree, char* instrument)
{

}

