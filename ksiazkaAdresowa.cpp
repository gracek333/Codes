#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

struct Adresat {
    int id = 0;
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

int dodajAdresata(vector <Adresat> &adresaci, int idOstatniegoAdresata) {
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
        plik << adresaci[indeksDodawanegoAdresata].id << "|" << adresaci[indeksDodawanegoAdresata].imie << "|" << adresaci[indeksDodawanegoAdresata].nazwisko << "|";
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

int wczytajAdresatowZPliku (vector <Adresat> &adresaci) {
    string linia;
    int nrLinii = 1;
    int idOstatniegoAdresata = 0;
    Adresat adresat;
    int pozycjaZnakuWLinii;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good()) {
        while (getline(plik, linia)) {
            pozycjaZnakuWLinii = 0;
            adresat.id = atoi((wczytajDanaZLinii(linia, pozycjaZnakuWLinii)).c_str());;
            adresat.imie = wczytajDanaZLinii(linia, pozycjaZnakuWLinii);
            adresat.nazwisko = wczytajDanaZLinii(linia, pozycjaZnakuWLinii);
            adresat.nrTelefonu = wczytajDanaZLinii(linia, pozycjaZnakuWLinii);
            adresat.email = wczytajDanaZLinii(linia, pozycjaZnakuWLinii);
            adresat.adres = wczytajDanaZLinii(linia, pozycjaZnakuWLinii);

            adresaci.push_back(adresat);

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

void zapiszZmianyDoPliku(vector <Adresat> adresaci) {
    fstream plik;
    plik.open("KsiazkaAdresowaTymczasowa.txt", ios::out|ios::app);

    if (plik.good()) {
        for (int i = 0; i < adresaci.size(); i++) {
            plik << adresaci[i].id << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|";
            plik << adresaci[i].nrTelefonu << "|" << adresaci[i].email << "|" << adresaci[i].adres << "|" << endl;
        }
        plik.close();
    }
    remove("KsiazkaAdresowa.txt");
    rename("KsiazkaAdresowaTymczasowa.txt", "KsiazkaAdresowa.txt");
}

void edytujDaneAdresata(vector <Adresat> &adresaci) {
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
            zapiszZmianyDoPliku(adresaci);
        } else if (wybor == '2') {
            adresaci[indeksAdresata].nazwisko = zmienDana("nazwisko");
            zapiszZmianyDoPliku(adresaci);
        } else if (wybor == '3') {
            adresaci[indeksAdresata].nrTelefonu = zmienDana("nrTelefonu");
            zapiszZmianyDoPliku(adresaci);
        } else if (wybor == '4') {
            adresaci[indeksAdresata].email = zmienDana("email");
            zapiszZmianyDoPliku(adresaci);
        } else if (wybor == '5') {
            adresaci[indeksAdresata].adres = zmienDana("adres");
            zapiszZmianyDoPliku(adresaci);
        } else if (wybor == '6') {}

    } else cout << "Brak adresata o tym id!" << endl << endl;

    system("pause");
}

int usunAdresata (vector <Adresat> &adresaci, int idOstatniegoAdresata) {
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
            zapiszZmianyDoPliku(adresaci);
        }
    }
    system("pause");
    return idOstatniegoAdresata;
}

int main() {
    vector <Adresat> adresaci;
    int idOstatniegoAdresata = 0;
    char wybor;

    idOstatniegoAdresata = wczytajAdresatowZPliku(adresaci);

    while(true) {
        system("cls");
        cout << "KSIAZKA ADRESOWA" << endl ;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu"  << endl;
        cout << "3. Wyszukaj po nazwisku"  << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor: ";

        wybor = wczytajZnak();

        if (wybor == '1') {
            idOstatniegoAdresata = dodajAdresata(adresaci, idOstatniegoAdresata);
        } else if (wybor == '2') {
            wyszukajPoImieniu(adresaci);
        } else if (wybor == '3') {
            wyszukajPoNazwisku(adresaci);
        } else if (wybor == '4') {
            wyswietlWszystkichAdresatow(adresaci);
        } else if (wybor == '5') {
            idOstatniegoAdresata = usunAdresata(adresaci, idOstatniegoAdresata);
        } else if (wybor == '6') {
            edytujDaneAdresata(adresaci);
        } else if (wybor == '9') {
            exit(0);
        }
    }
    return 0;
}
