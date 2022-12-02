#include <stdlib.h>

//USER DEFINED HEADER FILES
#include "functions.h"

/*System*/
double t_max = 0.0; //Simulation time [s]

//GLOBAL VARIABLES
double t = 0.0, tR = 0.0; //time [s]
double Vin = 0.0, Vin_max = 0.0; //Input voltage [V]
double val = 0.0; //Use in getValue(...) function to obtain user inputs

//COMANDLINE INSTRUCTIONS
/*1. System input instructions*/
char Input[] = "1. Reference voltage in [V]"; //This is printed on the command line requesting"Reference voltage in [V]" 
/*2. Simulation condtion instructions*/
char des_tmx[] = "1. Maximum simulation time in [s]"; //This is printed on the command line requesting "Max. simulation time in [s]"

struct PlantParams DCmotor; //Plant
double *Yn; //Plant model

//DEFINITION OF MAIN
int main(void){
    FILE *data, *gnp, *PlantSpecs;
    Yn = (double*)malloc(3*sizeof(double));

    //Open files for writing data
    data = fopen("ModelData.dat", "w"); //For saving t, Theta(t), w(t), & i(t)
    PlantSpecs = fopen("ParamData.dat", "w"); //For saving Motor parameters: Ke, Kf, Kt, J, R, & L

    printf("\n      **** SIMULATION PROGRAM FOR DC MOTOR ****\n");
    printf("             __________________________\n");
	printf("\nThe plant model is constructed using Runge-Kuta method.\n");
    printf("This program computes the model and plots the continues\n");
    printf("time characteristic curves of the solution of the model.\n");

    //Compute Model
    /*1. Request User to enter plant parameters*/
	DCmotor = getParameters();

    /*2. Get value for input voltage*/
	printf("\n  SYSTEM INPUT \n\n");
    Vin_max = getValue(Input, val);
    
    /*3. System computation loop*/
    printf("\n  SIMULATION CONDITION \n\n");
    t_max = getValue(des_tmx, val);

    /*3-1. Start simulation*/
    for (t = 0; t < t_max/TS; t++) //REMARK: t is converted to integer here
    {   
        if (t == 0)
        {
            /*1-1. save plant parameters in ParamData.dat file*/
            fprintf(PlantSpecs, "%s  %s     %s  %s  %s      %s\n", "Ke[V/ms^-1]", "Kf[-]", "Kt[Nm/A]", "J[kg*m^2]", "R[\u03a9]","L[H]");//Format the file headers
            fprintf(PlantSpecs, "%lf     %lf  %lf  %lf   %lf  %lf", DCmotor.Ke, DCmotor.Kf, DCmotor.Kt, DCmotor.J, DCmotor.R, DCmotor.L); //Save the data
            fclose(PlantSpecs);
            
            /*3-2. Format ModelData.dat file header: Time, Theta, w, i */
            //REMARK: UNICODE for printing the Greek characters Theta = "\u03B8", omega = "\u03c9"
            fprintf(data, "%s   %s    %s  %s\n", "Time[s]", "\u03B8[rad]", "\u03c9[rad/s]", "i[A]");
        }
		
		tR = t*TS; //t is converted back to real time here
		
		//4. Set value for input response
		Vin = stepResponse(tR, Vin_max);
		
       //5. Start Plant 
        /*5-1. save computed data of Model in ModelData.dat file*/
        fprintf(data, "%lf  %lf  %lf  %lf\n", tR, Yn[0], Yn[1], Yn[2]); //REMARK: Yn[0] = Theta(t), Yn[1] = omega(t), Yn[2] = i(t)

        /*5-2. run the model*/
        Yn = RungeKutaModel(DCmotor, Vin);  
    }
    free(Yn);
    fclose(data);

    //PLOT THE RESULTS
    /*1. start gnu plot*/
    gnp = popen("gnuplot -persistent", "w"); //-persistent keeps the plot open even when program terminates
    
    /*2-1.  plot the variables Theta(t), w(t), & i(t)*/
   fprintf(gnp, "set title 'Characteristic of \u03B8(t), \u03c9(t), and i(t) for Vin = 1.0V'\n"
                 "set xlabel 'Time [s]'\n"
                 "set xrange [0:2.5]\n"
                 "set yrange [0:0.5]\n"

                 "plot \"%s\" using 1:2 with lines linetype 1 title \"\u03B8(t) [rad]\",'' using 1:3 with lines linetype 2 title \"\u03c9(t) [rad/s]\",'' using 1:4 with lines linetype 3 title 'i(t) [A]' \n"
                 "quit\n", "ModelData.dat");

    pclose(gnp);
    
    printf("Simulation is completed! \n");

    return 0;
}
