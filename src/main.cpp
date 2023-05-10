/*
 * Metodolog√≠a de la Programaci√≥n: Language4
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
#include "Language.h"

/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "language4 [-t min|max] <file1.bgr> <file2.bgr> [ ... <filen.bgr>]" << endl;
}

Language * reservar(int n){
    Language *v = nullptr;
    if (n > 0) {
        v = new Language[n];
    }
    return v;
}

/**
 * Free the memory correspondenting to a vector of Language
 * @param larray the vector of Language objects
 */
void liberar(Language * larray){
    if (larray != nullptr) {
        delete[] larray;
        larray = nullptr;
    }
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

    // Parametro opcional -t[min/max] -> 2 parametros en primer lugar
    // language3 -t min
    //     0      1  2



    // variables
    Language *larray = nullptr;
    bool parametro_es_min = true; // true = min | false = max
    bool parametro_existe = true; // true = hay parametro -t | false = no hay parametro -t
    bool parametros_ok = true; // true = no hay problemas con los params | false = hay problemas con los params
    static const string MIN_OPERATION = "min";
    static const string MAX_OPERATION = "max";
    int salto = 0, pos_primer_language = 0;
    double min_distance = 0.0, max_distance = 0.0;
    int pos_language_min_distance = 1, pos_language_max_distance = 0;


    // comprobaciÛn de par·metros
    if (argc < 3) {
        showEnglishHelp(cout);
        exit(1);
    } else {
        //procesar los parametros y la variable salto
        string parametro_auxiliar = argv[1];
        salto = 0;
        if (parametro_auxiliar[0] == '-') { // Si hay par·metro 
            if (parametro_auxiliar == "-t") { // Si el parametro est· bien (es -t)
                if (argc < 5) { // Si hay par·metro -t y no hay ficheros suficientes (minimo 2), error.
                    parametros_ok = false;
                }
                pos_primer_language = 3; // si el parametro est·, el primer language se encuentra en la pos 3 de entre los argmentos
                salto = 2;
                parametro_auxiliar = argv[2];
                if (parametro_auxiliar == MAX_OPERATION) { // Si el parametro es max
                    parametro_es_min = false; // false = max
                } else if (parametro_auxiliar != MIN_OPERATION) {
                    parametros_ok = false;
                }
            } else { // Si el par·metro (-) no es v·lido
                parametros_ok = false;
            }
        } else { // Si no hay parametro -t
            parametro_existe = false;
            pos_primer_language = 1; // si no hay parametros, el primer language est· en 1
            salto = 0;
        }
    }

    std::string *nombres_archivos = new std::string[argc - 1 - salto]; // array para almacenar los nombres de los archivos
    double *distancias = new double[argc - 2 - salto]; // array para almacenar las distancias del primer language con los respectivos

    if (!parametros_ok) {
        showEnglishHelp(cout);
        exit(1);
    } else { // si los parametros son correctos
        larray = reservar(argc - 1 - salto); // se reserva memoria para [argc - 1 - salto] Language objects

        // si tenemos par·metro
        Language language_referencia, language_auxiliar;
        language_referencia.load(argv[pos_primer_language]); // cargamos el primer language
        //language_referencia.save("/home/sergio/NetBeansProjects/Language3/data/4bigrams.bgr");
        // rellenamos el vector dinamico y guardamos el nombre de cada uno de los languages
        for (int i = argc; i > pos_primer_language + 1; i--) {
            language_auxiliar.load(argv[argc - i + pos_primer_language + 1]);
            larray[argc - i] = language_auxiliar;
            nombres_archivos[argc - i] = argv[argc - i + pos_primer_language + 1];
        }
        for (int i = 0; i < argc - (pos_primer_language + 1); i++) {
            distancias[i] = language_referencia.getDistance(larray[i]);
            cout << "Distance to " << nombres_archivos[i] << ": " << language_referencia.getDistance(larray[i]) << endl;
        }
        
        // calculamos la menor y la mayor distancia
        min_distance = distancias[0];
        max_distance = distancias[0];
        for (int i = 1; i < argc - 2 - salto; i++) {

            if (distancias[i] < min_distance) {
                min_distance = distancias[i];
                pos_language_min_distance = i;
            }
            if (distancias[i] > max_distance) {
                max_distance = distancias[i];
                pos_language_max_distance = i;
            }
        }
    }


    // salida del programa dependiendo del param -t
    if (parametro_es_min) {
        cout << "Nearest language file: " << nombres_archivos[pos_language_min_distance] << ". Identifier of the nearest language: " << larray[pos_language_min_distance].getLanguageId() << endl;
    } else {
        cout << "Farthest language file: " << nombres_archivos[pos_language_max_distance] << ". Identifier of the farthest language: " << larray[pos_language_max_distance].getLanguageId() << endl;
    }
    // se libera toda la memoria reservada anteriormente
    liberar(larray);
    delete [] nombres_archivos;
    nombres_archivos = nullptr;
    delete [] distancias;
    distancias = nullptr;
}

