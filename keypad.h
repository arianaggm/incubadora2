#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> 

char map[4][4] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

char getKey();
int checkCols();
char check_rows(int col);
#endif	/* XC_HEADER_TEMPLATE_H */
