/* 
 * Fichier: main.cpp
 * Auteurs: Maude Laflamme(1690784), Elisabeth Fagnan(1893587) et Youcef Anis Dilmi(1895231)
 * Équipe: 96108
 * Remise:
 * Description:
 */

#include "sensors.h"
#include "diagnostic.h"
#include "parcours.h"
#include "memoire_24.h"


Sensors sensors;

enum MODE {MODE_DIAGNOSTIC = 0x00, MODE_PARCOURS = 0x01};
uint8_t nextMode;
uint8_t oldMode;
uint8_t compteur_buzzer =1;





ISR (INT0_vect)
{
    if(capteur_principal == GAUCHE){
        set_pwm(200, 200, FORWARD, BACKWARD);
        _delay_ms(1000);
        set_pwm(200, 200, BACKWARD, FORWARD);
        capteur_principal = DROITE;
        capteur_secondaire = GAUCHE;
    }

    else{
        set_pwm(200, 200, BACKWARD, FORWARD);
        _delay_ms(1000);
        set_pwm(200, 200, FORWARD, BACKWARD);
        capteur_principal = GAUCHE;
        capteur_secondaire = DROITE;
    }
    EIFR |= (1 << INTF0); 
}

ISR (ADC_vect)
{
    
    if (nextMode == MODE_DIAGNOSTIC) {
            transmitButton();
        if (sensors.getPresentSensor() == LEFT_SENSOR) {
            sensors.setLeft();
            transmitLeftSensor();
            sensors.readRight();
      
        }
        else if (sensors.getPresentSensor() == RIGHT_SENSOR) {
            sensors.setRight();
            transmitRightSensor();
            sensors.readLeft();
        }
    }

    else if (nextMode == MODE_PARCOURS) {
        if (sensors.getPresentSensor() == LEFT_SENSOR) {
            sensors.setLeft();
            sensors.readRight();
      
        }
        else if (sensors.getPresentSensor() == RIGHT_SENSOR) {
            sensors.setRight();
            sensors.readLeft();
        }
    }
    
}


ISR (TIMER2_COMPA_vect)
{

    if ( ((1 <= compteur_buzzer) && (compteur_buzzer <= 20)) || ((31 <= compteur_buzzer) && (compteur_buzzer <= 50)) || ((61 <= compteur_buzzer) && (compteur_buzzer <= 80))){
        startTimerCTC_WGM(10);
        compteur_buzzer++;
    }

    if (((21 <= compteur_buzzer) && (compteur_buzzer <= 30)) || ((51 <= compteur_buzzer) && (compteur_buzzer <= 60))){
        clearTimerCTC_WGM();
        compteur_buzzer++;
    }

    if (compteur_buzzer == 81){
        clearTimerCTC_WGM();
        clearTimerCTC_INT_2();
        compteur_buzzer = 1;
    }
}


int main()
{

    Memoire24CXXX myMem;
    uint16_t adresse = 0x0100;
    for(;;){
        myMem.lecture(adresse, &oldMode);
        if(oldMode == MODE_DIAGNOSTIC)
            nextMode = MODE_PARCOURS;
        else if (oldMode == MODE_PARCOURS)
            nextMode = MODE_DIAGNOSTIC;

        if(nextMode == MODE_PARCOURS) {
            myMem.ecriture(adresse, MODE_PARCOURS);
            parcours_run();
        }
        else {
            myMem.ecriture(adresse, MODE_DIAGNOSTIC);
            diagnostic_run();
        }
    }

    return 0;
}


/*ISR(TIMER1_COMPA_vect)
{
    clearTimerCTC_INT_1();
    Interval_parc left_Sensor = value_to_interval_parc(sensors.getLeft());
    Interval_parc right_Sensor = value_to_interval_parc(sensors.getRight());
    if (side == RIGHT)
        if (left_Sensor == MORE_60)

    if (side == LEFT)
        if (right_Sensor == MORE_60)


}
*/





/*    for(;;){
        uint8_t request = UART_receive();
        uint8_t data = UART_receive();
        switch (request) {
            case LEFTSPEED:
                operateLeftWheel(data);

            case RIGHTSPEED:
                operateRightWheel(data);

            case LEDCOLOR:
                operateLED(data);

            case INFO:
                sendInfo();
        }
*/














/*
ISR (ADC_vect)
{
        sensors.setLeft();
        UART_transmit_number(sensors.getLeft());
}

int main()
{
    sei();
    initialisationUART();
    // ADC mux : reference analogique externe
    //           ajuste a droite
    ADMUX  = ( 0 << REFS1 ) | ( 0 << REFS0 ) | ( 0 << ADLAR ) | ( 0 << MUX4 ) |
    ( 0 << MUX3 ) | ( 0 << MUX2 ) | ( 0 << MUX1) | ( 0 << MUX0 ) ;

    // ADC Status and Control Register A : 
    //  Active le convertisseur mais sans demarrer de conversion pour l'instant.
    //  Pas de declanchement automatique et avec interruption suivant
    //  la fin d'une convertion. Division de l'horloge par 64 (il faudra
    //  donc 13 cycles du convertisseur * 64 pour terminer une conversion
    //  soit 832 cycles d'horloge soit 104 micro-secondes
    ADCSRA = ( 1 << ADEN ) | ( 0 << ADSC )  | ( 0 << ADATE ) | ( 0 << ADIF ) |
    ( 1 << ADIE ) | ( 1 << ADPS2 ) | ( 1 << ADPS1 ) | ( 0 << ADPS0 ) ;

    for(;;){
        sensors.readLeft();
        _delay_ms(2000);
    }
}







ISR (ADC_vect)
ISR (ADC_vect)
{
    // Aller chercher le resultat sur 16 bits.
    adcVal =   ADCL;
    adcVal +=  ADCH << 8;
    UART_transmit_number(adcVal);
}



int main()
{
    sei();
    can myCan;
    initialisationUART();

    for (;;) {
        myCan.lecture(0);
        _delay_ms(2000);
    }

    return 0;
}

(ISR (ADC_vect)
{
    uint16_t value;
    // Aller chercher le resultat sur 16 bits.
    value = ADCL;
    value += ADCH << 8;
    UART_transmit_number(value);
}


int main()
{
    initialisationUART();
        // ADC mux : reference analogique externe
    //           ajuste a droite
    ADMUX  = ( 0 << REFS1 ) | ( 0 << REFS0 ) | ( 0 << ADLAR ) | ( 0 << MUX4 ) |
    ( 0 << MUX3 ) | ( 0 << MUX2 ) | ( 0 << MUX1) | ( 0 << MUX0 ) ;

    // ADC Status and Control Register A : 
    //  Active le convertisseur mais sans demarrer de conversion pour l'instant.
    //  Pas de declanchement automatique et avec interruption suivant
    //  la fin d'une convertion. Division de l'horloge par 64 (il faudra
    //  donc 13 cycles du convertisseur * 64 pour terminer une conversion
    //  soit 832 cycles d'horloge soit 104 micro-secondes
    ADCSRA = ( 1 << ADEN ) | ( 0 << ADSC )  | ( 0 << ADATE ) | ( 0 << ADIF ) |
    ( 1 << ADIE ) | ( 1 << ADPS2 ) | ( 1 << ADPS1 ) | ( 0 << ADPS0 ) ;

for(;;){
    ADMUX  &=  ~(( 1 << MUX4 ) | ( 1 << MUX3 ) | 
    ( 1 << MUX2 ) | ( 1 << MUX1)  | ( 1 << MUX0 ));

    // selectionner l'entree voulue
    ADMUX |= ((7 & 0x07) << MUX0) ;

    ADCSRA |= ( 1 << ADSC );
    _delay_ms(2000);
}



return 0;
}
*/