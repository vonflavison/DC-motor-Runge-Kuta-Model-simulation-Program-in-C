/*This header file contains the motor paramters and functions for accesing the paramters*/
#ifndef PARAM_H_
#define PARAM_H_

#include <stdio.h>

//struct for defining plant paramters
struct PlantParams
{
    double Ke; //Back emf constant [V/ms^-1]
    double Kf; //Friction (or drag) coefficient [-]
    double Kt; //Torque Constant [Nm/A]
    double J;  //motor inertia [kg*m^2]
    double R;  //Resistance [ohm]
    double L;  //Inductance [H]
};

//FUNCTION DECLARATIONS
struct PlantParams getParameters(void); //Prompts user to enter values for motor parameters

#endif
