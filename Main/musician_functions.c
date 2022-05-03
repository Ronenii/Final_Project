//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

/*Musician functions*/
#include "musician_header.h"

/*Functions*/


//Returns an array of pointers to musicians, built from the musicians text file.
//o(n) = n^2(n is the number of musicians)
void GetMusiciansFromFile(Musician**musicians, char * file_name, InstrumentTree tree)
{
	int physical_size=1, logical_size=0;
	char* textLine[LINE_LENGTH];

	FILE* file = fopen(file_name, "r");
	musicians = (Musician**)malloc(sizeof(Musician*)*physical_size);
	checkMemoryAllocation(musicians);
	fgets(textLine,LINE_LENGTH,file);
	while (feof(file) == 0)
	{
		musicians[logical_size] =getMusician(textLine,tree);
		logical_size++;
		if (logical_size == physical_size)
		{
			physical_size *= 2;
			musicians = (Musician**)realloc(musicians, sizeof(Musician*) * physical_size);
		}
		fgets(textLine, LINE_LENGTH, file);
	}
	fclose(file);
}

//Recieves a text line and returns a musician pointer built from the values stored in it.
//o(n) = n^2 (n is the music tree size)
Musician* getMusician(char* line, InstrumentTree tree)
{
	Musician* musician = (Musician*)malloc(sizeof(Musician));
	MPIList instrument_list;
	char *token, *name = (char*)malloc(LINE_LENGTH*sizeof(char));
	unsigned short InsID;
	createNewMPIList(&instrument_list);
	name[0] = '\0'; //So that it will be considered an ampty string to which we can concatenate words
	
	token = strtok(line, DELIMITERS);
	while (token != NULL)
	{
		if (isInstrument(tree, token))
		{
			InsID = findInsId(tree, token);
			token = strtok(NULL, DELIMITERS);
			insertMPIDataToEndList(&instrument_list, InsID, token);
		}
		else if(token[0] != '\n')//So we won't insert \n as a string
			addStringToName(name, token);
	
	token = strtok(NULL, DELIMITERS);
	}

	name[strlen(name)-1] = '\0';//To remove the last space in the name added in addStringToName
	name = (char*)realloc(name, sizeof(char) * (strlen(name) + 1));
	checkMemoryAllocation(name);
	musician->name = name;
	musician->instruments = instrument_list;

	return musician;
}

//Adds the given token into the name and adds a space for future words that will be added
void addStringToName(char* name, char* token)
{
	strcat(name, token);
	strcat(name, " ");
}

//Creates a new empty MPIList
void createNewMPIList(MPIList* instruments)
{
	instruments->head = instruments->tail = NULL;
}

//Creates a new LMPIListNode and assigns it the given values
MPIListNode* createNewMPIListNode(MPIListNode*next,unsigned short insID,char*price)
{
	MPIListNode* ListNode = (MPIListNode*)malloc(sizeof(MPIListNode));
	checkMemoryAllocation(ListNode);
	
	ListNode->mpi_data.insId = insID;
	ListNode->mpi_data.price = (float)atof(price);
	ListNode->next = next;
}

//Returns if the list is empty or not
bool MPIListIsEmpty(MPIList* lst)
{
	return (lst->head == NULL);
}

//Inserts the given data into a new MPIListNode which is then added to the end of the list
void insertMPIDataToEndList(MPIList* lst, unsigned short insID, char* price)
{
	MPIListNode* new_node;

	if (MPIListIsEmpty(lst))
	{
		new_node = createNewMPIListNode(NULL, insID,price);
		lst->tail = lst->head = new_node;
	}

	else
	{
		new_node = createNewMPIListNode(NULL, insID, price);
		lst->tail->next = new_node;
		lst->tail = new_node;
	}

}


