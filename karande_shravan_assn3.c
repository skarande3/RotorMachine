/*
 * Author: Shravan Karande
 * Date: 09/02/23
 * Description: This file is the main file that includes functions that deal with user's input.
 * Usage: 
 * ./exe -i <configuration file>
 * ./exe -e <in file> <out file> -r <rotor 1 start> <rotor 2 start>
 * ./exe -d <in file> <out file> -r <rotor 1 start> <rotor 2 start>
 * ./exe -e <in file> <out file> -r <rotor 1 start> <rotor 2 start> -i <config file>
 * ./exe -d <in file> <out file> -r <rotor 1 start> <rotor 2 start> -i <config file>
 */


#include "rotorMachine.h"
#include <stdio.h>

int main(int argc, char** argv) {

//initilizes the rotors
int rotor1[28];
int  rotor2[28];


//The user can simply set up the rotors.ini file.
if(argc == 3){

	buildIni(argv[2]);
        
}

//The user can encrypt a file using the current rotors.ini configuration.
else if(argc == 7 && strcmp(argv[1], "-e") == 0){

	buildRotors(rotor1, rotor2);

	setRotor1(rotor1, atoi(argv[5]));

	setRotor2(rotor2,atoi(argv[6]));

	FILE *inputFile = fopen(argv[2], "r");
	FILE *outputFile = fopen(argv[3], "w");

	encryptFile(inputFile, outputFile, rotor1, rotor2);
 
}

//The user can decrypt a file using the current rotors.ini configuration.
else if(argc == 7 && strcmp(argv[1], "-d") == 0){

	buildRotors(rotor1, rotor2);

	setRotor1(rotor1, atoi(argv[5]));

	setRotor2(rotor2,atoi(argv[6]));

	FILE *inputFile = fopen(argv[2], "r");
	FILE *outputFile = fopen(argv[3], "w");


	decryptFile(inputFile, outputFile, rotor1, rotor2);


}

//The user can encrypt a file and set up the rotors.ini.
else if(argc == 9 && strcmp(argv[1], "-e") == 0) {

	buildIni(argv[8]); 

	buildRotors(rotor1, rotor2); 

	setRotor1(rotor1, atoi(argv[5])); 

	setRotor2(rotor2,atoi(argv[6]));  

	FILE *inputFile = fopen(argv[2], "r");
	FILE *outputFile = fopen(argv[3], "w");

	encryptFile(inputFile, outputFile, rotor1, rotor2);

}

//The user can decrypt a file and set up the rotors.ini.
else if(argc == 9 && strcmp(argv[1], "-d") == 0) {


	buildIni(argv[8]);

	buildRotors(rotor1, rotor2);

	setRotor1(rotor1, atoi(argv[5]));

	setRotor2(rotor2,atoi(argv[6]));

	FILE *inputFile = fopen(argv[2], "r");
	FILE *outputFile = fopen(argv[3], "w");


	decryptFile(inputFile, outputFile, rotor1, rotor2);

}

//When the user runs the program incorrectly the following  usage error is given.
else {

	printf("usage\n./exe -i <configuration file>\n./exe -e <in file> <out file> -r <rotor 1 start> <rotor 2 start>\n./exe -d <in file> <out file> -r <rotor 1 start> <rotor 2 start>\n./exe -e <in file> <out file> -r <rotor 1 start> <rotor 2 start> -i <config file>\n./exe -d <in file> <out file> -r <rotor 1 start> <rotor 2 start> -i <config file>\n"); 
}


return 0; 

}

