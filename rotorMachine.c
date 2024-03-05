/*
 * Author: Shravan Karande
 * Date: 09/02/23
 * Description: This file include all the methods to which the enigma machine functions. the methods such as buildIni(), buildRotors() etc. 
 * Usage: 
 * ./exe -i <configuration file>
 * ./exe -e <in file> <out file> -r <rotor 1 start> <rotor 2 start>
 * ./exe -d <in file> <out file> -r <rotor 1 start> <rotor 2 start>
 * ./exe -e <in file> <out file> -r <rotor 1 start> <rotor 2 start> -i <config file>
 * ./exe -d <in file> <out file> -r <rotor 1 start> <rotor 2 start> -i <config file>
 * */

#include "rotorMachine.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h> 

//PART A

//The method take a file name as a parameter, reads it, XORs the values and prints it to rotors.ini. 
void buildIni(char *filename) {

	FILE *config; 
	FILE *rotorIni;

	//opens the config file for reading. 
	config = fopen(filename,"r"); 

	//if the pointer is equal to null, error message. 
	if(config == NULL) {
	printf("Unable to open the file.");

	return;
}
	
	//opens the rotorIni file for writing it.
	rotorIni = fopen("rotors.ini", "w"); 

	//if the pointer is equal to null, error message. 
	if(rotorIni == NULL) {
	printf("Unable to open the file.");

	return;
}
	int intVal;
	// uses fscanf to read the given file and the while loop makes sure an integer is read until 		the end is reached. The fprintf writes the XORed value to rotors.ini file. 

	while(fscanf(config, "%d",&intVal) == 1){ 
 
	intVal = intVal ^ 42;

	fprintf(rotorIni,"%d\n", intVal);

}
	//close both the files.
	 fclose(config);
	 fclose(rotorIni);
}



//PART B

//This method builds rotor1 and rotor2 through reading the rotors.ini file reverse XORing half the values and populating them in rotor1 and does the same for the 2nd half in rotor2.
void buildRotors(int rotor1[28], int rotor2[28]) {

	FILE *rotorFile;

	//opens the rotors.ini file and reads it.
	rotorFile = fopen("rotors.ini", "r");

	//if doesn't exist, error message. 
	if(rotorFile == NULL) {

		printf("Error: Rotor machine not initialized. Run with -i option and provide an appropriate configuration file.");

		return; 

	}
	int i;
	// this goes through the first 28 integers, reads them, reverse XORs them and stores them in rotor1[]
	for(i=0; i<28; i++){

		fscanf(rotorFile,"%d", &rotor1[i]); 
		rotor1[i] = rotor1[i] ^ 42;
	}
	// this continues where we left off (reads the second half), reverse XORs them and stores them in rotor2[]
	for(i=0; i<28; i++){
	
		fscanf(rotorFile,"%d", &rotor2[i]);
		rotor2[i] = rotor2[i] ^ 42;

	}
	// closes the file. 
	fclose(rotorFile);
	}



//PART C

//This method rotates rotor1 to right.
void rotateRotorRight(int rotor[28]) {

	int i;

	//sets a temp variable as the 28th integer value.
	int temp = rotor[27]; 

	//this moves the index to the right. 
	for (i = 27; i>0; i--){
	rotor[i] = rotor[i-1]; 
} 
	//sets the 28th integer as the first. 
	rotor[0] = temp; 
}


//This method rotates rotor2 to the left.
void rotateRotorLeft(int rotor[28]) {

	int i;
	//sets a temp variable as the 1st integer value.

	int temp = rotor[0]; 
	//this moves the index to the left. 

	for (i = 0; i<27; i++){
	rotor[i] = rotor[i+1];
}
	//sets the 1st integer to the last.  
	rotor[27] = temp; 
}


//this method sets rotor1 through doing the necessary rotations in the 2nd @param.  
void setRotor1(int rotor[28], int rotations) {

	int i;
	//does the desired number of rotations through calling on the rotate right function. 

	for (i = 0; i < rotations; i++) {
	 rotateRotorRight(rotor);

	}	
  }


//this method sets rotor2 through doing the necessary rotations in the 2nd @param.  
void setRotor2(int rotor[28], int rotations) {

	int i;
	//does the desired number of rotations through calling on the rotate left function. 
	 for (i = 0; i < rotations; i++) {
	     rotateRotorLeft(rotor);

   	}
}


//PART D

// This method converts the character value to the particular index assigned in the rotors. 
int charToIndex(char convert) {
	
	
	char upperCha = toupper(convert);
	if(upperCha == ' ') {
	return 26;
}

	if(upperCha == '.') {
	return 27; 
}
	// if the character is between A and Z the index value is found through subtracting it with A
	else if (upperCha >= 'A' && upperCha <= 'Z') {

		return upperCha - 'A'; 

	}
	
		return -1;
}  



// This method converts the index value to the particular character assigned in the rotors. 
char indexToChar(int convert) {
	
	if(convert == 26) {
	return ' '; 
}

	if(convert == 27) {
	return '.';
}
	// the character value is found through subtracting it with A and casting it to char.
	else {
	return (char)(convert + 'A'); 

}

	return "";
}


//PART F

//This method encrypts a file and writes it to another file. 
void encryptFile(FILE* infile, FILE* outfile, int rotor1[28], int rotor2[28]){
	char bufferReader[256]; 

	//the while loop continues until fgets  reads the bufferReader from the infile until it's reached the end. 
	while (fgets(bufferReader, sizeof(bufferReader), infile)) {

		//initiating all variables needed. 
		
		char character;
		int index=0;
		int valueInRotor1=0;
		char theEncryptedChar;
		int indexOfValueInRotor2=0;

		char encryptedLine[256]="";

		//This iterates through the bufferReader until it's reached the end. 

			for(int i=0; i < strlen(bufferReader) ; i++){
       
			    if(bufferReader[i] == '\0') {
			      break;
		}    

		if(bufferReader[i] == '\n') {
       			strncat(encryptedLine, "\n", 3);
			continue;
        	} 

	
		//an single character is stored in the character variable.            
		 character = bufferReader[i];
 
		//the index of that character is found through charToIndex method.
		 index = charToIndex(character); 

		//after finding that index we find the value of that index in rotor1. 
		 valueInRotor1 = rotor1[index]; 
 
		//this for loop is used iterate through rotor2 and find the value found in rotor1 in rotor2. It's index is stored in a varible.  
			for(int j =0; j< 28; j++){

				if(valueInRotor1 == rotor2[j]){
		
				indexOfValueInRotor2 = j;
    				break;

		}	
}
  
		// the char at the index in which value of rotor1 == value in rotor2 at jth position is found using indexToChar method. . 
		theEncryptedChar = indexToChar(indexOfValueInRotor2);


		// encLine+=theEncryptedChar;
		strncat(encryptedLine, &theEncryptedChar, 1);
 
 		rotateRotorRight(rotor1);
 	       rotateRotorLeft(rotor2);	
}
		//output each line at a time to given file.	
		fprintf(outfile, "%s", encryptedLine);  
    	}

}


//This method decrypts a file and writes it to another file. 
void decryptFile(FILE* infile, FILE* outfile, int rotor1[28], int rotor2[28]) {

	char bufferReader[256];
 
		while (fgets(bufferReader, 256, infile)) {
		
		//initiating all variables needed.
		char character2;
		int rotor2Index; 
		int rotor2Value;
		int indexOfValueInRotor1; 
		char theDecryptedChar; 
 
		char decryptedLine[256]=""; 

			
			for(int i=0; i < strlen(bufferReader); i++){
       
    			if(bufferReader[i] == '\0') {
			      break;
 		}
			// Handle newline character.
		        if(bufferReader[i] == '\n') {
                	strncat(decryptedLine, "\n", 3);
                        continue;
	        }

	character2 = bufferReader[i];

	// Convert the character to an index using rotor2.
	rotor2Index = charToIndex(character2);

	// Get the value from rotor2 at the given index.
	rotor2Value = rotor2[rotor2Index];

	for(int k =0; k< 28; k++){
	
	// Find the corresponding index in rotor1.
        if(rotor2Value == rotor1[k]){

                indexOfValueInRotor1 = k;
             break; 
	}
}
	
	// Append the decrypted character to the decryptedLine.
	theDecryptedChar = indexToChar(indexOfValueInRotor1); 
	//printf("this is decryp char %d: %c\n", i, theDecryptedChar);

	strncat(decryptedLine, &theDecryptedChar, 1);

	rotateRotorRight(rotor1);
	rotateRotorLeft(rotor2);
}
	// Write the decryptedLine to the output file.
	fprintf(outfile, "%s",decryptedLine);
    }
}

