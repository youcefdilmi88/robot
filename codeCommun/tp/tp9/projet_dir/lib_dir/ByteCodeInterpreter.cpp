/* 
 * Fichier: ByteCodeInterpreter.cpp
 * Auteurs: Maude Laflamme(1690784), Elisabeth Fagnan(1893587) et Youcef Anis Dilmi(1895231)
 * Équipe: 96108
 * Remise: 21 mars 2018
 * Description: Implémentation de la classe ByteCodeInterpreter
 */

#include <LED_PORTA.h>
#include <ByteCodeInterpreter.h>
#include <memoire_24.h>
#include <start_timer_CTC.h>
#include <PWM_PORTD.h>
#include <func_UART.h>


ByteCodeInterpreter::ByteCodeInterpreter()
{}

//Lecture des instructions dans la mémoire externe et appel du dispatcheur d'instructions
void ByteCodeInterpreter::run()
{
    uint8_t instruction = 0x00;
    uint8_t operand = 0x00;
    
    //class parameters initialization
    adress = 0x0000;
    dbt_read = false;
    fin_read = false;

    Memoire24CXXX myMem;
    myMem.init();
    initialisationUART();
    
    //Boucle de de lecture des instructions dans la mémoire externe et appel du dispatcheur d'instructions
    while( ! fin_read ) {
        myMem.lecture(adress++, &instruction);
        myMem.lecture(adress++, &operand);
        if(instruction == dbt){
            exec_DBT();
            myMem.lecture(adress++, &instruction);
            myMem.lecture(adress++, &operand);
        }
        if(dbt_read){
            dispatch_instruction(instruction, operand);
            UART_transmit_number(instruction);// Tranmission de l'octets d'instruction lu pour vérifier avec serieViaUSB -l
            UART_transmit_number(operand);// Tranmission de l'octets d'opérande lu pour vérifier avec serieViaUSB -l
        }
    }
}

//Dispatcheur d'instruction qui execute l'instruction 
//en fonction de l'octet lue dans la mémoire externe
void ByteCodeInterpreter::dispatch_instruction(uint8_t instruction, uint8_t operand)
{
        switch (instruction) {

			 
            case att: //Attendre
                    exec_ATT(operand);
                    break;


            case dal: //Allumer DEL
                    exec_DAL(operand);
                    break;


            case det: //Éteindre DEL
                    exec_DET(operand);
                    break;


            case sgo: //Jouer une sonorité
                    exec_SGO(operand);
                    break;


            case sar: //Arrêté de jouer la sonorité
                    exec_SAR();
                    break;


            case mar: //Arrêter les moteurs
                    exec_MAR();
                    break;


            case mav: //Avancer
                    exec_MAV(operand);
                    break;


            case mre: //Reculer
                    exec_MRE(operand);
                    break;


            case trd: //Tourner à droite
                    exec_TRD();
                    break;

            case trg: //Tourner à gauche
                   exec_TRG();
                    break;


            case dbc: //Début de boucle
                    exec_DBC(operand);
                    break;


            case fbc: //Fin de boucle
                    exec_FBC();
                    break;


            case fin: //FIN
                    exec_FIN();
                    break;

            default:
                    error_red(1000); 
                    break;
        }
}

    
    void ByteCodeInterpreter::exec_DBT()
    {
        dbt_read = true;
        LED_start();
    }
    
    void ByteCodeInterpreter::exec_ATT(uint8_t operand)
    {
        delay_loop_ms(operand*25);
    }
    
    void ByteCodeInterpreter::exec_DAL(uint8_t nLED)
    {
        PORTA = GREEN;
    }
    
    void ByteCodeInterpreter::exec_DET(uint8_t nLED)
    {
        PORTA = OFF;
    }
    
    void ByteCodeInterpreter::exec_SGO(uint8_t operand)
    {
        
        static uint8_t lookup_table[] = {36, 34, 32, 30, 28, 27, 25, 24, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 13, 12, 11, 10, 9, 9, 8, 8, 7, 7, 7, 6, 6, 6, 5, 5, 5, 5, 4 };
        startTimerCTC_WGM(lookup_table[operand - 45]);
    }
    
    void ByteCodeInterpreter::exec_SAR()
    {
        TCCR0A &= ~(1 << COM0A0);
    }
    
    void ByteCodeInterpreter::exec_MAR()
    {
        set_pwm(0, 0, FORWARD, FORWARD);
    }
    
    void ByteCodeInterpreter::exec_MAV(uint8_t duty)
    {
        init_pwm();
        set_pwm(duty-12, duty, FORWARD, FORWARD);
    }
    
    void ByteCodeInterpreter::exec_MRE(uint8_t duty)
    {
        init_pwm();
        set_pwm(duty, duty, BACKWARD, BACKWARD);
    }
    
    void ByteCodeInterpreter::exec_TRD()
    {
        init_pwm();
        set_pwm(255, 100, FORWARD, FORWARD);
    }
    
    void ByteCodeInterpreter::exec_TRG()
    { 
        init_pwm();
        set_pwm(100, 255, FORWARD, FORWARD);
    }
    
    void ByteCodeInterpreter::exec_DBC(uint8_t iterations)
    {  
            loop_beg = adress;
            loop_counter = iterations;
    }
    
    void ByteCodeInterpreter::exec_FBC()
    {
        if (loop_counter!=0x00){
            adress = loop_beg;
            loop_counter--;
        }
    }
    
    void ByteCodeInterpreter::exec_FIN()
    {
        fin_read = true;
        LED_finish();
        set_pwm(0,0,FORWARD, FORWARD);
        TCCR0A &= ~(1 << COM0A0);
    }
    
