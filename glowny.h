#ifndef GLOWNY_H
#define GLOWNY_H

#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;
/**
 * @brief The Zlgodzina class
 *
 *klasa, której typami są złote godziny
 */
class Zlgodzina{
    string typ;
    time_t rozp;
    time_t zakon;
public:
    Zlgodzina(string="brak", time_t=0, time_t=0);
    /**
     * @brief Stworz
     * @param g nowa ZG
     * @param baza_danych plik ze ZG
     * @param typy plik z typami
     *
     *Funkcja tworzy złotą godzinę, zawarte są w niej pozostałe funkcje
     */
    void Stworz(Zlgodzina &g, string baza_danych, string typy);
    /**
     * @brief CzasRozp
     * @param g nowa ZG
     *
     *nadaje zlotej godzine czas rozpoczęcia
     */
    void CzasRozp(Zlgodzina &g);
    /**
     * @brief CzasZakon
     * @param g nowa ZG
     * @param baza_danych plik ze ZG
     *
     *nadaje zlotej godzine czas zakonczenia, i dopisuje ją do pliku
     */
    void CzasZakon(Zlgodzina &g, string baza_danych);
    /**
     * @brief WTyp
     * @param g nowa ZG
     * @param typy plik z typami
     *
     *nadaje nowej ZG typ
     */
    void WTyp(Zlgodzina &g,string typy);    //wybiera typ


};
struct Type{
  string n;
  int nr;
  Type *nast;
};
/**
 * @brief Odliczaj
 * @param czas długość odliczanego czasu
 * @param nazwa słowo potrzebne do wyświetlania
 *
 *Funkcja odlicza zadany czas złotej godziny w opraciu o bieżący czas, i czas pobrany w memencie rozpoczęcia ZG.
 *Istnieje możliwość przerwania odliczania w trakcie.
 */
void Odliczaj(int czas, string nazwa); //odlicza 50 min i powiadamia dzwiękiem, uzyje funkcji difftime
#endif // GLOWNY_H
