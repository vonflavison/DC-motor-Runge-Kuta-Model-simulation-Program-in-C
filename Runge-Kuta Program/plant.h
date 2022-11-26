/*This file contains the Runge-Kuta and Euler Model for the plant*/
#ifndef PLANT_H_
#define PLANT_H_

#include "param.h"

//MACRO DEFINITIONS
/*Inverter Paramters*/
#define FS  (100000.0) //Carrier (or sampling) freqency of inverter [Hz]
#define TS	(1.0/((double)FS)) //Sampling Time period in [s]

/*Variables for Runge-Kuta Plant Models*/
extern double *f1, *f2, *f3, *f4; //derivatives of Runge-Kuta & Euler model
extern double Yn1[3], Yn2[3], Yn3[3], Yn4[3]; //array for holding the variables Theta(t), omega(t), & i(t)

//FUNCTION DECLARATIONS
double *DiffEquation(struct PlantParams plant, double *Variable, double InputVolt); //dx(t)/dt = Ax(t) + Bu(t)
double *RungeKutaModel(struct PlantParams plant, double InputVolt); //Yn+1 = Yn + H/6*f1 + H/3*f2 + H/3*f3 + H*f4

#endif
