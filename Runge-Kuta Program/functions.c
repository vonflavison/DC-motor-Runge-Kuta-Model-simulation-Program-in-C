#include "functions.h"

//vARIABLE DEFINITIONS
double StepFunc = 0.0;

//1. This function rquest input data from users
double getValue(char *InputType, double Value){
	printf("%s = ", InputType); //InputType = character string describing the type of response
    scanf("%lf", &Value);

	return Value;
}

//2. step function							 	
double stepResponse(double Time, double Step){
    if(Time >= 0 && Time <= 0.02){  	
		StepFunc = 0;                        	
	}else{                                   	
		StepFunc = Step;                     	
	}                                        	   
	
	return StepFunc;                         	
}
