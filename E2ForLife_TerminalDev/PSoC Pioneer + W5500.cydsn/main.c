/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

#include "w5500.h"

void ETH_PutChar( char ch );
uint16 ETH_GetChar( void );
void ETH_PutString( const char *str );

/* ------------------------------------------------------------------------ */
int main()
{
	uint8 socket;
	
	// Wait for IMP reset monitor on the WizIOShield-A board to come out of reset
	CyDelay(560);
	
	/*
	 * Initialize the hardware perepherals used to communicate
	 */
	ETH_CSN_Write(1);
	SPI0_Start();
	BLUE_Write(0);
	RED_Write(1);
	GREEN_Write(1);
	/* Initialize the w5500 */
	if (w5500_Start() != CYRET_SUCCESS) {
		RED_Write(0);
		for(;;);
	}
	
	socket = w5500_TcpOpenServer( 23 );
	w5500_TcpWaitForConnection( socket );
	GREEN_Write(0);
	BLUE_Write(1);
	RED_Write(1);
	w5500_TcpPrint( socket, "Hello World!\r\n");
	
	while (w5500_SocketSendComplete(socket) == 0) {
		CyDelay(1);
	}
	
	w5500_SocketClose( socket, 1 );
	
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
