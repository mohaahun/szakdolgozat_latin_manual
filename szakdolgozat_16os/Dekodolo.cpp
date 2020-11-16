#include "Dekodolo.h"
#include "RandomGen.h"
#include <vector>
#include <iostream>
#include <string>
#include <bitset>
#include <conio.h>

using namespace std;



void Dekodolo::GetDekodoltSzoveg()
{
	vector<int> randszamok;
	RandomGen randomgen;
	string input;
	string output;

	input = Dekodolo::Szovegbekero();		//Visszafejtend� szoveg bek�r�se usert�l
	randomgen.Getrandom(randszamok, input.length()); ////Randomgener�tor megh�v�sa
	Dekodolo::GetDekodoloMx();		//Dek�dol�m�trix megh�v�sa
	output = Dekodolo::Visszafejtes(input, randszamok);		//Visszafejtesi algoritmus
}


//Visszafejtend� szoveg bek�r�se usert�l
string Dekodolo::Szovegbekero()
{
	string userinput = "";

	cout << "Adja meg a visszafejtendo szoveget." << endl;
	cin.ignore();
	getline(std::cin, userinput);
	cout << " A megadott input: " << userinput << endl;


	return userinput;
}


//Visszafejtesi algoritmus
string Dekodolo::Visszafejtes(string input, vector<int> randszamok)
{
	//Bek�rt input bin�ris stringg� alak�t�sa
	string binary_input;
	for (unsigned int i = 0; i < input.size();i++)
	{
		bitset<8> b(input.c_str()[i]);
		binary_input += b.to_string();
	}

	//4 bites szeletekre v�g�s �s a szeletek integerr� alak�t�sa
	vector <unsigned int> binarytoint;
	for (unsigned int i = 0; i < binary_input.size() / 4;i++)
	{
		string chunk = "";
		for (int j = 0; j < 4;j++)
		{
			chunk.push_back(binary_input[(i * 4) + j]);
		}

		binarytoint.push_back(stoi(chunk, 0, 2));
	}


	//Dek�dol�si elj�r�s
	for (unsigned int i = 0;i < 4;i++) //H�nyszor fut le a k�dol�s
	{
		for (unsigned int j = 0;j < binarytoint.size();j++) //H�ny elemre fut a k�dol�s
		{
			binarytoint[j] = decoder[randszamok[((j * 2) + 1)]][binarytoint[j]];
			binarytoint[j] = decoder[randszamok[(j * 2)]][binarytoint[j]];
		}
	}

	//Dek�dolt �rt�kek egybef�gg� bin�ris stringg� alak�t�sa
	string crypto_binary = "";
	for (unsigned int i = 0;i < binarytoint.size();i++)
	{
		crypto_binary.append(bitset<4>(binarytoint[i]).to_string());
	}

	//Dek�dolt bin�ris string sz�veges form�ra hoz�sa
	string output = "";
	for (unsigned int i = 0;i < crypto_binary.size() / 8;i++)
	{
		bitset<8> b1(crypto_binary, i * 8, 8);
		output += static_cast<unsigned char>(stoi(b1.to_string(), nullptr, 2));
	}
	cout << "A dekodolas utan kapott szoveg:" << endl << endl << output << endl;
	return output;
}


//Dek�dol�m�trix megh�v�sa
void Dekodolo::GetDekodoloMx()
{
	for (int x = 0;x < 16;x++)
	{
		for (int y = 0;y < 16;y++)
		{
			decoder[x][coder[x][y]] = y;
		}
	}
}
