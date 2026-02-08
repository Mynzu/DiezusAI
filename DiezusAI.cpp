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
    string categoria;
    int severidad;
    string contenido;
};

class DiezusEngine {
private:
    unordered_map<int, Entry> storage;
    unordered_map<string, int> mapaEmocional;
    deque<int> historial;
    const size_t MAX_HISTORIAL = 10;
    string logPath = "sentimientos_semana.txt";

    string clean(string t) {
        string r = "";
        for(char c : t) if(!ispunct(c)) r += tolower(c);
        return r;
    }

    // Análisis de historial acumulado
    bool detectarEmergenciaSilenciosa() {
        ifstream file(logPath);
        if(!file) return false;
        string line;
        vector<int> ultimos;
        while(getline(file, line)) {
            size_t p = line.find("|");
            if(p != string::npos) ultimos.push_back(stoi(line.substr(p+1)));
        }
        if(ultimos.size() < 5) return false;
        
        int alarma = 0;
        for(size_t i = ultimos.size()-5; i < ultimos.size(); i++) {
            if(ultimos[i] == 0 || ultimos[i] == 9 || ultimos[i] == 4) alarma++;
        }
        return (alarma >= 3); 
    }

    void inicializarMapaEmocional() {
        mapaEmocional["triste"] = 0; mapaEmocional["mal"] = 0;
        mapaEmocional["feliz"] = 1;  mapaEmocional["bien"] = 1;
        mapaEmocional["puedo"] = 2;  mapaEmocional["fuerza"] = 2;
        mapaEmocional["odio"] = 4;   mapaEmocional["enojo"] = 4;
        mapaEmocional["solo"] = 6;   mapaEmocional["soledad"] = 6;
        mapaEmocional["morir"] = 9;  mapaEmocional["ayuda"] = 9;
    }

public:
    DiezusEngine() {
        inicializarMapaEmocional();
        ifstream file("dataset.txt");
        string line;
        while(getline(file, line)) {
            stringstream ss(line);
            string s_id, cat, s_sev, cont;
            if(getline(ss, s_id, '|') && getline(ss, cat, '|') && 
               getline(ss, s_sev, '|') && getline(ss, cont)) {
                try { storage[stoi(s_id)] = {stoi(s_id), cat, stoi(s_sev), cont}; } catch (...) {}
            }
        }
    }

    string analyze(string input) {
        string in = clean(input);
        int sevDetectada = 3; 
        bool negacion = (in.find("no ") != string::npos || in.find("nunca ") != string::npos);

        stringstream ss(in);
        string word;
        while(ss >> word) {
            if(mapaEmocional.count(word)) {
                sevDetectada = mapaEmocional[word];
                if(negacion && (sevDetectada == 1 || sevDetectada == 2)) sevDetectada = 0; 
                break;
            }
        }

        // Lógica de Emergencia Silenciosa (Long-term memory)
        bool malaRacha = detectarEmergenciaSilenciosa();
        
        int mejorID = -1;
        vector<int> posibles;
        for(auto const& [id, entry] : storage) {
            if(entry.severidad == (malaRacha ? 9 : sevDetectada)) {
                bool usado = false;
                for(int h : historial) if(h == id) usado = true;
                if(!usado) posibles.push_back(id);
            }
        }

        if(!posibles.empty()) {
            mejorID = posibles[rand() % posibles.size()];
            historial.push_back(mejorID);
            if(historial.size() > MAX_HISTORIAL) historial.pop_front();
        }

        string respuesta = (mejorID != -1) ? storage[mejorID].contenido : "Procesando información...";
        string accion = (sevDetectada == 9 || malaRacha) ? "trigger_games" : "none";

        if(sevDetectada == 9 || malaRacha) {
            respuesta = "He notado una tendencia crítica en tus últimos mensajes. Protocolo de bienestar activado.";
        }

        ofstream log(logPath, ios::app);
        log << time(0) << "|" << sevDetectada << endl;

        return "{\"sev\": " + to_string(sevDetectada) + ", \"res\": \"" + respuesta + "\", \"act\": \"" + accion + "\"}";
    }
};

int main(int argc, char* argv[]) {
    srand(time(0));
    DiezusEngine diezus;
    if(argc > 1) cout << diezus.analyze(argv[1]) << endl;
    else cout << "{\"error\": \"No input\"}" << endl;
    return 0;
}