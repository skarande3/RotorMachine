
 # Author: Shravan Karande
 # Date: 09/02/23
 # Description: This file include the Makefile for the code, it compiles the .c and .h file.  
 # Usage: 
 # ./exe -i <configuration file>
 # ./exe -e <in file> <out file> -r <rotor 1 start> <rotor 2 start>
 # ./exe -d <in file> <out file> -r <rotor 1 start> <rotor 2 start>
 # ./exe -e <in file> <out file> -r <rotor 1 start> <rotor 2 start> -i <config file>
 # ./exe -d <in file> <out file> -r <rotor 1 start> <rotor 2 start> -i <config file>
  

exe: rotorMachine.o karande_shravan_assn3.o
	gcc -g -Wall rotorMachine.o karande_shravan_assn3.o -o exe 

rotorMachine.o: rotorMachine.h
	gcc -g -Wall -c rotorMachine.c

karande_shravan_assn3.o: rotorMachine.h
	gcc -g -Wall -c karande_shravan_assn3.c

clean:
	rm -v *.o exe    
