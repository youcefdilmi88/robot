#ifndef SENSORS_H
#define SENSORS_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <func_UART.h>
#include <util/delay.h>

const uint8_t LEFT_SENSOR = 0x00;
const uint8_t RIGHT_SENSOR = 0x01;
const uint8_t OUTPUT = 0XFF;
const uint8_t INPUT = 0X00;

class Sensors
{
public:
	Sensors();

	void initConversion();
	void readLeft();
	void readRight();

	uint16_t getLeft();
	uint16_t getRight();
	uint8_t getPresentSensor();

	void	setLeft();
	void	setRight();

private:
	uint8_t presentSensor_;
	uint16_t rightVal_;
	uint16_t leftVal_;
};

extern Sensors sensors;

#endif /* SENSORS_H */