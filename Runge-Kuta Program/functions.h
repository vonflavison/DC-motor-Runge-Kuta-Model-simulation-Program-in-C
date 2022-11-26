/*This file contains other funtions for performing conversions and input-output*/
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "plant.h"

//VARIABLE DECLARATION
extern double StepFunc; //Step and Ramp functions respctively [-]

//FUNCTION DECLATIONS
double getValue(char *InputType, double Value);
double stepResponse(double Time, double Step); 

#endif
