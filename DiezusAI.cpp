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

struct Entry { int id, sev; string txt; };

class DiezusEngine {
private:
    unordered_map<int, Entry> storage;
    vector<pair<string, int>> dict = {
        {"suicid",9},{"matar",9},{"morir",9},{"ayuda",9},{"daño",9},
        {"triste",0},{"mal",0},{"depre",0},{"llorar",0},
        {"odio",4},{"enojo",4},{"solo",6}
    };
    
    void setM(string f, string v) { ofstream o(f); o << v; }
    string getM(string f, string d) { ifstream i(f); string v; return (i >> v) ? v : d; }

public:
    DiezusEngine() {
        ifstream f("dataset.txt"); string l;
        while(getline(f, l)) {
            stringstream ss(l); string s_id, cat, s_sev, txt;
            if(getline(ss, s_id, '|') && getline(ss, cat, '|') && getline(ss, s_sev, '|') && getline(ss, txt))
                storage[stoi(s_id)] = {stoi(s_id), stoi(s_sev), txt};
        }
    }

    string analyze(string raw) {
        if(raw.empty()) return "{\"sev\":3,\"res\":\"Te escucho...\",\"act\":\"none\"}";
        
        string in = raw; for(char &c : in) c = tolower(c);
        string ctx = getM("contexto.txt", "normal");
        int sev = 3; // Por defecto es neutral para evitar errores

        // 1. IDENTIDAD (Hola, Quién eres, Propósito)
        if(in.find("hola") != string::npos) return "{\"sev\":3,\"res\":\"Hola. Soy Diezus, tu acompañante de IA. ¿Cómo estás?\",\"act\":\"none\"}";
        if(in.find("quien eres") != string::npos) return "{\"sev\":3,\"res\":\"Soy Diezus, una IA de soporte emocional.\",\"act\":\"none\"}";
        if(in.find("proposito") != string::npos) return "{\"sev\":3,\"res\":\"Mi propósito es escucharte y proteger tu bienestar.\",\"act\":\"none\"}";

        // 2. CONTEXTO SÍ/NO
        if(ctx == "juego") {
            if(in.find("si") != string::npos || in.find("bueno") != string::npos) {
                setM("contexto.txt", "normal"); setM("avisos.txt", "0");
                return "{\"sev\":9,\"res\":\"Protocolo aceptado. Iniciando juego...\",\"act\":\"trigger_games\"}";
            }
        }

        // 3. DETECCIÓN EMOCIONAL
        bool detectado = false;
        for(auto &d : dict) if(in.find(d.first) != string::npos) { sev = d.second; detectado = true; break; }
        
        // 4. SELECCIÓN DE FRASE SEGURA
        vector<int> cands;
        for(auto const& [id, e] : storage) if(e.sev == sev) cands.push_back(id);

        // Si no hay frases para ese nivel o no entendió nada, usa nivel 3 (Neutral)
        if(cands.empty()) {
            for(auto const& [id, e] : storage) if(e.sev == 3) cands.push_back(id);
        }

        // Si después de todo sigue vacío (dataset vacío), enviamos respuesta de emergencia
        if(cands.empty()) return "{\"sev\":3,\"res\":\"Entiendo lo que dices, cuéntame más.\",\"act\":\"none\"}";

        string res = storage[cands[rand() % cands.size()]].txt;

        // 5. LÓGICA DE AVISOS
        if(detectado && (sev == 9 || sev == 0)) {
            int w = stoi(getM("avisos.txt", "0")) + 1;
            setM("avisos.txt", to_string(w));
            if(w >= 3) {
                setM("contexto.txt", "juego");
                return "{\"sev\":9,\"res\":\"" + res + " Noto que sigues mal. ¿Quieres jugar?\",\"act\":\"none\"}";
            }
        } else { setM("avisos.txt", "0"); }

        setM("contexto.txt", "normal");
        return "{\"sev\":"+to_string(sev)+",\"res\":\""+res+"\",\"act\":\"none\"}";
    }
};

int main(int argc, char* argv[]) {
    srand(time(0));
    DiezusEngine e;
    if(argc > 1) cout << e.analyze(argv[1]) << endl;
    return 0;
}