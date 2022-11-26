#include "param.h"

//This function prompts users to enter values for the motor specifications
struct PlantParams getParameters(void){
    struct PlantParams plant;
    
    printf("\n  ENTER VALUES FOR THE MOTOR PARAMETERS\n\n");
    printf("1. Back EMF Constant, Ke [V/ms^-1] = ");
    scanf("%lf", &plant.Ke);

    printf("2. Coefficient of friction. Kf [-] = ");
    scanf("%lf", &plant.Kf);

    printf("3. Torque constant, Kt [Nm/A] = ");
    scanf("%lf", &plant.Kt);

    printf("4. Motor Inertia, J [kg*m^2] = ");
    scanf("%lf", &plant.J);

    printf("5. Electrical Resistance, R [ohm] = ");
    scanf("%lf", &plant.R);

    printf("6. Inductance, L [H] = ");
    scanf("%lf", &plant.L);

    return plant;
}
