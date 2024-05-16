#include "tm4c123gh6pm.h"
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "uart7.h"
void UART7Init(void){
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R7;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;

    UART7_CTL_R &= ~0x01; //disable uart
    UART7_IBRD_R = 104 ; //integer baud rate divisor
    UART7_FBRD_R = 11 ; //float baud rate divisor
    UART7_LCRH_R |= 0x70 ; //fifo enable and width  8 bits
    UART7_CTL_R = 0X0301 ; //uart enable , rx enable , tx enable
    GPIO_PORTE_DEN_R |= 0X03; //digital enable
    GPIO_PORTE_AMSEL_R &= ~0x03; //clear analog mode
    GPIO_PORTE_AFSEL_R |= 0x03; //set alternate function
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R &= ~0xFF) | 0X00000011; //clear PE0 and PE1 then set them as uart

}

// intia portE uart7 as gps



uint8_t UART7_AVAILABLE(void){
        return (((UART7_FR_R & UART_FR_RXFE)) == UART_FR_RXFE) ? 0:1 ;
}

uint8_t UART7_read(void){
     while (UART7_AVAILABLE() != 1){};
    return (UART7_DR_R & 0xFF);
}

void UART7_write(char c){
    while ((UART7_FR_R & UART_FR_TXFF ) == UART_FR_TXFF){};
    UART7_DR_R = c;
    

