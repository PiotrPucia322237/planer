#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <algorithm>

/*
inteligentne wskaźniki
stringi

magazyn
dyski procesory etc
karta graficzna w pliku?
monitor
obudowa

wprowadzanie danych w menu

pytanie o typ elementu

wprowadź nazwę i dane netto

wyświetlanie danych które są (wyświetl wybrany typ)

sortowanie
*/

struct elementListy{
    std::string nazwa;
    double cenaNetto;
    std::shared_ptr<elementListy> next;
    std::weak_ptr<elementListy> prev;

    // elementListy(std::string n, double c, std::shared_ptr<elementListy> p)
    //     : nazwa(n), cenaNetto(c), next(nullptr), prev(p) { }
};

int main(int argc, char * argv[]){
    if(argc == 1){
        std::cout << "Brak pliku z danymi!" << std::endl;
        return 0;
    }
    std::string nazwaPliku = argv[1];
    std::fstream plik(nazwaPliku, std::ios::in);
    std::string linia;
    std::shared_ptr<elementListy> head = nullptr;
    std::shared_ptr<elementListy> current;
    while(plik >> linia){
        std::string nazwa = linia;
        plik >> linia;
        double cenaNetto = std::stod(linia);
        if(head == nullptr){
            head = std::make_shared<elementListy>(elementListy{nazwa, cenaNetto, nullptr});
            current = head;
        } else {
            std::shared_ptr<elementListy> newElement = std::make_shared<elementListy>(elementListy{nazwa, cenaNetto, nullptr, current});
            current->next = newElement;
            current = newElement;
        }
    }
    plik.close();

    // Wyświetlanie listy
    std::cout << "Wyświetlanie od początku:" << std::endl;
    std::shared_ptr<elementListy> temp = head;
    while(temp != nullptr){
        std::cout << "Nazwa: " << temp->nazwa << ", Cena netto: " << temp->cenaNetto << std::endl;
        temp = temp->next;
    }
    // a teraz od końca
    std::cout << "Wyświetlanie od końca:" << std::endl;
    std::shared_ptr<elementListy> tempTail = current;
    while(tempTail != nullptr){
        std::cout << "Nazwa: " << tempTail->nazwa << ", Cena netto: " << tempTail->cenaNetto << std::endl;
        tempTail = tempTail->prev.lock();
    }
    
    // std::sort(head, current, [](const std::shared_ptr<elementListy>& a, const std::shared_ptr<elementListy>& b){
    //     return a->cenaNetto < b->cenaNetto;
    // });


    // zapis pliku
    std::fstream plikWyj(nazwaPliku, std::ios::out);
    temp = head;
    while(temp != nullptr){
        plikWyj << temp->nazwa << " " << temp->cenaNetto << std::endl;
        temp = temp->next;
    }
    plikWyj.close();
    return 0;
}