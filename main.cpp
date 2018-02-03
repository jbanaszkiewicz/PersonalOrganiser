#include <iostream>
#include "interfejs.h"

using namespace std;
/**
 * \mainpage
 *\par Temat
 *\b Organizer \b pracy \b systemem \b złotych \b godzin
 *Projekt ma za zadania być narzędziem do organizacji czasu pracy, który jest podzielony na jednostki zwane złotymi godzinami
 *(dalej ZG). Każda trwa około 50 min, posiada czas rozpoczęcia, zakończenia i typ.
 *Po wykonaniu ZG program powiadomi użytkownika o tym, że powinien ją zakończyć,
 * a następnie rozpocznie odliczanie przerwy  Program będzie zapisywał wykonane ZG do pliku.
 *Dodatkowo będzie wyświetlał ilość zrobionych ZG dzisiaj lub danego dnia. Będzie możliwość dodawania i usuwania typów ZG,
 *a także semestrów.Użytkownik powinien każdego dnia pracy dodać ilość ZG, które zamierza zrobić.
 *Program będzie miał za zadanie także umożliwić statystyczne śledzenie wykonanej pracy,
 *tj. ilość i sumę długości złotych godzin danego dnia, w ostatnim tygodniu, konkretnego miesiąca, roku, semestru,
 *również przy uwzględnieniu tylko danego typu.
 *\author Jakub Banaszkiewicz
 *\version 1.0
 *par Kontakt
 *e-mail jakub.banaszkiewicz@gmail.com
 * @return
 */
int main()
{
    cout<<"Bardzo mi mi milo, ze znowu tu jestes :). Mam nadzieje, ze bedziemy sie dzisiaj wysmienicie razem bawic :D."<<endl;

    Menu("baza_danych.txt", "liczba_godzin.txt", "typy.txt", "semestr.txt");
    return 0;
}

