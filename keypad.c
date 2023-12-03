#include <xc.h>
#include "keypad.h"
    
int checkCols(){
    int col=4;
    if(PORTDbits.RD2==0){
        col = 0;
    }else if(PORTDbits.RD3==0){
        col = 1;
    }else if(PORTCbits.RC4==0){
        col = 2;
    }else if(PORTCbits.RC5==0){
        col = 3;
     }
return col;
}
    
char check_rows(int col){
    char tecla;
    if(col==4){
      tecla = ' ';
    }else{
      tecla = map[0][col];
     if(PORTCbits.RC6==0){
          tecla = map[0][col];
     }else if(PORTCbits.RC7==0){
          tecla = map[1][col];
     }else if(PORTDbits.RD4==0){
          tecla = map[2][col];
     }else if(PORTDbits.RD5==0){
          tecla = map[3][col];
     }
    }
    return tecla;
}
