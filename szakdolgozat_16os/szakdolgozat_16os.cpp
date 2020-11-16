// szakdolgozat_16os.cpp : Defines the entry point for the console application.

#include <iostream>
#include "Kodolo.h"
#include "Dekodolo.h"
#include "IOtest.h"
#include <string>
#include <chrono>
#include <conio.h>
#include "TimeConverter.h"

using namespace std;

int main()
{
    auto start = chrono::high_resolution_clock::now(); //start timer

    int trigger = 1; //While ciklus "kapcsoló" 
    int valaszto;   //user által megadott feladatválasztó


    while (trigger)     //Loop futtatása amíg megfelelõ input nem érkezik
    {
        //Userinput bekérése
        cout << "Kerem adja meg milyen muveletet szeretne elvegezni." << endl;
        cout << "1.) Kodolas" << endl;
        cout << "2.) Dekodolas" << endl;

        
        
        if (!(cin >> valaszto)) //Megadott input vizsgálata (integer inputot kapott-e) 
        {
            //Nem integer input esetén hibaüzenet visszaadása és cin stream ürítése;
            cout << "Ervenytelen input adja meg ujra" << endl << endl;;
            cin.clear();
            cin.ignore();
        }
        else //Integer input érkezett
        {
            Kodolo a;
            Dekodolo b;
            switch (valaszto)
            {
            case 1: //Kódoló meghívása
                cout << "A valasztott akcio az " << valaszto << "-es szamu." << endl;
               a.GetTitkosSzoveg();
                trigger = 0;
                break;
            case 2: //Dekódoló meghívása
                cout << "A valasztott akcio a " << valaszto << "-es szamu." << endl;
                b.GetDekodoltSzoveg();
                trigger = 0;
                break;

            default:   //1,2 értékektõl különbözõ integer input érkezett
                cout << "Ervenytelen input adja meg ujra" << endl << endl;;
                break;
            }
        }
     
    }

    auto stop = chrono::high_resolution_clock::now(); //stop timer
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout<< "Runtime: " << duration.count() << "microseconds" << endl;
    _getch();
    return 0;
}

