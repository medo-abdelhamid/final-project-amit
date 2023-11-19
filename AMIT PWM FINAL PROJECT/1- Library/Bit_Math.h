/*
 * Bit_Math.h
 *
 *  Created on: Nov 16, 2023
 *      Author: medoa
 */

// reg define
#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(Reg, Bit_No) Reg |= (1<<Bit_No)
#define CLR_BIT(Reg, Bit_No) Reg &=~ (1<<Bit_No)
#define CHK_BIT(Reg, Bit_No) Reg &= (1<<Bit_No)
#define TOG_BIT(Reg, Bit_No) Reg ^= (1<<Bit_No)


#endif
