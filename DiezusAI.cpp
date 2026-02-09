#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <deque>

using namespace std;

struct Entry {
    int id;
    string cat;
    int sev;
    string txt;
};

class DiezusEngine {
private:
    unordered_map<int, Entry> storage;
    // Usamos un vector de pares para poder iterar y buscar subcadenas
    vector<pair<string, int>> diccionarioCritico;
    deque<int> historial;
    const size_t MAX_H = 10;
    string logPath = "sentimientos_semana.txt";

    string clean(string t) {
        string r = "";
        for(char c : t) {
            if(!ispunct(c)) r += tolower(c);
        }
        return r;
    }

    void inicializarDiccionario() {
        // Palabras de alta prioridad (Nivel 9)
        diccionarioCritico.push_back({"suicid", 9});
        diccionarioCritico.push_back({"matar", 9});
        diccionarioCritico.push_back({"morir", 9});
        diccionarioCritico.push_back({"ayuda", 9});
        // Otras emociones
        diccionarioCritico.push_back({"triste", 0});
        diccionarioCritico.push_back({"mal", 0});
        diccionarioCritico.push_back({"feliz", 1});
        diccionarioCritico.push_back({"bien", 1});
        diccionarioCritico.push_back({"odio", 4});
        diccionarioCritico.push_back({"solo", 6});
    }

public:
    DiezusEngine() {
        inicializarDiccionario();
        ifstream f("dataset.txt");
        string l;
        while(getline(f, l)) {
            stringstream ss(l);
            string id, cat, sev, txt;
            if(getline(ss, id, '|') && getline(ss, cat, '|') && getline(ss, sev, '|') && getline(ss, txt)) {
                storage[stoi(id)] = {stoi(id), cat, stoi(sev), txt};
            }
        }
    }

    string analyze(string raw_input) {
        string in = clean(raw_input);
        int sev = 3; // Neutro por defecto

        // MEJORA TÉCNICA: Búsqueda de subcadena (Detecta "suicid" dentro de "suicidarme")
        for(auto const& [palabra, nivel] : diccionarioCritico) {
            if(in.find(palabra) != string::npos) {
                sev = nivel;
                // Si detectamos algo de nivel 9, dejamos de buscar, es prioridad.
                if(sev == 9) break; 
            }
        }

        // Manejo de negación simple
        if((in.find("no ") != string::npos) && sev == 1) sev = 0;

        // Selección de respuesta
        vector<int> candidatos;
        for(auto const& [id, e] : storage) {
            if(e.sev == sev) {
                bool u = false;
                for(int h : historial) if(h == id) u = true;
                if(!u) candidatos.push_back(id);
            }
        }

        int bid = -1;
        if(!candidatos.empty()) {
            bid = candidatos[rand() % candidatos.size()];
            historial.push_back(bid);
            if(historial.size() > MAX_H) historial.pop_front();
        }

        string res = (bid != -1) ? storage[bid].txt : "Entiendo. Cuéntame más al respecto.";
        string act = (sev == 9) ? "trigger_games" : "none";

        // Forzar respuesta de seguridad si es Nivel 9
        if(sev == 9) {
            res = "He detectado una situación de riesgo. Como tu IA de apoyo, mi protocolo indica que debemos hacer una pausa ahora mismo.";
        }

        // Log para Render
        ofstream log(logPath, ios::app);
        if(log) log << time(0) << "|" << sev << endl;

        return "{\"sev\": " + to_string(sev) + ", \"res\": \"" + res + "\", \"act\": \"" + act + "\"}";
    }
};

int main(int argc, char* argv[]) {
    srand(time(0));
    DiezusEngine engine;
    if(argc > 1) cout << engine.analyze(argv[1]) << endl;
    return 0;
}