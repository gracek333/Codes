#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

struct Uzytkownik {
    int id;
    string nazwa, haslo;
};

struct Adresat {
    int id = 0, idUzytkownika = 0;
    string imie = "", nazwisko = "", nrTelefonu = "", email = "", adres = "";
};

void wyczyscStrumienWejscia() {
    cin.clear();
    cin.sync();
}

string wczytajLinie() {
    string wejscie = "";
    wyczyscStrumienWejscia();
    getline(cin, wejscie);
    return wejscie;
}

char wczytajZnak() {
    string wejscie = "";
    wyczyscStrumienWejscia();
    char znak = {0};
    int znacznikWykonaniaPetli = 0;

    while (znacznikWykonaniaPetli == 0) {
        getline(cin, wejscie);
        if (wejscie.length() == 1) {
            znak = wejscie[0];
            znacznikWykonaniaPetli = 1;
        } else cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl << endl;
    }
    return znak;
}

int dodajAdresata(vector <Adresat> &adresaci, int idOstatniegoAdresata, int idZalogowanegoUzytkownika) {
    string imie, nazwisko, nrTelefonu, email, adres;
    cout << "Podaj imie: " << endl;
    imie = wczytajLinie();
    cout << "Podaj nazwisko: " << endl;
    nazwisko = wczytajLinie();
    cout << "Podaj numer telefonu: " << endl;
    nrTelefonu = wczytajLinie();
    cout << "Podaj adres mailowy: " << endl;
    email = wczytajLinie();
    cout << "Podaj adres: " << endl;
    adres = wczytajLinie();

    Adresat adresat;
    adresat.id = idOstatniegoAdresata + 1;
    adresat.idUzytkownika = idZalogowanegoUzytkownika;
    adresat.imie = imie;
    adresat.nazwisko = nazwisko;
    adresat.nrTelefonu = nrTelefonu;
    adresat.email = email;
    adresat.adres = adres;

    adresaci.push_back(adresat);

    int indeksDodawanegoAdresata = 0;
    if (adresaci.size() != 0) {
        indeksDodawanegoAdresata = adresaci.size() - 1;
    }
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out|ios::app);
    if (plik.good()) {
        plik << adresaci[indeksDodawanegoAdresata].id << "|" << adresaci[indeksDodawanegoAdresata].idUzytkownika << "|" << adresaci[indeksDodawanegoAdresata].imie << "|" << adresaci[indeksDodawanegoAdresata].nazwisko << "|";
        plik << adresaci[indeksDodawanegoAdresata].nrTelefonu << "|" << adresaci[indeksDodawanegoAdresata].email << "|" << adresaci[indeksDodawanegoAdresata].adres << "|" << endl;
        plik.close();
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych" << endl;
        system("pause");
    }
    cout << endl << "Adresat zostal dodany!" << endl << endl;
    system("pause");
    return idOstatniegoAdresata + 1;
}

void pokazDanePojedynczegoAdresata(vector <Adresat>::iterator &itr) {
    cout << endl;
    cout << "ID: " << (*itr).id << endl;
    cout << (*itr).imie << " " << (*itr).nazwisko << endl;
    cout << "Telefon: " << (*itr).nrTelefonu << endl;
    cout << "Email: " << (*itr).email << endl;
    cout << "Adres: " << (*itr).adres << endl;
    cout << endl;
}

void wyswietlWszystkichAdresatow (vector <Adresat> &adresaci) {
    for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
        pokazDanePojedynczegoAdresata(itr);
    }
    system("pause");
}

void wyszukajPoImieniu(vector <Adresat> &adresaci) {
    string imie;
    cout << "Podaj imie: " << endl;
    imie = wczytajLinie();

    for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
        if ((*itr).imie == imie) {
            pokazDanePojedynczegoAdresata(itr);
        }
    }
    cout << endl;
    system("pause");
}

void wyszukajPoNazwisku(vector <Adresat> &adresaci) {
    string nazwisko;
    cout << "Podaj nazwisko: " << endl;
    nazwisko = wczytajLinie();

    for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
        if ((*itr).nazwisko == nazwisko) {
            pokazDanePojedynczegoAdresata(itr);
        }
    }
    cout << endl;
    system("pause");
}

string wczytajDanaZLinii (string linia, int &pozycjaZnakuWLinii) {
    string dana = "";

    while (linia[pozycjaZnakuWLinii] != '|') {
        dana += linia[pozycjaZnakuWLinii];
        pozycjaZnakuWLinii++;
    }
    pozycjaZnakuWLinii++;
    return dana;
}

int wczytajAdresatowZPliku (vector <Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    string linia;
    int idOstatniegoAdresata = 0;
    Adresat adresat;
    int pozycjaZnakuWLinii;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good()) {
        while (getline(plik, linia)) {
            pozycjaZnakuWLinii = 0;
            adresat.id = atoi((wczytajDanaZLinii(linia, pozycjaZnakuWLinii)).c_str());
            adresat.idUzytkownika = atoi((wczytajDanaZLinii(linia, pozycjaZnakuWLinii)).c_str());
            adresat.imie = wczytajDanaZLinii(linia, pozycjaZnakuWLinii);
            adresat.nazwisko = wczytajDanaZLinii(linia, pozycjaZnakuWLinii);
            adresat.nrTelefonu = wczytajDanaZLinii(linia, pozycjaZnakuWLinii);
            adresat.email = wczytajDanaZLinii(linia, pozycjaZnakuWLinii);
            adresat.adres = wczytajDanaZLinii(linia, pozycjaZnakuWLinii);

            if (adresat.idUzytkownika == idZalogowanegoUzytkownika) {
                adresaci.push_back(adresat);
            }

            idOstatniegoAdresata = adresat.id;
        }
        plik.close();
    }
    return idOstatniegoAdresata;
}

int wczytajIdAdresata() {
    int idAdresata = 0;

    while (idAdresata == 0) {
        cout << "Podaj id adresata: ";
        cin >> idAdresata;
    }
    return idAdresata;
}

string zmienDana (string nazwaDanej) {
    cout << "Wpisz nowa wartosc dla danej - " << nazwaDanej << ": ";
    string nowaDana = wczytajLinie();
    cout << "Zapisano!" << endl << endl;
    return nowaDana;
}

void zapiszZmianyDoPlikuUzytkownicy(vector <Uzytkownik> &uzytkownicy) {
    fstream plik;
    plik.open("UzytkownicyTymczasowo.txt", ios::out|ios::app);

    if (plik.good()) {
        for (int i = 0; i < uzytkownicy.size(); i++) {
            plik << uzytkownicy[i].id << "|" << uzytkownicy[i].nazwa << "|" << uzytkownicy[i].haslo << "|" << endl;
        }
        plik.close();
    }
    remove("Uzytkownicy.txt");
    rename("UzytkownicyTymczasowo.txt", "Uzytkownicy.txt");
}

void zmianaHasla(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika) {
    string haslo;
    cout << "Podaj nowe haslo: ";
    haslo = zmienDana("haslo");

    for (int i = 0; i < uzytkownicy.size(); i++) {
        if (uzytkownicy[i].id == idZalogowanegoUzytkownika) {
            uzytkownicy[i].haslo = haslo;
            zapiszZmianyDoPlikuUzytkownicy(uzytkownicy);
            system("pause");
        }
    }
}

void zapiszZmianyDoPlikuAdresaci(vector <Adresat> adresaci, int idZalogowanegoUzytkownika, int indeksEdytowanegoAdresata, int znacznikUsuwaniaAdresata) {
    fstream plikTymczasowy, plikGlowny;
    plikTymczasowy.open("KsiazkaAdresowaTymczasowa.txt", ios::out|ios::app);
    plikGlowny.open("KsiazkaAdresowa.txt", ios::in);

    string linia;
    Adresat adresat;
    int pozycjaZnakuWLinii;

    if ((plikGlowny.good()) && (plikTymczasowy.good())) {
        while (getline(plikGlowny, linia)) {
            pozycjaZnakuWLinii = 0;
            adresat.id = atoi((wczytajDanaZLinii(linia, pozycjaZnakuWLinii)).c_str());
            adresat.idUzytkownika = atoi((wczytajDanaZLinii(linia, pozycjaZnakuWLinii)).c_str());
            adresat.imie = wczytajDanaZLinii(linia, pozycjaZnakuWLinii);
            adresat.nazwisko = wczytajDanaZLinii(linia, pozycjaZnakuWLinii);
            adresat.nrTelefonu = wczytajDanaZLinii(linia, pozycjaZnakuWLinii);
            adresat.email = wczytajDanaZLinii(linia, pozycjaZnakuWLinii);
            adresat.adres = wczytajDanaZLinii(linia, pozycjaZnakuWLinii);

            if (adresat.id != adresaci[indeksEdytowanegoAdresata].id) {
                plikTymczasowy << adresat.id << "|" << adresat.idUzytkownika << "|" << adresat.imie << "|" << adresat.nazwisko << "|";
                plikTymczasowy << adresat.nrTelefonu << "|" << adresat.email << "|" << adresat.adres << "|" << endl;
            } else if ((adresat.id == adresaci[indeksEdytowanegoAdresata].id) && (!znacznikUsuwaniaAdresata)) {
                plikTymczasowy << adresaci[indeksEdytowanegoAdresata].id << "|" << adresaci[indeksEdytowanegoAdresata].idUzytkownika << "|" << adresaci[indeksEdytowanegoAdresata].imie << "|" << adresaci[indeksEdytowanegoAdresata].nazwisko << "|";
                plikTymczasowy << adresaci[indeksEdytowanegoAdresata].nrTelefonu << "|" << adresaci[indeksEdytowanegoAdresata].email << "|" << adresaci[indeksEdytowanegoAdresata].adres << "|" << endl;
            } else if ((adresat.id == adresaci[indeksEdytowanegoAdresata].id) && (znacznikUsuwaniaAdresata)) {
            }
        }

        plikGlowny.close();
        plikTymczasowy.close();
    }
    remove("KsiazkaAdresowa.txt");
    rename("KsiazkaAdresowaTymczasowa.txt", "KsiazkaAdresowa.txt");
}

void edytujDaneAdresata(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    const bool znacznikUsuwaniaAdresata = false;
    int id = wczytajIdAdresata();
    bool adresatIstnieje = false;
    int indeksAdresata;

    for (int i = 0; i < adresaci.size(); i++) {
        if (adresaci[i].id == id) {
            adresatIstnieje = true;
            indeksAdresata = i;
            break;
        }
    }

    if (adresatIstnieje) {
        char wybor;
        system("cls");
        cout << "Wybierz dana do edycji:" << endl;
        cout << "1 - imie" << endl;
        cout << "2 - nazwisko"  << endl;
        cout << "3 - numer telefonu"  << endl;
        cout << "4 - email" << endl;
        cout << "5 - adres" << endl;
        cout << "6 - powrot do menu" << endl;
        cout << "Twoj wybor: ";
        wybor = wczytajZnak();
        if (wybor == '1') {
            adresaci[indeksAdresata].imie = zmienDana("imie");
            zapiszZmianyDoPlikuAdresaci(adresaci, idZalogowanegoUzytkownika, indeksAdresata, znacznikUsuwaniaAdresata);
        } else if (wybor == '2') {
            adresaci[indeksAdresata].nazwisko = zmienDana("nazwisko");
            zapiszZmianyDoPlikuAdresaci(adresaci, idZalogowanegoUzytkownika, indeksAdresata, znacznikUsuwaniaAdresata);
        } else if (wybor == '3') {
            adresaci[indeksAdresata].nrTelefonu = zmienDana("nrTelefonu");
            zapiszZmianyDoPlikuAdresaci(adresaci, idZalogowanegoUzytkownika, indeksAdresata, znacznikUsuwaniaAdresata);
        } else if (wybor == '4') {
            adresaci[indeksAdresata].email = zmienDana("email");
            zapiszZmianyDoPlikuAdresaci(adresaci, idZalogowanegoUzytkownika, indeksAdresata, znacznikUsuwaniaAdresata);
        } else if (wybor == '5') {
            adresaci[indeksAdresata].adres = zmienDana("adres");
            zapiszZmianyDoPlikuAdresaci(adresaci, idZalogowanegoUzytkownika, indeksAdresata, znacznikUsuwaniaAdresata);
        } else if (wybor == '6') {}

    } else cout << "Brak adresata o tym id!" << endl << endl;

    system("pause");
}

int usunAdresata (vector <Adresat> &adresaci, int idOstatniegoAdresata, int idZalogowanegoUzytkownika) {
    const bool znacznikUsuwaniaAdresata = true;
    char wybor;
    int id = wczytajIdAdresata();
    bool adresatNieIstnieje = true;
    int indeksAdresata;

    for (int i = 0; i < adresaci.size(); i++) {
        if (adresaci[i].id == id) {
            adresatNieIstnieje = false;
            indeksAdresata = i;
            break;
        }
    }

    if (adresatNieIstnieje) {
        cout << "Brak adresata o tym id!" << endl << endl;
    } else {
        cout << "Czy na pewno usunac dane wybranego adresata? <t/n>" << endl;
        cout << "Twoj wybor: ";
        wybor = wczytajZnak();

        if (wybor == 't') {
            adresaci.erase(adresaci.begin() + indeksAdresata, adresaci.begin() + indeksAdresata + 1);
            cout << "Usunieto!" << endl << endl;
            idOstatniegoAdresata = adresaci[adresaci.size() - 1].id;
            zapiszZmianyDoPlikuAdresaci(adresaci, idZalogowanegoUzytkownika, indeksAdresata, znacznikUsuwaniaAdresata);
        }
    }
    system("pause");
    return idOstatniegoAdresata;
}

void wczytajUzytkownikowZPliku (vector <Uzytkownik> &uzytkownicy) {
    string linia;
    Uzytkownik uzytkownik;
    int pozycjaZnakuWLinii;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    if (plik.good()) {
        while (getline(plik, linia)) {
            pozycjaZnakuWLinii = 0;
            uzytkownik.id = atoi((wczytajDanaZLinii(linia, pozycjaZnakuWLinii)).c_str());;
            uzytkownik.nazwa = wczytajDanaZLinii(linia, pozycjaZnakuWLinii);
            uzytkownik.haslo = wczytajDanaZLinii(linia, pozycjaZnakuWLinii);

            uzytkownicy.push_back(uzytkownik);
        }
        plik.close();
    }
}

void rejestracja(vector <Uzytkownik> &uzytkownicy) {
    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    nazwa = wczytajLinie();
    int i = 0;
    while (i < uzytkownicy.size()) {
        if (uzytkownicy[i].nazwa == nazwa) {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            nazwa = wczytajLinie();
            i = 0;
        } else {
            i++;
        }
    }
    cout << "Podaj haslo: " ;
    haslo = wczytajLinie();

    Uzytkownik uzytkownik;
    uzytkownik.id = uzytkownicy.size() + 1;
    uzytkownik.nazwa = nazwa;
    uzytkownik.haslo = haslo;

    uzytkownicy.push_back(uzytkownik);

    int indeksDodawanegoUzytkownika = 0;
    if (uzytkownicy.size() != 0) {
        indeksDodawanegoUzytkownika = uzytkownicy.size() - 1;
    }
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out|ios::app);
    if (plik.good()) {
        plik << uzytkownicy[indeksDodawanegoUzytkownika].id << "|" << uzytkownicy[indeksDodawanegoUzytkownika].nazwa << "|" << uzytkownicy[indeksDodawanegoUzytkownika].haslo << "|"<< endl;
        plik.close();
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych" << endl;
        system("pause");
    }
    cout << endl << "Uzytkownik zostal dodany!" << endl << endl;
    system("pause");
}

int logowanie(vector <Uzytkownik> &uzytkownicy) {
    string nazwa, haslo;
    cout << "Podaj login: ";
    nazwa = wczytajLinie();
    int i = 0;
    while (i < uzytkownicy.size()) {
        if (uzytkownicy[i].nazwa == nazwa) {
            for (int proby = 0; proby < 3; proby++) {
                cout << "Podaj haslo. Pozostalo prob " << 3-proby << ": ";
                haslo = wczytajLinie();
                if (uzytkownicy[i].haslo == haslo) {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba." << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    system("pause");
    return 0;
}

int main() {
    vector <Uzytkownik> uzytkownicy;
    int idZalogowanegoUzytkownika = 0;
    wczytajUzytkownikowZPliku(uzytkownicy);

    char wybor;

    while(1) {
        if (idZalogowanegoUzytkownika == 0) {
            system("cls");
            cout << "1. Logowanie"  << endl;
            cout << "2. Rejestracja" << endl;
            cout << "9. Zamknij program" << endl;
            cout << "Twoj wybor: ";
            wybor = wczytajZnak();

            if (wybor == '1') {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
            } else if (wybor == '2') {
                rejestracja(uzytkownicy);
            } else if (wybor == '9') {
                exit(0);
            }
        } else {
            vector <Adresat> adresaci;
            int idOstatniegoAdresata = 0;
            idOstatniegoAdresata = wczytajAdresatowZPliku(adresaci, idZalogowanegoUzytkownika);

            system("cls");
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu"  << endl;
            cout << "3. Wyszukaj po nazwisku"  << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmiana hasla" << endl;
            cout << "8. Wylogowanie"  << endl;
            cout << "Twoj wybor: ";
            wybor = wczytajZnak();
            if (wybor == '1') {
                idOstatniegoAdresata = dodajAdresata(adresaci, idOstatniegoAdresata, idZalogowanegoUzytkownika);
            } else if (wybor == '2') {
                wyszukajPoImieniu(adresaci);
            } else if (wybor == '3') {
                wyszukajPoNazwisku(adresaci);
            } else if (wybor == '4') {
                wyswietlWszystkichAdresatow(adresaci);
            } else if (wybor == '5') {
                idOstatniegoAdresata = usunAdresata(adresaci, idOstatniegoAdresata, idZalogowanegoUzytkownika);
            } else if (wybor == '6') {
                edytujDaneAdresata(adresaci, idZalogowanegoUzytkownika);
            } else if (wybor == '7') {
                zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
            } else if (wybor == '8') {
                idZalogowanegoUzytkownika = 0;
            }
        }
    }
    return 0;
}
