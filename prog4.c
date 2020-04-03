/*
Zachary Ikpefua
ENGR 2220
Project 4
Spring 2018

Purpose: To Convolude two different input files and store the result in an output file
			named by the user

Estimation: I estimated that this project will take two hours, however it took around
				3 days to complete

Known Bugs: -NONE-
*/

#include <stdio.h>
#include <stdlib.h>
#define INPUT0 0
#define INPUT1 1
//Structure for data
struct TData
{ int MinIndex, MaxIndex, Points;
  float *pValue;
} Input[2],Output;


void Convolve(struct TData Input[2], struct TData *Output);

int main (int argc,char* argv[]){

  int i = 0;
  int trash1 = 0;
  float trash2 = 0;
  FILE *input1;
  FILE *input2;
  FILE *out;


  Input[INPUT0].Points = 0;
  Input[INPUT1].Points = 0;

  input1 = fopen(*(argv + 1),"r");
  input2 = fopen(*(argv + 2),"r");

//Check to see if user actually entered in 3 files
  if(argc != 4){
	  fprintf(stderr,"Please enter 2 input file and 1 output file\n");
	  exit(1);
  }
//Check to see if each input file exists
  if(input1 == NULL || input2 == NULL){
    fprintf(stderr,"File open error. Exiting program\n");
    exit(1);
  }

 //Find out how many points are in each file and store them inside trash variables
  while(fscanf(input1,"%d %f",&trash1,&trash2) != -1){
    Input[INPUT0].Points += 1;
	}
  while(fscanf(input2,"%d %f",&trash1,&trash2) != -1){
    Input[INPUT1].Points += 1;
	}

//Create a dynamically declared array
  Input[INPUT0].pValue =(float*)malloc(Input[INPUT0].Points * sizeof(float));
  Input[INPUT1].pValue =(float*)malloc(Input[INPUT1].Points * sizeof(float));

//Rewind file in order to read in actual data
  rewind(input1);
  rewind(input2);

//Scan in File 1

	for(i = 0; i < Input[INPUT0].Points;i++){
 		if(i == 0){
    		fscanf(input1,"%d %f",&Input[INPUT0].MinIndex,&Input[INPUT0].pValue[i]);
  		}
  		else if(i == Input[INPUT0].Points-1){
    		fscanf(input1,"%d %f",&Input[INPUT0].MaxIndex,&Input[INPUT0].pValue[i]);
  		}
  		else{
    		fscanf(input1,"%d %f",&trash1,&Input[INPUT0].pValue[i]);
  		}
	}

//Scan in File 2
	for(i = 0; i < Input[INPUT1].Points; i++){
  		if(i == 0){
    		fscanf(input2,"%d %f",&Input[INPUT1].MinIndex,&Input[INPUT1].pValue[i]);
  	}
  		else if(i == Input[INPUT1].Points-1){
    		fscanf(input2,"%d %f",&Input[INPUT1].MaxIndex,&Input[INPUT1].pValue[i]);
  		}
  		else{
    		fscanf(input2,"%d %f",&trash1,&Input[INPUT1].pValue[i]);
  		}
	}

//Adjust the vector's starting position
	Input[INPUT0].pValue -= Input[INPUT0].MinIndex;
	Input[INPUT1].pValue -= Input[INPUT1].MinIndex;

Convolve(Input,&Output);

	//Prepare to write into output file
	out = fopen(*(argv + 3),"w");
	for(i = Output.MinIndex;i<= Output.MaxIndex;i++){
		fprintf(out,"%d\t%f\n",i,Output.pValue[i]);
	}

	//Close and free the memmory
	fclose(input1);
	fclose(input2);
	fclose(out);

	fprintf(stdout,"Convolution Finished! Please check your output file!\n");
	return 0;
}

/*
Inputs: Input[INPUT0], Input[INPUT1], outPtr-> Used pointer to modify Output
Outputs: None is void
Purpose:	To convolve the input functions/data points and to modify the
			output vector
*/
void Convolve(struct TData In[2],struct TData *outPtr){
	int n = 0;
	int m = 0;
	int s = 0; //Variable for shifting the function

	outPtr->MinIndex = In[INPUT0].MinIndex + In[INPUT1].MinIndex;
	outPtr->MaxIndex = In[INPUT0].MaxIndex + In[INPUT1].MaxIndex;
	outPtr->Points = (outPtr->MaxIndex - outPtr->MinIndex) + 1;
	outPtr->pValue = (float*)calloc(outPtr->Points,sizeof(float)); //Set a dynamically declared arry, but initallize all values to be zero
	outPtr->pValue -= outPtr->MinIndex;

	for(n = outPtr->MinIndex; n <= outPtr->MaxIndex; n++){
		outPtr->pValue[n] = 0;
		for(m = In[INPUT1].MinIndex; m <= In[INPUT1].MaxIndex; m++){ //Keep running while m is between the stationary function's range
			s = n - m;
			if(s >= In[INPUT0].MinIndex && s <= In[INPUT0].MaxIndex){ //If n - m is between the moving function's range
				outPtr->pValue[n] += In[INPUT0].pValue[s] * In[INPUT1].pValue[m];//Convolve function
			}
		}
	}
	return;
}
