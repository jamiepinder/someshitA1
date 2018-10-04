#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/VCardParser.h"


/*function that takes in the file pointer and returns an 
  unfolded line*/
char* unfoldLine(FILE* fp);

/*function that takes in the unfolded line and returns a 
  Property * to add to the list*/
void parseLine(char*);