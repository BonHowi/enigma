#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "classes.h"

// usinng namespace std;

int main(int argc, char* argv[]) {
        int asize;

        // read alphabet
        cin >> asize;
        Alphabet alphabet(asize);

        // read number of rotors
        int numRotors;
        cin >> numRotors;
        Rotor* rotors = new Rotor[numRotors];           // make empty rotors

        // make alphabet
        string temp;
        for (int i = 0; i < asize; i++) {
                string str = to_string(i+1);
                temp = str;
                alphabet.init(temp, i);
        }
         //alphabet.print();



        // read rotors
        for (int i = 0; i < numRotors; i++) {
                // initialize ith rotor
                rotors[i].init(/*s, t,*/ alphabet);
                //rotors[i].print(alphabet);
        }

        // read number of reflectors
        int numReflectors;
        cin >> numReflectors;
        Reflector* reflectors = new Reflector[numReflectors];   // make empty reflectors

        // read reflectors
        for (int i = 0; i < numReflectors; i++) {

                reflectors[i].init(/*s,*/ alphabet);
                //reflectors[i].print(alphabet);
        }

        // read number of enigmas
        int numEnigmas;

        cin >> numEnigmas;

        Enigma* enigmas = new Enigma[numEnigmas];               // make empty enigmas

        // read enigmas
        for (int i = 0; i < numEnigmas; i++) {
                // read number of rotors installed
                int rotorsInstalled;
                int k;
                cin >> rotorsInstalled;

                // set rotor count
                enigmas[i].init(rotorsInstalled, alphabet);

                // install rotors
                for (int j = 0; j < rotorsInstalled; j++) {
                        // read jth rotor info
                        int rotorIndex;
                        string rotorStart;

                        cin >> rotorIndex;
                        cin >> rotorStart;

                        // install jth rotor
                        enigmas[i].rotors[j] = rotors[rotorIndex];
                        // enigmas[i].rotors[j].print(alphabet);
                        int rStart = stoi(rotorStart);
                        //enigmas[i].rotors[j].setIndex(rotorStart, alphabet);
                        enigmas[i].rotors[j].setIndex(rStart);
                }
                // read reflector
                int reflectorIndex;
                cin >> reflectorIndex;

                // install reflector
                enigmas[i].setReflector(reflectors[reflectorIndex]);

                // read task
                string temp;
                string txt = "";
                do {
                        cin >> temp;
                        txt += temp;
                } while (txt.find('0') == -1);

                // set task
                enigmas[i].setString(txt);
        }

        for (int i = 0; i < numEnigmas; i++) {
                enigmas->print();
                cout << enigmas[i].encrypt() << endl;

                
        }
        //system("pause");
}
