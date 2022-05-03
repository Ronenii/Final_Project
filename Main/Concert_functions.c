//Ronen Gelmanovich 319047718
//Ori Teicher 209279405
#include "concert_header.h"

/*Concert functions*/

// The function gets data for a concert from the user.
// O(n) - n is concert name lentgh and hour length (which is always 5 HH:MM format). 
Concert getConcert()
{
	Concert concert_res;
	setConcertName(&concert_res); // sets the new name for the concert.
	setConcertDate(&concert_res); // sets the date and hour for the concert. 
	setConcertInstruments(&concert_res);
	return concert_res;
}

// This fucntion gets a concert and sets the concert's name due to the user's request.
void setConcertName(Concert* concert)
{
	printf("Enter concert name: ");
	char* concert_name = getString();
	int name_len = strlen(concert_name); // get size of name to allocate memory later. 
	concert->name = (char*)malloc(name_len * sizeof(char));
	checkMemoryAllocation(concert->name);
	strcpy(concert->name, concert_name); // copy the new name into the concert struct. 
}

// This fucntion gets a concert and sets the users date and hour request for the concert.
void setConcertDate(Concert* concert)
{
	char flush;
	printf("Enter concert date: ");
	scanf("%d%d%d", &concert->date_of_concert.day, &concert->date_of_concert.month, &concert->date_of_concert.year);

	flush = getchar(); // in order to not include the '\n' from before. 
	printf("Enter concert hour: ");
	char* concert_hour;
	concert_hour = getString();
	concert->date_of_concert.hour = getHourFromString(concert_hour);
}

// This fucntion gets a concert and sets the users requested instruments for the concert. 
void setConcertInstruments(Concert* concert)
{
	CIList concert_instruments_list = createConcertInstrumentList();
	char* instrument_name = getString();// get instruments from the user. 
	ConcertInstrument concert_intrument;
	setConcertInstrumentDetails(&concert_intrument);


}

// This fucntion sets the concert's instruments details from the user. 
void setConcertInstrumentDetails(ConcertInstrument* concert_instrument)
{
	printf("Enter concert's details: ( amount, id, importance by '0'\\'1' : ");
	scanf("%d%d%c", &concert_instrument->inst, &concert_instrument->num, concert_instrument->importance);
}

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
bool checkIfMusicianExists()
{
	bool check = false;
	/*need to create musician array first then check if exists due to instruments*/
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

// This fucntion creates an empty concert instruments list. 
void makeEmptyConcertInstrumentList(CIList* ci_list)
{
	ci_list->head = NULL;
	ci_list->tail = NULL;
}

// This fucntion inserts the CINode into the end of the list. 
void insertNodeToEndList(CIList* ci_list, ConcertInstrument data)
{
	CINode* ci_node = (CINode*)malloc(sizeof(CINode));
	checkMemoryAllocation(ci_node);
	ci_node->ci_data = data;
	ci_node->next = NULL;
	insertDataToEndList(ci_list, ci_node);
}

// This fucntion inserts the data of the CI_NODE to the end of the list
void insertDataToEndList(CIList* ci_list, CINode* new_ci_node)
{
	if (checkEmptyList(ci_list))
		makeEmptyConcertInstrumentList(ci_list);
	else 
	{
		ci_list->tail->next = new_ci_node; 
		ci_list->tail = new_ci_node;
	}
}

// The function creates an instrument list due to the user's input
CIList createConcertInstrumentList()
{
	/*creates a new list of instruments due to the users input*/
	
}

// This fucntion prints entire concert details. 
void printConcertDetails(Concert concert)
{
	printf("Concert name: ''%s''\n", concert.name);
	printf("Concert date: %d %d %d\n", concert.date_of_concert.day,
    concert.date_of_concert.hour, concert.date_of_concert.year);
	printConcertHour(concert.date_of_concert.hour);
	//print concert Musicians fucntion here (artist, artist instruments, price for playing on each instrument).

}

// This fucntion gets a float and prints the hour in an HH:MM format
void printConcertHour(float time)
{
	int hour = (int)time;
	float minutes = (time - (int)(time)) * FLOAT_CAST;
	printf("Concert hour : %.2d:%.2d", hour, (int)(ceil(minutes)));
}

