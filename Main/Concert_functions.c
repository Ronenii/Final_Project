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

// The fucntion gets a string from the user and allocates memory due to the ammount of letters of the input untill \n is being inserted. 
// O(n) - n is the string input length. 
char* getString()
{
	int logSize = 0, phySize = 1;
	char c;
	char* string = (char*)malloc(sizeof(char) * phySize); // sets memory for first char. 
	checkMemoryAllocation(string);
	c = getchar();
	while (c != '\n')
	{
		if (logSize == phySize)
		{
			phySize *= 2; // for realloc allocation the pyhsical size need to be multiplied by two. 
			string = (char*)realloc(string, sizeof(char) * phySize);
		}
		string[logSize] = c;
		logSize++;
		c = getchar();
	}
	string[logSize] = '\0'; // end of string. 
	return string;

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

// The fucntion checks if memory allocation succeeded. 
void checkMemoryAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Memory Allocation Failed! Ending program.");
		exit(1);
	}
}