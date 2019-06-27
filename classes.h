#pragma once
#include <memory>
#include <string>

using namespace std;

class Alphabet {
private:
public:
	string* letters;
	int size;

	Alphabet();
	~Alphabet();
	void init(int size, string in);
	int toIndex(string s);
	string toAlpha(int i);
	void print();
};

class Rotor {
private:
	int index;
	int size;
	int nTurns;

	int* forward;
	int* turns;
public:
	void init(string in, string t, Alphabet& a);
	Rotor();
	~Rotor();
	void setIndex(string s, Alphabet& a);
	int forwardSub(int i);
	int reverseSub(int i);
	bool onTurnover();
	void increment();
	void print(Alphabet& a);
};

class Reflector {
private:
	int size;
	int* reflections;
public:
	void init(string in, Alphabet& a);
	Reflector();
	~Reflector();
	int reflect(int i);
	void print(Alphabet& a);
};


class Enigma {
private:
	int numRotors;
	Alphabet alphabet;

	Reflector reflector;
	string enc;
public:
	Rotor* rotors;
	Enigma();
	~Enigma();
	void init(int numRotors, Alphabet& a);
	void addRotor(Rotor& r, int i);
	void setReflector(Reflector& r);
	void setString(string enc);
	void print();

	string encrypt();
	string encryptLetter(int letter);
};
