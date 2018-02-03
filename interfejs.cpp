#include <iostream>
#include "glowny.h"
#include "funkcje.h"
#include "statys.h"
#include <time.h>
#include <fstream>
#include "interfejs.h"


using namespace std;

void Menu(string baza_danych, string liczba_godzin, string typy, string semestr){
    int choice;
    do{
        cout << "Menu:"<< endl
            << "1.Zadaj liczbe godzin na dzis."<< endl
            << "2.Rozpocznij zlota godzine." << endl
            << "3.Edytuj ostatnia zlota godzine."<< endl
            << "4.Dodaj lub usun typ."<<endl
            << "5.Dodaj lub usun semestr."<<endl
            << "6.Przegladaj zlote godziny"<<endl
            << "7.Wejdz do statystyk"<<endl
            << "8.Zakoncz dzialanie programu"<<endl;

        while(!(cin>>choice)) //dopóki strumień jest w stanie błędu -> dopóki podawane są błędne dane
        {
          cout<<endl<<"Niepoprawne uzycie menu, wybierz ponownie: ";
          cin.clear(); //kasowanie flagi błędu strumienia
          cin.sync(); //kasowanie zbędnych znaków z bufora
        }

        switch(choice){
        case 1:
            ZadajLiczbe(liczba_godzin);
            break;
        case 2:
        {
            Zlgodzina g;
            g.Stworz(g, baza_danych, typy);
            break;
        }
        case 3:
            Edytuj(baza_danych, typy);
            break;
        case 4:
            DodajLubUsunTyp(typy);
            break;
        case 5:
            DodajLubUsunSemestr(semestr);
            break;
        case 6:
            Przegladaj(baza_danych);
            break;
        case 7:
            PokazStatystyki(baza_danych, liczba_godzin, typy, semestr);
            break;
        case 8:
            cout<<"Dziekuje za owocna prace"<<endl;
            break;
        default:
            cout<<"niepoprawne uzycie menu, wybierz ponownie"<<endl;
            break;

        }

    }
    while(choice!=8);
}
