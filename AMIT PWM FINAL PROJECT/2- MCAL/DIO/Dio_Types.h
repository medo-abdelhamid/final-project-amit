/*
 * Dio_Types.h
 *
 *  Created on: Nov 16, 2023
 *      Author: medoa
 */

#ifndef DIO_TYPES_H_
#define DIO_TYPES_H_

typedef enum{
	DIO_PORTA,
	DIO_PORTB,
	DIO_PORTC,
	DIO_PORTD
}port_type;			//port type

typedef enum{
	DIO_PIN0,
	DIO_PIN1,
	DIO_PIN2,
	DIO_PIN3,
	DIO_PIN4,
	DIO_PIN5,
	DIO_PIN6,
	DIO_PIN7
}pin_type;			//pin type

typedef enum{
	INPUT,
	OUTPUT
}direction_type;

typedef enum {
	STD_LOW,
	STD_HIGH
}level_type;

#endif
