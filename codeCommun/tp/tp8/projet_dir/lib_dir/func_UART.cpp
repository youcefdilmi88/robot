#include "func_UART.h" 




/**
* @brief Initialiser la communication avec USART en remplissant les bons registres
* @return void
*/
void initialisationUART ( void ) 
{
    // 2400 bauds.
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la reception et la transmission par le UART0
    UCSR0A = 0 ;
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    // Format des trames: 8 bits, 1 stop bits, none parity
    UCSR0C = (1 << UCSZ10) | (1 << UCSZ11);
}

unsigned char USART_Receive( void )
{
   /* Wait for data to be received */
   while ( !(UCSR0A & (1<<RXC)) )
      ;
   /* Get and return received data from buffer */
   return UDR0;
}

/**
* @brief Transmet un char* ou un uint8_t
* @param donnee La donnée à transmettre
* @return void
*/
void UART_transmit(uint8_t donnee) 
{
    while ( !( UCSR0A & (1<<UDRE0)) ){} //W ait for empty transmit buffer
    UDR0 = donnee; // Put data into buffer, sends the data
}

/**
* @brief Transmet un string
* @param string Le tableau de caratère à transmettre
* @return void
*/
void UART_transmit_string(char* string) 
{
    for (uint8_t i=0; string[i]!='\0'; i++) {
        UART_transmit(string[i]);
    }
}

/**
* @brief Transmet un nombre de 16 bits
* @param nombre Nombre de 16 bits à transmettre
* @return void
*/
void UART_transmit_number(uint16_t nombre) 
{
    char buff[100];
    sprintf(buff, "nombre=%d\n",nombre); //Imprime un nombre sous forme de uint16_t dans un tableau de caractères en caractère ASCII
    UART_transmit_string(buff);
}
