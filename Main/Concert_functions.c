//Ronen Gelmanovich 319047718
//Ori Teicher 209279405
#include "concert_header.h"

/*Concert functions*/

// The fucntion recieves a string in a form of an hour (for example : 20:30) and returns the string in a form of a float (in our example : 20.30) 
// O(n) - n is hour_string len (always 5 HH:MM format). 
float getHourFromString(char* hour_string)
{
	int str_index = 0;
	float cur_num = 0;
	while (hour_string[str_index] != '\0')
	{
		cur_num = cur_num * HOUR_CALC; // each time the current number multiply by 10 to turn into an hour format. 
		if (isDigit(hour_string[str_index]) && hour_string[str_index] != ':')
			cur_num = cur_num + (hour_string[str_index] - '0');// casts using ascii value to a float. 
		else
			cur_num /= HOUR_CALC;
		str_index++;
	}
	return (cur_num / FLOAT_CAST);
}

// The fucntion checks if a current char is a digit or not. 
bool isDigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}

// This fucntion checks if a musician exists in the musician's array for the requested concert. 
bool checkIfMusicianExists(Musician** musicians_arr,int size_of_musician_arr, char* musician_name)
{
	bool check = false;
	int musicians_arr_ind = 0; 
	for (int i = 0; i < size_of_musician_arr && check == false; i++)
	{
		if (strcmp(musicians_arr[musicians_arr_ind]->name, musician_name) == 0)
			check = true;
	}
	return check;
}

// This fucntion gets an instrument list and checks if its empty. 
bool checkEmptyList(CIList* instrument_list)
{
	if (instrument_list->head == NULL && instrument_list->tail == NULL)
		return true;
	else
		return false;
}

 // This function returns a new concert instrument list node. 
CINode* createNewCIListNode(int id, int amount, char importance, CINode* next)
{
	CINode* new_ci_node; 
	new_ci_node = (CINode*)malloc(sizeof(CINode));
	checkMemoryAllocation(new_ci_node);
	new_ci_node->ci_data.inst = id;
	new_ci_node->ci_data.num = amount; 
	new_ci_node->ci_data.importance = importance;
	new_ci_node->next = next;
	return new_ci_node;
}

// This fucntion inserts the CINode into the end of the list. 
void insertCINodeToEndList(CIList* ci_list, CINode* new_ci_tail)
{
	if (checkEmptyList(ci_list))
	{
		ci_list->head = new_ci_tail;
		ci_list->tail = new_ci_tail;
	}
	else
	{
		ci_list->tail->next = new_ci_tail;
		ci_list->tail = new_ci_tail;
	}
}


// This fucntion inserts the data of the CI_NODE to the end of the list
void insertCIDataToEndList(CIList* ci_list, int id, int amount, char importance)
{
	CINode* new_ci_tail; 
	new_ci_tail = createNewCIListNode(id, amount, importance, NULL);
	insertCINodeToEndList(ci_list, new_ci_tail);
}

// The function creates an instrument list due to the user's input
void makeEmptyCIList(CIList* ci_list)
{
	ci_list->head = NULL;
	ci_list->tail = NULL;
}

//// This fucntion prints entire concert details. 
//void printConcertDetails(Concert concert)
//{
//	CINode* curr = concert.instruments.head;
//	printf("Concert name: ''%s''\n", concert.name);
//	printf("Concert date: %d %d %d\n", concert.date_of_concert.day,
//    concert.date_of_concert.month, concert.date_of_concert.year);
//	printConcertHour(concert.date_of_concert.hour);
//	
//	while (curr != NULL)
//	{
//		printf("\nimportance: %c ID: %d count: %d\n",curr->ci_data.importance, curr->ci_data.inst, curr->ci_data.num);
//		curr = curr->next;
//	}
//	//print concert Musicians fucntion here (artist, artist instruments, price for playing on each instrument).
//}
//
//
//// This fucntion gets a float and prints the hour in an HH:MM format
//void printConcertHour(float time)
//{
//	int hour = (int)time;
//	float minutes = ((time - hour) * FLOAT_CAST);
//	if (minutes < HOUR_CALC)
//		printf("Concert hour : %d:0%d", hour, (int)(minutes));
//	else
//		printf("Concert hour : %d:%d", hour, (int)(minutes));
//}

// returns a concert to the user
Concert* GetConcert(InstrumentTree inst_tr)
{
	char* concert_line = getString(); 
	Concert* concert_res = (Concert*)malloc(sizeof(Concert));
	checkMemoryAllocation(concert_res);
	makeEmptyCIList(&(concert_res->instruments));
	SetConcertDetails(concert_res, concert_line,inst_tr, &(concert_res->instruments));
	return concert_res;
}

// This fucntion sets the cocnert's details from the users cocnert input.
void SetConcertDetails(Concert* concert, char* line, InstrumentTree inst_tr, CIList* inst_list)
{

	char* instruments; int amount,id; char importance;
	concert->name = strtok(line, SPACE);
	concert->date_of_concert.day = atoi(strtok(NULL, SPACE));
	concert->date_of_concert.month = atoi(strtok(NULL, SPACE));
	concert->date_of_concert.year = atoi(strtok(NULL, SPACE));
	concert->date_of_concert.hour = getHourFromString(strtok(NULL, SPACE));

	instruments = strtok(NULL, SPACE);
	id = findInsId(inst_tr, instruments);
	amount = atoi(strtok(NULL, SPACE));
	importance = strtok(NULL, SPACE)[0];

	while (instruments != NULL)
	{
		insertCIDataToEndList(inst_list, id, amount, importance);
		instruments = strtok(NULL, SPACE);
		if (instruments != NULL)
		{
			id = findInsId(inst_tr, instruments);
			amount = atoi(strtok(NULL, SPACE));
			importance = (strtok(NULL, SPACE))[0];
		}
	}
}
//input example: Tommorowland 20 20 2012 21:30 Viola 1 0 Drums 2 1



