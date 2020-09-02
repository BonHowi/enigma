#pragma once
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Alphabet {
private:
public:
        string* letters;
        int size;
        Alphabet();
        Alphabet(int size);
        ~Alphabet();
        void init(/*int size, */string in, int iterator);
        int toIndex(string s);
        string toAlpha(int i);
        void print();
};

class Rotor {
private:
        int index;
        int size;
        int nTurns;
        int indexIncrement;

        int* forward;
        int* turns;

        int* cables;
        int* tableIncrements;
        //vector<int> tableIncrements;
public:
        void init(Alphabet& a);
        Rotor();
        ~Rotor();
        void setIndex(string s, Alphabet& a);
        void setIndex(int ind);
        int forwardSub(int i);
        int reverseSub(int i);
        bool onTurnover();
        void increment();
        void print(Alphabet& a);
        void rotateCables(Alphabet& a);
};

class Reflector {
private:
        int size;
        int* reflections;
public:
        void init(/*string in, */Alphabet& a);
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
