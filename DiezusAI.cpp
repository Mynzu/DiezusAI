#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <memory>

using namespace std;

// Estructura de datos optimizada
struct Entry { 
    int id; 
    int sev; 
    string txt; 
};

class DiezusEngine {
private:
    unordered_map<int, Entry> storage;
    // Mapa semántico extendido para una detección más precisa
    const vector<pair<string, int>> semanticMap = {
        {"suicid", 9}, {"morir", 9}, {"matar", 9}, {"fin", 9}, {"quitarme", 9},
        {"dificil", 0}, {"triste", 0}, {"mal", 0}, {"llorar", 0}, {"cansado", 0},
        {"odio", 4}, {"enojo", 4}, {"furia", 4}, {"solo", 6}, {"soledad", 6}
    };

    // Helper para persistencia de archivos (Optimizado para Render/Docker)
    void saveState(const string& file, const string& val) {
        ofstream o(file, ios::trunc);
        if (o.is_open()) o << val;
    }

    string loadState(const string& file, const string& def) {
        ifstream i(file);
        string v;
        return (getline(i, v)) ? v : def;
    }

public:
    DiezusEngine() {
        // Carga de dataset con validación de errores
        ifstream f("dataset.txt");
        string line;
        while (getline(f, line)) {
            stringstream ss(line);
            string s_id, cat, s_sev, txt;
            if (getline(ss, s_id, '|') && getline(ss, cat, '|') && 
                getline(ss, s_sev, '|') && getline(ss, txt)) {
                int id = stoi(s_id);
                storage[id] = {id, stoi(s_sev), txt};
            }
        }
    }

    string analyze(string raw) {
        string in = raw;
        transform(in.begin(), in.end(), in.begin(), ::tolower);
        
        string ctx = loadState("contexto.txt", "normal");
        int currentSev = 3; // Neutral por defecto

        // 1. GESTIÓN DE IDENTIDAD (Prioridad Alta)
        if (in.find("hola") != string::npos) 
            return "{\"sev\":3,\"res\":\"Hola. Soy Diezus. ¿En qué puedo apoyarte?\",\"act\":\"none\"}";
        if (in.find("quien eres") != string::npos || in.find("quién eres") != string::npos) 
            return "{\"sev\":3,\"res\":\"Soy Diezus, una IA de soporte emocional diseñada para escucharte.\",\"act\":\"none\"}";
        if (in.find("proposito") != string::npos || in.find("propósito") != string::npos) 
            return "{\"sev\":3,\"res\":\"Mi propósito es ser tu refugio y ayudarte a encontrar calma.\",\"act\":\"none\"}";

        // 2. LÓGICA DE INTERRUPCIÓN (Juego)
        if (ctx == "juego") {
            if (in.find("si") != string::npos || in.find("claro") != string::npos || in.find("bueno") != string::npos) {
                saveState("contexto.txt", "normal");
                saveState("avisos.txt", "0");
                return "{\"sev\":9,\"res\":\"Iniciando protocolo de distracción. Vamos al juego.\",\"act\":\"trigger_games\"}";
            }
        }

        // 3. ANÁLISIS SEMÁNTICO DE SENTIMIENTOS
        int maxSevFound = -1;
        for (const auto& item : semanticMap) {
            if (in.find(item.first) != string::npos) {
                if (item.second > maxSevFound) maxSevFound = item.second;
            }
        }
        if (maxSevFound != -1) currentSev = maxSevFound;

        // 4. SELECCIÓN DE RESPUESTA BASADA EN SEVERIDAD
        vector<int> candidates;
        for (const auto& [id, entry] : storage) {
            if (entry.sev == currentSev) candidates.push_back(id);
        }

        // Fallback si no hay frases de esa severidad
        if (candidates.empty()) {
            for (const auto& [id, entry] : storage) if (entry.sev == 3) candidates.push_back(id);
        }

        string responseTxt = storage[candidates[rand() % candidates.size()]].txt;

        // 5. PERSISTENCIA Y DETECCIÓN DE CRISIS
        if (currentSev == 9 || currentSev == 0 || currentSev == 6) {
            int warnings = stoi(loadState("avisos.txt", "0")) + 1;
            saveState("avisos.txt", to_string(warnings));
            
            if (warnings >= 2) {
                saveState("contexto.txt", "juego");
                return "{\"sev\":" + to_string(currentSev) + ",\"res\":\"" + responseTxt + " Noto que te sientes muy mal. ¿Te gustaría distraerte con un juego?\",\"act\":\"suggest_game\"}";
            }
        } else {
            saveState("avisos.txt", "0");
        }

        saveState("contexto.txt", "normal");
        return "{\"sev\":" + to_string(currentSev) + ",\"res\":\"" + responseTxt + "\",\"act\":\"none\"}";
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    srand(static_cast<unsigned int>(time(0)));
    
    DiezusEngine engine;
    cout << engine.analyze(argv[1]) << endl;
    
    return 0;
}