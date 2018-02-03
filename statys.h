#ifndef STATYS_H
#define STATYS_H

#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;
/**
 * @brief The ListaZad struct
 *
 *Struktura odpowiedzialna za załadowanie zadanych złotych godzin na listę
 */

struct ListaZad{
    time_t data_zad;
    int ilosc;
    ListaZad *nast;
};
/**
 * @brief PokazStatystyki
 * @param baza_danych nazwa pliku ze ZG
 * @param liczba_godzin nazwa pliku z zadanymi ZG
 * @param typy nazwa pliku z typami
 * @param semestr   nazwa pliku z semestrami
 *
 *funkcja pełniąca rolę lokalnego interfejsu
 */

void PokazStatystyki(string baza_danych, string liczba_godzin, string typy, string semestr);
/**
 * @brief WgIlosci
 * @param baza_danych nazwa pliku ze ZG
 * @param liczba_godzin nazwa pliku z zadanymi ZG
 * @param semestr nazwa pliku z semestrami
 *
 *Część interfejsu odpowiedzialna za przekierowanie użytkownika do funkcji związanych z ilością złotych godzin w danym czasie
 */
void WgIlosci(string baza_danych, string liczba_godzin, string semestr);

/**
 * @brief WgTypu
 * @param baza_danych nazwa pliku ze ZG
 * @param liczba_godzin nazwa pliku z zadanymi ZG
 * @param typy nazwa pliku z typami
 * @param semestr   nazwa pliku z semestrami
 *
 *Część interfejsu odpowiedzialna za przekierowanie użytkownika do funkcji związanych z ilością złotych godzin w danym czasie i danego typu
 */
void WgTypu(string baza_danych, string typy, string semestr);

/**
 * @brief StatDzien
 * @param baza_danych nazwa pliku ze ZG
 * @param liczba_godzin nazwa pliku z zadanymi ZG
 *
 *funkcja wyświetla ilość zlotych godzin danego dnia, ich łączną dlugość, a także, jezeli tego dnia zaplanowano złote godziny,
 *stosunek zrobiobych do zadanych(wydajnosc). Jeśli nie, ten punkt zostaje pominięty.
 */
void StatDzien(string baza_danych, string liczba_godzin);
/**
 * @brief StatTydzien
 * @param baza_danych nazwa pliku ze ZG
 * @param liczba_godzin nazwa pliku z zadanymi ZG
 *
 *Funkcja zliczająca złote godziny, ich dlugość i wydajność przez ostatni tydzień(rozumiem przez to czas od 7 dni temu do teraz).
 */
void StatTydzien(string baza_danych, string liczba_godzin);
/**
 * @brief StatMiesiac
 * @param baza_danych nazwa pliku ze ZG
 * @param liczba_godzin nazwa pliku z zadanymi ZG
 *
 *funkcja pozwala wyswietlac ilosc zlotych godzin zadanego miesiąca, ich łączną długość, a także wydajność w tym okresie.
 */
void StatMiesiac(string baza_danych, string liczba_godzin);
/**
 * @brief StatRok
 * @param baza_danych nazwa pliku ze ZG
 * @param liczba_godzin nazwa pliku z zadanymi ZG
 *
 *funkcja pozwala wyswietlac ilosc zlotych godzin zadanego roku, ich łączną długość, a także wydajność w tym okresie.
 */
void StatRok(string baza_danych, string liczba_godzin);

/**
 * @brief StatSemestr
 * @param baza_danych nazwa pliku ze ZG
 * @param liczba_godzin nazwa pliku z zadanymi ZG
 * @param semestr   nazwa pliku z semestrami
 *
 **funkcja pozwala wyswietlac ilosc zlotych godzin w danym semestrze, ich łączną długość, a także wydajność w tym okresie.
 */
void StatSemestr(string baza_danych, string liczba_godzin, string semestr);

/**
 * @brief TypStatDzien
 * @param baza_danych nazwa pliku ze ZG
 * @param typy  nazwa pliku z typami
 *
 *funkcja pozwala wyswietlac ilosc zlotych godzin w danego dnia, wybranego typu i ich łączną długość.
 */
void TypStatDzien(string baza_danych, string typy);

/**
 * @brief TypStatTydzien
 * @param baza_danych nazwa pliku ze ZG
 * @param typy nazwa pliku z typami
 *
 *funkcja pozwala wyswietlac ilosc zlotych godzin  wybranego typu przez ostatni tydzień i ich łączną długość.
 */
void TypStatTydzien(string baza_danych, string typy);

/**
 * @brief TypStatMiesiac
 * @param baza_danych nazwa pliku ze ZG
 * @param typy nazwa pliku z typami
 *
 *funkcja pozwala wyswietlac ilosc zlotych godzin wybranego typu, w danym  miesiącu,  i ich łączną długość.
 */

void TypStatMiesiac(string baza_danych, string typy);

/**
 * @brief TypStatRok
 * @param baza_danych nazwa pliku ze ZG
 * @param typy nazwa pliku z typami
 *
 *funkcja pozwala wyswietlac ilosc zlotych godzin wybranego typu, w danym roku,  i ich łączną długość.
 */
void TypStatRok(string baza_danych, string typy);

/**
 * @brief TypStatSemestr
 * @param baza_danych nazwa pliku ze ZG
 * @param typy nazwa pliku z typami
 * @param semestr nazwa pliku z semestrami
 *
 *funkcja pozwala wyswietlac ilosc zlotych godzin wybranego typu, w danym semestrze,  i ich łączną długość.
 */
void TypStatSemestr(string baza_danych, string typy, string semestr);



#endif // STATYS_H
