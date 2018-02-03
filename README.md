# PersonalOrganiser
	Opis projektu
Projekt ma za zadania być narzędziem do organizacji czasu pracy, który jest podzielony na jednostki zwane złotymi godzinami(dalej ZG). Każda trwa około 50 min, posiada czas rozpoczęcia, zakończenia i typ. Po wykonaniu ZG program powiadomi użytkownika o tym, że powinien ją zakończyć, a następnie rozpocznie odliczanie przerwy  Program będzie zapisywał wykonane ZG do pliku. Dodatkowo będzie wyświetlał ilość zrobionych ZG dzisiaj lub danego dnia. Będzie możliwość dodawania i usuwania typów ZG, a także semestrów.
Użytkownik powinien każdego dnia pracy dodać ilość ZG, które zamierza zrobić. 
Program będzie miał za zadanie także umożliwić statystyczne śledzenie wykonanej pracy, tj. ilość i sumę długości złotych godzin danego dnia, w ostatnim tygodniu, konkretnego miesiąca, roku, semestru, również przy uwzględnieniu tylko danego typu. 



	Opis formatu danych wejściowych/wyjściowych
Pliki z danymi:
baza_danych.txt- plik zawierający wykonane złote godziny; każdy wers to kolejna złota godzina, a wersy będą zawierały: czas_rozpoczęcia czas_zakończenia typ
typy.txt- plik zawierający typy ZG, każda w osobnym wierszu
liczba_godzin.txt- plik zawierający liczbę złotych godzin danego dnia, każdy wers zawiera kolejny dzień pracy w formie: czas ilość
semestr.txt- plik zawierający semestry, każdy wers dotyczy innego semestru i ma formę: czas_rozpoczecia czas_zakonczenia nazwa
Dane wprowadzane przez użytkownika:
Użytkownik ma możliwość decydować o wartościach zmiennych w klasie Zlgodzina, jego czasie rozpoczęcia, zakończenia i typie. 
Użytkownik wprowadza ilość złotych godzin na dany dzień.
Użytkownik może dodawać i usuwać typy.
Użytkownik może dodawać i usuwać semestry.
	Opis testów
"Użytkownik wprowadza liczbę godzin na dziś:8, a także dodaje nowe typy: programowanie, fizyka(jeśli nie istnieją)".
"Użytkownik tworzy złotą godzinę, której nadaje typ ZAP. Po jej zakończeniu zostaje dopisana do pliku baza_danych.txt".
"Użytkownik zmienia typ ostatniej złotej godziny z ZAP na FIZ, co zostaje zmienione w pliku baza_danych.txt ".
"Użytkownik dodaje bieżący semestr do pliku semestr.txt(jeśli nie istnieje)."
"Użytkownik przegląda złote godziny tego dnia i wyświetla się: 
godzina rozpoczęcia: __________, godzina zakończenia:__________,  typ: fizyka, dlugosc: godzina zakończenia- godzina rozpoczęcia".
"Użytkownik w statystykach sprawdza, że w dniu w którym utworzył tą złotą godzinę, wyświetla się ilość=1, jej długość, wydajność równa 12%,
" Użytkownik dodatkowo sprawdza, że tego dnia ilość złotych godzin typu fizyka=1, natomiast ilość złotych godzin typu programowanie=0".
