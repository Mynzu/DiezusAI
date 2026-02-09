#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <chrono>

using namespace std;

struct Entry {
    int id;
    int sev;
    string txt;
};

class DiezusEngine {
private:
    unordered_map<int, Entry> storage;
    vector<pair<string, int>> diccionarioCritico;
    string logPath = "sentimientos_semana.txt";
    string histPath = "historial_ids.txt";
    string contextPath = "contexto.txt";

    string clean(string t) {
        string r = "";
        for(char c : t) if(!ispunct(c)) r += tolower(c);
        return r;
    }

    vector<int> cargarHistorial() {
        vector<int> h; ifstream f(histPath); int id;
        while(f >> id) h.push_back(id);
        return h;
    }

    void guardarHistorial(vector<int> h, int nuevoId) {
        h.push_back(nuevoId);
        if(h.size() > 20) h.erase(h.begin());
        ofstream f(histPath);
        for(int id : h) f << id << " ";
    }

    void setContext(string s) { ofstream f(contextPath); f << s; }
    string getContext() { ifstream f(contextPath); string s; f >> s; return s; }

public:
    DiezusEngine() {
        // Diccionario de impacto emocional
        diccionarioCritico = {
            {"suicid", 9}, {"matar", 9}, {"morir", 9}, {"ayuda", 9},
            {"triste", 0}, {"mal", 0}, {"feliz", 1}, {"bien", 1},
            {"odio", 4}, {"enojo", 4}, {"solo", 6}
        };

        // Carga de las 1700 frases
        ifstream f("dataset.txt");
        string l;
        while(getline(f, l)) {
            stringstream ss(l);
            string s_id, cat, s_sev, txt;
            if(getline(ss, s_id, '|') && getline(ss, cat, '|') && getline(ss, s_sev, '|') && getline(ss, txt)) {
                try { storage[stoi(s_id)] = {stoi(s_id), stoi(s_sev), txt}; } catch(...) {}
            }
        }
    }

    string analyze(string raw_input) {
        string in = clean(raw_input);
        string ctx = getContext();
        int sev = 3; 

        // 1. LÓGICA DE IDENTIDAD (Propósito y Quién es)
        if(in.find("quien eres") != string::npos || in.find("quien es usted") != string::npos) {
            setContext("normal");
            return "{\"sev\": 3, \"res\": \"Soy Diezus, un sistema de acompañamiento inteligente diseñado para escucharte y apoyarte en tus momentos críticos.\", \"act\": \"none\"}";
        }
        if(in.find("proposito") != string::npos || in.find("para que sirves") != string::npos) {
            setContext("normal");
            return "{\"sev\": 3, \"res\": \"Mi propósito es ser un puente hacia tu bienestar, procesando tus emociones y ofreciéndote herramientas de distracción cuando el camino se torna difícil.\", \"act\": \"none\"}";
        }
        if(in == "hola" || in == "buenos dias" || in == "buenas noches") {
            setContext("normal");
            return "{\"sev\": 3, \"res\": \"Hola. Soy Diezus. Estoy operativo y listo para escucharte. ¿Cómo te encuentras hoy?\", \"act\": \"none\"}";
        }

        // 2. LÓGICA DE CONTEXTO (Respuesta a pregunta de crisis)
        if(ctx == "esperando_juego") {
            if(in.find("si") != string::npos || in.find("claro") != string::npos || in.find("bueno") != string::npos) {
                setContext("normal");
                return "{\"sev\": 9, \"res\": \"Entendido. Iniciando protocolo de relajación. Espero que esto te ayude a despejar la mente.\", \"act\": \"trigger_games\"}";
            }
        }

        // 3. ANÁLISIS EMOCIONAL
        for(auto const& [palabra, nivel] : diccionarioCritico) {
            if(in.find(palabra) != string::npos) { sev = nivel; break; }
        }

        // 4. SELECCIÓN ANTI-REPETICIÓN (Dataset de 1700 frases)
        vector<int> usados = cargarHistorial();
        vector<int> candidatos;
        for(auto const& [id, e] : storage) {
            if(e.sev == sev && find(usados.begin(), usados.end(), id) == usados.end()) 
                candidatos.push_back(id);
        }

        if(candidatos.empty()) { // Reset si se acaban las opciones de ese nivel
            for(auto const& [id, e] : storage) if(e.sev == sev) candidatos.push_back(id);
        }

        int selectedID = candidatos[rand() % candidatos.size()];
        guardarHistorial(usados, selectedID);

        string respuesta = storage[selectedID].txt;
        string accion = "none";

        // 5. MANEJO DE CRISIS
        if(sev == 9) {
            setContext("esperando_juego");
            respuesta = "He detectado una carga emocional muy fuerte en tus palabras. Como Diezus, me preocupas. ¿Te gustaría intentar distraerte con un juego ahora?";
            accion = "none"; // No dispara el juego hasta que el usuario diga SÍ (Coherencia)
        } else {
            setContext("normal");
        }

        return "{\"sev\": " + to_string(sev) + ", \"res\": \"" + respuesta + "\", \"act\": \"" + accion + "\"}";
    }
};

int main(int argc, char* argv[]) {
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(static_cast<unsigned int>(seed));
    DiezusEngine engine;
    if(argc > 1) cout << engine.analyze(argv[1]) << endl;
    return 0;
}