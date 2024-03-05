/*
 * Author: Shravan Karande
 * Date: 09/02/23
 * Description: This file include all the method prototypes to which the enigma machine functions. This file is a .h file. 
 * Usage: 
 * ./exe -i <configuration file>
 * ./exe -e <in file> <out file> -r <rotor 1 start> <rotor 2 start>
 * ./exe -d <in file> <out file> -r <rotor 1 start> <rotor 2 start>
 * ./exe -e <in file> <out file> -r <rotor 1 start> <rotor 2 start> -i <config file>
 * ./exe -d <in file> <out file> -r <rotor 1 start> <rotor 2 start> -i <config file>
 */


#include <stdio.h>
#include <string.h>
#pragma once 

#ifndef ROTORMACHINE_H
#define ROTORMACHINE_H

void buildIni(char *);

void buildRotors(int[28], int[28]);

void rotateRotorRight(int[28]);

void rotateRotorLeft(int[28]);

void setRotor1(int[28], int);

void setRotor2(int[28], int);

int charToIndex(char);

char indexToChar(int);

void encryptFile(FILE*, FILE*, int rotor1[28], int rotor2[28]);

void decryptFile(FILE*, FILE*, int rotor1[28], int rotor2[28]);

void printRotors(int[28], int[28]);

#endif 
