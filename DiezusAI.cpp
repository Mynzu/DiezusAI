#include <napi.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <random>
#include <fstream>
#include <ctime>
#include <algorithm>

struct VectorHasher {
    size_t operator()(const std::vector<std::string>& v) const {
        size_t seed = 0;
        for (const std::string& s : v) {
            seed ^= std::hash<std::string>{}(s) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

typedef std::vector<std::string> Estado;
typedef std::unordered_map<Estado, std::unordered_map<std::string, int>, VectorHasher> MapaCerebro;

class DiezusEngine {
private:
    std::unordered_map<int, MapaCerebro> cerebros;
    std::mt19937 motor{static_cast<unsigned int>(std::time(nullptr))};

public:
    // Función: APRENDER (No se quitó, se mejoró con pesos de contexto)
    void aprender(std::string frase, int tipo) {
        std::stringstream ss(frase);
        std::string p;
        std::vector<std::string> words;
        while (ss >> p) words.push_back(p);
        if (words.size() < 1) return;

        words.push_back("[END]"); 

        for (size_t i = 0; i < words.size(); ++i) {
            if (i + 1 < words.size()) cerebros[tipo][{words[i]}][words[i+1]] += 5;
            if (i + 2 < words.size()) cerebros[tipo][{words[i], words[i+1]}][words[i+2]] += 25;
            if (i + 3 < words.size()) cerebros[tipo][{words[i], words[i+1], words[i+2]}][words[i+3]] += 60;
        }
    }

    // Función: GENERAR (Ahora termina frases correctamente)
    std::string generar(std::string semilla, int tipo, int limite = 15) {
        if (cerebros[tipo].empty()) return "Aquí estoy, hablemos.";

        if (semilla == "" || cerebros[tipo].count({semilla}) == 0) {
            auto it = cerebros[tipo].begin();
            if (it == cerebros[tipo].end()) return "Dime más.";
            std::advance(it, motor() % cerebros[tipo].size());
            semilla = it->first[0];
        }

        std::vector<std::string> actual = {semilla};
        std::string resultado = semilla;

        for (int i = 0; i < limite; ++i) {
            Estado ctx;
            if (actual.size() >= 2) ctx = {actual[actual.size()-2], actual.back()};
            else ctx = {actual.back()};

            if (cerebros[tipo].count(ctx) == 0) ctx = {actual.back()};
            
            if (cerebros[tipo].count(ctx)) {
                auto& opciones = cerebros[tipo][ctx];
                int total = 0;
                for (auto const& [pal, frec] : opciones) total += frec;
                
                std::uniform_int_distribution<int> dist(0, total - 1);
                int dintel = dist(motor);
                int suma = 0;
                for (auto const& [pal, frec] : opciones) {
                    suma += frec;
                    if (suma > dintel) {
                        if (pal == "[END]") return resultado + ".";
                        resultado += " " + pal;
                        actual.push_back(pal);
                        break;
                    }
                }
            } else break;
        }
        return resultado + ".";
    }

    // Función: GUARDAR MEMORIA (A petición tuya, guarda en archivo)
    void guardarMemoria(std::string filename) {
        std::ofstream file(filename);
        if (!file.is_open()) return;
        for (auto const& [tipo, mapa] : cerebros) {
            for (auto const& [ctx, subs] : mapa) {
                file << tipo << "|";
                for (const auto& s : ctx) file << s << " ";
                file << "-> ";
                for (auto const& [sig, f] : subs) file << sig << ":" << f << " ";
                file << "\n";
            }
        }
        file.close();
    }

    bool conoce(std::string p, int t) { return cerebros[t].count({p}) > 0; }
};

DiezusEngine diezus;
int crisis_counter = 0;

std::string limpiar(std::string t) {
    std::transform(t.begin(), t.end(), t.begin(), ::tolower);
    t.erase(std::remove_if(t.begin(), t.end(), [](char c) {
        return !isalnum(c) && !isspace(c);
    }), t.end());
    return t;
}

void CargarDataset() {
    std::ifstream file("dataset.txt");
    std::string linea;
    while (std::getline(file, linea)) {
        size_t pos = linea.find('|');
        if (pos != std::string::npos) {
            try {
                int tipo = std::stoi(linea.substr(0, pos));
                diezus.aprender(limpiar(linea.substr(pos + 1)), tipo);
            } catch(...) {}
        }
    }
}

// Función principal: CHAT (Contiene los 10 Niveles y Detección de Crisis)
Napi::String Chat(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string input = limpiar(info[0].As<Napi::String>().Utf8Value());
    
    int modo = 1; 
    bool alterado = false;

    // --- 10 NIVELES DE DETECCIÓN ---
    if (input.find("morir") != std::string::npos || input.find("suicid") != std::string::npos) {
        modo = 9; alterado = true;
    } 
    else if (input.find("miedo") != std::string::npos || input.find("asusta") != std::string::npos) {
        modo = 7;
    }
    else if (input.find("solo") != std::string::npos || input.find("vacio") != std::string::npos) {
        modo = 6; alterado = true;
    }
    else if (input.find("odio") != std::string::npos || input.find("enojo") != std::string::npos) {
        modo = 4;
    }
    else if (input.find("gracias") != std::string::npos) {
        modo = 3;
    }
    else if (input.find("pude") != std::string::npos || input.find("logre") != std::string::npos) {
        modo = 5;
    }
    else if (input.find("entiendo") != std::string::npos) {
        modo = 8;
    }
    else if (input.find("triste") != std::string::npos || input.find("duele") != std::string::npos || input.find("mal") != std::string::npos) {
        modo = 0; alterado = true;
    }

    // Lógica de Crisis (Detección de usuario alterado)
    if (alterado) crisis_counter++;
    else {
        if (crisis_counter > 0) crisis_counter--;
        diezus.aprender(input, modo); 
    }

    std::stringstream ss(input);
    std::string p, semilla = "";
    while (ss >> p) { 
        if (diezus.conoce(p, modo)) { semilla = p; break; } 
    }

    std::string respuesta = diezus.generar(semilla, modo);
    
    // Función: DISPARADOR DE JUEGOS (Cuando estás deprimido)
    if (alterado && crisis_counter >= 3) {
        respuesta = "Oye, te noto bastante mal. Ve a jugar un rato, ¿vale?";
        diezus.guardarMemoria("memoria_diezus.txt");
        crisis_counter = 0;
    }

    return Napi::String::New(env, respuesta);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    CargarDataset();
    exports.Set("chat", Napi::Function::New(env, Chat));
    return exports;
}

NODE_API_MODULE(Diezus, Init)