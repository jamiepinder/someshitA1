/****************************************************************
 					Jamie Pinder 0831678 
					CIS*2750 Assignment 1 
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/VCardParser.h"
#include "../include/cardFunctions.h"
#include "../include/LinkedListAPI.h"


int main(int argc, char* argv[]){
    /*int err=0;
    Card** card;
    err = createCard(argv[1],card);*/
	FILE* fp;
    char* line;
    fp=fopen(argv[1],"r");

    line=unfoldLine(fp);
    printf("LINE IS:  %s\n",line);
    parseLine(line);
    printf("\n");

    while(line[0]!='\0'){
    	free(line);
    	line=unfoldLine(fp);
    	printf("LINE IS:  %s\n",line);
    	parseLine(line);
    	printf("\n\n");

    }
    free(line);
    fclose(fp);
    return 0;
}

VCardErrorCode createCard(char* fileName, Card** obj){
    /*parses and allocates a Card obj*/
    FILE* fp;
    char* line=malloc(sizeof(char)*1000);
    char seg[128];

    int i=0;
    int k=0;
    int FNFlag=0;

    fp=fopen(fileName,"r");
    if(fp==NULL){
        /*obj==NULL;*/
        printf("INVALID FILE\n");
        return INV_FILE;
    }

    line=unfoldLine(fp);
    while(line[0]!='\0'){
    	if(FNFlag==0){
    	/*we haven't found the first fn property*/ 
    		while(i<strlen(line)){

	    		if(line[i]==':' || line[i]==';'){
	    			/*special character was found*/
	    			if(strcmp("FP",seg)==0 && FNFlag==0){
	    				/*this is the first FN property*/
	    				FNFlag=1;
	    				printf("FN SEGMENT FOUND: %s\n",seg);
	    				/*parse/set the property values*/
	    			}
		    		seg[k]=line[i];
		    		k++;
		    		i++;
	    		}
    		}
    	}
		free(line);
    	line=unfoldLine(fp);
    }

    fclose(fp);
    return 1;
    return OK;
}



void deleteProperty(void* toBeDeleted){
	Property* prop = toBeDeleted; 

	free(prop->name);
	free(prop->group);
	freeList(prop->parameters);
	freeList(prop->values);
	free(prop);
}

char* printProperty(void* toBePrinted){
	Property* prop = toBePrinted;
	char* printString = malloc(sizeof(char)*2000);

	strcpy(printString,prop->name);
	strcat(printString," ");
	strcat(printString,prop->group);
	strcat(printString," ");

	strcat(printString,toString(prop->parameters));
	strcat(printString," ");
	strcat(printString,toString(prop->values));

	return printString;
}

void deleteParameter(void* toBeDeleted){
	free(toBeDeleted);
}

char* printParameter(void* toBePrinted){
	Parameter* param = toBePrinted;
	char * printParam = malloc(sizeof(char)*500);

	strcpy(printParam,param->name);
	strcat(printParam,param->value);

	return printParam;

}
void deleteValue(void* toBeDeleted){
	free(toBeDeleted);

}
/*
char* printValue(void* toBePrinted){
	c
}
*/
void deleteDate(void* toBeDeleted){
	free(toBeDeleted);
}

char* printDate(void* toBePrinted){
	DateTime* date = toBePrinted;
	char * printString = malloc(sizeof(char)*500);

	strcpy(printString," ");

	if(date->UTC==true){
    	strcat(printString,date->date);
    	strcat(printString," ");
    	strcat(printString,date->time);
	}
	if(date->isText==true){
		strcat(printString,date->text);
	}

	return printString;
}

int compareDates(const void* first,const void* second){
	return 0;
}

/*
int compareParameters(const void* first,const void* second);

int compareValues(const void* first,const void* second);

int compareProperties(const void* first,const void* second){
*/
