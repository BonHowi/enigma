#include <sstream>
#include <iostream>
#include "classes.h"

using namespace std;

/**
 * Rotor class
 */
Rotor::Rotor() {
	this->forward = NULL;
	this->turns = NULL;
	this->nTurns = 0;
	this->size = 0;
	this->index = 0;
}

void Rotor::init(string in, string t, Alphabet& a) {
	stringstream ss(in);
	stringstream turns(t);

	this->size = a.size;
	turns >> this->nTurns;

	this->forward = new int[size];
	this->turns = new int[nTurns];

	for (int i = 0; i < this->size; i++) {
		string s;
		ss >> s;

		int j = a.toIndex(s);

		this->forward[i] = j;
	}

	for (int i = 0; i < this->nTurns; i++) {
		string s;
		turns >> s;
		int j = a.toIndex(s);

		this->turns[i] = j;
	}

	this->index = 0;
}

Rotor::~Rotor() {
	delete[] this->forward;
	delete[] this->turns;
}

void Rotor::setIndex(string s, Alphabet& a) {
	int j = a.toIndex(s);
	for (int i = 0; i < this->size; i++) {
		if (this->forward[i] == j)
			this->index = i;
	}
}

int Rotor::forwardSub(int i) {
	return this->forward[(i + this->index) % this->size];
}


int Rotor::reverseSub(int i) {
	for (int j = 0; j < this->size; j++) {
		if (this->forwardSub(j) == i)
			return j;
	}
	return 0;
}

bool Rotor::onTurnover()
{
	int j = this->forwardSub(0);
	for (int i = 0; i < this->nTurns; i++) {
		if (this->turns[i] == j)
			return true;
	}
	return false;
}

void Rotor::increment() {
	/*this->index--;
	if (this->index < 0)
		this->index = this->size - 1;*/
	this->index++;
	if (this->index > this->size - 1)
		this->index = 0;
}

void Rotor::print(Alphabet& a) {
	for (int i = 0; i < this->size; i++)
		cout << a.toAlpha(i) << ": " << a.toAlpha(this->forwardSub(i)) << endl;
	cout << endl;

	for (int i = 0; i < this->size; i++)
		cout << a.toAlpha(i) << ": " << a.toAlpha(this->reverseSub(i)) << endl;
	cout << endl;

	if (this->nTurns > 0) {
		cout << "Turnover: ";
		for (int i = 0; i < this->nTurns; i++)
			cout << a.toAlpha(this->turns[i]) << " ";
		cout << endl;
	}

}


/**
 * Reflector class
 */
Reflector::Reflector() {
	this->reflections = NULL;
	this->size = 0;
}
void Reflector::init(string in, Alphabet& a) {
	this->size = a.size;
	this->reflections = new int[size];

	stringstream ss(in);

	for (int i = 0; i < this->size; i++) {
		string s;
		ss >> s;
		int j = a.toIndex(s);

		this->reflections[i] = j;
	}
}

Reflector::~Reflector() {
	delete[] this->reflections;
}

int Reflector::reflect(int i) {
	return this->reflections[i];
}

void Reflector::print(Alphabet& a) {
	for (int i = 0; i < this->size; i++)
		cout << a.toAlpha(i) << ": " << a.toAlpha(this->reflections[i]) << endl;
}

/**
 * Alphabet class
 */

Alphabet::Alphabet() {
	this->size = 0;
	this->letters = NULL;
}

void Alphabet::init(int size, string in) {
	this->size = size;
	this->letters = new string[size];

	stringstream ss(in);

	for (int i = 0; i < size; i++)
		ss >> this->letters[i];
}

Alphabet::~Alphabet() {
	delete[] this->letters;
}

int Alphabet::toIndex(string s) {
	for (int i = 0; i < this->size; i++) {
		if (letters[i] == s)
			return i;
	}
	return -1;
}

string Alphabet::toAlpha(int i) {
	if (i < this->size)
		return this->letters[i];
	return "";
}

void Alphabet::print() {
	for (int i = 0; i < this->size; i++)
		cout << this->letters[i] << endl;
}

/**
 * Enigma class
 */

Enigma::Enigma() {
	this->rotors = NULL;
	this->numRotors = 0;
}

Enigma::~Enigma() {
	delete[] rotors;
}

void Enigma::init(int numRotors, Alphabet& a) {
	this->numRotors = numRotors;
	this->rotors = new Rotor[numRotors];
	this->alphabet = a;
}

void Enigma::addRotor(Rotor& r, int i) {
	this->rotors[i] = r;
}

void Enigma::setReflector(Reflector& r) {
	this->reflector = r;
}

void Enigma::print() {
	cout << "--Alphabet--" << endl;
	this->alphabet.print();
	cout << endl << endl;

	cout << "--Rotors--" << endl;
	for (int i = 0; i < this->numRotors; i++) {
		this->rotors[i].print(this->alphabet);
		cout << endl;
	}
	cout << endl;


	cout << "--Reflector--" << endl;
	this->reflector.print(this->alphabet);
	cout << endl;
}

string Enigma::encryptLetter(int letter)
{
	// increment first rotor before encoding
	this->rotors[0].increment();
	//this->rotors[0].print(alphabet);

	//cout << alphabet.toAlpha(letter) << " -> ";
	// pass through rotors
	for (int i = 0; i < this->numRotors; i++) {
		// if on turnover letter
		if (this->rotors[i].onTurnover()) {
			// if not last rotor
			if (i < this->numRotors) {
				this->rotors[i + 1].increment();		// increment next rotor
			}
		}

		// pass through rotor
		letter = this->rotors[i].forwardSub(letter);

		//cout << "[Rotor " << i + 1 << "] -> " << alphabet.toAlpha(letter) << " -> ";
	}

	// pass through reflector
	letter = this->reflector.reflect(letter);
	//cout << "[Reflector] -> " << alphabet.toAlpha(letter) << " -> ";


	// pass through rotors in reverse
	for (int i = this->numRotors - 1; i >= 0; i--) {
		letter = this->rotors[i].reverseSub(letter);
		//cout << "[Rotor " << i + 1 << "] -> " << alphabet.toAlpha(letter) << " -> ";
	}

	//cout << "RETURN" << endl;
	// return encrypted letter
	return this->alphabet.toAlpha(letter);
}

void Enigma::setString(string enc) {
	this->enc = enc;
}

string Enigma::encrypt() {
	string s;

	// until the string ends
	while (this->enc[0] != '$') {
		// match letter
		for (int i = 0; i < this->alphabet.size; i++) {
			// on match
			if (this->enc.find(this->alphabet.letters[i]) == 0) {
				// append encrypted letter to s
				string t = this->encryptLetter(i);
				s += t;

				//cout << this->alphabet.letters[i] << " -> " << t << endl;

				// remove letter from enc
				this->enc.erase(0, this->alphabet.letters[i].length());
			}
		}
	}

	return s;
}
