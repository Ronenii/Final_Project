//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

/*Instruments header*/


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
int findInsId(InstrumentTree tree, char* instrument);