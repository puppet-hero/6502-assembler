// assembler.cpp
/// note to self, the tutorial/starting code is in teams for 9/30/2021
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* ------------------------------------------------------------------------ */
/*					    IMPORTANT NOTE ON INPUT								*/
/* if the command isn't meant to have an operand in 6502, don't include one */
/* ex, if you put "CLC 55", you'll probably run into problems				*/
/* likewise if it's meant to have an operand, put one or it won't work		*/
/* ------------------------------------------------------------------------ */

int main(int argc, char *argv[]) {
	ifstream prog_input(argv[1]);						//open input stream
	ofstream prog_output(argv[2]);						//open output stream

	string input_bytes;									//the byte we are working with
	string output_bytes;								//holds the output string

	bool hasOperand = false;
	
	prog_output << "v2.0 raw\n4*0 ";					//add header to start of output file

	while(prog_input >> input_bytes) {					//for as long as the input file has bytes to check,
		printf("Input: %s\n", input_bytes.c_str());		//tell the console what command is being read

		/* read the command and translate it to output string. set hasOperand to true if it has one */
		if (input_bytes.compare("LDA") == 0) {
			output_bytes = output_bytes + "3 ";
			hasOperand = true;
		}
		if (input_bytes.compare("LDY") == 0) {
			output_bytes = output_bytes + "2 ";
			hasOperand = true;
		}
		if (input_bytes.compare("LDX") == 0) {
			output_bytes = output_bytes + "1 ";
			hasOperand = true;
		}
		if (input_bytes.compare("TAX") == 0) {
			output_bytes = output_bytes + "9 ";
		}
		if (input_bytes.compare("SEC") == 0) {
			output_bytes = output_bytes + "5 ";
		}
		if (input_bytes.compare("JMP") == 0) {
			output_bytes = output_bytes + "b ";
			hasOperand = true;
		}
		if (input_bytes.compare("ADC") == 0) {
			output_bytes = output_bytes + "4 ";
		}
		if (input_bytes.compare("STA") == 0) {
			output_bytes = output_bytes + "c ";
			hasOperand = true;
		}
		if (input_bytes.compare("CLC") == 0) {
			output_bytes = output_bytes + "8 ";
		}
		if (input_bytes.compare("BCS") == 0) {
			output_bytes = output_bytes + "7 ";
			hasOperand = true;
		}

		/* set the operand value in output */
		if (hasOperand == true) {
			prog_input >> input_bytes;							//take in the command's associated arguement
			output_bytes = output_bytes + input_bytes + " ";	//and pass it into the output
		}
		else {
			output_bytes = output_bytes + "0 ";					//and pass it into the output
		}
	}

	prog_output << output_bytes;								//write the output to our file
	prog_input.close();											//close input stream
	prog_output.close();										//close output stream
}