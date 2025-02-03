#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Razones por las que la persona esta en la isla, par de recursos que se pueden encontrar { comida, bebida }
map<string, pair<string, string>> reasons_why = {
    {"avión", {"humanos", "sangre"}},
    {"naufragio", {"ardilla", "agua de árbol arce"}},
    {"helicóptero", {"pescado", "cocos"}},
    {"paracaidas", {"pescado", "wisky"}},
    {"submarino", {"manta raya", ".. mejor no saber que es eso"}},
    {"lancha", {"pescado", "vodka"}},
    {"bote", {"salmón", "zumo"}},
    {"PESCADOR EMBRUJADO", {"pescado fantasma", "agua de charco"}},
    {"pirata !Jack Sparrow¡", {"megalodon", "mezcla de ron con cerveza pirata"}},
};
// Sitios para explorar
map<string, pair<string, string>> explore_site = {
    {"Zona desierta", {"Menos mal que tienes un refugio", "Desgraciadamente no tienes un refugio"}},
    {"Cueva", {"Encontrasete frutos del bosque, y pasaras la noche en la cueva, te alimentaste y recuperaste vida", "No encontraste nada util en la cueva, pasaras la noche en la cueva y obtubiste un refugio improvisado, no necesitas construir uno"}},
    {"Montaña", {"Encontraste bebida extraña, y pasaras la noche en la bodega, te alimentaste y recuperaste vida", "Genial me he cansado para nada"}},
    {"Volcán", {"Te encontraste a los habitantes de los volcanes, te alojan en sus casas y te dan todo lo necesario para sobrevivir todos los dias", "Te encontraste a los habitantes de los volcanes, parece ser que les das mala espina, asique te asesinan"}},
    {"Casa pirata", {"¡Ohh, qué sorpresa! Un invitado no invitado...\n  Ahora dime, ¿vienes a robarme, a matarme o—espera—acaso traes ron?\n Porque si no traes ron, amigo mío, tenemos un problema... un problema grande. 🍻🏴‍☠️", "¡Vaya, vaya! Si es que los buenos piratas no necesitan invitación...\nEspero que hayas traído ron, porque si no, tendré que considerar seriamente si seguir dejándote con vida... ¡Ja! ¡Es broma! (O tal vez no...) 🍻🏴‍☠️"}},
};

// Forward declarations
class Persona;
class ExplorationManager;
// First class definition
class ExplorationManager {
private:
    Persona* persona;
public:
    ExplorationManager(Persona* p) : persona(p) {}
    template<typename Iterator>
    void exploreZone(string& reason, string& site, Iterator& it, Persona& person);
};

// Persona en una isla desierta
class Persona {
    // Atributos privados
   private:
    string nombre;
    ExplorationManager* explorationManager;
    int tiempoEnIsla = 0;
    int vida = 100;
    int hambre = 0;
    int sed = 0;
    string site = "Playa";
    bool refugio = false;

   public:
    // Constructor
    Persona(string nombre, int vida) {
         explorationManager = new ExplorationManager(this);
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

    string getSite() {
        return site;
    }

    ExplorationManager* getExplorationManager() {
        return explorationManager;
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

    void setSite(string site) {
        this->site = site;
    }

    void setExplorationManager(ExplorationManager* explorationManager) {
        this->explorationManager = explorationManager;
    }

    // Métodos
    void showStatus() {
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

// Clase de utilidades
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
        for (int i = 0; i <= duration; ++i) {
            int percentage = (i * 100) / duration;
            cout << "\r\033[1;32mCargando " << percentage << "%\033[0m" << flush;
            this_thread::sleep_for(chrono::milliseconds(300));
        }
        cout << "\n";
    }

    static void showMenu(Persona& person, string site) {
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

    // Configuración inicial para añadir finales alternativos y no repetir códigp
    static void initialConfiguration() {
        explore_site["Cementerio pirata"] = explore_site["Casa pirata"];
        explore_site["Zona helada"] = explore_site["Zona desierta"];
        explore_site["Bosque"] = explore_site["Cueva"];
        explore_site["Ciudad abandonada"] = explore_site["Volcan"];
        explore_site["Bodega"] = explore_site["Montaña"];
    }
};

// Clase para generar números aleatorios
class Random {
   public:
    static bool randomNothing(int destino) {
        if (destino < 1 || destino > 5) {
            Utils::printRed("Te crees muy gracioso... pero no lo eres, el destino no te dará nada");
            return false;
        } else {
            int random_number = (rand() % 5) + 1;
            Utils::printGreen("Destino " + to_string(random_number));
            return random_number != destino;
        }
    }

    static int getDestino() {
        // El usuario selecionará un número al azar entre 1 y 10, al igual que la máquina si es el mismo número, entonces no encontró nada
        cout << "Elije un numero entre [1, 5] que determinara tu destino: ";
        int destino;
        cin >> destino;

        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            destino = -1;
        }

        return destino;
    }
};

template<typename Iterator>
void ExplorationManager::exploreZone(string& reason, string& site,  Iterator& it, Persona& person) {
        if(reason == "paracaidas" || site == "lancha"){
            Utils::printGreen("Lo ves todo demasiado borroso devido a la bebida, no puedes explorar");
            return;
        }

        // Mostramos el mensaje según el sitio y la persona que seas
        if (site == "Casa pirata" || site == "Cementerio pirata") {
            if (reason == "pirata !Jack Sparrow¡") {
                cout << it->second.first << "\n";
                Utils::printRed("Parece que tuviste problemas con los piratas en tu accidente");
                Utils::printRed("HAS SIDO ASESINADO POR... ¡Jack Sparrow! 🏴‍☠️");
                person.setVida(0);
            } else {
                cout << it->second.second << "\n";
                Utils::printGreen("HAS SIDO RESCATADO POR... ¡Jack Sparrow! 🏴‍☠️");
                person.setVida(100);
                person.setTiempoEnIsla(10);
            }
        } else if (site == "Zona desierta" || site == "Zona helada") {
            if(person.getRefugio()){
                Utils::printGreen(it->second.first);
                Utils::printGreen("Tanta caminata te ha dejado exhausto, parece que no has encontrado nada util, dormiras en tu refugio y recuperaras vida");
                person.setVida(person.getVida() + 20);
            } else {
                Utils::printRed(it->second.second);
                Utils::printRed("Tanta caminata te ha dejado exhausto, parece que no has encontrado nada util, dormiras en la intemperie y perderás vida");
                person.setVida(person.getVida() - 10);
            }
        } else if (site == "Cueva" || site == "Bosque") {
            if(rand() % 2){
                Utils::printGreen(it->second.first);
                person.setVida(person.getVida() + 20);
                person.setHambre(person.getHambre() + 20);
            } else {
                Utils::printGreen(it->second.second);
                person.setRefugio(true);
            }
        } else if (site == "Montaña" || site == "Bodega") {
            if(rand() % 2){
                Utils::printGreen(it->second.first);
                person.setVida(person.getVida() + 20);
                person.setSed(person.getSed() + 20);    
                person.setHambre(person.getHambre() + 20);
                person.setRefugio(true);
            } else {
                Utils::printGreen(it->second.second);
            }
        } else if (site == "Volcan" || site == "Ciudad abandonada") {
            if(rand() % 2){
                Utils::printGreen(it->second.first);
                person.setVida(100);
                person.setTiempoEnIsla(10);
            } else {
                Utils::printRed(it->second.first);
                person.setVida(0);
                person.setTiempoEnIsla(10);
            }
        } else{
            Utils::printRed("Parece ser que el programador no es muy avisapado y algo se le ha escapado");
            Utils::printGreen("Ganas 10 de vida por la confusión, abre una issue en el repositorio para que lo arreglen");
            person.setVida(person.getVida() + 10);
        }
    }

bool solve(Persona person, string reason) {
    cout << "---------------------------------" << "\n";
    cout << "Bienvenido a la isla desierta " << person.getNombre() << "\n";
    cout << "Estas aqui devido a un problema con un " << reason << "\n";
    cout << "Tu vida es de " << person.getVida() << "\n";
    Utils::showLoading(30);
    cout << "---------------------------------" << "\n";

    while (person.getVida() > 0 && person.getTiempoEnIsla() < 10) {
        Utils::showMenu(person, person.getSite());

        char option;
        cin >> option;

        switch (option) {
            case '1': {
                cout << "Buscando comida..." << "\n";
                sleep(1);

                // Obtenemos nuestro destino
                int destino = Random::getDestino();
                if (!Random::randomNothing(destino)) {
                    Utils::printRed("No encontraste nada\n");
                } else {
                    // Si no coincide encontrará algo pr lo que subimos sus stats de hambre entre 20 y 50
                    Utils::printGreen("Encontraste " + reasons_why[reason].first + "\n");
                    person.setHambre(person.getHambre() + rand() % 50 + 20);
                }
                break;
            }
            case '2': {
                cout << "Buscando bebida..." << "\n";
                sleep(1);

                // Obtenemos nuestro destino
                int destino = Random::getDestino();
                if (!Random::randomNothing(destino)) {
                    Utils::printRed("No encontraste nada\n");
                } else {
                    // Si no coincide encontrará algo pr lo que subimos sus stats de sed entre 20 y 50
                    Utils::printGreen("Encontraste " + reasons_why[reason].second + "\n");
                    person.setSed(person.getSed() + rand() % 50 + 20);
                }
                break;
            }
            case '3': {
                // Verificamos si ya tiene un refugio para constuirlo o no
                if (person.getRefugio()) {
                    Utils::printRed("Ya tienes un refugio\n");
                } else {
                    cout << "Construyendo refugio en la " << person.getSite() << "...\n";
                    sleep(1);
                    Utils::printGreen("Refugio construido\n");
                    person.setRefugio(true);
                }
                break;
            }
            case '4': {
                cout << "Explorando..." << "\n";
                sleep(1);
                // TODO: Implementar la exploración de la isla
                // Obtenemos un sitio aleatorio
                auto it = next(begin(explore_site), rand() % explore_site.size());
                string site = it->first; // Nombre del sitio
                person.setSite(site);

                cout<<"Encontraste un "<<site<<"\n";

                person.getExplorationManager()->exploreZone(reason, site, it, person);
                break;
            }
            default: {
                Utils::printRed("Opcion invalida");
                break;
            }
        }

        person.timePass();    // Pasa el tiempo en la isla las stads de hambre y sed disminuyen
        person.showStatus();  // Verifica el estado de la persona

        cout << "\nPresiona cualquier tecla para continuar" << "\n";
        cin.ignore();
        cin.get();
    }

    system("clear");
    cout << "---------------------------------\n";
    (person.getVida() <= 0) ? Utils::printRed("HAS MUERTO") : Utils::printGreen("HAS SIDO RESCATADO");
    cout << "---------------------------------\n";
    return false;
}

int main() {
    Utils::initialConfiguration();
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