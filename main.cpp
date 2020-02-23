#include <iostream>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <algorithm>
#include <cstdio>


using namespace std;

struct Osoba
{
    int id;
    int id_Uzytkownika;
    string imie;
    string nazwisko;
    string telefon;
    string email;
    string adres;
};
struct Uzytkownik
{
    int id_Uzytkownika;
    string login;
    string haslo;
};
//funkcja dodaje dane, ale nie zawiera interfejsu
bool dodajDane(int id_Uzytkownika, string imie, string nazwisko, string telefon, string email, string adres, vector<Osoba> &kontener);
void edytujDane(vector<Osoba> &kontener, int nrZalogowanegoUzytkownika);
void edytujRekord(vector<Osoba> &kontener, int id, char opcja);
string getLastLine(std::ifstream& in);
int logowanieUzytkownika(vector<Uzytkownik> kontener);
bool rejestracjaUzytkownika(vector<Uzytkownik> &kontener);
void usunDane(vector<Osoba> &kontener, int nrZalogowanegoUzytkownika);
void wypiszRekord(std::vector<Osoba>::const_iterator i);
void wyszukajImie(vector <Osoba> kontener);
void wyszukajNazwisko(vector <Osoba> kontener);
void wypiszWszystkieDane(vector<Osoba> kontener);
//funkcja z interfejsem do dodawania danych. Wykorzystuje funkcje dodajDane
void wpiszNowyRekord(vector<Osoba> &kontener, int nrZalogowanegoUzytkownika);
int wczytajPlik(vector<Osoba> &kontener, int id_Uzytkownika);
int wczytajPlikUzytkownikow(vector<Uzytkownik> &kontener);
bool zapiszDoPliku(vector<Osoba> kontener, int nrZalogowanegoUzytkownika);
bool zapiszDoPliku_PodmianaPlikow(vector<Osoba> kontener, int id_Uzytkownika);
bool zapiszDoPlikuUzytkownikow(vector<Uzytkownik> kontener);
/*--------------------------------------------------------------------------------------*/
int menuLogowania()
{
    vector <Uzytkownik> daneUzytkownikow;
    int nrZalogowanegoUzytkownika;
    char c;
    system("cls");
    wczytajPlikUzytkownikow(daneUzytkownikow);
    cout << "--------------------------------------------------"<< endl;
    cout << "MENU:"<< endl;
    cout << "Logowanie (l)"<<endl;
    cout << "Rejestracja (r)"<<endl;
    cout << "Zakoncz (z)"<<endl;
    c = _getch();

    switch( c )
    {
    case 'l':
        nrZalogowanegoUzytkownika = logowanieUzytkownika(daneUzytkownikow);
        if (nrZalogowanegoUzytkownika == 0) return 0;
        if (nrZalogowanegoUzytkownika != 0) return nrZalogowanegoUzytkownika;
        break;
    case 'r':
        rejestracjaUzytkownika(daneUzytkownikow);
        zapiszDoPlikuUzytkownikow(daneUzytkownikow);
        return 0;
        break;
    case 'z':
        return -1;
        break;
    default:
        //jakio kod
        break;
    }
}
bool menuBazy(vector<Osoba> &kontener, int nrZalogowanegoUzytkownika)
{
    char c;
    system("cls");
    cout <<"Uzytkownik:" << nrZalogowanegoUzytkownika<<endl;
    cout << "--------------------------------------------------"<< endl;
    cout << "MENU:"<< endl;
    cout << "Dodaj Adresata (d)"<<endl;
    cout << "Wyszukaj Imie (i)"<<endl;
    cout << "Wyszukaj Nazwisko (n)"<<endl;
    cout << "Wypisz Wszystkie Dane (w)"<<endl;
    cout << "Usun Dane (u)"<<endl;
    cout << "Edytuj Dane (e)"<<endl;
    cout << "Zakoncz (z)"<<endl;
    c = _getch();

    switch( c )
    {
    case 'd':
        zapiszDoPliku_PodmianaPlikow(kontener, nrZalogowanegoUzytkownika);
        wpiszNowyRekord(kontener, nrZalogowanegoUzytkownika);
        wczytajPlik(kontener,nrZalogowanegoUzytkownika);
        return true;
        break;
    case 'w':
        wypiszWszystkieDane(kontener);
        return true;
        break;
    case 'i':
        wyszukajImie(kontener);
        return true;
        break;
    case 'n':
        wyszukajNazwisko(kontener);
        return true;
        break;
    case 'u':
        usunDane(kontener, nrZalogowanegoUzytkownika);
        return true;
        break;
    case 'e':
        edytujDane(kontener, nrZalogowanegoUzytkownika);
        return true;
        break;
    case 'z':
        return false;
        break;
    default:
        //jakio kod
        break;
    }
}
int main()
{
    Osoba zmiennaOsoby;
    vector <Osoba> kontenerGlowna;
    int nrZalogowanegoUzytkownika=0;
    setlocale(LC_ALL, "");
    while(nrZalogowanegoUzytkownika == 0)
    {
        nrZalogowanegoUzytkownika = menuLogowania();
    }
    cout << "ilosc rekordow: " <<  wczytajPlik(kontenerGlowna,nrZalogowanegoUzytkownika)<<endl;
    //petla glowna programu
    if (nrZalogowanegoUzytkownika!=-1) while(menuBazy(kontenerGlowna, nrZalogowanegoUzytkownika));
    system("cls");
    cout <<"Dziekuje za skorzystanie z programu."<<endl;
    return 0;
}
bool dodajDane(int id_Uzytkownika, string imie, string nazwisko, string telefon, string email, string adres, vector<Osoba> &kontener)
{
    Osoba zmiennaOsoby;
    if (kontener.size()!=0)
        zmiennaOsoby.id = kontener[kontener.size()-1].id+1; //numerujemy od 0 a nie od 1; numer jest ostatnim id powiekszonym o 1.
    if (kontener.size()==0)
        zmiennaOsoby.id = 1;  //jeśli kontener jest punty to pierwsze ID jest rowne 0
    zmiennaOsoby.id_Uzytkownika = id_Uzytkownika;
    zmiennaOsoby.imie = imie;
    zmiennaOsoby.nazwisko = nazwisko;
    zmiennaOsoby.telefon = telefon;
    zmiennaOsoby.email = email;
    zmiennaOsoby.adres = adres;
    kontener.push_back(zmiennaOsoby);
    zapiszDoPliku(kontener, id_Uzytkownika);
    return true;
}
void edytujDane(vector<Osoba> &kontener, int nrZalogowanegoUzytkownika)
{
    int id;
    char c;
    system("cls");
    cout << "ID Rekordu: ";
    cin >> id;
    cout << "Edytuj Imie (i), Nazwisko (n), telefon (t), mail (m), adres (a), powrot (p)"<<endl;
    c = _getch();
    edytujRekord(kontener,id,c);
    zapiszDoPliku_PodmianaPlikow(kontener, nrZalogowanegoUzytkownika);
}
void edytujRekord(vector<Osoba> &kontener, int id, char opcja)
{
    string noweDane;
    if (!kontener.empty())
    {
        for (vector<Osoba>::iterator i = kontener.begin(); i != kontener.end(); ++i)
        {
            if((*i).id==id) //nale¿y doda warunek w razie gdy nie ma takiego id rekordu dla wybranego u¿ytkownika
            {
                cout <<"Stara wartosc: ";
                switch (opcja)
                {
                case 'i':
                    cout << (*i).imie << endl;
                    break;
                case 'n':
                    cout << (*i).nazwisko << endl;
                    break;
                case 't':
                    cout << (*i).telefon << endl;
                    break;
                case 'm':
                    cout << (*i).email << endl;
                    break;
                case 'a':
                    cout << (*i).adres << endl;
                    break;
                }
                cout << "Nowa wartosc: ";
                cin >> noweDane;
                switch (opcja)
                {
                case 'i':
                    (*i).imie = noweDane;
                    break;
                case 'n':
                    (*i).nazwisko = noweDane;
                    break;
                case 't':
                    (*i).telefon = noweDane;
                    break;
                case 'm':
                    (*i).email = noweDane;
                    break;
                case 'a':
                    (*i).adres = noweDane;
                    break;
                }
            }
        }
        cout << endl;
    }
    else
    {
        cout<<"Ta opcja nie dziala poniewaz nie ma jeszcze wpisanych zadnych danych."<<endl;
    }
    cout <<"Nacisnij dowolny klawisz by powrocic do Menu Glownego."<<endl;
    char c = _getch();
}
int logowanieUzytkownika(vector<Uzytkownik> kontener)
{
        Uzytkownik rekord;
        bool zalogowano = false;
        system("cls");
        cout << "podaj login:";
        cin >> rekord.login;
        cout << "podaj haslo:";
        cin >> rekord.haslo;
        for (vector<Uzytkownik>::iterator i = kontener.begin(); i != kontener.end(); ++i)
        {
            if((*i).login==rekord.login)
            {

                if ((*i).haslo == rekord.haslo) zalogowano = true;
                rekord.id_Uzytkownika = (*i).id_Uzytkownika;
                break;
            }
        }
        if (zalogowano == true) cout << "Zalogowales sie. Nacisnij dowolny klawisz."<<endl;
        if (zalogowano == false)
        {
            cout << "Podano bledny login lub haslo. Nacisnij dowolny klawisz."<<endl;
            rekord.id_Uzytkownika = 0;
        }

        char c = _getch();
        return rekord.id_Uzytkownika;
}
bool rejestracjaUzytkownika(vector<Uzytkownik> &kontener)
{
    bool powtorzenieLoginu = true;
    bool idIstnieje = false;
    Uzytkownik daneLogowania;
    while (powtorzenieLoginu)
    {
        powtorzenieLoginu = false;
        idIstnieje = false;
        system("cls");
        cout << "Login: ";
        cin >> daneLogowania.login;
        for (vector<Uzytkownik>::iterator i = kontener.begin(); i != kontener.end(); ++i)
        {
            if((*i).login==daneLogowania.login)
            {
                idIstnieje = true;
                cout << "Podany login istnieje. Nacisnij dowolny klaiwsz i podaj inny login"<<endl;
                char c = _getch();
                break;
            }
        }
        if (idIstnieje==true) powtorzenieLoginu = true;
        if (idIstnieje==false) powtorzenieLoginu = false;
    }
    cout << "haslo: ";
    cin >> daneLogowania.haslo;
    cout << endl;
    if (kontener.size()!=0)
        daneLogowania.id_Uzytkownika = kontener[kontener.size()-1].id_Uzytkownika+1; //numerujemy od 0 a nie od 1; numer jest ostatnim id powiekszonym o 1.
    if (kontener.size()==0)
        daneLogowania.id_Uzytkownika = 1;
    kontener.push_back(daneLogowania);
    return true;
}
void usunDane(vector<Osoba> &kontener, int nrZalogowanegoUzytkownika)
{
    bool idIstnieje = false;
    char c;
    system("cls");
    if (!kontener.empty())
    {
        int id;
        cout<<"Podaj id:";
        cin>>id;

        for (vector<Osoba>::iterator i = kontener.begin(); i != kontener.end(); ++i)
        {
            if((*i).id==id)
            {
                idIstnieje = true;
                cout << (*i).id << " ";
                cout << (*i).imie << " ";
                cout << (*i).nazwisko << " ";
                cout << (*i).telefon << " ";
                cout << (*i).email << " ";
                cout << (*i).adres << " "<< endl;
                cout <<"Czy na pewno chcesz usunac powyzsze dane? (t/n) "<<endl;
                c = _getch();
                if (c =='t')
                {
                    kontener.erase(i);
                    cout <<"Usunieto rekord" <<endl;
                    zapiszDoPliku_PodmianaPlikow(kontener, nrZalogowanegoUzytkownika);
                }
                if (c =='n')
                    cout << "Zrezygnowales" << endl;
                break;
            }
        }
    }
    else
    {
        cout<<"Ta opcja nie dziala poniewaz nie ma jeszcze wpisanych zadnych danych."<<endl;
    }
    if (idIstnieje == false) cout << "Podane ID nie istnieje."<<endl;
    cout <<"Nacisnij dowolny klawisz by powrocic do Menu Glownego."<<endl;
    c = _getch();
}
//Funkcja wczytuje do kontenera dane ksiazki wedlug wskazanego id_Uzytkownika. Jesli id_Uzytkownika jest rowne 0 to wczytywani sa wszyscy.
int wczytajPlik(vector<Osoba> &kontener, int id_Uzytkownika)
{
    Osoba rekord;
    fstream newfile;
    kontener.clear();
    newfile.open("Adresy.txt",ios::in); //open a file to perform read operation using file object
    if (newfile.is_open())    //checking whether the file is open
    {
        string fragmentTekstu;
        int i = 0;
        while(getline(newfile, fragmentTekstu,'|'))  //read data from file object and put it into string.
        {
            switch (i)
            {
            case 0:
                istringstream(fragmentTekstu) >> rekord.id;
                i++;
                break;
            case 1:
                istringstream(fragmentTekstu) >> rekord.id_Uzytkownika;
                i++;
                break;
            case 2:
                rekord.imie = fragmentTekstu;
                i++;
                break;
            case 3:
                rekord.nazwisko = fragmentTekstu;
                i++;
                break;
            case 4:
                rekord.telefon = fragmentTekstu;
                i++;
                break;
            case 5:
                rekord.email = fragmentTekstu;
                i++;
                break;
            case 6:
                rekord.adres = fragmentTekstu;
                i=0;
                if (rekord.id_Uzytkownika == id_Uzytkownika) kontener.push_back(rekord);
                if (id_Uzytkownika==0) kontener.push_back(rekord); //jesli id_Uzytkownika=0 wtedy wczytywani sa wszyscy
                break;
            }

        }

        newfile.close(); //close the file object.
        cout <<"Wczytano dane adresowe z pliku."<<endl;
        return rekord.id; //funkcja zwraca liczbe id ostatniego rekordu
    }
    else
    {
        cout <<"Pierwsze Dzialanie Programu."<<endl;
        return 0;
    }
}
int wczytajPlikUzytkownikow(vector<Uzytkownik> &kontener)
{
    Uzytkownik rekord;
    fstream newfile;
    kontener.clear();
    newfile.open("Uzytkownicy.txt",ios::in); //open a file to perform read operation using file object
    if (newfile.is_open())    //checking whether the file is open
    {
        string fragmentTekstu;
        int i = 0;
        while(getline(newfile, fragmentTekstu,'|'))  //read data from file object and put it into string.
        {
            switch (i)
            {
            case 0:
                istringstream(fragmentTekstu) >> rekord.id_Uzytkownika;
                i++;
                break;
            case 1:
                rekord.login = fragmentTekstu;
                i++;
                break;
            case 2:
                rekord.haslo = fragmentTekstu;
                i=0;
                kontener.push_back(rekord);
                break;
            }

        }

        newfile.close(); //close the file object.
        cout <<"Wczytano dane adresowe z pliku Uzytkownicy."<<endl;
        return rekord.id_Uzytkownika; //funkcja zwraca liczbe id ostatniego rekordu
    }
    else
    {
        cout <<"Brak Uzytkownikow w bazie."<<endl;
        return 0;
    }
}
void wpiszNowyRekord(vector<Osoba> &kontener, int nrZalogowanegoUzytkownika)
{
    string imie, nazwisko, telefon, email, adres;
    wczytajPlik(kontener, 0);//wczytanie wszystkich danyc bez wzgledu na numer zalogowanego
    system("cls");
    cout << "Imie:";
    cin >> imie;
    cout << "Nazwisko:";
    cin >> nazwisko;
    cout << "telefon:";
    cin >> telefon;
    cout << "email:";
    cin >> email;
    cout << "Adres:";
    cin.sync();
    getline(cin,adres);
    cout << endl;
    dodajDane(nrZalogowanegoUzytkownika,imie, nazwisko, telefon, email, adres, kontener);
    //cout <<"Dodano dane do bazy. Nacisnij dowolny klawisz by powrocic do Menu Glownego."<<endl;
    char c = _getch();
}
void wypiszRekord(std::vector<Osoba>::const_iterator i)
{
            cout << (*i).id << endl;
            cout << (*i).imie << endl;
            cout << (*i).nazwisko << endl;
            cout << (*i).telefon << endl;
            cout << (*i).email << endl;
            cout << (*i).adres << endl;
}
void wypiszWszystkieDane(vector<Osoba> kontener)
{
    system("cls");
    if (!kontener.empty())
    {
        for (vector<Osoba>::iterator i = kontener.begin(); i != kontener.end(); ++i)
        {
            cout <<"nr"<< (*i).id << ": " << (*i).imie<<" "<<(*i).nazwisko<<";"<<endl;
            cout <<"tel: "<< (*i).telefon <<"; email: " <<(*i).email<<";"<<endl;
            cout <<"adres: "<< (*i).adres <<";"<<endl;
            cout <<endl;
        }
        cout <<endl;
    }
    else
    {
        cout <<"Brak danych zapisanych w pliku."<<endl;
    }
    cout <<"Nacisnij dowolny klawisz by powrocic do Menu Glownego."<<endl;
    char c = _getch();
}
void wyszukajImie(vector <Osoba> kontener)
{
    system("cls");
    if (!kontener.empty())
    {
        string imie = "";
        cout<<"Wyszukaj Imie:";
        cin>>imie;
        //transform(imie.begin(), imie.end(), imie.begin(), ::tolower); Zamiana na LowerCase
        for (vector<Osoba>::iterator i = kontener.begin(); i != kontener.end(); ++i)
        {
            if((*i).imie==imie)
            {
                wypiszRekord(i);
            }
            cout << endl;
        }
        cout << endl;
    }
    else
    {
        cout<<"Ta opcja nie dziala poniewaz nie ma jeszcze wpisanych zadnych danych."<<endl;
    }
    cout <<"Nacisnij dowolny klawisz by powrocic do Menu Glownego."<<endl;
    char c = _getch();
}
void wyszukajNazwisko(vector <Osoba> kontener)
{
    system("cls");
    if (!kontener.empty())
    {
        string nazwisko = "";
        cout<<"Wyszukaj Nazwisko:";
        cin>>nazwisko;
        for (vector<Osoba>::iterator i = kontener.begin(); i != kontener.end(); ++i)
        {
            if((*i).nazwisko==nazwisko)
            {
                wypiszRekord(i);
            }
            cout << endl;
        }
        cout << endl;
    }
    else
    {
        cout <<"Ta opcja nie dziala poniewaz nie ma wprowadzonych zadnych danych."<<endl;
    }
    cout <<"Nacisnij dowolny klawisz by powrocic do Menu Glownego."<<endl;
    char c = _getch();
}
bool zapiszDoPliku(vector<Osoba> kontener, int nrZalogowanegoUzytkownika)
{
    fstream plik;
    plik.open("Adresy.txt", std::ofstream::out | std::ofstream::trunc);
    if (!kontener.empty())
    {
        for (vector<Osoba>::iterator i = kontener.begin(); i != kontener.end(); ++i)
        {
            plik << (*i).id << "|";
            plik << (*i).id_Uzytkownika << "|";
            plik << (*i).imie << "|";
            plik << (*i).nazwisko << "|";
            plik << (*i).telefon << "|";
            plik << (*i).email << "|";
            plik << (*i).adres << "|";
            plik <<endl;
        }
        plik.close();
        cout <<"Dane zostaly zapisane do pliku Adresy.txt. Nacisnij dowolny klawisz."<<endl;
    }
    else if (kontener.empty())
    {
        plik <<"";
        plik.close();
        cout <<"Dane1 zostaly zapisane do pliku Adresy.txt. Nacisnij dowolny klawisz."<<endl;
        menuBazy(kontener, nrZalogowanegoUzytkownika);
    }
    return true;
}
bool zapiszDoPliku_PodmianaPlikow(vector<Osoba> kontener, int id_Uzytkownika)
{
    Osoba rekord;
    fstream plik; //oryginalny plik z danymi
    plik.open("Adresy.txt",ios::in);
    fstream plikTymczasowy; //plik do nadpisywania
    plikTymczasowy.open("Adresy_temp.txt", std::ofstream::out | std::ofstream::trunc);
    vector<Osoba>::iterator iteracja = kontener.begin();
    if (plik.is_open())
    {
        int i=0;
        string fragmentTekstu="";
        while(getline(plik, fragmentTekstu,'|'))
        {
            switch (i)
            {
            case 0:
                istringstream(fragmentTekstu) >> rekord.id;
                i++;
                break;
            case 1:
                istringstream(fragmentTekstu) >> rekord.id_Uzytkownika;
                i++;
                break;
            case 2:
                rekord.imie = fragmentTekstu;
                i++;
                break;
            case 3:
                rekord.nazwisko = fragmentTekstu;
                i++;
                break;
            case 4:
                rekord.telefon = fragmentTekstu;
                i++;
                break;
            case 5:
                rekord.email = fragmentTekstu;
                i++;
                break;
            case 6:
                rekord.adres = fragmentTekstu;
                i=0;
                if (rekord.id_Uzytkownika == id_Uzytkownika) // jesli rekord z pliku ma to samo id co id uzytkownika to sprawdza poprawnosc
                {
                    if ((*iteracja).id==rekord.id) //jesli dla rekordu z pliku nie istnieje takie samo id rekordu w kontenerze to nic nie jest przepisywane
                    {
                        plikTymczasowy << (*iteracja).id << "|";
                        plikTymczasowy << (*iteracja).id_Uzytkownika << "|";
                        plikTymczasowy << (*iteracja).imie << "|";
                        plikTymczasowy << (*iteracja).nazwisko << "|";
                        plikTymczasowy << (*iteracja).telefon << "|";
                        plikTymczasowy << (*iteracja).email << "|";
                        plikTymczasowy << (*iteracja).adres << "|";
                        plikTymczasowy << endl;
                        iteracja++;
                    }

                }
                else if (rekord.id_Uzytkownika != id_Uzytkownika) //jesli id_uzytkownika jest rozne od id_uzytkownika zalogowanego to przepisywana jest linijka
                {
                    plikTymczasowy << rekord.id << "|";
                    plikTymczasowy << rekord.id_Uzytkownika << "|";
                    plikTymczasowy << rekord.imie << "|";
                    plikTymczasowy << rekord.nazwisko << "|";
                    plikTymczasowy << rekord.telefon << "|";
                    plikTymczasowy << rekord.email << "|";
                    plikTymczasowy << rekord.adres << "|";
                    plikTymczasowy <<endl;
                }
                break;
            }
        }
        while (iteracja != kontener.end()) //przypadek jesli w kontenerze jest wiecej linijek niz w pliku oryginalnym
        {
            plikTymczasowy << (*iteracja).id << "|";
            plikTymczasowy << (*iteracja).id_Uzytkownika << "|";
            plikTymczasowy << (*iteracja).imie << "|";
            plikTymczasowy << (*iteracja).nazwisko << "|";
            plikTymczasowy << (*iteracja).telefon << "|";
            plikTymczasowy << (*iteracja).email << "|";
            plikTymczasowy << (*iteracja).adres << "|";
            plikTymczasowy << endl;
            iteracja++;
        }
    }

    //zapisanie danych do pliku "adresy_temp", usuniecie pliku "adresy", zamiana nazwy pliku "adresy_temp" na "adresy"
    plikTymczasowy.close();
    plik.close();
    remove("Adresy.txt");
    int result = rename("Adresy_temp.txt", "Adresy.txt");
    if( result != 0 )
        printf( "Problem z zapisem pliku.\n" );
    else
        printf( "Plik nadpisano. \n" );

    return true;
}
bool zapiszDoPlikuUzytkownikow(vector<Uzytkownik> kontener)
{
    fstream plik;
    plik.open("Uzytkownicy.txt", std::ofstream::out | std::ofstream::trunc);
    if (!kontener.empty())
    {
        for (vector<Uzytkownik>::iterator i = kontener.begin(); i != kontener.end(); ++i)
        {
            plik << (*i).id_Uzytkownika << "|";
            plik << (*i).login << "|";
            plik << (*i).haslo << "|";
            plik <<endl;
        }
        plik.close();
        cout <<"Dane zostaly zapisane do pliku Uzytkownicy.txt. Nacisnij dowolny klawisz."<<endl;
    }
    else if (kontener.empty())
    {
        plik <<"";
        plik.close();
        cout <<"Dane zostaly zapisane do pliku Uzytkownicy.txt. Nacisnij dowolny klawisz."<<endl;
    }
    return true;
}
