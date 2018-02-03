#include <iostream>
#include "glowny.h"
#include <time.h>
#include <fstream>
#include "funkcje.h"
#include <iomanip>

using namespace std;

tm Zamien(time_t czasUNIX){

    tm * t;
    t=new tm;
    t=localtime( & czasUNIX );
    return *t;
}
void ZadajLiczbe(string liczba_g){
    time_t czas;
    time(&czas);
///Otwieram plik z zadaną liczną złotych godzin
    ifstream f;
    f.open(liczba_g.c_str());
    tm tb;
    tb=Zamien(czas);
    int x;
    int y;
    if(f.good()){
        while (!f.eof()) {
            f>>x>>y;
        }

    }
    tm t;
    t=Zamien(x);
///sprawdzenie, czy tego dnia już nie wczytywano zadanej liczby ZG.
    if(!(tb.tm_year==t.tm_year && tb.tm_mday==t.tm_mday && tb.tm_mon==t.tm_mon)){
        cout<<"zadaj liczbe godzin na dzis:";
        int liczba=0;
        while(!(cin>>liczba)) //dopóki strumień jest w stanie błędu -> dopóki podawane są błędne dane
        {
          cin.clear(); //kasowanie flagi błędu strumienia
          cin.sync(); //kasowanie zbędnych znaków z bufora
        }
///zapisanie zadanych ZG do pliku
        ofstream k;
        k.open(liczba_g.c_str(), ios::app);

        k<<endl<<czas<<" "<<liczba;
        k.close();

    }
    f.close();

}

void Edytuj(string baza_danych, string typy){
    int choice;
    do{
        cout << "Menu:"<< endl
            << "1.Edytuj."<< endl
            << "2.Koniec." << endl;

        while(!(cin>>choice)) //dopóki strumień jest w stanie błędu -> dopóki podawane są błędne dane
        {
          cin.clear(); //kasowanie flagi błędu strumienia
          cin.sync(); //kasowanie zbędnych znaków z bufora
        }

        switch(choice){
        case 1:
            {
///załadowanie ZG do listy.
                Lista *glowa=NULL;

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
                cout<<"aktualny typ: "<<aktual->typ_L<<endl;

                f.close();

///Załadowanie typów do listy.
                ifstream h;
                string x;
                int licznik=1;
                Type *glowa2=NULL;
                Type *tmp=NULL;
                h.open(typy.c_str());
                if(h.good()){
                    while (!h.eof()) {
                        getline(h, x);
                        if(x!=""){
                            if(glowa2==NULL){
                              glowa2=new Type;
                              tmp=glowa2;
                            }
                            else{
                                tmp->nast=new Type;
                                tmp=tmp->nast;
                            }
                            tmp->n=x;
                            tmp->nr=licznik;
                            tmp->nast=NULL;
                            cout<<tmp->nr<<". "<<tmp->n<<endl;
                            ++licznik;
                    }
                    }
                }
                else cout<<"cos nie dziala"<<endl;
///przy ostatnim obrocie licznik się niepotrzebnie zwiększył
                --licznik;
                h.close();
///wybranie typu, na który chce zamienić.
                int a;
                do{
                    cout<<"wybierz nowy typ";
                    while(!(cin>>a))
                    {
                      cout<<"wybierz nowy typ";
                      cin.clear();
                      cin.sync();
                    }
                }
                while(a<1 || a>licznik);
///wyświetlenie typów
                tmp=glowa2;
                while(tmp!=NULL){
                    if(tmp->nr==a)
                        aktual->typ_L=tmp->n;
                    tmp=tmp->nast;
                }
                ofstream g;
                g.open(baza_danych.c_str());
                while(glowa!=NULL){
                    g<<glowa->rozp_L<<" ";
                    g<<glowa->zakon_L<<" ";
                    g<<glowa->typ_L<<endl;
                    glowa=glowa->nast;
                }
                g.close();
                delete glowa;
                delete aktual;
                delete tmp;
                delete glowa2;
            }

            break;
        case 2:

            cout<<endl;
            break;


        default:
            cout<<"niepoprawne uzycie menu, wybierz ponownie"<<endl;
            break;

        }

    }
    while(choice!=2);

}

void Przegladaj(string baza_danych){
    int rok, miesiac, dzien;
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
    Lista *glowa=NULL;

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
    cout<<setw(28)<<left<<"DATA"<<setw(13)<<left<<"ROZPOCZECIE" <<setw(9)<<left<<"TYP"<< setw(10)<<left<<"DLUGOSC"<<endl;

    aktual=glowa;
    tm r, z;
    char bufor[ 64 ];
    while(aktual!=NULL){
        r=Zamien(aktual->rozp_L);
        z=Zamien(aktual->zakon_L);
        if(r.tm_year==rok-1900 && r.tm_mon==miesiac-1 && r.tm_mday==dzien){
            setlocale( LC_ALL, "Polish" );
            strftime( bufor, sizeof( bufor ), "%A %d %B %Y  %H:%M" , & r );
            cout<<setw(41)<<left<<bufor;
            cout<< setw(7)<<left<<aktual->typ_L<<"  ";
            int min, sek;
             min=difftime(aktual->zakon_L, aktual->rozp_L)/60;
            sek=difftime(aktual->zakon_L, aktual->rozp_L)-60*min;
            cout<<min<<":"<<sek<<endl;

        }
        aktual=aktual->nast;
    }
    cout<<endl<<"To wszystkie zlote godziny wykonane tego dnia"<<endl;


    delete glowa;
    delete aktual;
}

void DodajLubUsunTyp(string typy){
    ifstream f;
///zaladowanie typów do listy
    string x;
    int licznik=1;
    Type *glowa=NULL;
    Type *aktual=NULL;
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
    aktual=glowa;

    int wybor1;
    do{
        cout << "Menu:"<< endl
            << "1.Dodaj."<< endl
            << "2.Usun." << endl
            << "3. Koniec."<<endl<<endl;

        while(!(cin>>wybor1)) //dopóki strumień jest w stanie błędu -> dopóki podawane są błędne dane
        {
          cin.clear(); //kasowanie flagi błędu strumienia
          cin.sync(); //kasowanie zbędnych znaków z bufora
        }
        switch(wybor1){
        case 1:
        {
///dodawanie nowego typu
            string liczy;
            string nowe;
            bool sprawdz=0;
            cout<<"Wpisz nowy typ: ";
            cin>>nowe;
            while (aktual!=NULL) {
                if(aktual->n==nowe)
                    sprawdz=1;
                aktual=aktual->nast;

            }
            aktual=glowa;
            while (sprawdz==1) {
                sprawdz=0;
                while (aktual!=NULL) {

                        while (aktual->n==nowe) {
                            cout<<"Taki typ juz istnieje. Chcesz kontunowac dodawanie, czy wyjsc?";

                            cout<<endl<<"1.Kontynuuj."<<endl<<"2.Wyjdz."<<endl;
                            do{
                                cin>>liczy;
                            }
                            while(!(liczy=="1" || liczy=="2"));
                            if(liczy=="1"){
                                cout<<"Podaj nazwe nowego typu: ";
                                cin>>nowe;
                            }
                            else
                                break;


                            sprawdz=1;
                        }


                    aktual=aktual->nast;
                }
                aktual=glowa;
            }
            if(liczy!="2"){
            while(aktual->nast!=NULL)
                aktual=aktual->nast;
            aktual->nast=new Type;
            aktual=aktual->nast;
            aktual->nast=NULL;
            aktual->n=nowe;
            aktual->nr=licznik+1;
            ++licznik;
            cout<<"Typ pomyslnie dodano :)"<<endl;
            }
            aktual=glowa;

            while(aktual!=NULL) {
                cout<<aktual->nr<<". "<<aktual->n <<endl;
                aktual=aktual->nast;
            }

            aktual=glowa;
            cin.clear();
            cin.sync();


        }
            break;
        case 2:
        {
///usuwanie wybranego typu
            while (aktual!=NULL) {
                cout<<aktual->nr<<". "<<aktual->n<<endl;
                aktual=aktual->nast;
            }
            aktual=glowa;

            int n;
            cout<<"Podaj numer typu, ktory chcesz usunac: ";
            do{

                while(!(cin>>n)) //dopóki strumień jest w stanie błędu -> dopóki podawane są błędne dane
                {
                  cout<<"Podaj numer typu, ktory chcesz usunac: ";
                  cin.clear(); //kasowanie flagi błędu strumienia
                  cin.sync(); //kasowanie zbędnych znaków z bufora
                }
                if(!(n<=licznik && n>0))
                    cout<<"Podaj numer typu, ktory chcesz usunac: ";
            }
        ///w zmienną \b x podstawiam wybrany typ
            while(!(n<=licznik && n>0));
            if(n==1){
                Type *tmp=glowa;
                glowa=glowa->nast;
                delete tmp;
            }
            else{
                Type *tmp=NULL;
                int licz=0;
                while(licz!=n-2){
                    aktual=aktual->nast;
                    ++licz;
                }
                tmp=aktual->nast;
                aktual->nast=aktual->nast->nast;
                delete tmp;
                aktual=aktual->nast;
                while (aktual!=NULL) {
                    aktual->nr=aktual->nr-1;
                    aktual=aktual->nast;


                }
            }
            --licznik;
            aktual=glowa;
            cin.clear();
            cin.sync();

        }
            break;
        case 3:
            cout<<endl;
            break;
        default:
            cout<<"niepoprawne uzycie menu, wybierz ponownie"<<endl;
            break;
        }


    }
    while(wybor1!=3);



    ofstream g;
    g.open(typy.c_str());
    aktual=glowa;
    while (aktual!=NULL) {
        g<<aktual->n<<endl;
        aktual=aktual->nast;
    }
    g.close();
    delete aktual;
    delete glowa;
}

void DodajLubUsunSemestr(string semestr){
///ładuje semestry na listę i przy okazji wyświetlam
    string liczy;
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
                rozp=Zamien(r);
                zakon=Zamien(z);
                setlocale( LC_ALL, "Polish" );
                cout<<aktual->nr_S<<". ";
                strftime( bufor, sizeof( bufor ), "%x" , & rozp );
                cout<<"rozpoczecie: "<<bufor<<" ";
                strftime( bufor, sizeof( bufor ), "%x" , & zakon );
                cout<<"zakonczenie: "<<bufor<<" ";
                cout<<aktual->n_S<<endl;
                ++licznik;
                f>>r;
                f>>z;
                f>>x;



        }
    }

    else cout<<"cos nie dziala"<<endl;

    f.close();
    aktual=glowa;

    int wybor1;
    do{
        cout << "Menu:"<< endl
            << "1.Dodaj."<< endl
            << "2.Usun." << endl
            << "3. Koniec."<<endl<<endl;

        while(!(cin>>wybor1)) //dopóki strumień jest w stanie błędu -> dopóki podawane są błędne dane
        {
          cin.clear(); //kasowanie flagi błędu strumienia
          cin.sync(); //kasowanie zbędnych znaków z bufora
        }
        switch(wybor1){
        case 1:
        {
///wyswietlenie ponowne semestrow
            while (aktual!=NULL) {
                rozp=Zamien(aktual->rozp_S);
                zakon=Zamien(aktual->zakon_S);
                setlocale( LC_ALL, "Polish" );
                cout<<aktual->nr_S<<". ";
                strftime( bufor, sizeof( bufor ), "%x" , & rozp );
                cout<<"rozpoczecie: "<<bufor<<" ";
                strftime( bufor, sizeof( bufor ), "%x" , & zakon );
                cout<<"zakonczenie: "<<bufor<<" ";
                cout<<aktual->n_S<<endl;
                aktual=aktual->nast;
            }
            aktual=glowa;
            time_t czas;
            time(&czas);
///dodanie nowego semestru
            while(aktual->nast!=NULL && glowa!=NULL)
                aktual=aktual->nast;
            aktual->nast=new Semestry;
            aktual=aktual->nast;
            aktual->nast=NULL;
    aktual=glowa;
    string nowe;
    bool sprawdz=0;
    cout<<"Wpisz nowy semestr-nazwa: ";
    cin>>nowe;
    while (aktual!=NULL) {
        if(aktual->n_S==nowe)
            sprawdz=1;
        aktual=aktual->nast;

    }

    aktual=glowa;
    while (sprawdz==1) {
        sprawdz=0;
        while (aktual!=NULL) {

                while (aktual->n_S==nowe) {
                    cout<<"Taki semestr juz istnieje. Chcesz kontunowac dodawanie, czy wyjsc?";

                    cout<<endl<<"1.Kontynuuj."<<endl<<"2.Wyjdz."<<endl;
                    do{
                        cin>>liczy;
                    }
                    while(!(liczy=="1" || liczy=="2"));
                    if(liczy=="1"){
                        cout<<"Podaj nazwe nowego semestru: ";
                        cin>>nowe;
                    }
                    else
                        break;



                    sprawdz=1;
                }



            aktual=aktual->nast;
        }
        aktual=glowa;

    }
    if(liczy!="2"){
        while(aktual->nast!=NULL)
            aktual=aktual->nast;
        aktual->n_S=nowe;
///wczytuje bierzący czas i potem go przerabiam na taki jak chcę. Ta opcja chyba działa poprawnie. Nie znalazłem lepszego rozwiązania.
            tm czasTM=Zamien(czas);
            do{
            cout<<"Wpisz czas rozpoczecia[rok]: ";
            do{

                while(!(cin>>czasTM.tm_year))
                {
                  cout<<"Wpisz czas rozpoczecia[rok]: ";
                  cin.clear();
                  cin.sync();
                }
                if(czasTM.tm_year<1980)
                    cout<<"Wpisz czas rozpoczecia[rok]: ";
            }
            while(czasTM.tm_year<1980);

            cout<<"Wpisz czas rozpoczecia[miesiac-liczba]: ";
            do{

                while(!(cin>>czasTM.tm_mon))
                {
                  cout<<"Wpisz czas rozpoczecia[miesiac-liczba]: ";
                  cin.clear();
                  cin.sync();
                }
                if(czasTM.tm_mon<1 || czasTM.tm_mon>12)
                    cout<<"Wpisz czas rozpoczecia[miesiac-liczba]: ";
            }
            while(czasTM.tm_mon<1 || czasTM.tm_mon>12);
            --czasTM.tm_mon;
            cout<<"Wpisz czas rozpoczecia[dzien miesiaca]: ";
            do{

                while(!(cin>>czasTM.tm_mday))
                {
                  cout<<"Wpisz czas rozpoczecia[dzien miesiaca]: ";
                  cin.clear();
                  cin.sync();
                }
                if(czasTM.tm_mday<1 || czasTM.tm_mday>31)
                    cout<<"Wpisz czas rozpoczecia[dzien miesiaca]: ";
            }
            while(czasTM.tm_mday<1 || czasTM.tm_mday>31);


            czasTM.tm_year=czasTM.tm_year-1900;
            czasTM.tm_hour=1;
            czasTM.tm_min=1;
            czasTM.tm_sec=1;
            aktual->rozp_S=mktime(&czasTM);

            cout<<"Wpisz czas zakonczenia[rok]: ";
            do{

                while(!(cin>>czasTM.tm_year))
                {
                  cout<<"Wpisz czas zakonczenia[rok]: ";
                  cin.clear();
                  cin.sync();
                }
                if(czasTM.tm_year<1980)
                    cout<<"Wpisz czas zakonczenia[rok]: ";
            }
            while(czasTM.tm_year<1980);

            cout<<"Wpisz czas zakonczenia[miesiac-liczba]: ";
            do{

                while(!(cin>>czasTM.tm_mon))
                {
                  cout<<"Wpisz czas zakonczenia[miesiac-liczba]: ";
                  cin.clear();
                  cin.sync();
                }
                if(czasTM.tm_mon<1 || czasTM.tm_mon>12)
                    cout<<"Wpisz czas zakonczenia[miesiac-liczba]: ";
            }
            while(czasTM.tm_mon<1 || czasTM.tm_mon>12);
            --czasTM.tm_mon;
            cout<<"Wpisz czas zakonczenia[dzien miesiaca]: ";
            do{

                while(!(cin>>czasTM.tm_mday))
                {
                  cout<<"Wpisz czas zakonczenia[dzien miesiaca]: ";
                  cin.clear();
                  cin.sync();
                }
                if(czasTM.tm_mday<1 || czasTM.tm_mday>31)
                    cout<<"Wpisz czas zakonczenia[dzien miesiaca]: ";
            }
            while(czasTM.tm_mday<1 || czasTM.tm_mday>31);

            czasTM.tm_year=czasTM.tm_year-1900;
            czasTM.tm_hour=22;
            czasTM.tm_min=58;
            czasTM.tm_sec=58;
            aktual->zakon_S=mktime(&czasTM);
            aktual->nr_S=licznik;
            ++licznik;
            if(aktual->rozp_S>aktual->zakon_S)
                --licznik;
            }
            while (aktual->rozp_S>aktual->zakon_S);
            cout<<"Typ pomyslnie dodano :)"<<endl;
    }
    else{
        aktual=glowa;
        while (aktual->nast->nast!=NULL)
            aktual=aktual->nast;
            Semestry *tmp2=NULL;
            tmp2=aktual->nast;
            delete tmp2;
            aktual->nast=NULL;

    }
            aktual=glowa;

            while(aktual!=NULL) {
                rozp=Zamien(aktual->rozp_S);
                zakon=Zamien(aktual->zakon_S);
                setlocale( LC_ALL, "Polish" );
                cout<<aktual->nr_S<<". ";
                strftime( bufor, sizeof( bufor ), "%x" , & rozp );
                cout<<"rozpoczecie: "<<bufor<<" ";
                strftime( bufor, sizeof( bufor ), "%x" , & zakon );
                cout<<"zakonczenie: "<<bufor<<" ";
                cout<<aktual->n_S<<endl;
                aktual=aktual->nast;
            }

            aktual=glowa;
            cin.clear();
            cin.sync();



      }
            break;
        case 2:
        {
            while (aktual!=NULL) {
                rozp=Zamien(aktual->rozp_S);
                zakon=Zamien(aktual->zakon_S);
                setlocale( LC_ALL, "Polish" );
                cout<<aktual->nr_S<<". ";
                strftime( bufor, sizeof( bufor ), "%x" , & rozp );
                cout<<"rozpoczecie: "<<bufor<<" ";
                strftime( bufor, sizeof( bufor ), "%x" , & zakon );
                cout<<"zakonczenie: "<<bufor<<" ";
                cout<<aktual->n_S<<endl;
                aktual=aktual->nast;
            }
            aktual=glowa;
///usuwanie wybranego semestru
            int n;
            cout<<"Podaj numer semestru, ktory chcesz usunac: ";
            cout<<licznik<<endl;
            do{
            while(!(cin>>n)) //dopóki strumień jest w stanie błędu -> dopóki podawane są błędne dane
            {
              cout<<"Podano bledy numer: ";
              cin.clear(); //kasowanie flagi błędu strumienia
              cin.sync(); //kasowanie zbędnych znaków z bufora
            }
            if(n>licznik-1 || n<1)
                cout<<"Podano bledy numer: ";
            }
            while(n>licznik-1 || n<1);
            if(n==1){
                Semestry *tmp=glowa;
                glowa=glowa->nast;
                delete tmp;
                aktual=glowa;
                while (aktual!=NULL) {
                    --aktual->nr_S;
                    aktual=aktual->nast;
                }
            }
            else{
                Semestry *tmp=NULL;
                int licz=0;
                while(licz!=n-2){
                    aktual=aktual->nast;
                    ++licz;
                }
                tmp=aktual->nast;
                aktual->nast=aktual->nast->nast;
                delete tmp;
                aktual=aktual->nast;
                while (aktual!=NULL) {
                    aktual->nr_S=aktual->nr_S-1;
                    aktual=aktual->nast;


                }
            }
            --licznik;
            aktual=glowa;
            cin.clear();
            cin.sync();

        }
            break;
        case 3:
            cout<<endl;
            break;
        default:
            cout<<"niepoprawne uzycie menu, wybierz ponownie"<<endl;
            break;
        }


    }
    while(wybor1!=3);


///zaladowanie semestrów po usuwaniu i dodawaniu do pliku
    ofstream g;
    g.open(semestr.c_str());
    aktual=glowa;
    while (aktual!=NULL) {
        g<<aktual->rozp_S<<" "<<aktual->zakon_S<<" "<<aktual->n_S<<endl;
        aktual=aktual->nast;
    }
    g.close();

    delete aktual;
    delete glowa;

}



