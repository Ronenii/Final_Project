//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

/*Instrument functions*/
#include "instrument_header.h"

/*Functions*/
//Initializes a new NULLTree
void createNewTree(InstrumentTree* tree)
{
	tree->root = NULL;
}

//Recieves a string and an int, assigns it to a new TreeNode and returns it.
TreeNode* createNewInstrument(char* name, unsigned short insID)
{
	TreeNode* instrument = (TreeNode*)malloc(sizeof(TreeNode));
	checkMemoryAllocation(instrument);
	instrument->insId = insID;
	instrument->instrument = _strdup(name);
	checkMemoryAllocation(instrument->instrument);
	instrument->left = instrument->right = NULL;
	return instrument;
}

//Adds a given new instrument into a given tree
//o(n) = n (n is the tree size)
void insertInstrumentToTree(InstrumentTree* instrument_tree, char* instrument, unsigned short insID)
{
	instrument_tree->root = insertInstrumentToTreeRec(instrument_tree->root, instrument, insID);
}

TreeNode* insertInstrumentToTreeRec(TreeNode* current_tree_node, char* instrument, unsigned short insID)
{
	if (current_tree_node == NULL) //If the tree is empty then the root is set to be A new instrument TreeNode
	{
		current_tree_node = createNewInstrument(instrument, insID);
		return current_tree_node;
	}

	if (*(current_tree_node->instrument) < *instrument) //Selection of where to send the instrument based on it's first letter
	{
		current_tree_node->right = insertInstrumentToTreeRec(current_tree_node->right, instrument, insID);
	}

	else if (*(current_tree_node->instrument) > *instrument)
		current_tree_node->left = insertInstrumentToTreeRec(current_tree_node->left, instrument, insID);

	else //Compares between the first non-matching character using strcmp
	{
		if (strcmp(current_tree_node->instrument, instrument) > 0)
			current_tree_node->left = insertInstrumentToTreeRec(current_tree_node->left, instrument, insID);
		else
			current_tree_node->right = insertInstrumentToTreeRec(current_tree_node->right, instrument, insID);
	}
	return current_tree_node;
}

//Recieves a string array(names of all instruments), creates a new tree node for each instrument and inserts it into the instrument tree
//o(n) = n^2 (n is instruments_size\number of lines in the text file)
void buildInstrumentTree(InstrumentTree* instrument_tree, char* file_name, int * instrument_count)
{
	createNewTree(instrument_tree);
	FILE* file = fopen(file_name, "r");
	checkFileOpening(file);
	char* instrument[INSTRUMENT_NAME_SIZE];
	int insID = 0;
	while (!feof(file))
	{
		fscanf(file, "%s", instrument);
		//fgets(instrument, INSTRUMENT_NAME_SIZE, file);
		insertInstrumentToTree(instrument_tree, instrument, insID);
		insID++;
	}
	(*instrument_count) = insID;
	fclose(file);
}

//Runs through the tree using strcmp to find if the given string is in the tree.
//If the instrument is found then it returns it's id, else returns -1.
//o(n) = n (n is the the tree size)
int findInsId(InstrumentTree tree, char* str)
{
	return findInsIdRec(tree.root, str);
}

int findInsIdRec(TreeNode* current_tree_node, char* str)
{
	if (current_tree_node == NULL)
		return -1;

	if (strcmp(current_tree_node->instrument, str) == 0)
		return current_tree_node->insId;

	//Compares the root and instrument and sends them left or right in the tree according to the lexicographical values
	else if (strcmp(current_tree_node->instrument, str) > 0)
		return findInsIdRec(current_tree_node->left, str);

	else
		return findInsIdRec(current_tree_node->right, str);
}

//void printTree(InstrumentTree tree)
//{
//	printTreeRec(tree.root);
//}
//
//void printTreeRec(TreeNode* root)
//{
//	if (root == NULL)
//		return;
//	printTreeRec(root->left);
//	printf("Instrument: %s\nID: %d\n", root->instrument, root->insId);
//	printTreeRec(root->right);
//}

//Checks if the tree is empty
bool isEmptyInstrumentTree(InstrumentTree t)
{
	return t.root == NULL;
}

//Frees the memory of the Instrument tree
//o(n) = n (n is the size of the tree)
void freeInstrumentTree(InstrumentTree tree)
{
	freeInstrumentTreeRec(tree.root);
}

void freeInstrumentTreeRec(TreeNode* node)
{
	if (node == NULL)
		return;

	freeInstrumentTreeRec(node->left);
	freeInstrumentTreeRec(node->right);
	freeTreeNode(node);
}

//Frees the given TreeNode's data
void freeTreeNode(TreeNode* node)
{
	free(node->instrument);
	free(node);
}

