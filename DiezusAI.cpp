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
        if(h.size() > 25) h.erase(h.begin());
        ofstream f(histPath);
        for(int id : h) f << id << " ";
    }

    void setContext(string s) { ofstream f(contextPath); f << s; }
    string getContext() { 
        ifstream f(contextPath); 
        string s; 
        if(!(f >> s)) return "normal"; 
        return s; 
    }

public:
    DiezusEngine() {
        // Diccionario de detección de palabras clave
        diccionarioCritico = {
            {"suicid", 9}, {"matar", 9}, {"morir", 9}, {"ayuda", 9}, {"daño", 9},
            {"triste", 0}, {"mal", 0}, {"depre", 0}, {"llorar", 0},
            {"feliz", 1}, {"alegre", 1}, {"bien", 1},
            {"odio", 4}, {"enojo", 4}, {"solo", 6}
        };

        // Carga del Dataset (Tus 1700 frases)
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
        int sev = 3; // Neutro por defecto

        // 1. IDENTIDAD Y PROPÓSITO
        if(in == "hola" || in == "buenos dias" || in == "buenas noches") {
            setContext("normal");
            return "{\"sev\": 3, \"res\": \"Hola, soy Diezus. Estoy aquí para acompañarte. ¿Cómo te sientes en este momento?\", \"act\": \"none\"}";
        }
        if(in.find("quien eres") != string::npos || in.find("tu nombre") != string::npos) {
            setContext("normal");
            return "{\"sev\": 3, \"res\": \"Soy Diezus, una inteligencia diseñada para el soporte emocional y la prevención. Mi nombre es un recordatorio de que siempre hay alguien escuchando.\", \"act\": \"none\"}";
        }
        if(in.find("proposito") != string::npos || in.find("para que sirves") != string::npos) {
            setContext("normal");
            return "{\"sev\": 3, \"res\": \"Mi propósito es procesar tus emociones y ofrecerte un espacio seguro. Si detecto que estás en riesgo, te sugeriré actividades para proteger tu bienestar.\", \"act\": \"none\"}";
        }

        // 2. LÓGICA DE CONTEXTO (Respuesta a la pregunta de juegos)
        if(ctx == "esperando_juego") {
            if(in.find("si") != string::npos || in.find("bueno") != string::npos || in.find("claro") != string::npos || in.find("vale") != string::npos) {
                setContext("normal");
                return "{\"sev\": 9, \"res\": \"Me alegra que aceptes. Iniciando zona de relax. ¡Disfruta el juego!\", \"act\": \"trigger_games\"}";
            } else if(in.find("no") != string::npos) {
                setContext("normal");
                return "{\"sev\": 3, \"res\": \"Entiendo. Respeto tu espacio. Aquí seguiré si necesitas hablar de nuevo.\", \"act\": \"none\"}";
            }
        }

        // 3. ANÁLISIS DE SENTIMIENTOS
        for(auto const& [palabra, nivel] : diccionarioCritico) {
            if(in.find(palabra) != string::npos) { sev = nivel; break; }
        }

        // 4. SELECCIÓN DE RESPUESTA VARIADA (Dataset de 1700 frases)
        vector<int> usados = cargarHistorial();
        vector<int> candidatos;
        for(auto const& [id, e] : storage) {
            if(e.sev == sev && find(usados.begin(), usados.end(), id) == usados.end()) 
                candidatos.push_back(id);
        }

        // Si se agotan las frases nuevas, reiniciar historial para ese nivel
        if(candidatos.empty()) {
            for(auto const& [id, e] : storage) if(e.sev == sev) candidatos.push_back(id);
        }

        int selectedID = candidatos[rand() % candidatos.size()];
        guardarHistorial(usados, selectedID);

        string respuestaBase = storage[selectedID].txt;
        string respuestaFinal = respuestaBase;
        string accion = "none";

        // 5. MANEJO DE CRISIS (NIVEL 9)
        if(sev == 9) {
            setContext("esperando_juego");
            respuestaFinal = respuestaBase + " Noto que estás pasando por algo muy difícil. Como Diezus, me preocupas. ¿Te gustaría distraerte un poco con un juego?";
        } else {
            setContext("normal");
        }

        // Registro de telemetría (Log semanal)
        ofstream log(logPath, ios::app);
        if(log) log << time(0) << "|" << sev << endl;

        return "{\"sev\": " + to_string(sev) + ", \"res\": \"" + respuestaFinal + "\", \"act\": \"" + accion + "\"}";
    }
};

int main(int argc, char* argv[]) {
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(static_cast<unsigned int>(seed));
    
    DiezusEngine engine;
    if(argc > 1) {
        cout << engine.analyze(argv[1]) << endl;
    } else {
        cout << "{\"status\": \"active\", \"identity\": \"Diezus\"}" << endl;
    }
    return 0;
}