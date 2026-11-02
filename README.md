# Wypożyczalnia Rowerów

## Opis projektu

Program konsolowy napisany w języku C++, służący do obsługi wypożyczalni rowerów.

## Funkcjonalności

- Dodawanie rowerów (ID, opis, rodzaj, cena za godzinę).
- Wypożyczanie rowerów na podstawie ID.
- Zwracanie rowerów i obliczanie kosztu wypożyczenia.
- Wyświetlanie wszystkich rowerów w formie tabeli.
- Wczytywanie rowerów z pliku tekstowego.
- Sprawdzanie dostępności rowerów.
- Obsługa błędów za pomocą try, throw i catch.

## Technologie

- C++
- vector
- string
- fstream
- try / throw / catch

## Struktura plików

Wypozyczalnia-Rowerow/
|
|-- main.cpp
|-- rowery.txt
|-- README.md

## Format pliku rowery.txt

Dane rowerów przechowywane są w pliku tekstowym.

Format:
ID;Opis;Rodzaj;Cena;

Przykład:
1;Rower gorski;Downhill;25.50;
2;Rower miejski;Miejski;15.00;
3;Rower BMX;Freestyle;18.00;

## Menu programu

1. Dodaj rower
2. Wypożycz rower
3. Zwróć rower
4. Wypisz rowery
5. Wyjście

## Obsługa błędów

Program sprawdza:
- Czy podane ID istnieje.
- Czy rower jest już wypożyczony.
- Czy rower można zwrócić.
- Czy liczba godzin jest większa od zera.
- Czy cena jest prawidłowa.
- Czy ID roweru się nie powtarza.

## Uruchomienie programu

1. Pobierz repozytorium.
2. Otwórz projekt w środowisku obsługującym C++.
3. Skompiluj plik main.cpp.
4. Umieść plik rowery.txt w katalogu roboczym.
5. Uruchom program.

## Autor

Projekt edukacyjny wykonany w języku C++.
