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
void insertInstrumentToTree(InstrumentTree* instrument_tree, char* instrument, unsigned short insID);
TreeNode* insertInstrumentToTreeRec(TreeNode* current_tree_node, char* instrument, unsigned short insID);
void buildInstrumentTree(InstrumentTree* instrument_tree, char* file_name, int* instrument_count);
int findInsId(InstrumentTree tree, char* str);
//void printTree(InstrumentTree tree);
//void printTreeRec(TreeNode* root);
bool isEmptyInstrumentTree(InstrumentTree t);
void createNewTree(InstrumentTree* tree);
void freeInstrumentTree(InstrumentTree tree);
void freeInstrumentTreeRec(TreeNode* node);
void freeTreeNode(TreeNode* node);
