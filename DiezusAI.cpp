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

// Estructura para manejar los datos del dataset de 1700 frases
struct Entry { 
    int id; 
    int sev; 
    string txt; 
};

class DiezusEngine {
private:
    unordered_map<int, Entry> storage;
    vector<pair<string, int>> diccionario;
    string contextPath = "contexto.txt";
    string histPath = "historial_ids.txt";
    string warnPath = "avisos.txt";

    // Limpieza de texto para que la IA entienda sin importar puntos o mayúsculas
    string clean(string t) {
        string r = "";
        for(char c : t) if(!ispunct(c)) r += tolower(c);
        return r;
    }

    // Funciones de Persistencia (La "Memoria" de la IA)
    int getWarnings() { ifstream f(warnPath); int c = 0; f >> c; return c; }
    void setWarnings(int c) { ofstream f(warnPath); f << c; }
    void setContext(string s) { ofstream f(contextPath); f << s; }
    string getContext() { ifstream f(contextPath); string s; if(!(f >> s)) return "normal"; return s; }

    // Sistema para que no repita frases de las 1700
    vector<int> cargarHistorial() {
        vector<int> h; ifstream f(histPath); int id;
        while(f >> id) h.push_back(id);
        return h;
    }

    void guardarHistorial(vector<int> h, int nuevoId) {
        h.push_back(nuevoId);
        if(h.size() > 50) h.erase(h.begin()); // Recordar las últimas 50 frases para no repetirlas
        ofstream f(histPath);
        for(int id : h) f << id << " ";
    }

public:
    DiezusEngine() {
        // Mapeo semántico para el análisis de sentimiento
        diccionario = {
            {"suicid", 9}, {"matar", 9}, {"morir", 9}, {"ayuda", 9}, {"daño", 9},
            {"triste", 0}, {"mal", 0}, {"depre", 0}, {"llorar", 0},
            {"feliz", 1}, {"alegre", 1}, {"bien", 1},
            {"odio", 4}, {"enojo", 4}, {"rabia", 4},
            {"solo", 6}, {"soledad", 6}
        };

        // Carga robusta del dataset de 1700 frases
        ifstream f("dataset.txt");
        string l;
        while(getline(f, l)) {
            stringstream ss(l); string s_id, cat, s_sev, txt;
            if(getline(ss, s_id, '|') && getline(ss, cat, '|') && getline(ss, s_sev, '|') && getline(ss, txt)) {
                try {
                    storage[stoi(s_id)] = {stoi(s_id), stoi(s_sev), txt};
                } catch(...) { continue; }
            }
        }
    }

    string analyze(string raw) {
        string in = clean(raw);
        string ctx = getContext();
        int sev = 3; // Neutro

        // --- 1. CAPA DE IDENTIDAD (HOLA, QUIÉN ERES, PROPÓSITO) ---
        if(in == "hola" || in == "buenos dias" || in == "buenas noches") {
            setContext("normal");
            return "{\"sev\":3,\"res\":\"Hola. Soy Diezus, tu acompañante de IA. ¿Cómo te encuentras hoy?\",\"act\":\"none\"}";
        }
        if(in.find("quien eres") != string::npos || in.find("tu nombre") != string::npos) {
            setContext("normal");
            return "{\"sev\":3,\"res\":\"Soy Diezus, una Inteligencia Artificial diseñada para el soporte emocional y la prevención de crisis.\",\"act\":\"none\"}";
        }
        if(in.find("proposito") != string::npos || in.find("para que sirves") != string::npos) {
            setContext("normal");
            return "{\"sev\":3,\"res\":\"Mi propósito es escucharte y analizar tu estado emocional para ofrecerte apoyo y distracción en momentos difíciles.\",\"act\":\"none\"}";
        }

        // --- 2. CAPA DE CONTEXTO (SÍ/NO A JUEGOS) ---
        if(ctx == "esperando_juego") {
            if(in.find("si") != string::npos || in.find("claro") != string::npos || in.find("bueno") != string::npos) {
                setContext("normal"); setWarnings(0);
                return "{\"sev\":9,\"res\":\"Protocolo aceptado. Abriendo zona de juegos para despejar tu mente.\",\"act\":\"trigger_games\"}";
            } else if(in.find("no") != string::npos) {
                setContext("normal"); setWarnings(0);
                return "{\"sev\":3,\"res\":\"Entiendo perfectamente. Aquí estaré para cuando decidas hablar de nuevo.\",\"act\":\"none\"}";
            }
        }

        // --- 3. ANÁLISIS SEMÁNTICO ---
        for(auto const& d : diccionario) {
            if(in.find(d.first) != string::npos) { sev = d.second; break; }
        }

        // --- 4. SELECCIÓN DE RESPUESTA (ANTI-REPETICIÓN) ---
        vector<int> usados = cargarHistorial();
        vector<int> candidatos;
        for(auto const& [id, e] : storage) {
            if(e.sev == sev && find(usados.begin(), usados.end(), id) == usados.end()) 
                candidatos.push_back(id);
        }

        if(candidatos.empty()) { // Si se acaban, reseteamos el historial del nivel
            for(auto const& [id, e] : storage) if(e.sev == sev) candidatos.push_back(id);
        }

        int selectedID = candidatos[rand() % candidatos.size()];
        guardarHistorial(usados, selectedID);
        string respuesta = storage[selectedID].txt;

        // --- 5. LÓGICA DE INTERVENCIÓN (3 AVISOS) ---
        if(sev == 9 || sev == 0) {
            int w = getWarnings() + 1;
            setWarnings(w);
            if(w >= 3) {
                setContext("esperando_juego");
                return "{\"sev\":9,\"res\":\"" + respuesta + " Noto que el malestar persiste. ¿Te gustaría intentar distraerte con un juego?\",\"act\":\"none\"}";
            }
        } else {
            setWarnings(0);
        }

        setContext("normal");
        return "{\"sev\":"+to_string(sev)+",\"res\":\""+respuesta+"\",\"act\":\"none\"}";
    }
};

int main(int argc, char* argv[]) {
    // Semilla de nanosegundos para máxima aleatoriedad
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(static_cast<unsigned int>(seed));

    DiezusEngine diezus;
    if(argc > 1) {
        cout << diezus.analyze(argv[1]) << endl;
    } else {
        cout << "{\"status\":\"active\",\"name\":\"Diezus\"}" << endl;
    }
    return 0;
}