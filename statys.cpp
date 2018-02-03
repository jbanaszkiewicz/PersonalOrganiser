#include <iostream>
#include <time.h>
#include <fstream>
#include "statys.h"
#include "funkcje.h"
#include <iomanip>
using namespace std;


void StatDzien(string baza_danych, string liczba_godzin){
    int rok, miesiac, dzien;
///podanie daty
    cout<<"Podaj rok: ";
    while(!(cin>>rok))
    {
      cout<<"Podaj rok: ";
      cin.clear();
      cin.sync();
    }
    cout<<"Podaj miesiac: [cyfra]";
    do{

        while(!(cin>>miesiac))
        {
          cout<<"Podaj miesiac: [cyfra]";
          cin.clear();
          cin.sync();
        }
        if(miesiac<1 || miesiac>12)
           cout<<"Podaj miesiac: [cyfra]";
    }
    while(miesiac<1 || miesiac>12);

    cout<<"Podaj dzien: [cyfra]";
    do{

        while(!(cin>>dzien))
        {
          cout<<"Podaj dzien: [cyfra]";
          cin.clear();
          cin.sync();
        }
        if(dzien<1 || dzien>31)
           cout<<"Podaj dzien: [cyfra]";
    }
    while(dzien<1 || dzien>31);
///załadowanie  ZG na listę
    Lista *glowa=NULL;
    int licznikD=0;
    int dlugosc=0;

    string typ;
    time_t rozp;
    time_t zakon;


    Lista *aktual=NULL;
    ifstream f;
    f.open(baza_danych.c_str());
    if(f.good()){
        f>>rozp;
        f>>zakon;
        f>>typ;
        while (!f.eof()) {

            if(glowa==NULL){
              glowa=new Lista;
              aktual=glowa;
            }
            else{
                aktual->nast=new Lista;
                aktual=aktual->nast;
            }

            aktual->rozp_L=rozp;
            aktual->zakon_L=zakon;
            aktual->typ_L=typ;
            aktual->nast=NULL;
            f>>rozp;
            f>>zakon;
            f>>typ;

        }
    }
    else cout<<"cos nie dziala"<<endl;

    f.close();
///wyszukanie ZG z danego okresu i wyświetlenie ich
    aktual=glowa;
    tm r, z;
    while(aktual!=NULL){
        r=Zamien(aktual->rozp_L);
        z=Zamien(aktual->zakon_L);
        if(r.tm_year==rok-1900 && r.tm_mon==miesiac-1 && r.tm_mday==dzien){
            setlocale( LC_ALL, "Polish" );
            ++licznikD;
            dlugosc=dlugosc+difftime(aktual->zakon_L, aktual->rozp_L);

        }
        aktual=aktual->nast;
    }
    cout<<"Laczna ilosc zlotych godzin tego dnia: "<< licznikD<<endl;
    cout<<"Laczny czas zlotych godzin tego dnia: ";
    int hour, min, sek;
    hour=dlugosc/3600;
    min=(dlugosc-3600*hour)/60;
    sek=dlugosc-60*min-3600*hour;
    cout<< hour<<":"<<min<<":"<<sek<<endl;

    aktual=glowa;
///policzenie i wyświetlenie wydajności
    f.open(liczba_godzin.c_str());
    time_t data;
    int i;
    tm t;
    if(f.good()){
        while (!f.eof()) {
            f>>data;
            f>>i;
            t=Zamien(data);
             if(t.tm_year==rok-1900 && t.tm_mon==miesiac-1 && t.tm_mday==dzien){
                 cout<<setprecision( 3 )<<"Wydajnosc tego dnia: "<<(double(licznikD)/i)*100<<"%"<<endl;
             }

        }
    }

    f.close();

    delete glowa;
    delete aktual;
}
void StatTydzien(string baza_danych, string liczba_godzin){

    Lista *glowa=NULL;
    int licznikD=0;
    int dlugosc=0;

    string typ;
    time_t rozp;
    time_t zakon;

///Załadowanie pliku baza_danych do listy
    Lista *aktual=NULL;
    ifstream f;
    f.open(baza_danych.c_str());
    if(f.good()){
        f>>rozp;
        f>>zakon;
        f>>typ;
        while (!f.eof()) {

            if(glowa==NULL){
              glowa=new Lista;
              aktual=glowa;
            }
            else{
                aktual->nast=new Lista;
                aktual=aktual->nast;
            }

            aktual->rozp_L=rozp;
            aktual->zakon_L=zakon;
            aktual->typ_L=typ;
            aktual->nast=NULL;
            f>>rozp;
            f>>zakon;
            f>>typ;

        }
    }
    else cout<<"cos nie dziala"<<endl;

    f.close();
///liczenie ilosci i dlugosci zlotych godzin
    aktual=glowa;
    tm r, z;
    time_t czas;
    time(&czas);
    ///604800 -tyle sekund trwa tydzień ;)
    while(aktual!=NULL){
        if(aktual->rozp_L>=(czas-604800)){
            setlocale( LC_ALL, "Polish" );
            ++licznikD;
            dlugosc=dlugosc+difftime(aktual->zakon_L, aktual->rozp_L);

        }
        aktual=aktual->nast;
    }
    cout<<"Laczna ilosc zlotych godzin w tym tygodniu: "<< licznikD<<endl;
    cout<<"Laczny czas zlotych godzin w tym tygodniu: ";
    int hour, min, sek;
    hour=dlugosc/3600;
    min=(dlugosc-3600*hour)/60;
    sek=dlugosc-60*min-3600*hour;
    cout<< hour<<":"<<min<<":"<<sek<<endl;
///załadowanie zadanych ZG do listę
    aktual=glowa;
    ListaZad *glowa2=NULL;
    ListaZad *aktual2=NULL;

    time_t data;
    int ile;
    f.open(liczba_godzin.c_str());
    if(f.good()){

        while (!f.eof()) {
            f>>data;
            f>>ile;
            if(glowa2==NULL){
              glowa2=new ListaZad;
              aktual2=glowa2;
            }
            else{
                aktual2->nast=new ListaZad;
                aktual2=aktual2->nast;
            }

            aktual2->data_zad=data;
            aktual2->ilosc=ile;
            aktual2->nast=NULL;


        }
    }
    else cout<<"cos nie dziala"<<endl;
    aktual2=glowa2;
    f.close();
    ///\b razem liczy ilosc zlotych godzin
    int razem=0;
    ///\b sprawdz zmienna potrzebna do liczenia czy danego dnia zadano liczbe godzin
    bool sprawdz=0;
///funkcja zliczajaca zlote godziny, ktorym nie przydzielono zadanej ilosci
    while(aktual!=NULL){
        r=Zamien(aktual->rozp_L);
        if(aktual->rozp_L>=(czas-604800)){
            while (aktual2!=NULL) {
                z=Zamien(aktual2->data_zad);
                if(z.tm_year==r.tm_year && z.tm_mon==r.tm_mon && z.tm_mday==r.tm_mday){
                    sprawdz=1;
                }
                aktual2=aktual2->nast;
            }
            aktual2=glowa2;
            if(sprawdz==0)
                ++razem;

        }
        sprawdz=0;
        aktual=aktual->nast;
        aktual2=glowa2;
    }

    aktual2=glowa2;
///funkcja zliczajaca zadane zlote godziny z wybranego okresu
    while (aktual2!=NULL) {
        z=Zamien(aktual2->data_zad);
        if(aktual2->data_zad>=(czas-604800)){
            razem=razem+aktual2->ilosc;
        }
        aktual2=aktual2->nast;
    }

    if(razem!=0)
        cout<<setprecision( 3 )<<"Wydajnosc w tym tygodniu: "<<(double(licznikD)/razem)*100<<"%"<<endl;
    else
        cout<< "Wydajnosc w tym tygodniu: 0%"<<endl;

    delete glowa2;
    delete aktual2;
    delete glowa;
    delete aktual;
}
void StatMiesiac(string baza_danych, string liczba_godzin){
    int rok, miesiac;
///podanie daty
    cout<<"Podaj rok: ";
    while(!(cin>>rok))
    {
      cout<<"Podaj rok: ";
      cin.clear();
      cin.sync();
    }
    cout<<"Podaj miesiac: [cyfra]";
    do{

        while(!(cin>>miesiac))
        {
          cout<<"Podaj miesiac: [cyfra]";
          cin.clear();
          cin.sync();
        }
        if(miesiac<1 || miesiac>12)
           cout<<"Podaj miesiac: [cyfra]";
    }
    while(miesiac<1 || miesiac>12);

    Lista *glowa=NULL;
    int licznikD=0;
    int dlugosc=0;

    string typ;
    time_t rozp;
    time_t zakon;

///Załadowanie pliku baza_danych do listy
    Lista *aktual=NULL;
    ifstream f;
    f.open(baza_danych.c_str());
    if(f.good()){
        f>>rozp;
        f>>zakon;
        f>>typ;
        while (!f.eof()) {

            if(glowa==NULL){
              glowa=new Lista;
              aktual=glowa;
            }
            else{
                aktual->nast=new Lista;
                aktual=aktual->nast;
            }

            aktual->rozp_L=rozp;
            aktual->zakon_L=zakon;
            aktual->typ_L=typ;
            aktual->nast=NULL;
            f>>rozp;
            f>>zakon;
            f>>typ;

        }
    }
    else cout<<"cos nie dziala"<<endl;

    f.close();
///liczenie ilosci i dlugosci zlotych godzin
    aktual=glowa;
    tm r, z;
    while(aktual!=NULL){
        r=Zamien(aktual->rozp_L);
        z=Zamien(aktual->zakon_L);
        if(r.tm_year==rok-1900 && r.tm_mon==miesiac-1){
            setlocale( LC_ALL, "Polish" );
            ++licznikD;
            dlugosc=dlugosc+difftime(aktual->zakon_L, aktual->rozp_L);

        }
        aktual=aktual->nast;
    }
    cout<<"Laczna ilosc zlotych godzin w tym miesiacu: "<< licznikD<<endl;
    cout<<"Laczny czas zlotych godzin w tym miesiacu: ";
    int hour, min, sek;
    hour=dlugosc/3600;
    min=(dlugosc-3600*hour)/60;
    sek=dlugosc-60*min-3600*hour;
    cout<< hour<<":"<<min<<":"<<sek<<endl;
///zadadowanie zadanych ZG do listy
    aktual=glowa;
    ListaZad *glowa2=NULL;
    ListaZad *aktual2=NULL;

    time_t data;
    int ile;
    f.open(liczba_godzin.c_str());
    if(f.good()){

        while (!f.eof()) {
            f>>data;
            f>>ile;
            if(glowa2==NULL){
              glowa2=new ListaZad;
              aktual2=glowa2;
            }
            else{
                aktual2->nast=new ListaZad;
                aktual2=aktual2->nast;
            }

            aktual2->data_zad=data;
            aktual2->ilosc=ile;
            aktual2->nast=NULL;


        }
    }
    else cout<<"cos nie dziala"<<endl;
    aktual2=glowa2;
    f.close();
    ///\b razem liczy ilosc zlotych godzin
    int razem=0;
    ///\b sprawdz zmienna potrzebna do liczenia czy danego dnia zadano liczbe godzin
    bool sprawdz=0;
///funkcja zliczajaca zlote godziny, ktorym nie przydzielono zadanej ilosci
    while(aktual!=NULL){
        r=Zamien(aktual->rozp_L);
        if(r.tm_year==rok-1900 && r.tm_mon==miesiac-1){
            while (aktual2!=NULL) {
                z=Zamien(aktual2->data_zad);
                if(z.tm_year==r.tm_year && z.tm_mon==r.tm_mon && z.tm_mday==r.tm_mday){
                    sprawdz=1;
                }
                aktual2=aktual2->nast;
            }
            aktual2=glowa2;
            if(sprawdz==0)
                ++razem;

        }
        sprawdz=0;
        aktual=aktual->nast;
        aktual2=glowa2;
    }

    aktual2=glowa2;
///funkcja zliczajaca zadane zlote godziny z wybranego okresu
    while (aktual2!=NULL) {
        z=Zamien(aktual2->data_zad);
        if(z.tm_year==rok-1900 && z.tm_mon==miesiac-1){
            razem=razem+aktual2->ilosc;
        }
        aktual2=aktual2->nast;
    }

    if(razem!=0)
        cout<<setprecision( 3 )<<"Wydajnosc w tym miesiacu: "<<(double(licznikD)/razem)*100<<"%"<<endl;
    else
        cout<< "Wydajnosc w tym miesiacu: 0%"<<endl;

    delete glowa2;
    delete aktual2;
    delete glowa;
    delete aktual;

}
void StatRok(string baza_danych, string liczba_godzin){
    int rok;
///podanie daty
    cout<<"Podaj rok: ";
    while(!(cin>>rok))
    {
      cout<<"Podaj rok: ";
      cin.clear();
      cin.sync();
    }
    Lista *glowa=NULL;
    int licznikD=0;
    int dlugosc=0;

    string typ;
    time_t rozp;
    time_t zakon;

///Załadowanie pliku baza_danych do listy
    Lista *aktual=NULL;
    ifstream f;
    f.open(baza_danych.c_str());
    if(f.good()){
        f>>rozp;
        f>>zakon;
        f>>typ;
        while (!f.eof()) {

            if(glowa==NULL){
              glowa=new Lista;
              aktual=glowa;
            }
            else{
                aktual->nast=new Lista;
                aktual=aktual->nast;
            }

            aktual->rozp_L=rozp;
            aktual->zakon_L=zakon;
            aktual->typ_L=typ;
            aktual->nast=NULL;
            f>>rozp;
            f>>zakon;
            f>>typ;

        }
    }
    else cout<<"cos nie dziala"<<endl;

    f.close();
///liczenie ilosci i dlugosci zlotych godzin
    aktual=glowa;
    tm r, z;
    while(aktual!=NULL){
        r=Zamien(aktual->rozp_L);
        z=Zamien(aktual->zakon_L);
        if(r.tm_year==rok-1900){
            setlocale( LC_ALL, "Polish" );
            ++licznikD;
            dlugosc=dlugosc+difftime(aktual->zakon_L, aktual->rozp_L);

        }
        aktual=aktual->nast;
    }
    cout<<"Laczna ilosc zlotych godzin w tym roku: "<< licznikD<<endl;
    cout<<"Laczny czas zlotych godzin w tym roku: ";
    int hour, min, sek;
    hour=dlugosc/3600;
    min=(dlugosc-3600*hour)/60;
    sek=dlugosc-60*min-3600*hour;
    cout<< hour<<":"<<min<<":"<<sek<<endl;
///zadadowanie zadanych ZG do listy
    aktual=glowa;
    ListaZad *glowa2=NULL;
    ListaZad *aktual2=NULL;

    time_t data;
    int ile;
    f.open(liczba_godzin.c_str());
    if(f.good()){

        while (!f.eof()) {
            f>>data;
            f>>ile;
            if(glowa2==NULL){
              glowa2=new ListaZad;
              aktual2=glowa2;
            }
            else{
                aktual2->nast=new ListaZad;
                aktual2=aktual2->nast;
            }

            aktual2->data_zad=data;
            aktual2->ilosc=ile;
            aktual2->nast=NULL;


        }
    }
    else cout<<"cos nie dziala"<<endl;
    aktual2=glowa2;
    f.close();
    ///\b razem liczy ilosc zlotych godzin
    int razem=0;
    ///\b sprawdz zmienna potrzebna do liczenia czy danego dnia zadano liczbe godzin
    bool sprawdz=0;
///funkcja zliczajaca zlote godziny, ktorym nie przydzielono zadanej ilosci
    while(aktual!=NULL){
        r=Zamien(aktual->rozp_L);
        if(r.tm_year==rok-1900){
            while (aktual2!=NULL) {
                z=Zamien(aktual2->data_zad);
                if(z.tm_year==r.tm_year && z.tm_mon==r.tm_mon && z.tm_mday==r.tm_mday){
                    sprawdz=1;
                }
                aktual2=aktual2->nast;
            }
            aktual2=glowa2;
            if(sprawdz==0)
                ++razem;

        }
        sprawdz=0;
        aktual=aktual->nast;
        aktual2=glowa2;
    }

    aktual2=glowa2;
///funkcja zliczajaca zadane zlote godziny z wybranego okresu
    while (aktual2!=NULL) {
        z=Zamien(aktual2->data_zad);
        if(z.tm_year==rok-1900){
            razem=razem+aktual2->ilosc;
        }
        aktual2=aktual2->nast;
    }


    if(razem!=0)
        cout<<setprecision( 3 )<<"Wydajnosc w tym roku: "<<(double(licznikD)/razem)*100<<"%"<<endl;
    else
        cout<< "Wydajnosc w tym roku: 0%"<<endl;

    delete glowa2;
    delete aktual2;
    delete glowa;
    delete aktual;
}
void StatSemestr(string baza_danych, string liczba_godzin, string semestr){
///załadowanie semestrow na listę
    ifstream f;
    string x;
    time_t r;
    time_t z;
    tm rozp;
    tm zakon;
    char bufor[ 64 ];
    int licznik=1;
    Semestry *glowa=NULL;
    Semestry *aktual=NULL;
    f.open(semestr.c_str());
    if(f.good()){
        f>>r;
        f>>z;
        f>>x;
        while (!f.eof()) {



                if(glowa==NULL){
                  glowa=new Semestry;
                  aktual=glowa;
                }
                else{
                    aktual->nast=new Semestry;
                    aktual=aktual->nast;
                }
                aktual->n_S=x;
                aktual->nr_S=licznik;
                aktual->rozp_S=r;
                aktual->zakon_S=z;
                aktual->nast=NULL;

                ++licznik;
                f>>r;
                f>>z;
                f>>x;




        }
    }

    else cout<<"cos nie dziala"<<endl;
    --licznik;
    f.close();
///wyswietlenie semestrów.
    aktual=glowa;
    setlocale( LC_ALL, "Polish" );
    while(aktual!=NULL){
        rozp=Zamien(aktual->rozp_S);
        zakon=Zamien(aktual->zakon_S);

        cout<<aktual->nr_S<<". ";
        strftime( bufor, sizeof( bufor ), "%x" , & rozp );
        cout<<"rozpoczecie: "<<bufor<<" ";
        strftime( bufor, sizeof( bufor ), "%x" , & zakon );
        cout<<"zakonczenie: "<<bufor<<" ";
        cout<<aktual->n_S<<endl;
        aktual=aktual->nast;
    }
    aktual=glowa;

    string typ2;
    time_t rozp2;
    time_t zakon2;
///zaladowanie zlotych godzin na listę.
    Lista *glowa2=NULL;
    Lista *aktual2=NULL;
    f.open(baza_danych.c_str());
    if(f.good()){
        f>>rozp2;
        f>>zakon2;
        f>>typ2;
        while (!f.eof()) {

            if(glowa2==NULL){
              glowa2=new Lista;
              aktual2=glowa2;
            }
            else{
                aktual2->nast=new Lista;
                aktual2=aktual2->nast;
            }

            aktual2->rozp_L=rozp2;
            aktual2->zakon_L=zakon2;
            aktual2->typ_L=typ2;
            aktual2->nast=NULL;
            f>>rozp2;
            f>>zakon2;
            f>>typ2;

        }
    }
    else cout<<"cos nie dziala"<<endl;
    aktual2=glowa2;
    f.close();
    int wybor;
///wybór semestru
    cout<<"wybierz semestr: ";
    do{

        while(!(cin>>wybor)) //dopóki strumień jest w stanie błędu -> dopóki podawane są błędne dane
        {
          cout<<"wybierz semestr: ";
          cin.clear(); //kasowanie flagi błędu strumienia
          cin.sync(); //kasowanie zbędnych znaków z bufora
        }
        if(wybor>licznik || wybor<1)
            cout<<"wybierz semestr: ";
    }
    while(wybor>licznik || wybor<1);
/// \b r data rozpoczecia wybranego semestru
///\b z data zakonczenia wybranego semestru
    double licznikD=0, dlugosc=0;
    while (aktual!=NULL) {
        if(aktual->nr_S==wybor){
            r=aktual->rozp_S;
            z=aktual->zakon_S;
        }
        aktual=aktual->nast;
    }
    aktual=glowa;
///zliczanie ilosci zlotych godzin w semestrze i łącznego czasu+wyswietlanie.
    while (aktual2!=NULL) {
        if(aktual2->rozp_L>=r && aktual2->rozp_L<=z){
            setlocale( LC_ALL, "Polish" );
            ++licznikD;
            dlugosc=dlugosc+difftime(aktual2->zakon_L, aktual2->rozp_L);

        }
        aktual2=aktual2->nast;
    }
    aktual2=glowa2;
    cout<<"Laczna ilosc zlotych godzin w tym semestrze: "<< licznikD<<endl;
    cout<<"Laczny czas zlotych godzin w tym semestrze: ";
    int hour, min, sek;
    hour=dlugosc/3600;
    min=(dlugosc-3600*hour)/60;
    sek=dlugosc-60*min-3600*hour;
    cout<< hour<<":"<<min<<":"<<sek<<endl;
///załadowanie zadanych złotych godzin do listy
    ListaZad *glowa3=NULL;
    ListaZad *aktual3=NULL;

    time_t data;
    int ile;
    f.open(liczba_godzin.c_str());
    if(f.good()){

        while (!f.eof()) {
            f>>data;
            f>>ile;
            if(glowa3==NULL){
              glowa3=new ListaZad;
              aktual3=glowa3;
            }
            else{
                aktual3->nast=new ListaZad;
                aktual3=aktual3->nast;
            }

            aktual3->data_zad=data;
            aktual3->ilosc=ile;
            aktual3->nast=NULL;


        }
    }
    else cout<<"cos nie dziala"<<endl;
    aktual3=glowa3;
    aktual2=glowa2;
    aktual=glowa;
    f.close();

    ///\b razem liczy ilosc zlotych godzin
    int razem=0;
    ///\b sprawdz zmienna potrzebna do liczenia czy danego dnia zadano liczbe godzin
    bool sprawdz=0;
///funkcja zliczajaca zlote godziny, ktorym nie przydzielono zadanej ilosci
    while(aktual2!=NULL){
        rozp=Zamien(aktual2->rozp_L);
        if(aktual2->rozp_L>=r && aktual2->rozp_L<=z){
            while (aktual3!=NULL) {
                zakon=Zamien(aktual3->data_zad);
                if(zakon.tm_year==rozp.tm_year && zakon.tm_mon==rozp.tm_mon && zakon.tm_mday==rozp.tm_mday){
                    sprawdz=1;
                }
                aktual3=aktual3->nast;
            }
            if(sprawdz==0)
                ++razem;

        }
        sprawdz=0;
        aktual2=aktual2->nast;
        aktual3=glowa3;
    }

    aktual3=glowa3;
///funkcja zliczajaca zadane zlote godziny z wybranego okresu
    while (aktual3!=NULL) {
        if(aktual3->data_zad>=r && aktual3->data_zad<=z){
            razem=razem+aktual3->ilosc;
        }
        aktual3=aktual3->nast;
    }


    if(razem!=0)
        cout<<setprecision( 3 )<<"Wydajnosc w tym semestrze: "<<(double(licznikD)/razem)*100<<"%"<<endl;
    else
        cout<< "Wydajnosc w tym semestrze: 0%"<<endl;




    delete aktual3;
    delete glowa3;
    delete aktual2;
    delete glowa2;
    delete aktual;
    delete glowa;
}
void TypStatDzien(string baza_danych, string typy){
    int rok, miesiac, dzien, nr;
    cout<<"Podaj rok: ";
    while(!(cin>>rok))
    {
      cout<<"Podaj rok: ";
      cin.clear();
      cin.sync();
    }
    cout<<"Podaj miesiac: [cyfra]";
    do{

        while(!(cin>>miesiac))
        {
          cout<<"Podaj miesiac: [cyfra]";
          cin.clear();
          cin.sync();
        }
        if(miesiac<1 || miesiac>12)
           cout<<"Podaj miesiac: [cyfra]";
    }
    while(miesiac<1 || miesiac>12);

    cout<<"Podaj dzien: [cyfra]";
    do{

        while(!(cin>>dzien))
        {
          cout<<"Podaj dzien: [cyfra]";
          cin.clear();
          cin.sync();
        }
        if(dzien<1 || dzien>31)
           cout<<"Podaj dzien: [cyfra]";
    }
    while(dzien<1 || dzien>31);
    ifstream f;
///zaladowanie typów do listy
    string x;
    int licznik=1;
    Type *glowa2=NULL;
    Type *aktual2=NULL;
    f.open(typy.c_str());
    if(f.good()){
        while (!f.eof()) {
            getline(f, x);
            if(x!=""){
                if(glowa2==NULL){
                  glowa2=new Type;
                  aktual2=glowa2;
                }
                else{
                    aktual2->nast=new Type;
                    aktual2=aktual2->nast;
                }
                aktual2->n=x;
                aktual2->nr=licznik;
                aktual2->nast=NULL;
                cout<<aktual2->nr<<". "<<aktual2->n<<endl;
                ++licznik;

            }
        }
    }
    else cout<<"cos nie dziala"<<endl;
///zmniejszam licznik, bo przy ostatnm obrocie pętli licznik się niepotrzebnie zwiększył.
    --licznik;

    f.close();
    aktual2=glowa2;
///wybranie typu
    cout<<"Wybierz nr typu: ";
    do{
        while(!(cin>>nr))
        {
          cout<<"Wybierz nr typu: ";
          cin.clear(); //kasowanie flagi błędu strumienia
          cin.sync(); //kasowanie zbędnych znaków z bufora
        }
        if(!(nr<=licznik && nr>0))
            cout<<"Wybierz nr typu: ";
    }
///w zmienną \b x podstawiam wybrany typ
    while(!(nr<=licznik && nr>0));
    while (aktual2!=NULL) {
        if(aktual2->nr==nr)
            x=aktual2->n;
        aktual2=aktual2->nast;
    }
    aktual2=glowa2;

    Lista *glowa=NULL;
    int licznikD=0;
    int dlugosc=0;

    string typ;
    time_t rozp;
    time_t zakon;


    Lista *aktual=NULL;
///pobranie danych z bazy danych
    f.open(baza_danych.c_str());
    if(f.good()){
        f>>rozp;
        f>>zakon;
        f>>typ;
        while (!f.eof()) {

            if(glowa==NULL){
              glowa=new Lista;
              aktual=glowa;
            }
            else{
                aktual->nast=new Lista;
                aktual=aktual->nast;
            }

            aktual->rozp_L=rozp;
            aktual->zakon_L=zakon;
            aktual->typ_L=typ;
            aktual->nast=NULL;
            f>>rozp;
            f>>zakon;
            f>>typ;

        }
    }
    else cout<<"cos nie dziala"<<endl;

    f.close();
///zliczenie ilości i długości wybranych ZG
    aktual=glowa;
    tm r, z;
    while(aktual!=NULL){
        r=Zamien(aktual->rozp_L);
        z=Zamien(aktual->zakon_L);
        if(r.tm_year==rok-1900 && r.tm_mon==miesiac-1 && r.tm_mday==dzien && aktual->typ_L==x){
            ++licznikD;
            dlugosc=dlugosc+difftime(aktual->zakon_L, aktual->rozp_L);

        }
        aktual=aktual->nast;
    }
    cout<<"Laczna ilosc zlotych godzin tego dnia wybranego typu: "<< licznikD<<endl;
    cout<<"Laczny czas zlotych godzin tego dnia wybranego typu: ";
    int hour, min, sek;
    hour=dlugosc/3600;
    min=(dlugosc-3600*hour)/60;
    sek=dlugosc-60*min-3600*hour;
    cout<< hour<<":"<<min<<":"<<sek<<endl;
    delete glowa2;
    delete aktual2;
    delete glowa;
    delete aktual;
}
void TypStatTydzien(string baza_danych, string typy){
    int nr;
    ifstream f;
///zaladowanie typów do listy
    string x;
    int licznik=1;
    Type *glowa3=NULL;
    Type *aktual3=NULL;
    f.open(typy.c_str());
    if(f.good()){
        while (!f.eof()) {
            getline(f, x);
            if(x!=""){
                if(glowa3==NULL){
                  glowa3=new Type;
                  aktual3=glowa3;
                }
                else{
                    aktual3->nast=new Type;
                    aktual3=aktual3->nast;
                }
                aktual3->n=x;
                aktual3->nr=licznik;
                aktual3->nast=NULL;
                cout<<aktual3->nr<<". "<<aktual3->n<<endl;
                ++licznik;

            }
        }
    }
    else cout<<"cos nie dziala"<<endl;
///zmniejszam licznik, bo przy ostatnm obrocie pętli licznik się niepotrzebnie zwiększył.
    --licznik;

    f.close();
    aktual3=glowa3;
///wybranie typu
    cout<<"Wybierz nr typu: ";
    do{
        while(!(cin>>nr))
        {
          cout<<"Wybierz nr typu: ";
          cin.clear(); //kasowanie flagi błędu strumienia
          cin.sync(); //kasowanie zbędnych znaków z bufora
        }
        if(!(nr<=licznik && nr>0))
            cout<<"Wybierz nr typu: ";
    }
///w zmienną \b x podstawiam wybrany typ
    while(!(nr<=licznik && nr>0));
    while (aktual3!=NULL) {
        if(aktual3->nr==nr)
            x=aktual3->n;
        aktual3=aktual3->nast;
    }
    aktual3=glowa3;

    Lista *glowa=NULL;
    int licznikD=0;
    int dlugosc=0;

    string typ;
    time_t rozp;
    time_t zakon;

///Załadowanie pliku baza_danych do listy
    Lista *aktual=NULL;
    f.open(baza_danych.c_str());
    if(f.good()){
        f>>rozp;
        f>>zakon;
        f>>typ;
        while (!f.eof()) {

            if(glowa==NULL){
              glowa=new Lista;
              aktual=glowa;
            }
            else{
                aktual->nast=new Lista;
                aktual=aktual->nast;
            }

            aktual->rozp_L=rozp;
            aktual->zakon_L=zakon;
            aktual->typ_L=typ;
            aktual->nast=NULL;
            f>>rozp;
            f>>zakon;
            f>>typ;

        }
    }
    else cout<<"cos nie dziala"<<endl;

    f.close();
///liczenie ilosci i dlugosci zlotych godzin
    aktual=glowa;
    time_t czas;
    time(&czas);
    ///604800 -tyle sekund trwa tydzień ;)
    while(aktual!=NULL){
        if(aktual->rozp_L>=(czas-604800) && aktual->typ_L==x){
            setlocale( LC_ALL, "Polish" );
            ++licznikD;
            dlugosc=dlugosc+difftime(aktual->zakon_L, aktual->rozp_L);

        }
        aktual=aktual->nast;
    }
    cout<<"Laczna ilosc zlotych godzin w tym tygodniu typu "<<x<<": "<< licznikD<<endl;
    cout<<"Laczny czas zlotych godzin w tym tygodniu typu "<<x<<": ";
    int hour, min, sek;
    hour=dlugosc/3600;
    min=(dlugosc-3600*hour)/60;
    sek=dlugosc-60*min-3600*hour;
    cout<< hour<<":"<<min<<":"<<sek<<endl;


    delete glowa3;
    delete aktual3;
    delete glowa;
    delete aktual;
}
void TypStatMiesiac(string baza_danych,  string typy){
    int rok, miesiac;
    cout<<"Podaj rok: ";
    while(!(cin>>rok))
    {
      cout<<"Podaj rok: ";
      cin.clear();
      cin.sync();
    }
    cout<<"Podaj miesiac: [cyfra]";
    do{

        while(!(cin>>miesiac))
        {
          cout<<"Podaj miesiac: [cyfra]";
          cin.clear();
          cin.sync();
        }
        if(miesiac<1 || miesiac>12)
           cout<<"Podaj miesiac: [cyfra]";
    }
    while(miesiac<1 || miesiac>12);

    Lista *glowa=NULL;
    int licznikD=0;
    int dlugosc=0;

    string typ;
    time_t rozp;
    time_t zakon;

///Załadowanie pliku baza_danych do listy
    Lista *aktual=NULL;
    ifstream f;
    f.open(baza_danych.c_str());
    if(f.good()){
        f>>rozp;
        f>>zakon;
        f>>typ;
        while (!f.eof()) {

            if(glowa==NULL){
              glowa=new Lista;
              aktual=glowa;
            }
            else{
                aktual->nast=new Lista;
                aktual=aktual->nast;
            }

            aktual->rozp_L=rozp;
            aktual->zakon_L=zakon;
            aktual->typ_L=typ;
            aktual->nast=NULL;
            f>>rozp;
            f>>zakon;
            f>>typ;

        }
    }
    else cout<<"cos nie dziala"<<endl;

    f.close();
    int nr;
///zaladowanie typów do listy
    string x;
    int licznik=1;
    Type *glowa3=NULL;
    Type *aktual3=NULL;
    f.open(typy.c_str());
    if(f.good()){
        while (!f.eof()) {
            getline(f, x);
            if(x!=""){
                if(glowa3==NULL){
                  glowa3=new Type;
                  aktual3=glowa3;
                }
                else{
                    aktual3->nast=new Type;
                    aktual3=aktual3->nast;
                }
                aktual3->n=x;
                aktual3->nr=licznik;
                aktual3->nast=NULL;
                cout<<aktual3->nr<<". "<<aktual3->n<<endl;
                ++licznik;

            }
        }
    }
    else cout<<"cos nie dziala"<<endl;
///zmniejszam licznik, bo przy ostatnm obrocie pętli licznik się niepotrzebnie zwiększył.
    --licznik;

    f.close();
    aktual3=glowa3;
///wybranie typu
    cout<<"Wybierz nr typu: ";
    do{
        while(!(cin>>nr))
        {
          cout<<"Wybierz nr typu: ";
          cin.clear(); //kasowanie flagi błędu strumienia
          cin.sync(); //kasowanie zbędnych znaków z bufora
        }
        if(!(nr<=licznik && nr>0))
            cout<<"Wybierz nr typu: ";
    }
///w zmienną \b x podstawiam wybrany typ
    while(!(nr<=licznik && nr>0));
    while (aktual3!=NULL) {
        if(aktual3->nr==nr)
            x=aktual3->n;
        aktual3=aktual3->nast;
    }
    aktual3=glowa3;

///liczenie ilosci i dlugosci zlotych godzin
    aktual=glowa;
    tm r, z;
    while(aktual!=NULL){
        r=Zamien(aktual->rozp_L);
        z=Zamien(aktual->zakon_L);
        if(r.tm_year==rok-1900 && r.tm_mon==miesiac-1 && aktual->typ_L==x){
            ++licznikD;
            dlugosc=dlugosc+difftime(aktual->zakon_L, aktual->rozp_L);

        }
        aktual=aktual->nast;
    }
    cout<<"Laczna ilosc zlotych godzin w tym miesiacu typu "<<x<<": "<< licznikD<<endl;
    cout<<"Laczny czas zlotych godzin w tym miesiacu typu "<<x<<": ";
    int hour, min, sek;
    hour=dlugosc/3600;
    min=(dlugosc-3600*hour)/60;
    sek=dlugosc-60*min-3600*hour;
    cout<< hour<<":"<<min<<":"<<sek<<endl;


    delete glowa3;
    delete aktual3;
    delete glowa;
    delete aktual;


}
void TypStatRok(string baza_danych, string typy){
    int rok,nr;
    cout<<"Podaj rok: ";
    while(!(cin>>rok))
    {
      cout<<"Podaj rok: ";
      cin.clear();
      cin.sync();
    }

    Lista *glowa=NULL;
    int licznikD=0;
    int dlugosc=0;

    string typ;
    time_t rozp;
    time_t zakon;

///Załadowanie pliku baza_danych do listy
    Lista *aktual=NULL;
    ifstream f;
    f.open(baza_danych.c_str());
    if(f.good()){
        f>>rozp;
        f>>zakon;
        f>>typ;
        while (!f.eof()) {

            if(glowa==NULL){
              glowa=new Lista;
              aktual=glowa;
            }
            else{
                aktual->nast=new Lista;
                aktual=aktual->nast;
            }

            aktual->rozp_L=rozp;
            aktual->zakon_L=zakon;
            aktual->typ_L=typ;
            aktual->nast=NULL;
            f>>rozp;
            f>>zakon;
            f>>typ;

        }
    }
    else cout<<"cos nie dziala"<<endl;

    f.close();
///zaladowanie typów do listy
    string x;
    int licznik=1;
    Type *glowa3=NULL;
    Type *aktual3=NULL;
    f.open(typy.c_str());
    if(f.good()){
        while (!f.eof()) {
            getline(f, x);
            if(x!=""){
                if(glowa3==NULL){
                  glowa3=new Type;
                  aktual3=glowa3;
                }
                else{
                    aktual3->nast=new Type;
                    aktual3=aktual3->nast;
                }
                aktual3->n=x;
                aktual3->nr=licznik;
                aktual3->nast=NULL;
                cout<<aktual3->nr<<". "<<aktual3->n<<endl;
                ++licznik;

            }
        }
    }
    else cout<<"cos nie dziala"<<endl;
///zmniejszam licznik, bo przy ostatnm obrocie pętli licznik się niepotrzebnie zwiększył.
    --licznik;

    f.close();
    aktual3=glowa3;
///wybranie typu
    cout<<"Wybierz nr typu: ";
    do{
        while(!(cin>>nr))
        {
          cout<<"Wybierz nr typu: ";
          cin.clear(); //kasowanie flagi błędu strumienia
          cin.sync(); //kasowanie zbędnych znaków z bufora
        }
        if(!(nr<=licznik && nr>0))
            cout<<"Wybierz nr typu: ";
    }
///w zmienną \b x podstawiam wybrany typ
    while(!(nr<=licznik && nr>0));
    while (aktual3!=NULL) {
        if(aktual3->nr==nr)
            x=aktual3->n;
        aktual3=aktual3->nast;
    }
    aktual3=glowa3;

///liczenie ilosci i dlugosci zlotych godzin
    aktual=glowa;
    tm r, z;
    while(aktual!=NULL){
        r=Zamien(aktual->rozp_L);
        z=Zamien(aktual->zakon_L);
        if(r.tm_year==rok-1900 && aktual->typ_L==x){
            setlocale( LC_ALL, "Polish" );
            ++licznikD;
            dlugosc=dlugosc+difftime(aktual->zakon_L, aktual->rozp_L);

        }
        aktual=aktual->nast;
    }
    cout<<"Laczna ilosc zlotych godzin w tym roku typu "<<x<<": "<< licznikD<<endl;
    cout<<"Laczny czas zlotych godzin w tym roku typu "<<x<<": ";
    int hour, min, sek;
    hour=dlugosc/3600;
    min=(dlugosc-3600*hour)/60;
    sek=dlugosc-60*min-3600*hour;
    cout<< hour<<":"<<min<<":"<<sek<<endl;

    delete glowa3;
    delete aktual3;
    delete glowa;
    delete aktual;
}
void TypStatSemestr(string baza_danych, string typy, string semestr){
///załadowanie semestrow na listę
    ifstream f;
    string w;
    time_t r;
    time_t z;
    tm rozp;
    tm zakon;
    char bufor[ 64 ];
    int licznik1=1;
    Semestry *glowa=NULL;
    Semestry *aktual=NULL;
    f.open(semestr.c_str());
    if(f.good()){
        f>>r;
        f>>z;
        f>>w;
        while (!f.eof()) {



                if(glowa==NULL){
                  glowa=new Semestry;
                  aktual=glowa;
                }
                else{
                    aktual->nast=new Semestry;
                    aktual=aktual->nast;
                }
                aktual->n_S=w;
                aktual->nr_S=licznik1;
                aktual->rozp_S=r;
                aktual->zakon_S=z;
                aktual->nast=NULL;

                ++licznik1;
                f>>r;
                f>>z;
                f>>w;




        }
    }

    else cout<<"cos nie dziala"<<endl;
    --licznik1;
    f.close();
///wyswietlenie semestrów.
    aktual=glowa;
    setlocale( LC_ALL, "Polish" );
    while(aktual!=NULL){
        rozp=Zamien(aktual->rozp_S);
        zakon=Zamien(aktual->zakon_S);

        cout<<aktual->nr_S<<". ";
        strftime( bufor, sizeof( bufor ), "%x" , & rozp );
        cout<<"rozpoczecie: "<<bufor<<" ";
        strftime( bufor, sizeof( bufor ), "%x" , & zakon );
        cout<<"zakonczenie: "<<bufor<<" ";
        cout<<aktual->n_S<<endl;
        aktual=aktual->nast;
    }
    aktual=glowa;

    string typ2;
    time_t rozp2;
    time_t zakon2;
///zaladowanie zlotych godzin na listę.
    Lista *glowa2=NULL;
    Lista *aktual2=NULL;
    f.open(baza_danych.c_str());
    if(f.good()){
        f>>rozp2;
        f>>zakon2;
        f>>typ2;
        while (!f.eof()) {

            if(glowa2==NULL){
              glowa2=new Lista;
              aktual2=glowa2;
            }
            else{
                aktual2->nast=new Lista;
                aktual2=aktual2->nast;
            }

            aktual2->rozp_L=rozp2;
            aktual2->zakon_L=zakon2;
            aktual2->typ_L=typ2;
            aktual2->nast=NULL;
            f>>rozp2;
            f>>zakon2;
            f>>typ2;

        }
    }
    else cout<<"cos nie dziala"<<endl;
    aktual2=glowa2;
    f.close();
    int wybor;
///wybór semestru
    cout<<"wybierz semestr: ";
    do{

        while(!(cin>>wybor)) //dopóki strumień jest w stanie błędu -> dopóki podawane są błędne dane
        {
          cout<<"wybierz semestr: ";
          cin.clear(); //kasowanie flagi błędu strumienia
          cin.sync(); //kasowanie zbędnych znaków z bufora
        }
        if(wybor>licznik1 || wybor<1)
            cout<<"wybierz semestr: ";
    }
    while(wybor>licznik1 || wybor<1);
/// \b r data rozpoczecia wybranego semestru
///\b z data zakonczenia wybranego semestru
    double licznikD=0, dlugosc=0;
    while (aktual!=NULL) {
        if(aktual->nr_S==wybor){
            r=aktual->rozp_S;
            z=aktual->zakon_S;
        }
        aktual=aktual->nast;
    }
    aktual=glowa;
    int nr;
///zaladowanie typów do listy
    string x;
    int licznik=1;
    Type *glowa3=NULL;
    Type *aktual3=NULL;
    f.open(typy.c_str());
    if(f.good()){
        while (!f.eof()) {
            getline(f, x);
            if(x!=""){
                if(glowa3==NULL){
                  glowa3=new Type;
                  aktual3=glowa3;
                }
                else{
                    aktual3->nast=new Type;
                    aktual3=aktual3->nast;
                }
                aktual3->n=x;
                aktual3->nr=licznik;
                aktual3->nast=NULL;
                cout<<aktual3->nr<<". "<<aktual3->n<<endl;
                ++licznik;

            }
        }
    }
    else cout<<"cos nie dziala"<<endl;
///zmniejszam licznik, bo przy ostatnm obrocie pętli licznik się niepotrzebnie zwiększył.
    --licznik;

    f.close();
    aktual3=glowa3;
///wybranie typu
    cout<<"Wybierz nr typu: ";
    do{
        while(!(cin>>nr))
        {
          cout<<"Wybierz nr typu: ";
          cin.clear(); //kasowanie flagi błędu strumienia
          cin.sync(); //kasowanie zbędnych znaków z bufora
        }
        if(!(nr<=licznik && nr>0))
            cout<<"Wybierz nr typu: ";
    }
///w zmienną \b x podstawiam wybrany typ
    while(!(nr<=licznik && nr>0));
    while (aktual3!=NULL) {
        if(aktual3->nr==nr)
            x=aktual3->n;
        aktual3=aktual3->nast;
    }
    aktual3=glowa3;
///zliczanie ilosci zlotych godzin w semestrze i łącznego czasu+wyswietlanie.
    while (aktual2!=NULL) {
        if(aktual2->rozp_L>=r && aktual2->rozp_L<=z && aktual2->typ_L==x){
            setlocale( LC_ALL, "Polish" );
            ++licznikD;
            dlugosc=dlugosc+difftime(aktual2->zakon_L, aktual2->rozp_L);

        }
        aktual2=aktual2->nast;
    }
    aktual2=glowa2;
    cout<<"Laczna ilosc zlotych godzin w tym semestrze typu "<<x<<": "<< licznikD<<endl;
    cout<<"Laczny czas zlotych godzin w tym semestrze typu "<<x<<": ";
    int hour, min, sek;
    hour=dlugosc/3600;
    min=(dlugosc-3600*hour)/60;
    sek=dlugosc-60*min-3600*hour;
    cout<< hour<<":"<<min<<":"<<sek<<endl;





    delete aktual3;
    delete glowa3;
    delete aktual2;
    delete glowa2;
    delete aktual;
    delete glowa;
}
void WgIlosci(string baza_danych, string liczba_godzin, string semestr){
    int wybor1;
    do{
        cout << "Menu:"<< endl
            << "1.Sprawdz ile zrobiles zlotych godzin w danym DNIU."<< endl
            << "2.Sprawdz ile zrobiles zlotych godzin przez ostatni TYDZIEN."<< endl
            << "3.Sprawdz ile zrobiles zlotych godzin w danym MIESIACU." << endl
            << "4.Sprawdz ile zrobiles zlotych godzin w danym ROKU."<< endl
            << "5.Sprawdz ile zrobiles zlotych godzin w danym SEMESTRZE."<<endl
            << "6.Wyjscie."<< endl<<endl;

        while(!(cin>>wybor1))
        {
          cout<<endl<<"Niepoprawne uzycie menu, wybierz ponownie: ";
          cin.clear();
          cin.sync();
        }
        switch(wybor1){
        case 1:
            StatDzien(baza_danych, liczba_godzin);
            break;
        case 2:
            StatTydzien(baza_danych, liczba_godzin);
            break;

        case 3:
            StatMiesiac(baza_danych, liczba_godzin);
            break;
        case 4:
            StatRok(baza_danych, liczba_godzin);
            break;
        case 5:
            StatSemestr(baza_danych, liczba_godzin, semestr);
            break;
        case 6:
            cout<<endl;
            break;
        default:
            cout<<"Niepoprawne uzycie menu, wybierz ponownie"<<endl;
            break;
        }
    }
    while(wybor1!=6);
}

void WgTypu(string baza_danych, string typy, string semestr){
    int wybor1;
    do{
        cout << "Menu:"<< endl
            << "1.Sprawdz ile zrobiles zlotych godzin w danym DNIU danego TYPU."<< endl
            << "2.Sprawdz ile zrobiles zlotych godzin w tym TYGODNIU danego TYPU."<< endl
            << "3.Sprawdz ile zrobiles zlotych godzin w danym MIESIACU danego TYPU." << endl
            << "4.Sprawdz ile zrobiles zlotych godzin w danym ROKU danego TYPU."<< endl
            << "5.Sprawdz ile zrobiles zlotych godzin w danym SEMESTRZE danego TYPU."<<endl
            << "6.Wyjscie."<< endl<<endl;

        while(!(cin>>wybor1))
        {
          cout<<endl<<"Niepoprawne uzycie menu, wybierz ponownie: ";
          cin.clear();
          cin.sync();
        }
        switch(wybor1){
        case 1:
            TypStatDzien(baza_danych, typy);
            break;
        case 2:
            TypStatTydzien(baza_danych, typy);
            break;

        case 3:
            TypStatMiesiac(baza_danych, typy);
            break;
        case 4:
            TypStatRok(baza_danych, typy);
            break;
        case 5:
            TypStatSemestr(baza_danych, typy, semestr);
            break;
        case 6:
            cout<<endl;
            break;
        default:
            cout<<"Niepoprawne uzycie menu, wybierz ponownie"<<endl;
            break;
        }
    }
    while(wybor1!=6);
}
void PokazStatystyki(string baza_danych, string liczba_godzin, string typy, string semestr){
    int wybor2;
    do{
            cout << "Menu:"<< endl
            << "1.Przegladaj wedlug ilosci"<< endl
            << "2.Przegladaj wg ilosci i typu."<< endl
            << "3.Wyjscie."<< endl<<endl;


            while(!(cin>>wybor2))
            {
             cout<<endl<<"Niepoprawne uzycie menu, wybierz ponownie: ";
             cin.clear();
             cin.sync();
            }

            switch(wybor2){
            case 1:
                WgIlosci(baza_danych, liczba_godzin, semestr);
                break;
            case 2:
                WgTypu(baza_danych, typy, semestr);
                break;
            case 3:
                cout<<endl;
                break;
            default:
                cout<<"Niepoprawne uzycie menu, wybierz ponownie"<<endl;
                break;
            }
    }
    while(wybor2!=3);

}
