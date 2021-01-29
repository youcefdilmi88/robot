/* 
 * Fichier:   main.cpp
 * Auteurs: Maude Laflamme(1690784), Elisabeth Fagnan(1893587) et Youcef Anis Dilmi(1895231)
 * Équipe: 96108
 * Remise: 21 mars 2018
 * Description: Appel de la méthode run() de la classe ByteCodeInterpreter afin de lire les octets
 * en mémoire et executer les instructions.
 */

const uint8_t OUTPUT = 0xFF;
const uint8_t INTPUT = 0x00;

#include <ByteCodeInterpreter.h>

int main()
{
	DDRA = OUTPUT;
    DDRD= OUTPUT;
    DDRB = OUTPUT;
    ByteCodeInterpreter hihi;
    hihi.run();
    return 0;
}
