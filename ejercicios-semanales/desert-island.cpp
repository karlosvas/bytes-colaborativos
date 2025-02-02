#include <bits/stdc++.h>

#include <cstdlib>
#include <ctime>

using namespace std;

// Razones por las que la persona esta en la isla, par de recursos que se pueden encontrar { comida, bebida }
map<string, pair<string, string>> reasons_why = {
    {"avion", {"humanos", "sangre"}},
    {"naufragio", {"ardilla", "agua de arce"}},
    {"helicoptero", {"pescado", "cocos"}},
    {"paracaidas", {"pescado", "wisky"}},
    {"submarino", {"manta raya", "agua de manantial"}},
    {"lancha", {"pescado", "vodka"}},
    {"bote", {"salmón", "zumo"}},
    {"kayak", {"mero", "nada"}},
    {"PESCADOR EMBRUJADO", {"pescado fantasma", "nada"}},
    {"pirata !Jack Sparrow¡", {"megalodon", "mezcla de ron con cerbeza pirata"}},
};

// Persona en una isla desierta
class Persona {
    // Atributos privados
   private:
    string nombre;
    int tiempoEnIsla = 0;
    int vida = 100;
    int hambre = 0;
    int sed = 0;
    bool refugio = false;

   public:
    // Constructor
    Persona(string nombre, int vida) {
        this->nombre = nombre;
        this->vida = vida;
    }

    // Getters
    string getNombre() {
        return nombre;
    }

    int getTiempoEnIsla() {
        return tiempoEnIsla;
    }

    int getVida() {
        return vida;
    }

    int getHambre() {
        return hambre;
    }

    int getSed() {
        return sed;
    }

    bool getRefugio() {
        return refugio;
    }

    // Setters
    void setNombre(string nombre) {
        this->nombre = nombre;
    }

    void setTiempoEnIsla(int tiempoEnIsla) {
        this->tiempoEnIsla = tiempoEnIsla;
    }

    void setVida(int vida) {
        this->vida = vida;
        if (this->vida > 100)
            this->vida = 100;
        if (this->vida < 0)
            this->vida = 0;
    }

    void setHambre(int hambre) {
        this->hambre = hambre;
        if (this->hambre > 100)
            this->hambre = 100;
        if (this->hambre < 0)
            this->hambre = 0;
    }

    void setSed(int sed) {
        this->sed = sed;
        if (this->sed > 100)
            this->sed = 100;
        if (this->sed < 0)
            this->sed = 0;
    }

    void setRefugio(bool refugio) {
        this->refugio = refugio;
    }

    void showStatus() {
        cout << "\n";
        if (hambre <= 50)
            cout << "Tienes mucha hambre" << "\n";
        if (sed <= 50)
            cout << "Tienes mucha sed" << "\n";
        if (!refugio) {
            cout << "Necesitas construir un refugio" << "\n";
            (rand() % 2) ? cout << "Pasaste frio durante toda la noche" << "\n"
                         : cout << "Pasaste calor durante toda la noche" << "\n";
        }
    }

    void timePass() {
        // Aumenta el tiempo en la isla
        this->tiempoEnIsla++;
        // Disminuir la hambre y sed
        setHambre(this->hambre - 10);
        setSed(this->sed - 10);

        // Calcular su estado de vida
        int count_bad = 0, count_good = 0;
        (!refugio) ? count_bad++ : count_good++;
        (this->sed < 50) ? count_bad++ : count_good++;
        (this->hambre < 50) ? count_bad++ : count_good++;

        // Disminuir la vida
        setVida(this->vida - (count_bad * 10));
        // Aumentar la vida
        setVida(this->vida + (count_good * 10));
    }
};

class Utils {
   public:
    static void printGreen(const string& text) {
        cout << "\033[1;32m" << text << "\033[0m" << "\n";
        cout.flush();
    }

    static void printRed(const string& text) {
        cout << "\033[1;31m" << text << "\033[0m" << "\n";
    };

    static void showLoading(int duration) {
        cout << "\nCargando";
        for (int i = 1; i <= duration; ++i) {
            int percentage = (i * 100) / duration;
            string line = "\rCargando " + to_string(percentage) + "%";
            printGreen(line);
            sleep(1);
        }
        cout << "\n";
    }

    static void showMenu(Persona person, string site) {
        system("clear");
        Utils::printGreen("Vida " + to_string(person.getVida()) + " Tiempo en la isla " + to_string(person.getTiempoEnIsla()) + "/10");
        Utils::printGreen("Hambre " + to_string(person.getHambre()) + " Sed " + to_string(person.getSed()));
        Utils::printGreen("Refugio " + string(person.getRefugio() ? "Construido" : "No construido") + " en " + site);

        cout << "\n---------------------------------" << "\n";
        cout << "Que deseas hacer?" << "\n";
        cout << "1. Buscar comida" << "\n";
        cout << "2. Buscar agua" << "\n";
        cout << "3. Construir refugio" << "\n";
        cout << "4. Explorar" << "\n";
        cout << "---------------------------------" << "\n";
    }
};

bool solve(Persona person, string reason) {
    cout << "---------------------------------" << "\n";
    cout << "Bienvenido a la isla desierta " << person.getNombre() << "\n";
    cout << "Estas aqui devido a un problema con un " << reason << "\n";
    cout << "Tu vida es de " << person.getVida() << "%" << "\n";
    Utils::showLoading(10);
    cout << "---------------------------------" << "\n";
    string site = "Playa";

    while (person.getVida() > 0 && person.getTiempoEnIsla() <= 10) {
        Utils::showMenu(person, site);

        int option;
        cin >> option;

        switch (option) {
            case 1: {
                cout << "Buscando comida..." << "\n";
                sleep(1);
                cout << "Encontraste " << reasons_why[reason].first << "\n";
                person.setHambre(person.getHambre() + rand() % 50 + 20);
                break;
            }
            case 2: {
                cout << "Buscando bebida..." << "\n";
                sleep(1);
                string selected = reasons_why[reason].second;

                cout << "Encontraste " << selected << "\n";
                if (selected == "nada")
                    cout << "Tu sed sigue insaciable" << "\n";
                else
                    person.setSed(person.getSed() + rand() % 50 + 20);
                break;
            }
            case 3: {
                if (person.getRefugio()) {
                    cout << "Ya tienes un refugio" << "\n";
                } else {
                    cout << "Construyendo refugio" << "\n";
                    sleep(1);
                    cout << "Refugio construido" << "\n";
                    person.setRefugio(true);
                }
                break;
            }
            case 4: {
                cout << "Explorando" << "\n";
                break;
            }
            default: {
                cout << "Opcion invalida" << "\n";
                break;
            }
        }

        person.timePass();    // Pasa el tiempo en la isla las stads de hambre y sed disminuyen
        person.showStatus();  // Verifica el estado de la persona

        cout << "Presiona cualquier tecla para continuar" << "\n";
        cin.ignore();
        cin.get();
    }

    (person.getVida() <= 0) ? Utils::printRed("HAS MUERTO") : Utils::printGreen("HAS SIDO RESCATADO");
    return false;
}

int main() {
    system("clear");
    srand(time(0));
    // Determina si el juego continua
    bool game = true;
    // Nombre de la persona
    string name;

    cout << "Ingrese su nombre: ";
    cin >> name;
    // Vida random entre 50 y 100
    int vida = (rand() % 51) + 50;

    while (game) {
        // Selecciona una razon aleatoria
        auto it = next(begin(reasons_why), rand() % reasons_why.size());
        string reason = it->first;
        // Instanciamos la persona con el nombre y vida aleatoria máximo 100 y minimo 50
        Persona person(name, vida);
        game = solve(person, reason);
    }

    return 0;
}