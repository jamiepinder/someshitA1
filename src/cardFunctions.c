#include "../include/cardFunctions.h"

char* unfoldLine(FILE* fp){
	char* line = malloc(sizeof(char)*2000);
	line[0]='\0';
	int toCopy;
	int i=0;

	toCopy=fgetc(fp);
	while(toCopy!=EOF){

		if(toCopy=='\r'){
			toCopy=fgetc(fp);

			if(toCopy=='\n'){
				toCopy=fgetc(fp);

				if(toCopy!=' '){
					fseek(fp,-1,SEEK_CUR);
					return line;
				}
			}
		}
		line[i]=toCopy;
		i++;
		line[i]='\0';
		toCopy=fgetc(fp);
	}
	return line;
}

void parseLine(char* line){
	/*Property* newProp;*/
	char seg[300];

	int i=0;
	int k=0;

	int firstDelim=0;
	int paramMode=0;
	int valueMode=0;
	int pValueMode=0;


	while(k<strlen(line)){
        /*if this is the first colon/semi colon this is the name*/
		if((line[k]==':' || line[k]==';') && firstDelim ==0){
			/*found ; so add whats in next seg to param*/
			if(line[k]==';'){
				paramMode = 1;
			}
			/*found : so add whats in next seg to value*/
			if(line[k]==':'){
				valueMode = 1;
			}
			/*set prop name to seg*/
			printf("PROPERTY NAME: %s\n",seg);
			/*strcpy(newProp->name,seg);*/
			memset(seg,'\0',300);
			firstDelim =1;
			i=0;
		}

		/*if the value mode is set then the following is a list of 
		values separated by semi colons*/
		if(valueMode==1){
			/*if(line[k]==';'&& pValueMode==1){
				printf("PARAM VALUE: %s\n",seg);
				memset(seg,'\0',300);
				i=0;
				pValueMode=0;
			}*/
			if(line[k]==';'){
				if(strlen(seg)==1){
					printf("EMPTY PROP VAL: \n");
				}
				else
					printf("PROP VALUE: %s\n",seg);
				memset(seg,'\0',300);
				i=0;
			}

		}

		/*if the parameter mode is set then there are parameter(s) 
		 followed by a value (which will be delimeted with colon*/
		else if(paramMode==1){
			if(line[k]==':'&& pValueMode==1){
				/*set value mode to 1 as the next segment is the value
				 seg (current) is a parameter
				 add seg to param list*/
				printf("PARAM VALUE:  %s\n",seg);
				memset(seg,'\0',300);
				/*unset param mode*/
				valueMode=1;
				paramMode=0;
				pValueMode=0;
				i=0;
			}

			if(line[k]==';' && pValueMode==1){
				/*this is another parameter to be added to the list*/
				printf("PARAM VALUE:  %s\n",seg);
				memset(seg,'\0',300);
				i=0;
			}
			/*else if(line[k]==';'){
				printf("PARAM VALUE 3: %d  %s\n",k,seg);
				memset(seg,'\0',300);
				i=0;
			}
			else if(line[k]==':'){
				printf("PARAM NAME: %s\n",seg);
				memset(seg,'\0',300);
				i=0;
			}*/

			else if(line[k]=='='){
				/*segment previous to this is the parameter name*/
				/*the next segment is the value*/
				printf("PARAM NAME:  %s\n",seg);
				memset(seg,'\0',300);
				pValueMode=1;
				i=0;
			}

		}

		seg[i] = line[k];
		i++;
		k++;

		if(k==strlen(line)){
			if(paramMode==1){
				printf("PARAM NAME: %s\n",seg);
				memset(seg,'\0',300);
			}
			else if(valueMode==1){
				printf("PROPERTY VALUE: %s\n",seg);
				memset(seg,'\0',300);
			}
		}	

	}
	/*check that there is propterty name, that there are values, and
	(if empty) the group and parameters are not null*/ 
}

