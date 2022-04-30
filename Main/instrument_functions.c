//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

/*Instrument functions*/

#include "instrument_header.h"

/*Functions*/

//Recieves a string and an int, assigns it to a new TreeNode and returns it.
TreeNode* createNewInstrument(char* name, unsigned short insID)
{
	TreeNode* instrument = (TreeNode*)malloc(sizeof(TreeNode));
	checkMemoryAllocation(instrument);
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

	else //Compares between the first non-matching character using strcmp
	{
		if (strcmp(current_tree_node->instrument, instrument->instrument) > 0)
			insertInstrumentToTreeRec(current_tree_node->left, instrument);
		else
			insertInstrumentToTreeRec(current_tree_node->right, instrument);
	}
}

//Recieves a string array(names of all instruments), creates a new tree node for each instrument and inserts it into the instrument tree
//o(n) = n^2 (n is instruments_size)
void buildInstrumentTree(InstrumentTree * instrument_tree,char * file_name)
{
	TreeNode* new_instrument;
	FILE* file = fopen(file_name, "r");
	checkFileOpening(file);
	char* instrument[INSTRUMENT_NAME_SIZE];
	int insID = 0;
	while (true)
	{
		fscanf(file, "%s", instrument);
		if (feof(file))
			break;
		new_instrument = createNewInstrument(instrument, insID); //the instrument is assigned a name and an id based on it's index in the list
		insertInstrumentToTree(instrument_tree, new_instrument);
		insID++;
	}

	fclose(file);
}

//Runs through the tree using strcmp to find the matching given instrument. Returns it's ID.
//o(n) = n (n is the the tree size)
int findInsId(InstrumentTree tree, char* instrument)
{
	return indInsIdRec(tree.root, instrument);
}

int findInsIdRec(TreeNode * current_tree_node, char* instrument)
{
	if (strcmp(current_tree_node->instrument, instrument) == 0) 
		return current_tree_node->insId;

	//Compares the root and instrument and sends them left or right in the tree according to the lexicographical values
	else if (strcmp(current_tree_node->instrument, instrument) > 0)
		return findInsIdRec(current_tree_node->left, instrument);

	else 
		return findInsIdRec(current_tree_node->right, instrument);
}

//Returns boolean value dependant on if the given str is an instrument in the tree
//o(n) = n (n is the tree size)
bool isInstrument(InstrumentTree tree, char* str)
{
	if(!isEmptyInstrumentTree(tree))
		return isInstrumentRec(tree.root, str);
}

bool isInstrumentRec(TreeNode* current_tree_node, char* str)
{
	if (strcmp(current_tree_node->instrument, str))
		return true;
	
	//Compares the root and str and sends them left or right in the tree according to the lexicographical values
	else if (strcmp(current_tree_node->instrument, str) > 0) 
		return isInstrumentRec(current_tree_node->left, str);

	else  if (strcmp(current_tree_node->instrument, str) < 0)
		return isInstrumentRec(current_tree_node->right, str);
	else //If the current_tree_node is NULL basically
		return false;
}

//Checks if the tree is empty
bool isEmptyInstrumentTree(InstrumentTree t)
{
	return t.root == NULL;
}

