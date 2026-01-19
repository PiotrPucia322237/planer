#include <iostream>
#include <vector>
#include <algorithm>

struct Osoba{
    std::string imie;
    std::string nazwisko;
    std::string miejscowosc;
    int wiek;
    Osoba(std::string imie_, std::string nazwisko_, std::string miejscowosc_, int wiek_) : imie(imie_), nazwisko(nazwisko_), miejscowosc(miejscowosc_), wiek(wiek_) {}
};
// filtruj, sortuj
std::vector<Osoba> filtrujWiekiem(std::vector<Osoba>& osoby, int minimalnyWiek){
    std::vector<Osoba> wynik;
    for(auto & it : osoby){
        if(it.wiek >= minimalnyWiek){
            wynik.push_back(it);
        }
    }
    return wynik;
}
std::vector<Osoba> filtrujMiastem(std::vector<Osoba> & osoby, std::string miasto){
    std::vector<Osoba> wynik;
    for(auto & it : osoby){
        if(it.miejscowosc == miasto){
            wynik.push_back(it);
        }
    }
    return wynik;
}
std::vector<Osoba> sortujPoWieku(std::vector<Osoba> & osoby){
    std::sort(osoby.begin(), osoby.end(), [](const Osoba& a, const Osoba& b){
        return a.wiek < b.wiek;
    });
    return osoby;
}
void wyswietlOsoby(std::vector<Osoba> & osoby){
    for(auto & it : osoby){
        std::cout << "- " << it.imie << " " << it.nazwisko << ", " << it.miejscowosc << ", " << it.wiek << " lat\n";
    }
}
int main(){
    std::vector<Osoba> ludzie = {
        Osoba("Jan", "Kowalski", "Warszawa", 25),
        Osoba("Anna", "Nowak", "Krakow", 30),
        Osoba("Piotr", "Zielinski", "Gliwice", 22),
        Osoba("Kasia", "Wozniak", "Wroclaw", 28),
        Osoba("Patryk", "Nieduszny", "Gliwice", 26),
    };

    std::cout << "Podaj minimalny wiek do filtrowania: ";
    int minimalnyWiek;
    std::cin >> minimalnyWiek;
    std::vector<Osoba> przefiltrowane = filtrujWiekiem(ludzie, minimalnyWiek);
    std::cout << "Osoby powyzej wieku " << minimalnyWiek << ":\n";
    wyswietlOsoby(przefiltrowane);

    std::cout << "Podaj miasto do filtrowania: ";
    std::string miasto;
    std::cin >> miasto;
    std::vector<Osoba> przefiltrowaneMiastem = filtrujMiastem(ludzie, miasto);
    std::cout << "Osoby z miasta " << miasto << ":\n";
    wyswietlOsoby(przefiltrowaneMiastem);

    std::vector<Osoba> posortowane = sortujPoWieku(ludzie);
    std::cout << "Osoby posortowane po wieku rosnąco:\n";
    wyswietlOsoby(posortowane);




    return 0;
}