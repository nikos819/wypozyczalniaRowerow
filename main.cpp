#include <iostream>  // Biblioteka do wyswietlania i pobierania danych
#include <fstream>   // Biblioteka do obslugi plikow
#include <vector>    // Biblioteka pozwalajaca przechowywac wiele rowerow
#include <iomanip>   // Biblioteka do formatowania tabeli i liczb
#include <string>    // Biblioteka do obslugi tekstu

using namespace std;

// STRUKTURA ROWER
// Struktura przechowuje wszystkie informacje o jednym rowerze
struct Rower
{
    int id;             // Numer identyfikacyjny roweru
    string opis;        // Opis roweru
    string rodzaj;      // Rodzaj roweru, np. gorski, miejski
    double cena;        // Cena wypozyczenia za jedna godzine
    bool wypozyczony;   // Status roweru: true - wypozyczony, false - dostepny
};

// Wektor przechowuje wszystkie dodane rowery
// Mozemy dodawac do niego kolejne elementy bez ustalania limitu
vector<Rower> rowery;


// FUNKCJA MENU
// Wyswietla menu glowne programu
void menu()
{
    cout << "\n===== WYPOZYCZALNIA ROWEROW =====\n";

    cout << "1. Dodaj rower\n";
    cout << "2. Wypozycz rower\n";
    cout << "3. Zwroc rower\n";
    cout << "4. Wypisz rowery\n";
    cout << "5. Wyjscie\n";

    cout << "Wybierz opcje: ";
}


// FUNKCJA SZUKAJACA ROWERU
// Przyjmuje ID roweru i sprawdza, czy taki rower istnieje
int znajdzRower(int id)
{
    // Petla przechodzi przez wszystkie rowery zapisane w wektorze
    for (int i = 0; i < rowery.size(); i++)
    {
        // Sprawdzamy, czy ID aktualnego roweru jest takie samo jak podane
        if (rowery[i].id == id)
        {
            // Jesli znaleziono rower, zwracamy jego numer w wektorze
            return i;
        }
    }

    // Jesli nie znaleziono roweru, zwracamy -1
    return -1;
}


// FUNKCJA DODAJACA ROWER
void dodaj()
{
    // TRY - tutaj umieszczamy instrukcje, ktore moga spowodowac blad
    try
    {
        // Tworzymy nowy obiekt typu Rower
        Rower r;

        // Pobieramy ID nowego roweru
        cout << "Podaj ID: ";
        if (!(cin >> r.id))
            throw "Nieprawidlowe ID!";

        // Sprawdzamy, czy rower o takim ID juz istnieje
        if (znajdzRower(r.id) != -1)
            throw "Takie ID juz istnieje!";

        // Czyscimy znak nowej linii pozostawiony przez cin
        cin.ignore();

        // Pobieramy opis roweru
        cout << "Podaj opis: ";
        getline(cin, r.opis);

        // Pobieramy rodzaj roweru
        cout << "Podaj rodzaj: ";
        getline(cin, r.rodzaj);

        // Pobieramy cene wypozyczenia za jedna godzine
        cout << "Podaj cene za godzine: ";

        // Sprawdzamy, czy cena jest liczba i czy jest wieksza od zera
        if (!(cin >> r.cena) || r.cena <= 0)
            throw "Nieprawidlowa cena!";

        // Nowy rower na poczatku jest dostepny
        // false oznacza, ze rower nie jest wypozyczony
        r.wypozyczony = false;

        // Dodajemy nowy rower do wektora
        rowery.push_back(r);

        // Informujemy uzytkownika o powodzeniu operacji
        cout << "Dodano rower!\n";
    }

    // CATCH - przechwytuje bledy zgloszone przez throw
    catch (const char* e)
    {
        // Wyswietlamy komunikat bledu
        cout << "BLAD: " << e << endl;

        // Czyscimy stan bledu strumienia wejscia
        cin.clear();

        // Usuwamy pozostale znaki z bufora
        cin.ignore(10000, '\n');
    }
}


// FUNKCJA WYPOZYCZAJACA ROWER
void wypozycz()
{
    try
    {
        // Zmienna przechowujaca ID wybranego roweru
        int id;

        // Pobieramy ID roweru od uzytkownika
        cout << "Podaj ID roweru: ";

        if (!(cin >> id))
            throw "Nieprawidlowe ID!";

        // Szukamy roweru o podanym ID
        // Funkcja zwraca jego indeks w wektorze
        int indeks = znajdzRower(id);

        // Jesli indeks wynosi -1, rower nie istnieje
        if (indeks == -1)
            throw "Nie ma takiego roweru!";

        // Sprawdzamy, czy rower jest juz wypozyczony
        if (rowery[indeks].wypozyczony)
            throw "Rower jest juz wypozyczony!";

        // Zmieniamy status roweru na wypozyczony
        // true oznacza, ze rower jest zajety
        rowery[indeks].wypozyczony = true;

        // Informujemy o udanym wypozyczeniu
        cout << "Rower zostal wypozyczony!\n";
    }

    // Przechwytywanie bledow
    catch (const char* e)
    {
        cout << "BLAD: " << e << endl;

        // Czyszczenie blednego wejscia
        cin.clear();
        cin.ignore(10000, '\n');
    }
}


// FUNKCJA ZWRACAJACA ROWER
void zwroc()
{
    try
    {
        // Zmienna na ID roweru
        int id;

        // Zmienna na liczbe godzin wypozyczenia
        double godziny;

        // Pobieramy ID roweru
        cout << "Podaj ID roweru: ";

        if (!(cin >> id))
            throw "Nieprawidlowe ID!";

        // Szukamy roweru w wektorze
        int indeks = znajdzRower(id);

        // Sprawdzamy, czy rower istnieje
        if (indeks == -1)
            throw "Nie ma takiego roweru!";

        // Sprawdzamy, czy rower jest wypozyczony
        // Jesli nie jest, nie mozemy go zwrocic
        if (!rowery[indeks].wypozyczony)
            throw "Ten rower nie jest wypozyczony!";

        // Pobieramy liczbe godzin wypozyczenia
        cout << "Podaj liczbe godzin: ";

        // Sprawdzamy, czy podano prawidlowa liczbe godzin
        if (!(cin >> godziny) || godziny <= 0)
            throw "Liczba godzin musi byc wieksza od zera!";

        // Obliczamy koszt wypozyczenia
        // Liczba godzin razy cena za jedna godzine
        double koszt = godziny * rowery[indeks].cena;

        // Ustawiamy wyswietlanie dwoch miejsc po przecinku
        cout << fixed << setprecision(2);

        // Wyswietlamy rachunek
        cout << "\n======= RACHUNEK =======\n";

        cout << "Rower: " << rowery[indeks].opis << endl;
        cout << "Godziny: " << godziny << endl;
        cout << "Cena za godzine: " << rowery[indeks].cena << " zl\n";
        cout << "Do zaplaty: " << koszt << " zl\n";

        cout << "========================\n";

        // Zmieniamy status roweru na dostepny
        // false oznacza, ze rower zostal zwrocony
        rowery[indeks].wypozyczony = false;

        cout << "Rower zostal zwrocony!\n";
    }

    // Przechwytywanie bledow
    catch (const char* e)
    {
        cout << "BLAD: " << e << endl;

        cin.clear();
        cin.ignore(10000, '\n');
    }
}



// FUNKCJA WYPISUJACA WSZYSTKIE ROWERY
void wypisz()
{
    // Sprawdzamy, czy sa jakies rowery
    if (rowery.empty())
    {
        cout << "\nBrak rowerow!\n";
        return;
    }

    // Naglowek tabeli
    cout << "\n";
    cout << "+-------+---------------------+-------------------+-------------+----------------+\n";

    cout << "| " << left
         << setw(6) << "ID"
         << "| " << setw(20) << "OPIS"
         << "| " << setw(18) << "RODZAJ"
         << "| " << setw(12) << "CENA (zl)"
         << "| " << setw(15) << "STATUS"
         << "|\n";

    cout << "+-------+---------------------+-------------------+-------------+----------------+\n";

    // Wyswietlanie wszystkich rowerow
    for (int i = 0; i < rowery.size(); i++)
    {
        cout << "| " << left
             << setw(6) << rowery[i].id
             << "| " << setw(20) << rowery[i].opis
             << "| " << setw(18) << rowery[i].rodzaj
             << "| " << fixed << setprecision(2)
             << setw(12) << rowery[i].cena
             << "| " << setw(15)
             << (rowery[i].wypozyczony ? "Wypozyczony" : "Dostepny")
             << "|\n";
             if (i == rowery.size() - 1)
            {
                cout << "+-------+---------------------+-------------------+-------------+----------------+\n";
            }
            else
            {
                cout << "----------------------------------------------------------------------------------\n";
            }
    }
    cout << "\nLiczba wszystkich rowerow: " << rowery.size() << endl;
}
// FUNKCJA WCZYTUJACA ROWERY Z PLIKU
void wczytaj()
{
    ifstream plik("a.txt");

    if (!plik)
    {
        cout << "Nie mozna otworzyc pliku!\n";
        return;
    }

    Rower r;
    string cena;

    while (plik >> r.id)
    {
        // Pomijamy srednik po ID
        plik.ignore();

        // Wczytujemy opis
        getline(plik, r.opis, ';');

        // Wczytujemy rodzaj
        getline(plik, r.rodzaj, ';');

        // Wczytujemy cene
        getline(plik, cena, ';');

        // Zamieniamy tekst na liczbe
        r.cena = stod(cena);

        // Kazdy wczytany rower jest dostepny
        r.wypozyczony = false;

        // Dodajemy rower do wektora
        rowery.push_back(r);
    }

    plik.close();

    cout << "Wczytano rowery z pliku!\n";
}

// FUNKCJA GLOWNA PROGRAMU
int main()
{
    // Zmienna przechowujaca wybrana opcje menu
    int pMenu;

    // Petla wykonuje sie przynajmniej raz
    // Menu bedzie wyswietlane ponownie po kazdej operacji
    do
    {
        // Wyswietlamy menu
        menu();

        // Pobieramy wybor uzytkownika
        cin >> pMenu;

        // Jesli wybrano 1, dodajemy rower
        if (pMenu == 1)
            dodaj();

        // Jesli wybrano 2, wypozyczamy rower
        else if (pMenu == 2)
            wypozycz();

        // Jesli wybrano 3, zwracamy rower
        else if (pMenu == 3)
            zwroc();

        // Jesli wybrano 4, wyswietlamy wszystkie rowery
        else if (pMenu == 4)
            wypisz();
        // Jesli wybrano 5, wczytujemy z pliku
        else if (pMenu == 5)
            wczytaj();

        // Jesli wybrano 5, konczymy program
        else if (pMenu == 6)
            cout << "Koniec programu!\n";

        // Jesli wybrano inna liczbe, wyswietlamy blad
        else
            cout << "Nieprawidlowa opcja!\n";

    // Petla dziala tak dlugo, dopoki uzytkownik nie wybierze 5
    } while (pMenu != 6);

    // Zakonczenie programu
    return 0;
}
