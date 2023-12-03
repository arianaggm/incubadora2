#include "config.h"
#include "LCD_PORTD.h"
#include <xc.h>
#include "functions.h"
#include "keypad.h"



void myChars(void);
void delay(int a);
void configPorts(void);
void specialChars(void);
void configInterrupts(void);
void T0_1s(void);
void contar(void);
void programarTiempo(void);
void check4Buttons(void);


char y = 0;
char contador = 0;
char bandera = OFF;
int speed = 0;
int espera = 100;
int x = 0;
char s_unit = '0';
char s_dec = '0';
char m_unit = '0';
char m_dec = '0';
char SETTING = 1;
char COUNT_END = 0;
char H_DC = 0;

double Kp = 10;
double Ki = 1;
double Kd = 0;
double I = 0;

char duty3;
char HiLo;

int lec1;


void main(void) {
    OSCCON = 0x7F; //8MHz      // Start the oscillator
    iniLCD();
    LCDcommand(DispOn);
    configADC(1);
    
    BLUE_pin = OUT;
    GREEN_pin = OUT;
    RED_pin = OUT;
    iniLCD();
    unsigned int lect1;
    configHeater();
    setHEATER_DC(HDC);
    
    
    //lec1 = analogRead(0);
    unsigned int lec1;
    double volts;
    double temp;
    LCDprint(11,"Temperature; ", 0); //imprime temperatura
    while(1){
        lec1 = analogRead(SENSOR);
        volts = 5.0*lec1/1023.0;
        temp = volts*10.018-0.15;
        heatingstatus(temp);
        updateLCD(temp);
        updateHEAT(temp);
        __delay_ms(500);
    }
    return;
}
    

void heatingstatus(double temp) {
    if (temp < DESIRED_TEMP - 2) {
        RED = LOW; //blue
        GREEN = LOW;
        BLUE = HI;
    } else if (temp < DESIRED_TEMP +1) {
        RED = LOW; //green
        GREEN = HI;
        BLUE = LOW;
    } else if (temp < DESIRED_TEMP + 3) {
        RED = HI; // yellow
        GREEN = HI;
        BLUE = LOW;
    } else {
        RED = HI; // red
        GREEN = LOW;
        BLUE = LOW;
    }
}


void updateLCD (double temp) {
    double decimals;
    MoveCursor (0, LINE_DOWN);
    LCDint(temp);
    LCDchar('.');
    decimals=temp-(int)temp;
    decimals*=100;
    if (decimals<10){
        LCDchar('0');
    }
    LCDint(decimals);
    LCDchar('  ');
    LCDchar(DEGREE);
    LCDchar('C');
    LCDchar('   ');
    if (temp<35){
        LCDprint(8,"COLD      ",0);
    }else if (temp<37.5){
        LCDprint(8,"NORMAL      ",0);
    }else if (temp<40){
        LCDprint(8,"WARM      ",0);
    }
    else{
        LCDprint(8,"HOT      ",0);
    }
        
}

void configHeater(){
    HEATER_out = OUT;
    PR2 =_XTAL_FREQ/(4.0*PWM_FREQ*16.0)-1;
    setHEATER_DC(50);
    T2CON = 0b00000111; //T2 ON, <1:0>prescaler = 16
    CCP1CON = 0b00001100; //<5:4>=<00> PWM mode
    return;
}

void setHEATER_DC(char x){
    if (x>100){
        x =100;
    }
    int val = x*multiplier;
    CCPR1L = (val - val%4)/4;
    CCP1CONbits.DC1B = val%4;
}

//void updateHEAT(double temp){
//        if (temp < t_objective){
//            HDC++;
//            setHEATER_DC(HDC);
//        }else{
//            HDC--;
//            setHEATER_DC(HDC);
//        }
//}

double PID(double temp){
    double err = t_objective-temp;
    double P = Kp*err;
    I = I + Ki*err*(Tau/1000.0);
    return P + I;
    
}

void updateHEAT(double temp){
    PID(temp);
    setHEATER_DC(H_DC);
    /*
    if(temp < t_objective){
            H_DC++;
            setHEATER_DC(H_DC);
        }else{
            H_DC=0;
            setHEATER_DC(H_DC);
        }
     * */
}
