#include "plant.h"

double *f1, *f2, *f3, *f4;
double Yn1[3] = {0.0,0.0,0.0}, Yn2[3] = {0.0,0.0,0.0}, Yn3[3] = {0.0,0.0,0.0}, Yn4[3] = {0.0,0.0,0.0};

//Function for computing dx(t)/dt = Ax(t) + Bu(t)
double *DiffEquation(struct PlantParams plant, double *Variable, double InputVolt){
    double K_e = plant.Ke, K_f = plant.Kf, K_t = plant.Kt, mJ = plant.J, mR = plant.R, mL = plant.L;
    
    double A[3][3] = {
        {0.0, 1.0, 0.0},
        {0.0, -(K_f/mJ), (K_t/mJ)},
        {0.0, -(K_e/mL), -(mR/mL)}
    };
    double B[3] = {0.0, 0.0, (1/mL)};
    double u = InputVolt; //i.e., u(t)

    double *X = Variable; //i.e., x(t) = {Theta(t), omega(t), i(t)}
    static double dX[3]; //This array contains the result dx(t)/dt

    //comput model dx(t)/dt = Ax(t) + Bu(t)
    for (int i = 0; i < 3; i++)
    {
        dX[i] = 0.0;
        for (int j = 0; j < 3; j++)
        {
            dX[i] += A[i][j]*X[j];
        }
        dX[i] += B[i]*u;  
    }
    
    return dX;
}

//This function computes the Runge-Kuta Model Yn+1 = Yn + H/6*f1 + H/3*f2 + H/3*f3 + H*f4
double *RungeKutaModel(struct PlantParams plant, double InputVolt){ 
    //Differential equations y = dx(t)/dt
    f1 = DiffEquation(plant, Yn1, InputVolt); //i.e., f1 = f(Yn1, tn)
    f2 = DiffEquation(plant, Yn2, InputVolt); //i.e., f2 = f(Yn1 + (H/2)*f1, tn + H/2)
    f3 = DiffEquation(plant, Yn3, InputVolt); //i.e., f3 = f(Yn1 + (H/2)*f2, tn + H/2)
    f4 = DiffEquation(plant, Yn4, InputVolt); //i.e., f3 = f(Yn1 + H*f3, tn + H)
        
    for (int k = 0; k < 3; k++)
    {
        Yn2[k] = Yn1[k] + (0.5*TS)*f1[k]; //i.e., Yn1 + (H/2)*f1
        Yn3[k] = Yn1[k] + (0.5*TS)*f2[k]; //i.e., Yn1 + (H/2)*f2
        Yn4[k] = Yn1[k] + TS*f3[k]; //i.e., Yn1 + H*f3
            
        //Runge-Kuta method: The solution, y, of a differential equation f = dy(t)/dt is given by:
		//Yn+1 = Yn + H/6*f1 + H/3*f2 + H/3*f3 + H/6*f4, H is time step
        Yn1[k] += (f1[k] + 2*f2[k] + 2*f3[k] + f4[k])*(TS/6); 
    }
       
    return Yn1;
}

