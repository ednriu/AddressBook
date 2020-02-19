#include <iostream>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <algorithm>

using namespace std;

struct Osoba
{
    int id;
    string imie;
    string nazwisko;
    string telefon;
    string email;
    string adres;
};
//funkcja dodaje dane, ale nie zawiera interfejsu
bool dodajDane(string imie, string nazwisko, string telefon, string email, string adres, vector<Osoba> &kontener);
void edytujDane(vector<Osoba> &kontener);
void edytujRekord(vector<Osoba> &kontener, int id, char opcja);
void usunDane(vector<Osoba> &kontener);
bool zapiszDoPliku(vector<Osoba> kontener);
void wypiszRekord(std::vector<Osoba>::const_iterator i);
void wyszukajImie(vector <Osoba> kontener);
void wyszukajNazwisko(vector <Osoba> kontener);
void wypiszWszystkieDane(vector<Osoba> kontener);
//funkcja z interfejsem do dodawania danych. Wykorzystuje funkcje dodajDane
void wpiszNowyRekord(vector<Osoba> &kontener);
bool wczytajPlik(vector<Osoba> &kontener);
bool menu(vector<Osoba> &kontener)
{
    char c;
    system("cls");
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
        wpiszNowyRekord(kontener);
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
        usunDane(kontener);
        return true;
        break;
    case 'e':
        edytujDane(kontener);
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
    wczytajPlik(kontenerGlowna);
    setlocale(LC_ALL, "");
    //petla glowna programu
    while(menu(kontenerGlowna));
    system("cls");
    cout <<"Dziekuje za skorzystanie z programu."<<endl;
    return 0;
}
bool dodajDane(string imie, string nazwisko, string telefon, string email, string adres, vector<Osoba> &kontener)
{
    Osoba zmiennaOsoby;
    if (kontener.size()!=0)
        zmiennaOsoby.id = kontener[kontener.size()-1].id+1; //numerujemy od 0 a nie od 1; numer jest ostatnim id powiekszonym o 1.
    if (kontener.size()==0)
        zmiennaOsoby.id = 1;  //jeśli kontener jest punty to pierwsze ID jest rowne 0
    zmiennaOsoby.imie = imie;
    zmiennaOsoby.nazwisko = nazwisko;
    zmiennaOsoby.telefon = telefon;
    zmiennaOsoby.email = email;
    zmiennaOsoby.adres = adres;
    kontener.push_back(zmiennaOsoby);
    zapiszDoPliku(kontener); //Zapisanie danych do pliku
    return true;
}
void edytujDane(vector<Osoba> &kontener)
{
    int id;
    char c;
    system("cls");
    cout << "ID Rekordu: ";
    cin >> id;
    cout << "Edytuj Imie (i), Nazwisko (n), telefon (t), mail (m), adres (a), powrot (p)"<<endl;
    c = _getch();
    edytujRekord(kontener,id,c);
    zapiszDoPliku(kontener);
}
void edytujRekord(vector<Osoba> &kontener, int id, char opcja)
{
    string noweDane;
    if (!kontener.empty())
    {
        for (vector<Osoba>::iterator i = kontener.begin(); i != kontener.end(); ++i)
        {
            if((*i).id==id)
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
void usunDane(vector<Osoba> &kontener)
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
                    zapiszDoPliku(kontener);
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
bool wczytajPlik(vector<Osoba> &kontener)
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
                //rekord.id = i;
                i++;
                //cout<<fragmentTekstu<<endl;
                break;
            case 1:
                rekord.imie = fragmentTekstu;
                i++;
                //cout<<fragmentTekstu<<endl;
                break;

            case 2:
                rekord.nazwisko = fragmentTekstu;
                i++;
                //cout<<fragmentTekstu<<endl;
                break;

            case 3:
                rekord.telefon = fragmentTekstu;
                i++;
                //cout<<fragmentTekstu<<endl;
                break;

            case 4:
                rekord.email = fragmentTekstu;
                i++;
                //cout<<fragmentTekstu<<endl;
                break;

            case 5:
                rekord.adres = fragmentTekstu;
                i=0;;
                //cout<<fragmentTekstu<<"---"<<endl;
                kontener.push_back(rekord);
                break;
            }

        }

        newfile.close(); //close the file object.
        cout <<"Wczytano dane adresowe z pliku."<<endl;
        return true;
    }
    else
    {
        cout <<"Pierwsze Dzialanie Programu."<<endl;
        return false;
    }
}
void wpiszNowyRekord(vector<Osoba> &kontener)
{
    string imie, nazwisko, telefon, email, adres;
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
    dodajDane(imie, nazwisko, telefon, email, adres, kontener);
    cout <<"Dodano dane do bazy. Nacisnij dowolny klawisz by powrocic do Menu Glownego."<<endl;
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

bool zapiszDoPliku(vector<Osoba> kontener)
{
    fstream plik;
    plik.open("Adresy.txt", std::ofstream::out | std::ofstream::trunc);
    if (!kontener.empty())
    {
        for (vector<Osoba>::iterator i = kontener.begin(); i != kontener.end(); ++i)
        {
            plik << (*i).id << "|";
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
        menu(kontener);
    }
    return true;
}
