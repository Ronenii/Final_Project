//Ronen Gelmanovich 319047718
//Ori Teicher 209279405
#include "concert_header.h"
/*Concert functions*/
#define NAME_SIZE 50
#define HOUR_SIZE 6
#define FLOAT_CAST 100.0
#define HOUR_CALC 10
/*Functions*/
#pragma warning(disable:4996)

// This fucntion gets a concert details from the user and returns him a matching concert due to his request. 
Concert getConcert()
{
	Concert concert_res;
	setConcertName(&concert_res);
	setConcertDate(&concert_res);
	return concert_res;
}

// This fucntion gets a concert and sets the concert's name due to the user's request.
void setConcertName(Concert* concert)
{
	char concert_name[NAME_SIZE];
	printf("Enter concert name: ");
	scanf("%s", &concert_name);
	int name_len = strlen(concert_name);
	concert->name = (char*)malloc(name_len * sizeof(char));
	strcpy(concert->name, concert_name);
}

// This fucntion gets a concert and sets the users date request for the concert.
void setConcertDate(Concert* concert)
{
	printf("Enter concert date: ");
	scanf("%d%d%d",concert->date_of_concert.day , concert->date_of_concert.month, concert->date_of_concert.year);
	printf("Enter concert hour: ");
	char concert_hour[HOUR_SIZE];
	scanf("%s", &concert_hour);
	concert->date_of_concert.hour = getHourFromString(concert_hour);
}

// The fucntion recieves a string in a form of an hour (for example : 20:30) and returns the string in a form of a float (in our example : 20.30) 
// O(n) - n is hour_string len. 
float getHourFromString(char* hour_string)
{
	int str_index = 0;
	float cur_num = 0;
	while (hour_string[str_index] != '\0')
	{
		cur_num = cur_num * HOUR_CALC; // each time the current number multiply by 10 to turn into an hour format. 
		if (isDigit(hour_string[str_index]))
			cur_num = cur_num + (hour_string[str_index] - '0'); // casts using ascii value to a float. 
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