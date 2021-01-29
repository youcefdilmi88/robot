#include <sensors.h>

//Constructeur par défaut de la classe Sensor.
Sensors::Sensors()
{}

/********************************************************************************************
* @brief Initialise la conversion des valeurs analogiques des capteurs en valeurs numériques.
* @param --
* @return void
********************************************************************************************/
void Sensors::initConversion()
{
    cli();
    ADMUX  = ( 0 << REFS1 ) | ( 0 << REFS0 ) | ( 0 << ADLAR ) | ( 0 << MUX4 ) |  // ADC mux : reference analogique externe
    ( 0 << MUX3 ) | ( 0 << MUX2 ) | ( 0 << MUX1) | ( 0 << MUX0 ) ;               //           ajuste a droite

    // ADC Status and Control Register A : 
    //  Active le convertisseur mais sans demarrer de conversion pour l'instant.
    //  Pas de declanchement automatique et avec interruption suivant
    //  la fin d'une convertion. Division de l'horloge par 64 (il faudra
    //  donc 13 cycles du convertisseur * 64 pour terminer une conversion
    //  soit 832 cycles d'horloge soit 104 micro-secondes
    ADCSRA = ( 1 << ADEN ) | ( 0 << ADSC )  | ( 0 << ADATE ) | ( 0 << ADIF ) |
    ( 1 << ADIE ) | ( 1 << ADPS2 ) | ( 1 << ADPS1 ) | ( 0 << ADPS0 ) ;
    sei();
    readLeft();
}


/********************************************************************************************
* @brief Lit la valeur analogique du capteur de gauche et débute la conversion en valeur numérique.
* @param --
* @return void
********************************************************************************************/
void Sensors::readLeft()
{
    presentSensor = LEFT_SENSOR;
    // Garder les bits de ADMUX intacts, sauf les bit permettant 
    // la selection de l'entree
    ADMUX  &=  ~(( 1 << MUX4 ) | ( 1 << MUX3 ) | 
                ( 1 << MUX2 ) | ( 1 << MUX1)  | ( 1 << MUX0 ));

    // selectionner l'entree voulue
    ADMUX |= ((0x00 & 0x07) << MUX0) ;

    // demarrer la conversion
    ADCSRA |= ( 1 << ADSC );
}

/********************************************************************************************
* @brief Lit la valeur analogique du capteur de droite et débute la conversion en valeur numérique.
* @param --
* @return void
********************************************************************************************/
void Sensors::readRight()
{
    presentSensor = RIGHT_SENSOR;
    // Garder les bits de ADMUX intacts, sauf les bit permettant 
    // la selection de l'entree
    ADMUX  &=  ~(( 1 << MUX4 ) | ( 1 << MUX3 ) | 
                ( 1 << MUX2 ) | ( 1 << MUX1)  | ( 1 << MUX0 ));

    // selectionner l'entree voulue
    ADMUX |= ((0x01 & 0x07) << MUX0);

    // demarrer la conversion
    ADCSRA |= ( 1 << ADSC );
}

/*************************************************************************
* @brief Set l'attribut leftVal_ à la valeur convertie du capteur gauche.
* @param --
* @return void
**************************************************************************/
void Sensors::setLeft()
{
    leftVal_ = ADCL;
    leftVal_ += ADCH << 8;
}

/*************************************************************************
* @brief Set l'attribut rightVal_ à la valeur convertie du capteur droit.
* @param --
* @return void
**************************************************************************/
void Sensors::setRight()
{
    rightVal_ = ADCL;
    rightVal_ += ADCH << 8;
}

/*************************************************************************
* @brief Retourne l'attribut rightVal_.
* @param --
* @return uint16_t rightVal_
**************************************************************************/
uint16_t Sensors::getRight()
{
    return rightVal_;
}

/*************************************************************************
* @brief Retourne l'attribut leftVal_.
* @param --
* @return uint16_t leftVal_
**************************************************************************/
uint16_t Sensors::getLeft()
{
    return leftVal_;
}

/*************************************************************************
* @brief Retourne le capteur qui est présentement converti.
* @param --
* @return uint8_t presentSensor_
**************************************************************************/
uint8_t Sensors::getPresentSensor()
{
    return presentSensor_;
}
