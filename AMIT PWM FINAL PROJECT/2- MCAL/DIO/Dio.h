/*
 * Dio.h
 *
 *  Created on: Nov 19, 2023
 *      Author: medoa
 */

#ifndef DIO_H_
#define DIO_H_

#include "Dio_Reg.h"
#include "Bit_Math.h"
#include "Std_Types.h"
#include "Dio_Types.h"

//	Functions prototypes	
void Dio_ConfigChannel(port_type port, pin_type pin, direction_type direction);
void Dio_WriteChannel(port_type port, pin_type pin, level_type level);
void Dio_WriteGroup(port_type port, u8 mask, u8 data);
void Dio_ToggelChannel(port_type port, pin_type pin);
level_type Dio_ReadChannel(port_type port, pin_type pin);


#endif
