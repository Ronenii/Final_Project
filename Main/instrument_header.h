//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

/*Instruments header*/

#include "main_header.h"

#pragma once
/*Constants*/


/*Structs*/
typedef struct treeNode {
	char* instrument;
	unsigned short insId;
	struct treeNode* left;
	struct treeNode* right;
} TreeNode;

typedef struct tree {
	TreeNode* root;
} InstrumentTree;

/*Function refrences*/
TreeNode* createNewInstrument(char* name, unsigned short insID);
void insertInstrumentToTree(InstrumentTree* instrument_tree, TreeNode* instrument);
void insertInstrumentToTreeRec(TreeNode* current_tree_node, TreeNode* instrument);
void buildInstrumentTree(InstrumentTree* instrument_tree, char** instruments, int instruments_size);
int findInsId(InstrumentTree tree, char* instrument);