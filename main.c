/*******************************************************************************
 * (c) Copyright 2012-2015 Microsemi SoC Products Group.  All rights reserved.
 *
 *  Simple SmartFusion2 microcontroller subsystem UART example program
 *  transmitting a greeting message using UART1. Any characters received on
 *  UART1 are echoed back. The UART configuration is specified as part of the
 *  call to MSS_UART_init().
 *
 * SVN $Revision: 7985 $
 * SVN $Date: 2015-10-12 12:26:08 +0530 (Mon, 12 Oct 2015) $
 */
#include "drivers/mss_uart/mss_uart.h"
#include <stdio.h>
#include <stdlib.h>

//#define UART_RUNS 10
#define UART_RUNS 0
#define FIB_MAX   39

mss_uart_instance_t * const gp_my_uart = &g_mss_uart1;



static int fib(int i) {
    return (i>1) ? fib(i-1) + fib(i-2) : i;
}

int main() {
	char str[80];
    size_t rx_size;
    uint8_t rx_buff[1];
    
    /* Turn off the watchdog */
    SYSREG->WDOG_CR = 0;
    
    MSS_UART_init(gp_my_uart,
                  MSS_UART_57600_BAUD,
                  MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);

    /*--------------------------------------------------------------------------
     * Send greeting message over the UART.
     */
    MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"\n\r\n\r**********************************************************************\n\r");
    MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"******************** SmartFusion2 MMUART Example *********************\n\r");
    MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"**********************************************************************\n\r");
    MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"Hello world22.\n\r");

    int i, j;

    MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"starting fib...\n\r");

    for (j=0; j< UART_RUNS; j++) {
    	sprintf(str, "--------------  Run %d of %d ---------------------\n\r", j+1, UART_RUNS);
        MSS_UART_polled_tx_string(gp_my_uart, str);
        for(i=0; i< FIB_MAX; i++) {
        	sprintf(str, "fib(%d) = %d\n\r", i, fib(i));
            MSS_UART_polled_tx_string(gp_my_uart, str);
        }
    }

    MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"finishing...\n\r");
    MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"Now it will output back (echo) your input\n\r");

    for (;;)
    {
        rx_size = MSS_UART_get_rx(gp_my_uart, rx_buff, sizeof(rx_buff));
        if( rx_size > 0 )
        {
            MSS_UART_polled_tx(gp_my_uart, rx_buff, sizeof(rx_buff));
        }
    }
}


