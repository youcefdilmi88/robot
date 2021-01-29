#include "diagnostic.h"
#include "sensors.h"


/********************************************
 * @brief Transmet l'état du bouton interrupt
 * @param ---
 * @return void
 ********************************************/

void transmitButton()
{	
	bool isPressed = (PIND & 0x04);
	UART_transmit(BUTTON_STATE);
	if (isPressed)
		UART_transmit(0x01);
	else 
		UART_transmit(0x00);
}

/********************************************
 * @brief Transmet l'état du capteur gauche
 * @param ---
 * @return void
 ********************************************/

void transmitLeftSensor()
{
    uint8_t value = value_to_interval_diagnostic_left(sensors.getLeft());
    UART_transmit(LEFTSENSOR);
    UART_transmit(value);

}

/***********************************************************************************
 * @brief Transmet l'état du capteur droit
 * @param ---
 * @return void
 ***********************************************************************************/

void transmitRightSensor()
{
    uint8_t value = value_to_interval_diagnostic_right(sensors.getRight());
    UART_transmit(RIGHTSENSOR);
    UART_transmit(value);
    
}

/***********************************************************************************
 * @brief Transmet les infos du robots en appelant UART_transmit
 * @param ---
 * @return void
 ***********************************************************************************/

void sendInfo()
{
	char nom[7] = "Claude";
	char session[5] = "18-1";
	char team[6] = "96108";
	UART_transmit(NAME); //nom
	UART_transmit_string(nom);
	UART_transmit(TEAM); //équipe
	UART_transmit_string(team);
	UART_transmit(SECTION); //groupe
	UART_transmit(0x5);
	UART_transmit(SESSION); //session
	UART_transmit_string(session);
	UART_transmit(BASE_COLOR); //couleur
	UART_transmit(0x1);
}

/***********************************************************************************
 * @brief Ajuste la vitesse de la roue gauche selon la valeur reçue
 * @param data : ratio de la vitesse
 * @return void
 ***********************************************************************************/

void operateLeftWheel(uint8_t data)
{
	int8_t vitesse = (int8_t)data;
	switch (vitesse)
	{
		case (-100): 
			setLeftWheel(255, BACKWARD);
			break;

		case (-75):
			setLeftWheel(192, BACKWARD);
			break;

		case (-50):
			setLeftWheel(128, BACKWARD);
			break;

		case (-25):
			setLeftWheel(255, BACKWARD);
			_delay_ms(100);
			setLeftWheel(64, BACKWARD);
			break;

		case 0:
			setLeftWheel(0, FORWARD);
			break;

		case 25:
			setLeftWheel(255,FORWARD);
			_delay_ms(100);
			setLeftWheel(64, FORWARD);
			break;

		case 50:
			setLeftWheel(128, FORWARD);
			break;

		case 75:
			setLeftWheel(192, FORWARD);
			break;

		case 100:
			setLeftWheel(255, FORWARD);
			break;

		default: 
			break;
	}
}

/***********************************************************************************
 * @brief Ajuste la vitesse de la roue droite selon la valeur reçue
 * @param data : ratio de la vitesse
 * @return void
 ***********************************************************************************/

void operateRightWheel(uint8_t data)
{
	int8_t vitesse = (int8_t)data;
	switch (vitesse)
	{
		case (-100): 
			setRightWheel(255, BACKWARD);
			break;

		case (-75):
			setRightWheel(192, BACKWARD);
			break;

		case (-50):
			setRightWheel(128, BACKWARD);
			break;

		case (-25):
			setRightWheel(255,BACKWARD);
			_delay_ms(100);
			setRightWheel(64, BACKWARD);
			break;

		case 0:
			setRightWheel(0, FORWARD);
			break;

		case 25:
			setRightWheel(255,FORWARD);
			_delay_ms(100);
			setRightWheel(64, FORWARD);
			break;

		case 50:
			setRightWheel(128, FORWARD);
			break;

		case 75:
			setRightWheel(192, FORWARD);
			break;

		case 100:
			setRightWheel(255, FORWARD);
			break;

		default:
			break; 
	}
}

/***********************************************************************************
 * @brief Allume la del selon la couleur reçue
 * @param data : couleur
 * @return void
 ***********************************************************************************/

void operateLED(uint8_t data)
{
	switch(data)
	{
		case 0:
			PORTC = OFF;
			break;
		case 1:
			PORTC = GREEN;
			break;
		case 2:
			PORTC = RED;
			break;
		default:
			break;
	}
}

/***********************************************************************************
 * @brief 
 * @param ---
 * @return void
 ***********************************************************************************/

void diagnostic_run()
{	
	DDRD = 0xF0;
    DDRC = OUTPUT;
    LED_diagnostic();
    initialisationUART();
    sensors.initConversion();
    init_pwm();
    uint8_t request = 0;
   	uint8_t data = 0;

    for(;;) {
	    while( !(UCSR0A & (1<<RXC0)) ){}
	    cli();
   		request = UDR0;
        while( !(UCSR0A & (1<<RXC0)) ){}
        data = UDR0;
   		action(request, data);
   		sei();
	}
}

/***********************************************************************************
 * @brief Effectue l'Action selon l'instruction reçue
 * @param data : operande de l'action , request : instruction demandée
 * @return void
 ***********************************************************************************/

void action(uint8_t request, uint8_t data){
		
    switch (request) {
			case LEFTSPEED:
				operateLeftWheel(data);
				operateLeftWheel(data);
				break;

			case RIGHTSPEED:
				operateRightWheel(data);
				operateRightWheel(data);
				break;

			case LEDCOLOR:
				operateLED(data);
				operateLED(data);
				break;

			case INFO:
				sendInfo();
				break;

			default:
				error_green_red(500, 500);
		}
}

