#include "Kodolo.h"
#include "RandomGen.h"
#include <vector>
#include <iostream>
#include <string>
#include <bitset>
#include <conio.h>

using namespace std;


//Kódoló algoritmus "main" függvénye
void Kodolo::GetTitkosSzoveg()
{
	vector<int> randszamok;
	RandomGen randomgen;
	string input;
	string output;
	
	input = Kodolo::Szovegbekero();		//Kódolandó szöveg bekérése a felhasználótól
	randomgen.Getrandom(randszamok, input.length());		//Randomgenerátor meghívása
	output = Kodolo::Titkosito(input,randszamok);		//Titkosító algoritmus 
}


//Kódolandó szöveg bekérése a felhasználótól
string Kodolo::Szovegbekero()
{
	string userinput;

	cout << "Adja meg a titkositando szoveget." << endl;
	cin.ignore();
	getline(std::cin, userinput);
	cout << " A megadott input: " << userinput << endl;


	return userinput;
}


//Titkosító algoritmus
string Kodolo::Titkosito(string input, vector<int> randszamok)
{
	//Bekért szöveg bináris stringgé alakítása és kiírása
	string binary_input;
	for (unsigned int i = 0; i < input.size();i++)
	{
		bitset<8> b(input.c_str()[i]);
		binary_input += b.to_string();
	}	

	//4 bites szeletekre vágás és a szeletek integerré alakítása
	vector <unsigned int> binarytoint;
	for(unsigned int i=0; i<binary_input.size()/4;i++)
	{
		string chunk = "";
		for (int j = 0; j < 4;j++)
		{
			chunk.push_back(binary_input[(i*4) + j]);
		}

		binarytoint.push_back(stoi(chunk, 0, 2));
	}	

	//Kódolási eljárás
	for (unsigned int i = 0;i < 4;i++) //Hányszor fut le a kódolás
	{ 
		for (unsigned int j = 0;j < binarytoint.size();j++)	//Hány elemre fut a kódolás
		{
			binarytoint[j] = coder[randszamok[(j * 2)]][binarytoint[j]];
			binarytoint[j] = coder[randszamok[((j * 2)+1)]][binarytoint[j]];
		}
	}

	//Kódolás utáni szeletek egybefüggõ bináris stringgé alakítása
	string crypto_binary = "";
	for (unsigned int i = 0;i < binarytoint.size();i++)
	{
		crypto_binary.append(bitset<4>(binarytoint[i]).to_string());
	}

	//Kódolt bináris string szöveggé alakítása
	string output = "";
	for (unsigned int i = 0;i < crypto_binary.size() / 8;i++)
	{
		bitset<8> b1(crypto_binary, i * 8, 8);
		output += static_cast<unsigned char>(stoi(b1.to_string(), nullptr, 2));
	}
	//Kódolt szöveg 
	cout << "A kodolas utan kapott szoveg:" << endl << endl << output << endl;

	return output;
}

