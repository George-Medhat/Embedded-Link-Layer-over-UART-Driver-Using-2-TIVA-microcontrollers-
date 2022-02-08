
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
  char data[20];
  uint32_t TX_CRC;
  uint32_t RX_CRC;
  PLL_Init();       // 50  MHz
  UART_Init();              // initialize UART
  OutCRLF();

  while(1)
  {

      //Receive source MAC addresses
      UART_OutString("  Source   MAC   addresses=");
      UART5_InString(string,19);  OutCRLF();

      //Receive Destination MAC addresses
      UART_OutString(" Destination MAC addresses=");
      UART5_InString(string,19);  OutCRLF();


      //Receive Data Length
      UART_OutString(" Data Length(In Bytes) =");
      UART5_InUHex(); OutCRLF();


      //Receive Data
      UART_OutString(" Data Recieved=");
      UART5_InString(data,19);  OutCRLF();

      //Receive TX CRC
      UART_OutString(" TX CRC=");
      TX_CRC=UART5_InUHex(); OutCRLF();

     //compute RX CRC
      UART_OutString(" RX CRC=");
      RX_CRC=crcSlow(data, strlen(data));
      UART_OutUHex(RX_CRC); OutCRLF();


      //Compare TX CRC & RX CRC to validate data sent
      if((int)TX_CRC==(int)RX_CRC)
      {      UART_OutString(" No ERROR, Data is sent correctly");
      OutCRLF();

      }
      else    { UART_OutString(" ERROR, Data is sent incorrectly");
      OutCRLF();
      }
      OutCRLF();
      OutCRLF();
  }

}
