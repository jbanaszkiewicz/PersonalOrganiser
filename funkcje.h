#ifndef FUNKCJE_H
#define FUNKCJE_H
#include <iostream>
#include "glowny.h"
#include <time.h>
#include <fstream>

using namespace std;
/**
 * @brief The Lista struct
 *
 *struktura potrzebna przy działaniu na ZG
 */
struct Lista{
    string typ_L;
    time_t rozp_L;
    time_t zakon_L;
    Lista *nast;
};
/**
 * @brief The Semestry struct
 *
 *struktura potrzebna przy działaniu na semestrach
 */

struct Semestry{
    int nr_S;
    string n_S;
    time_t rozp_S;
    time_t zakon_S;
    Semestry *nast;
};

/**
 * @brief ZadajLiczbe
 *
 * @param liczba_g plik z liczbami godzin na konkretny dzien
 *
 *Funkcja pozwala dodać ilość zlotych godzin na konkretny dzień, i zapobiega temu, żeby zrobić to więcej niż raz
 */
void ZadajLiczbe(string liczba_g);
/**
 * @brief Zamien
 * @param czasUNIX pobieram czas w formacie time_t
 * @return funkcja zwraca czas w formie tm
 */
tm Zamien(time_t czasUNIX);

/**
 * @brief Edytuj
 *
 * @param baza_danych plik ze złotymi godzinami
 * @param typy  plik z typami złotych godzin
 *
 *Funkcja pozwala zmienić ostatnio dodaną złotą godzinę
 */
void Edytuj(string baza_danych, string typy);

/**
 * @brief Przegladaj
 * @param baza_danych
 *
 *funkcja pozwalająca przeglądać złote godziny z konkretnego dnia
 *funkcja wymaga od użytkownika wpisania roku, miesiąca i dnia(wszystko jako liczby)
 *funkcja wyświetla dzień tygodnia, godzinę rozpoczęcia, typ i czas trwania
 */
void Przegladaj(string baza_danych);

/**
 * @brief DodajLubUsunTyp
 * @param typy plik z typami
 *
 *funkcja pozawalająca dodać lub usunac typy
 */
void DodajLubUsunTyp(string typy);

/**
 * @brief DodajLubUsunSemestr
 * @param semestr plik zamierający zapisane semstry
 *
 *Funkcja pozawalająca dodać lub usunac semestry, ktore znajduja sie w pliku "semestr.txt".
 *Funkcja wyświetla datę rozpoczęcia, zakończenia i nazwę semestru, żeby wiedzieć co ew. usunąć lub dodać.
 */
void DodajLubUsunSemestr(string semestr);


#endif // FUNKCJE_H
