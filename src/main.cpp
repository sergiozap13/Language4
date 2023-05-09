/*
 * Metodología de la Programación: Language4
 * Curso 2022/2023
 */

/* 
 * File:   main.cpp
 * @author estudiante1: Zapata De la Hoz, Sergio
 *
 * Created on 12 February 2023, 10:40
 */
using namespace std;

#include <iostream>
#include <fstream>

/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "language4 [-t min|max] <file1.bgr> <file2.bgr> [ ... <filen.bgr>]" << endl;
}

/**
 * This program reads an undefined number of Language objects from the set of 
 * files passed as parameters to main(). All the Languages object, except the 
 * first one, must be stored in a dynamic array of Language objects. Then, 
 * for each Language in the dynamic array, this program prints to the 
 * standard output the name of the file of that Language and the distance from 
 * the first Language to the current Language. 
 * Finally, the program should print in the standard output, the name of 
 * the file with the Language with the minimum|maximum distance to the Language 
 * of the first file and its language identifier.
 * 
 * At least, two Language files are required to run this program.
 * Running example:
 * > language4 [-t min|max] <file1.bgr> <file2.bgr> [  ... <filen.bgr>] 
 */
int main(int argc, char* argv[]) {
    if(argc < 3){
        exit(1);
    }
}

