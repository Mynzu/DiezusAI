#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>

using namespace std;

struct Entry { int id, sev; string txt; };

class DiezusEngine {
private:
    unordered_map<int, Entry> storage;
    // Diccionario extendido para detectar sentimientos en frases naturales
    vector<pair<string, int>> semanticMap = {
        {"suicid", 9}, {"morir", 9}, {"matar", 9}, {"fin", 9}, {"quitarme", 9},
        {"dificil", 0}, {"triste", 0}, {"mal", 0}, {"llorar", 0}, {"cansado", 0},
        {"odio", 4}, {"enojo", 4}, {"furia", 4}, {"solo", 6}, {"soledad", 6}
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
        string in = raw; for(char &c : in) c = tolower(c);
        string ctx = getM("contexto.txt", "normal");
        int sev = 3; 

        // 1. GESTIÓN DE IDENTIDAD (Lo que Diezus ES)
        if(in.find("hola") != string::npos) return "{\"sev\":3,\"res\":\"Hola. Soy Diezus. ¿En qué puedo apoyarte?\",\"act\":\"none\"}";
        if(in.find("quien eres") != string::npos) return "{\"sev\":3,\"res\":\"Soy Diezus, una IA de soporte emocional diseñada para escucharte.\",\"act\":\"none\"}";
        if(in.find("proposito") != string::npos) return "{\"sev\":3,\"res\":\"Mi propósito es ser tu refugio y ayudarte a encontrar calma.\",\"act\":\"none\"}";

        // 2. LÓGICA DE CONTEXTO (Respuesta al juego)
        if(ctx == "juego") {
            if(in.find("si") != string::npos || in.find("claro") != string::npos || in.find("bueno") != string::npos) {
                setM("contexto.txt", "normal"); setM("avisos.txt", "0");
                return "{\"sev\":9,\"res\":\"Iniciando protocolo de distracción. Vamos al juego.\",\"act\":\"trigger_games\"}";
            }
        }

        // 3. ANÁLISIS SEMÁNTICO (Aquí deja de repetir palabras)
        // Buscamos la palabra con MAYOR severidad en la frase del usuario
        int maxSevFound = -1;
        for(auto &d : semanticMap) {
            if(in.find(d.first) != string::npos) {
                if(d.second > maxSevFound) maxSevFound = d.second;
            }
        }
        if(maxSevFound != -1) sev = maxSevFound;

        // 4. SELECCIÓN DINÁMICA DE TUS 1700 FRASES
        vector<int> ids;
        for(auto const& [id, e] : storage) if(e.sev == sev) ids.push_back(id);
        
        // Si no detectó nada específico, usamos una frase neutral (Nivel 3)
        if(ids.empty()) {
            for(auto const& [id, e] : storage) if(e.sev == 3) ids.push_back(id);
        }

        string res = storage[ids[rand() % ids.size()]].txt;

        // 5. LÓGICA DE PERSISTENCIA (No saltar al juego de inmediato)
        if(sev == 9 || sev == 0) {
            int w = stoi(getM("avisos.txt", "0")) + 1;
            setM("avisos.txt", to_string(w));
            if(w >= 2) { // Bajamos a 2 avisos para que sea más reactivo
                setM("contexto.txt", "juego");
                return "{\"sev\":9,\"res\":\"" + res + " Noto que el sentimiento persiste. ¿Te gustaría distraerte con un juego?\",\"act\":\"none\"}";
            }
        } else setM("avisos.txt", "0");

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