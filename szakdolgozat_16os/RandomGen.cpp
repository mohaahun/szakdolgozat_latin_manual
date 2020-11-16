#include "RandomGen.h"
#include <iostream>
#include <vector>
#include <random>

using namespace std;

void RandomGen::Getrandom(vector<int>& rvector,int inputhossz)
{
    unsigned int seed=0;


    //Randomfüggvény által használt mag bekérése
    cout << "Kerem adja meg a randomgenerator magjat." << endl;
    cin >> seed;
    cout << endl << "A megadott mag: " << seed << endl << endl;

    //Randomszámok generálása vectorba
    srand(seed);
    rvector.clear();
    for (int i = 0; i < inputhossz*4; i++)
    {
        rvector.push_back(rand() % 15);
    }
}
