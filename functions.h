
#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

//frequencias
#define PWM_FREQ 2500
#define _XTAL_FREQ 8000000

//inonoffwi
#define ON 1
#define OFF 0
#define IN 1
#define OUT 0
#define HI 1
#define LOW 0

//colores
#define RED_pin TRISEbits.RE2 //red
#define GREEN_pin TRISEbits.RE1 //green
#define BLUE_pin TRISEbits.RE0 //blue
#define RED LATEbits.LE2 //red
#define GREEN LATEbits.LE1 //green
#define BLUE LATEbits.LE0 //blue

//temp
#define HEATER_out TRISCbits.RC2
#define DESIRED_TEMP 38     // Default desired temperature
#define SENSOR 0
#define DEGREE 223
#define Tau 250

void configADC (char CHANNELS);
unsigned int analogRead (char canal);
void configHeater (void);
void setHEATER_DC(char x);
double multiplier = _XTAL_FREQ/(PWM_FREQ*16.0*100.0);
void heatingstatus(double temp);
void updateLCD (double t);
double PID(double temp);
unsigned int analogRead(char canal);
void updateHEAT(double temp);
double t_objective = 38; //objetivo de temp
char HDC = 0; //heat duty cycle

#endif
