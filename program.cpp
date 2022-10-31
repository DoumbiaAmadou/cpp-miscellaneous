#include <fstream>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

struct Person
{
    string nom{""};
    string prenom{""};
    string sexe{""};
    int age{0};
};

template <typename T>
void entree_securisee(T &variable)
{
    while (!(std::cin >> variable))
    {
        std::cout << "Entrée invalide. Recommence." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

template <typename T, typename Predicat>
void entree_securisee(T &variable, Predicat predicat)
{
    while (!(std::cin >> variable) || !predicat(variable))
    {
        std::cout << "Entrée invalide. Recommence." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void demander_infos(Person &p)
{
    std::cout << "Nom ? ";
    entree_securisee(p.nom);
    std::cout << "Prénom ? ";
    entree_securisee(p.prenom);
    std::cout << "Sexe ? ";
    entree_securisee(p.sexe);
    std::cout << "Age ? ";
    entree_securisee(p.age, [](int &age)
                     { return age >= 0; });
}

std::string enregistrer_infos(const Person &person)
{
    string nom_fichier{person.prenom + "." + person.nom + ".csv"};
    ofstream fichierOuvert{nom_fichier};
    fichierOuvert << person.nom << ',' << person.prenom << ',' << person.sexe << ',' << person.age << endl;

    return nom_fichier;
}

int main()
{
    Person p;

    demander_infos(p);
    auto save = [&](const Person &person)
    {
        string name = {person.nom + "." + person.prenom + ".csv"};
        ofstream fichieOuvert{name};
        fichieOuvert << person.prenom << ',' << person.nom << ',' << person.sexe << ',' << person.age << endl;
        return name;
    };

    string nom_fichier = save(p); // enregistrer_infos(p);
    std::cout << std::endl
              << "Ces données seront enregistrées dans le fichier " << nom_fichier << std::endl;

    return 0;
}