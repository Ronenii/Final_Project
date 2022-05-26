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
bool checkIfMusicianExists(Musician** musicians_arr, int size_of_musician_arr, char* musician_name)
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


// returns a concert to the user
Concert* GetConcert(InstrumentTree inst_tr)
{
	char* concert_line = getString();
	if (!strcmp(concert_line, ""))
		return NULL;
	Concert* concert_res = (Concert*)malloc(sizeof(Concert));
	checkMemoryAllocation(concert_res);
	makeEmptyCIList(&(concert_res->instruments));
	SetConcertDetails(concert_res, concert_line, inst_tr, &(concert_res->instruments));
	return concert_res;
}

// This fucntion sets the cocnert's details from the users cocnert input.
void SetConcertDetails(Concert* concert, char* line, InstrumentTree inst_tr, CIList* inst_list)
{

	char* instruments; int amount, id; char importance;
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

// The fucntion releases the concert instrument list from memory
// O(n) - n is list length.
void freeCIList(CIList instruments_list)
{
	CINode* curr, * prev;
	curr = instruments_list.head;
	while (curr != NULL)
	{
		prev = curr;
		curr = curr->next;
		free(prev);
	}
}

// This fucntion realeases a cocnert from memory.
void freeConcert(Concert* concert)
{
	freeCIList(concert->instruments);
	free(concert->name);
	free(concert);
}

//input example: Tommorowland 13 11 2012 21:30 Viola 1 0 Drums 2 1 Piano 5 0  Violin 1 0 
// This fucntion returns matching musicians array, due to concert input
Musician** getMusiciansArrToConcert(Concert* concert, Musician*** musicians_collection_arr, int* concert_musicians_count)
{
	int log_size = 0, physic_size = 1, curr_amount_of_instruments, successful_input;CINode* concert_inst_node = concert->instruments.head;
	Musician** concert_musician_arr = (Musician**)malloc(sizeof(Musician*));
	checkMemoryAllocation(concert_musician_arr);
	while (concert_inst_node != NULL && concert_musician_arr!=NULL)
	{
		curr_amount_of_instruments = concert_inst_node->ci_data.num; // sets how many musician's are requested for a certain instrument
		successful_input = 0; // counts how many musicians has been pulled from the musicians collection array into the res concert musicians array.
		for (int music_collection_ind = 0; music_collection_ind < curr_amount_of_instruments; music_collection_ind++)
		{
			sortMusiciansByImportance(musicians_collection_arr[concert_inst_node->ci_data.inst], concert_inst_node->ci_data.inst, concert_inst_node->ci_data.importance);
			Musician* concert_musician = getMusicianFromPointersArray(musicians_collection_arr, concert_inst_node->ci_data.inst, &successful_input);
			if (concert_musician != NULL && concert_musician->availability == true) // if musician is found and not used , add him to the array. 
			{
				if (log_size == physic_size)
				{
					physic_size *= PHYSIC_SIZE_INCREASE;
					concert_musician_arr = (Musician**)realloc(concert_musician_arr, sizeof(Musician*) * physic_size);
					checkMemoryAllocation(concert_musician_arr);
				}
				concert_musician_arr[log_size++] = concert_musician;
				concert_musician->availability = false; // changes musician status to taken after hes been picked to the concert. 
			}
		}
		concert_musician_arr = checkSuccessfulInput(concert_musician_arr, successful_input, curr_amount_of_instruments);
		concert_inst_node = concert_inst_node->next; // move to next instrument and select his musicians.
	}
	*concert_musicians_count = log_size; // returns new concert array size. 
	return concert_musician_arr;
}

/* if theres not a complete match between the amount of musicians requested to the amount of musicians that are availabe from
musicians collection array, the fucntion will return NULL and alert the user that there is no concert availabe for his request*/
Musician** checkSuccessfulInput(Musician** musicians_arr,int amount_of_pulled_musicians, int inst_required)
{
	if (amount_of_pulled_musicians != inst_required)
	{
		free(musicians_arr);
		return NULL;
	}
	else
		return musicians_arr;
}



// returns a musician adress who plays the give inst_id instrument 
Musician* getMusicianFromPointersArray(Musician*** musicians_collection_arr, int inst_id, int * successful_input)
{
	if (inst_id != NOT_FOUND)
	{
		for (int musician_ind = 0; musicians_collection_arr[inst_id][musician_ind] != NULL; musician_ind++)
		{
			if (musicians_collection_arr[inst_id][musician_ind]->availability == true)
			{
				Musician* res_musician = musicians_collection_arr[inst_id][musician_ind];
				res_musician->concert_inst_id = inst_id;
				(*successful_input)++;
				return res_musician;
			}
		}
	}
	else
		return NULL;
}

// This fucntion prints entire concert details. 
void printConcertDetails(Concert* concert, Musician** concert_musicians, int concert_musicians_size, InstrumentTree tr)
{
	if (concert_musicians_size != 0 && concert_musicians !=NULL)
	{
		printf("\n%s %d %d %d ", concert->name, concert->date_of_concert.day, concert->date_of_concert.month, concert->date_of_concert.year);
		printConcertHour(concert->date_of_concert.hour);
		printMusicians(concert_musicians, concert_musicians_size, tr, concert);
	}
	else
		printf("\nCould not find musicians for the concert %s\n\n\n", concert->name);
}

// prints concert_musicians array. 
void printMusicians(Musician** musicians, int size, InstrumentTree tr)
{
	float curr_price, total_price = 0.0;
	for (int musician_ind = 0; musician_ind < size; musician_ind++)
	{
		for (int inst_ind = 0; inst_ind < musicians[musician_ind]->name_length; inst_ind++)
		{
			printf("%s ", musicians[musician_ind]->name[inst_ind]);
		}
		curr_price = getInstPriceFromList(musicians[musician_ind]->instruments, musicians[musician_ind]->concert_inst_id);
		total_price += curr_price; // get total price; 
		printf(" - %s (%.2f) ", getConcertInstNameFromTree(tr, musicians[musician_ind]->concert_inst_id), curr_price);
	}
	if (total_price != 0.0)
		printf("\nTotal cost: %.2f\n\n\n\n", total_price);
}

// returns the current instrument's price from the musician's instrument list. 
float getInstPriceFromList(MPIList musician_inst_lst, int inst_id)
{
	MPIListNode* curr_inst = musician_inst_lst.head;
	while (curr_inst != NULL)
	{
		if (curr_inst->mpi_data.insId == inst_id)
			return curr_inst->mpi_data.price;
		curr_inst = curr_inst->next;
	}
}

// This fucntion gets a float and prints the hour in an HH:MM format
void printConcertHour(float time)
{
	int hour = (int)time;
	float minutes = ((time - hour) * FLOAT_CAST);
	if (minutes < HOUR_CALC)
		printf("%d:0%d\n", hour, (int)(minutes));
	else
		printf("%d:%d\n", hour, (int)(minutes));
}

// returns the requested instrument's name string using his id. 
char* getConcertInstNameFromTree(InstrumentTree inst_tr, int id)
{
	char* res_inst_name;
	getConcertInstNameFromTreeHelper(inst_tr.root, id, &res_inst_name);
	return res_inst_name;
}

// helper, when the id is found, strdup will return the full instrument's name to res pointer. 
void getConcertInstNameFromTreeHelper(TreeNode* curr, int id, char** res)
{
	if (curr == NULL)
		return;
	else
	{
		if (curr->insId == id)
			*res = _strdup(curr->instrument);
		else
		{
			getConcertInstNameFromTreeHelper(curr->left, id, res);
			getConcertInstNameFromTreeHelper(curr->right, id, res);
		}
	}
}

// sets all musicians availabe again so we could use them in more concerts. 
void setAllMusiciansAvailable(Musician** musicians_arr, int arr_size)
{
		for (int musician_ind = 0; musician_ind < arr_size; musician_ind++)
			musicians_arr[musician_ind]->availability = true;
}

// prints welcome messege. 
void printWelcomeMessege()
{
	printf("Welcome to our concert search engine, please enter concert name, date and instruments:\n\n");
}