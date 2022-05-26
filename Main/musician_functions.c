//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

/*Musician functions*/
#include "musician_header.h"

/*Functions*/
Musician*** createMusiciansCollection(Musician** MusicianGroup, int size, int musician_count)
{
	Musician*** MusicianCollection = (Musician***)malloc(sizeof(Musician**) * size);
	checkMemoryAllocation(MusicianCollection);
	for (int instrument_index = 0; instrument_index < size; instrument_index++)
	{
		MusicianCollection[instrument_index] = getMusiciansByInstrument(MusicianGroup, musician_count, instrument_index);
	}

	return MusicianCollection;
}


//Returns an array of pointers to musicians, built from the musicians text file.
//o(n) = n^3 (n is the music tree size\number of words in line\number of lines in the file)
Musician** GetMusiciansFromFile(char* file_name, InstrumentTree tree, int* count)
{
	int physical_size = 1, logical_size = 0;
	char* textLine[LINE_LENGTH];

	FILE* file = fopen(file_name, "r");
	Musician** musicians = (Musician**)malloc(sizeof(Musician*) * physical_size);
	checkMemoryAllocation(musicians);

	while (!feof(file))
	{
		fgets(textLine, LINE_LENGTH, file);
		musicians[logical_size++] = getMusician(textLine, tree);
		if (logical_size == physical_size)
		{
			physical_size *= 2;
			musicians = (Musician**)realloc(musicians, sizeof(Musician*) * physical_size);
		}
	}
	musicians = (Musician**)realloc(musicians, sizeof(Musician*) * logical_size);
	*count = logical_size;
	fclose(file);
	return musicians;
}

Musician** getMusiciansByInstrument(Musician** MusicianGroup, int musician_count, int insID)
{
	int playing_musicians = 0;
	Musician** MusiciansByInstruments = (Musician**)malloc(sizeof(Musician*) * (musician_count));
	checkMemoryAllocation(MusiciansByInstruments);
	for (int musician_pindex = 0; musician_pindex < musician_count; musician_pindex++)
	{
		if (playsInstrument(MusicianGroup[musician_pindex], insID))
			MusiciansByInstruments[playing_musicians++] = MusicianGroup[musician_pindex];
	}
	MusiciansByInstruments = (Musician**)realloc(MusiciansByInstruments, sizeof(Musician**) * (playing_musicians + 1));
	MusiciansByInstruments[playing_musicians] = NULL;
	return MusiciansByInstruments;
}

bool playsInstrument(Musician* musician, int insID)
{
	MPIListNode* curr = musician->instruments.head;

	while (curr != NULL)
	{
		if (insID == curr->mpi_data.insId)
			return true;
		curr = curr->next;
	}
	return false;
}

//Recieves a text line and returns a musician pointer built from the values stored in it.
//o(n) = n^2 (n is the music tree size\number of words in a text file line)
Musician* getMusician(char* line, InstrumentTree tree)
{
	Musician* musician = (Musician*)malloc(sizeof(Musician));
	checkMemoryAllocation(musician);
	MPIList instrument_list;
	char* token, ** name = (char**)malloc(LINE_LENGTH * sizeof(char*)); //Given the maximum possible size for the array, will later realloc.
	int InsID, name_index = 0;
	createNewMPIList(&instrument_list);

	token = strtok(line, DELIMITERS);
	while (token != NULL)
	{
		InsID = findInsId(tree, token);
		if (InsID == NOT_FOUND && token[0] != '\n') //If the string is not an instrument and not '\n' then it is a name
			addStringToName(name, token, &name_index);
		else if (InsID != NOT_FOUND)//This is an else if and not an else in case the token is equal to '\n' so that w won't insert it
		{
			token = strtok(NULL, DELIMITERS); //We have the id of the instrument and we know that after an instrument comes it's price. 
			insertMPIDataToEndList(&instrument_list, InsID, token);
		}
		token = strtok(NULL, DELIMITERS);
	}
	name = (char**)realloc(name, sizeof(char*) * (name_index)); //Name index also represents the number of words in the name
	checkMemoryAllocation(name);
	set_musician(musician, name, name_index, instrument_list);

	return musician;
}

//Adds the given token (the name) into the string array
void addStringToName(char** name, char* token, int* name_index)
{
	name[*name_index] = _strdup(token);
	checkMemoryAllocation(name[*name_index]);
	(*name_index)++;
}

//Creates a new empty MPIList
void createNewMPIList(MPIList* instruments)
{
	instruments->head = instruments->tail = NULL;
}

//Creates a new LMPIListNode and assigns it the given values
MPIListNode* createNewMPIListNode(MPIListNode* next, unsigned short insID, char* price)
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
		new_node = createNewMPIListNode(NULL, insID, price);
		lst->tail = lst->head = new_node;
	}

	else
	{
		new_node = createNewMPIListNode(NULL, insID, price);
		lst->tail->next = new_node;
		lst->tail = new_node;
	}

}

//Assigns all of the given musician's parameters based on the given data
void set_musician(Musician* musician, char** name, int name_length, MPIList instrument_list)
{
	musician->name = name;
	musician->name_length = name_length;
	musician->instruments = instrument_list;
	musician->availability = true;
}

//Frees the musicians pointer array
//o(n) = n^2 (n is the musician size/name array size/Instrument list size
void freeMusicians(Musician** musicians, int musicians_size)
{
	for (int i = 0; i < musicians_size; i++)
		freeMusician(musicians[i]);
	free(musicians);
}

//Frees the musician pointer
//o(n) =  n (n is thee name array size/Instrument list size)
void freeMusician(Musician* musician)
{
	freeName(musician->name, musician->name_length);
	freeMPIList(musician->instruments);
}

//Frees the name array
//o(n) =  n (n is the name array size)
void freeName(char** name, int name_size)
{
	for (int i = 0; i < name_size; i++)
		free(name[i]);
	free(name);
}

//Frees the instrument list]
//o(n) = n (n is the instrument list size)
void freeMPIList(MPIList instrument_list)
{
	MPIListNode* del, * curr = instrument_list.head;

	while (curr != NULL)
	{
		del = curr;
		curr = curr->next;
		free(del);
	}
}

void sortMusiciansByImportance(Musician** musicians, int instrument_id, char importance)
{
	int count = 0;
	ConcertMusician* concert_musicians;
	while (musicians[count] != NULL) {count++;
	}
	concert_musicians = CreateConcertMusicians(musicians, instrument_id, count);
	if (importance == '1')
		qsort(concert_musicians, count, sizeof(ConcertMusician), compareYakar);
	else
		qsort(concert_musicians, count, sizeof(ConcertMusician), compareZol);

	placeSortedArr(concert_musicians, musicians, count);

	free(concert_musicians);
}

ConcertMusician* CreateConcertMusicians(Musician** musicians, int instrument_id, int count)
{
	ConcertMusician* ret = (ConcertMusician*)malloc(sizeof(ConcertMusician) * count);
	checkMemoryAllocation(ret);
	for (int i = 0; i < count; i++)
	{
		ret[i].musician = musicians[i];
		ret[i].price = getInstrumentPrice(musicians[i], instrument_id);
	}
	return ret;
}

void placeSortedArr(ConcertMusician* concert_musicians, Musician** musicians, int count)
{
	for (int i = 0; i < count; i++)
		musicians[i] = concert_musicians[i].musician;
}

float getInstrumentPrice(Musician* musician, int instrument_id)
{
	MPIListNode* node = musician->instruments.head;
	while (node->mpi_data.insId != instrument_id)
		node = node->next;

	return node->mpi_data.price;
}

int compareZol(ConcertMusician* m1, ConcertMusician* m2)
{
	if (m1->price - m2->price > 0)
		return 1;
	else
		return -1;

}

int compareYakar(ConcertMusician* m1, ConcertMusician* m2)
{
	if (m1->price - m2->price > 0)
		return -1;
	else
		return 1;
}
//void printMusicians(Musician** musicians,int size)
//{
//	MPIListNode *ins_list_curr;
//	for (int i = 0; i < size; i++)
//	{
//		for (int j = 0; j < musicians[i]->name_length; j++)
//			printf("%s ", musicians[i]->name[j]);
//		ins_list_curr = musicians[i]->instruments.head;
//
//		while (ins_list_curr != NULL)
//		{
//			printf("%d %f\n", ins_list_curr->mpi_data.insId, ins_list_curr->mpi_data.price);
//			ins_list_curr = ins_list_curr->next;
//		}
//	}
//}
