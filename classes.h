#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "classes.h"

using namespace std;

int main(int argc, char* argv[]) {
	string s, t;		// temporary strings
	int alphabetSize;

	// read alphabet
	cin >> alphabetSize;
	cin.get();		// newline
	getline(cin, s);

	// make alphabet
	Alphabet alphabet;
	alphabet.init(alphabetSize, s);

	// read number of rotors
	int numRotors;
	cin >> numRotors;
	cin.get();		// newline
	Rotor* rotors = new Rotor[numRotors];		// make empty rotors

	// read rotors
	for (int i = 0; i < numRotors; i++) {
		getline(cin, s);
		getline(cin, t);

		// initialize ith rotor
		rotors[i].init(s, t, alphabet);
	}

	// read number of reflectors
	int numReflectors;
	cin >> numReflectors;
	cin.get();		// newline
	Reflector* reflectors = new Reflector[numReflectors];	// make empty reflectors

	// read reflectors
	for (int i = 0; i < numReflectors; i++) {
		getline(cin, s);

		reflectors[i].init(s, alphabet);
	}

	// read number of enigmas
	int numEnigmas;
	cin >> numEnigmas;
	cin.get();		// newline
	Enigma* enigmas = new Enigma[numEnigmas];		// make empty enigmas

	// read enigmas
	for (int i = 0; i < numEnigmas; i++) {
		// read number of rotors installed
		int k;
		cin >> k;

		// set rotor count
		enigmas[i].init(k, alphabet);

		// install rotors
		for (int j = 0; j < k; j++) {
			// read jth rotor info
			int rotorIndex;
			string rotorStart;

			cin >> rotorIndex;
			cin >> rotorStart;

			// install jth rotor
			enigmas[i].rotors[j] = rotors[rotorIndex];
			enigmas[i].rotors[j].setIndex(rotorStart, alphabet);
		}
		// read reflector
		int reflectorIndex;
		cin >> reflectorIndex;
		cin.get();	// newline

		// install reflector
		enigmas[i].setReflector(reflectors[reflectorIndex]);

		// read task
		getline(cin, s);

		// set task
		enigmas[i].setString(s);
	}

	for (int i = 0; i < numEnigmas; i++) {
		//enigmas->print();
		cout << enigmas[i].encrypt() << endl;
	}
	system("pause");
}
