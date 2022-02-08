
 #include <stdio.h>
#include <stdint.h>
#include "PLL.h"
#include "UART.h"

#include <string.h>

#include "crc.h"
//---------------------OutCRLF---------------------
// Output a CR,LF to UART to go to a new line
// Input: none
// Output: none
void OutCRLF(void){
  UART_OutChar(CR);
  UART_OutChar(LF);
}
//debug code
int main(void){




        char string[20];  // global to assist in debugging


        PLL_Init();       // 50  MHz
        UART_Init();              // initialize UART
        OutCRLF();


        while(1)
          {

                    UART_OutString("DataToBeSend: ");
                    UART_InString(string,19);
                    UART_OutString(" DataSent=");
                    UART_OutString(string);
                    encapsulation_sendframe(string);
                    OutCRLF();
          }

}
