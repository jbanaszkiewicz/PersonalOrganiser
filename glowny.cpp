#include <iostream>
#include "glowny.h"
#include <time.h>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <funkcje.h>
using namespace std;

Zlgodzina::Zlgodzina(string t, time_t r, time_t z){
    typ=t;
    rozp=r;
    zakon=z;
}


void Zlgodzina::CzasRozp(Zlgodzina &g){

    string i;
    ///zabezpieczenie przed wybraniem niepoprawnego przycisku
    if(i!="1")
        do{
          cout<<"rozpocznij(1):";
          cin>>i;
        }
        while(i!="1");
    if(i=="1"){
    time(&g.rozp);
    localtime(&g.rozp);
    }

}

void Zlgodzina::CzasZakon(Zlgodzina &g, string baza_danych){
    system("cls");

    string i;

    ///zabezpieczenie przed wybraniem niepoprawnego przycisku
    do{
      cout<<"zakoncz(1):";
      cin>>i;
    }
    while(i!="1");

    if(i=="1"){
    time(&g.zakon);
    localtime(&g.zakon);


///dodanie czasu rozpoczecia i zakonczenia do pliku
    ofstream k;
    k.open(baza_danych.c_str(), ios::app);

    k<<g.rozp<< " "<< g.zakon<< " "<<g.typ<<endl;

    k.close();


    }

}

void Zlgodzina::WTyp(Zlgodzina &g,string typy){
    ifstream f;
    string x;
    int licznik=1;
    Type *glowa=NULL;
    Type *aktual=NULL;
///otwieram plik z typami
    f.open(typy.c_str());
    if(f.good()){
        while (!f.eof()) {
            getline(f, x);
            if(x!=""){
                if(glowa==NULL){
                  glowa=new Type;
                  aktual=glowa;
                }
                else{
                    aktual->nast=new Type;
                    aktual=aktual->nast;
                }
                aktual->n=x;
                aktual->nr=licznik;
                aktual->nast=NULL;
                cout<<aktual->nr<<". "<<aktual->n<<endl;
                ++licznik;
            }
        }
    }
    else cout<<"cos nie dziala"<<endl;
    --licznik;
    f.close();
    int a;
    do{
        cout<<"wybierz typ: ";
        while(!(cin>>a) || a>licznik || a<0)
        {
          cout<<"wybierz typ: ";
          cin.clear();
          cin.sync();
        }
    }
    while(a<1 || a>licznik);
    aktual=glowa;
    while(aktual!=NULL){
        if(aktual->nr==a)
            g.typ=aktual->n;
        aktual=aktual->nast;
    }
    delete glowa;
    delete aktual;
}

void Odliczaj(int czas, string nazwa){
///
    time_t czas1;
    time_t czast;
///pobieram czas na początku
    time(&czas1);

    int min;
    int sek;
    do{
///pobieram bierzący czas
        time(&czast);
        min=(czast-czas1)/60;
        sek=czast-czas1-min*60;
///wyświetlam bieżącą różnicę czasu
        cout<<nazwa<<": "<<min<<":"<<sek<<endl;
        Sleep(1000);
        system("cls");
///powiadomienie w czasie przerwy,że minęło kolejne 5 min(żeby za długo się nie lenić) ;)
        if(nazwa=="Przerwa" && (czast-czas1)%300==0){
            if(difftime(czast,czas1)!=0)
                Beep(2000, 500);
        }
///przerwanie odliczania po kliknięciu dowolnego przycisku
        if(kbhit())
        {

            break;
        }



    }
    while(difftime(czast, czas1)<czas);


    Beep(2000, 500);


}

void Zlgodzina::Stworz(Zlgodzina &g,string baza_danych, string typy){
     WTyp(g,typy);
     CzasRozp(g);
     Odliczaj(3000, "Minelo");
     CzasZakon(g, baza_danych);
     Odliczaj(1800, "Przerwa");
}


