//Ronen Gelmanovich 319047718
//Ori Teicher 209279405
#include "concert_header.h"
/*Concert functions*/
#define NAME_SIZE 50
#define HOUR_SIZE 6
/*Functions*/
#pragma warning(disable:4996)

Concert getConcert()
{
	Concert concert_res;
	char concert_name[NAME_SIZE];
	setConcertName(concert_res);
	
}

void setConcertName(Concert concert)
{
	char concert_name[NAME_SIZE];
	printf("Enter concert name: ");
	scanf("%s", &concert_name);
	int name_len = strlen(concert_name);
	concert.name = (char*)malloc(name_len * sizeof(char));
	strcpy(concert.name, concert_name);
}

void setConcertDate(Concert concert)
{
	printf("Enter concert date: ");
	scanf("%d%d%d",&concert.date_of_concert.day , &concert.date_of_concert.month, &concert.date_of_concert.year);
	printf("Enter concert hour: ");
	char concert_hour[HOUR_SIZE];
	scanf("%s", &concert_hour);
}

float getHourFromString(char* hour_string)