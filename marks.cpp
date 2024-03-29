//	Steffan Jones
//	201275923
//  S.D.Jones@student.liverpool.ac.uk

#include <stdlib.h>
#include <stdio.h>
#include "stdafx.h"

int main()
{
	int marks[6];			//Array called marks with size 6
	marks[0] = 0;			//Declaring values in the array
	marks[1] = 0;
	marks[2] = 0;
	marks[3] = 0;
	marks[4] = 0;
	marks[5] = 0;
	int numFails = 0;		//integer called numFails with initial value of 0
	int numPasses = 0;		//integer called numPasses with initial value of 0
	int counter = 0;		//integer called counter with initial value of 0

	char ask[] = "Enter the mark for module ";					//char called ask which asks for the module mark
	char colon[] = ": ";										//used for printing a ": "
	char format[] = "%d";										//used to format input and output so that the input would become a decimal value 
	char errorMessage[] = "Input must be between 0-100\n";		//error message used when an invalid input is inputted
	char callPasses[] = "\nNumber of passes = ";				//used at the end of the program when printing the value of numPasses
	char callFails[] = "\nNumber of fails = ";					//used at the end of the program when printing the value of numFails

	_asm {
			lea ebx, marks;				//load marks into ebx	
l1:										//Label for jumping
			inc counter					//increment the counter
			lea eax, ask;				//load the char ask into eax	
			push eax			
			call printf					//print ask
			add esp, 4
			
			lea ecx, counter			//load counter into ecx
			mov eax, [ecx]				//load the value at address ecx into eax
			push eax
			lea eax, format				//use the format char so that the output will be decimal
			push eax
			call printf					//print the value of counter
			add esp, 8
			lea eax, colon;				//load the char colon into eax
			push eax
			call printf					//print the colon char
			add esp, 4

			lea eax, [ebx];				//load the value of marks array into eax
			push eax
			lea eax, format				//format	
			push eax
			call scanf					//scan for input and input it into the array
			add esp, 8
			cmp counter, 6				//compare the value of counter with 6
			jle checkRange				//if counter is less than or equal to 6 then jump to checkRange

checkRange :							//label for jumping
			cmp[ebx], 0					//compare if the value of address ebx to 0
			jl invalidInput				//if [ebx] is less than 0 jump to invalidInput
			cmp[ebx], 100				//compare if the value of address ebx to 100	
			jg invalidInput				//if [ebx] is more than 100 jump to invalidInput
			add ebx, 4					//this array value is fine therefore add 4 to index (move onto next array value)
			cmp counter, 6				//compare the value of counter to 6
			jl l1						//if counter is less than 6 jump to l1
			mov counter, 0				//reset the counter to 0
			sub ebx, 4					//subtract ebx by 4
			jmp MarkCheck				//jump to MarkCheck

invalidInput:							//label for jumping
			dec counter					//decrement the value in counter
			lea eax, errorMessage;		//load the char errorMessage into eax
			push eax
			call printf					//print the char errorMessage
			add esp, 4
			jmp l1						//jump to l1

MarkCheck:								//label for jumping
			cmp[ebx], 40				//compare the value at address ebx to 40
			jl fail						//if the value is less than 40 jump to fail
			jge pass					//if the value is greater and or equal to 40 jump to pass

fail :									//label for jumping
			add numFails, 1				//add 1 to the integer numFails
			inc counter					//increment the value at counter
			sub ebx, 4					//subtract ebx by 4
			jmp allChecked				//jump to allChecked to see if all array values have been checked

pass:									//label for jumping
			add numPasses, 1			//add one to the integer numPasses
			inc counter					//increment the value of counter
			sub ebx, 4					//subtract ebx by 4
			jmp allChecked				//jump to allChecked to see if all array values have been checked

allChecked:	
			cmp counter, 6				//compare the values of counter with 6
			je printResults				//if counter is equal to 6 then jump to printResults as all the inputs have been checked
			jl MarkCheck				//if counter is less than 6 then jump to MarkCheck as not all inputs have been checked
						
printResults:							//label for jumping
			lea eax, callPasses;		//load the char callPasses to eax
			push eax					
			call printf					//print callPasses
			add esp, 4
			lea ebx, numPasses			//load the value of numPasses into ebx
			mov eax, [ebx]				//move the value of numPasses into eax
			push eax
			lea eax, format				//format
			push eax
			call printf					//print char callPasses + numPasses
			add esp, 8
			lea eax, callFails;			//load the char callPasses to eax
			push eax					
			call printf					//print callFails
			add esp, 4
			lea ebx, numFails			//load the value of numFails into ebx
			mov eax, [ebx]				//move the value of numFails into eax
			push eax
			lea eax, format				//format
			push eax
			call printf					//print char callFails + numFails
			add esp, 8
	}
	return 0;
}


