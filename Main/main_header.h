//Ronen Gelmanovich 319047718
//Ori Teicher 209279405

/*Main header*/
#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>


/*Consts*/
#define INSTRUMENT_NAME_SIZE 150
#define	LINE_LENGTH 150
#define DELIMITERS " ,.;:?!-\t'()[]{}<>~_"
#define NUMBERS "0123456789\\n"
#define NOT_FOUND -1

/*Function refrences*/
void checkMemoryAllocation(void* ptr);
void checkFileOpening(FILE* f);