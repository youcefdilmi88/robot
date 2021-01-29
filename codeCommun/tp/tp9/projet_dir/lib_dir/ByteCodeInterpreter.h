/* 
 * Fichier:  ByteCodeInterpreter.h
 * Auteurs: Maude Laflamme(1690784), Elisabeth Fagnan(1893587) et Youcef Anis Dilmi(1895231)
 * Équipe: 96108
 * Remise: 21 mars 2018
 * Description: Déclaration de la classe ByteCodeInterpreter
 */

#ifndef BYTECODEINTERPRETER_H
#define BYTECODEINTERPRETER_H

#include <avr/io.h>
#include <memoire_24.h>


const uint8_t OUTPUT = 0xFF;
const uint8_t INTPUT = 0x00;

enum mnemonic { dbt=0x01, att=0x02, dal=0x44, det=0x45, sgo=0x48, sar=0x09, mar=0x61,
 mav=0x62, mre=0x63, trd=0x64, trg=0x65, dbc=0xC0, fbc=0xC1, fin=0xFF };

class ByteCodeInterpreter 
{
    
    public:
        ByteCodeInterpreter();
        void run();
    
    private:
        void dispatch_instruction(uint8_t instruction, uint8_t operand);
        void exec_DBT();
        void exec_ATT(uint8_t operand);
        void exec_DAL(uint8_t nLED);
        void exec_DET(uint8_t nLED);
        void exec_SGO(uint8_t operand);
        void exec_SAR();
        void exec_MAR();
        void exec_MAV(uint8_t duty);
        void exec_MRE(uint8_t duty);
        void exec_TRD();
        void exec_TRG();
        void exec_DBC(uint8_t iterations);
        void exec_FBC();
        void exec_FIN();
    

        //parameters
        bool dbt_read;
        bool fin_read;
        uint8_t loop_counter;
        uint16_t loop_beg;
        uint16_t adress;
    
};

#endif /* BYTECODEINTERPRETER_H */

