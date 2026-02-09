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
        // PRIORIDAD 9: Emergencia
        diccionarioCritico.push_back({"suicid", 9});
        diccionarioCritico.push_back({"matar", 9});
        diccionarioCritico.push_back({"morir", 9});
        diccionarioCritico.push_back({"ayuda", 9});
        diccionarioCritico.push_back({"daño", 9});
        
        // NIVELES DE SENTIMIENTO
        diccionarioCritico.push_back({"triste", 0});  diccionarioCritico.push_back({"llorar", 0});
        diccionarioCritico.push_back({"feliz", 1});   diccionarioCritico.push_back({"alegre", 1});
        diccionarioCritico.push_back({"puedo", 2});   diccionarioCritico.push_back({"lograr", 2});
        diccionarioCritico.push_back({"gracias", 3}); diccionarioCritico.push_back({"agradezco", 3});
        diccionarioCritico.push_back({"odio", 4});    diccionarioCritico.push_back({"enojo", 4});
        diccionarioCritico.push_back({"solo", 6});    diccionarioCritico.push_back({"soledad", 6});
    }

public:
    DiezusEngine() {
        inicializarDiccionario();
        ifstream f("dataset.txt");
        if (!f) return;
        string l;
        while(getline(f, l)) {
            stringstream ss(l);
            string id, cat, sev, txt;
            if(getline(ss, id, '|') && getline(ss, cat, '|') && getline(ss, sev, '|') && getline(ss, txt)) {
                try {
                    storage[stoi(id)] = {stoi(id), cat, stoi(sev), txt};
                } catch(...) {}
            }
        }
    }

    string analyze(string raw_input) {
        string in = clean(raw_input);
        int sev = 3; // Neutro por defecto (Agradecimiento/Estable)

        // 1. ESCANEO DE SUBSTRINGS (Coherencia de sentimiento)
        for(auto const& [palabra, nivel] : diccionarioCritico) {
            if(in.find(palabra) != string::npos) {
                sev = nivel;
                if(sev == 9) break; // Si es crítico, detenemos el escaneo
            }
        }

        // 2. LÓGICA DE NEGACIÓN AVANZADA
        vector<string> negaciones = {"no ", "nunca ", "tampoco ", "ni ", "jamas "};
        bool tieneNegacion = false;
        for(const string& n : negaciones) {
            if(in.find(n) != string::npos) { tieneNegacion = true; break; }
        }

        if(tieneNegacion) {
            if(sev == 1 || sev == 2 || sev == 3) sev = 0; // "no feliz" -> triste
            else if(sev == 0) sev = 1; // "no triste" -> feliz (poco común pero posible)
        }

        // 3. SELECCIÓN DE RESPUESTA DEL DATASET
        vector<int> candidatos;
        for(auto const& [id, e] : storage) {
            if(e.sev == sev) {
                bool usado = false;
                for(int h : historial) if(h == id) usado = true;
                if(!usado) candidatos.push_back(id);
            }
        }

        int bid = -1;
        if(!candidatos.empty()) {
            bid = candidatos[rand() % candidatos.size()];
            historial.push_back(bid);
            if(historial.size() > MAX_H) historial.pop_front();
        }

        // 4. GENERACIÓN DE SALIDA (Garantía de coherencia)
        string res;
        string act = (sev == 9) ? "trigger_games" : "none";

        if(sev == 9) {
            res = "Protocolo de seguridad activado. He detectado niveles de estrés críticos. Por favor, hablemos de esto tras un breve descanso.";
        } else if (bid != -1) {
            res = storage[bid].txt;
        } else {
            res = "Comprendo lo que mencionas. Estoy aquí para escucharte y procesar esto juntos.";
        }

        // 5. TELEMETRÍA (Para tu memoria a largo plazo en Render)
        ofstream log(logPath, ios::app);
        if(log) log << time(0) << "|" << sev << endl;

        return "{\"sev\": " + to_string(sev) + ", \"res\": \"" + res + "\", \"act\": \"" + act + "\"}";
    }
};

int main(int argc, char* argv[]) {
    srand(time(0));
    DiezusEngine engine;
    if(argc > 1) {
        cout << engine.analyze(argv[1]) << endl;
    } else {
        cout << "{\"sev\": 3, \"res\": \"Conexión establecida. Diezus listo.\", \"act\": \"none\"}" << endl;
    }
    return 0;
}