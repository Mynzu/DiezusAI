
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <random>
#include <napi.h>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <set>

struct VectorHasher {
    size_t operator()(const std::vector<std::string>& v) const {
        size_t seed = 0;
        for (const std::string& s : v) seed ^= std::hash<std::string>{}(s) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

typedef std::vector<std::string> EstadoMental;
typedef std::unordered_map<EstadoMental, std::unordered_map<std::string, int>, VectorHasher> MapaCerebro;

std::mt19937 motor_global(static_cast<unsigned int>(std::time(nullptr)));

class CerebroGenerativo {
private:
    std::unordered_map<int, MapaCerebro> cerebros;
public:
    void aprender(std::string frase, int tipo) {
        std::stringstream ss(frase);
        std::vector<std::string> pal;
        std::string p;
        while (ss >> p) pal.push_back(p);
        if (pal.size() < 2) return;
        for (size_t i = 0; i < pal.size(); ++i) {
            if (i + 2 < pal.size()) cerebros[tipo][{pal[i], pal[i+1]}][pal[i+2]] += 100;
            if (i + 1 < pal.size()) cerebros[tipo][{pal[i]}][pal[i+1]] += 1;
        }
    }

    bool tienePalabra(std::string p, int t) { return cerebros[t].count({p}) > 0; }

    std::string generar(std::string semilla, int longitud_max, int tipo) {
        auto& mapa = cerebros[tipo];
        if (mapa.count({semilla}) == 0) return "";

        EstadoMental actual = {semilla};
        std::string resultado = semilla;
        
        for (int i = 0; i < longitud_max; ++i) {
            EstadoMental ctx;
            if (actual.size() >= 2) ctx = {actual[actual.size()-2], actual.back()};
            else ctx = {actual.back()};

            if (mapa.count(ctx)) {
                auto& opciones = mapa[ctx];
                std::vector<std::pair<std::string, int>> candidatas(opciones.begin(), opciones.end());
                // Mezclamos un poco para que no sea 100% estático
                std::shuffle(candidatas.begin(), candidatas.end(), motor_global);
                
                std::string mejor = candidatas[0].first;
                int max_f = candidatas[0].second;
                for(auto const& c : candidatas) {
                    if (c.second > max_f) { max_f = c.second; mejor = c.first; }
                }
                resultado += " " + mejor;
                actual.push_back(mejor);
                if (mejor.find(".") != std::string::npos) break;
            } else break;
        }
        return resultado;
    }
};

CerebroGenerativo miIA;
bool cargado = false;

std::string limpiar(std::string t) {
    std::transform(t.begin(), t.end(), t.begin(), ::tolower);
    std::string r = "";
    for(unsigned char c : t) if(isalnum(c) || isspace(c) || c == '.') r += c;
    return r;
}

void InicializarIA() {
    if (cargado) return;
    std::ifstream file("dataset.txt");
    std::string linea;
    while (getline(file, linea)) {
        size_t pos = linea.find('|');
        if (pos != std::string::npos) {
            try {
                int tipo = std::stoi(linea.substr(0, pos));
                miIA.aprender(limpiar(linea.substr(pos + 1)), tipo);
            } catch (...) { continue; }
        }
    }
    cargado = true;
}

Napi::String ChatWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    InicializarIA();
    std::string entrada = limpiar(info[0].As<Napi::String>().Utf8Value());
    
    int cod = 1;
    if (entrada.find("morir") != std::string::npos || entrada.find("suicid") != std::string::npos) cod = 9;
    else if (entrada.find("solo") != std::string::npos || entrada.find("mal") != std::string::npos) cod = 0;

    // Banco de intros dinámicas para estados críticos
    std::vector<std::string> intros_apoyo = {
        " Entiendo que es un momento dificil. ",
        " No estas solo en esto, te escucho. ",
        " Siento mucho que pases por esto. ",
        " Estoy aqui contigo. "
    };

    std::stringstream ss(entrada);
    std::string p, semilla = "";
    while(ss >> p) { if(miIA.tienePalabra(p, cod)) { semilla = p; break; } }
    
    std::string respuesta_ia = "";
    if (semilla != "") respuesta_ia = miIA.generar(semilla, 8, cod);

    std::string respuesta_final;
    if (cod == 9 || cod == 0) {
        std::uniform_int_distribution<int> dist(0, intros_apoyo.size() - 1);
        respuesta_final = intros_apoyo[dist(motor_global)] + respuesta_ia;
        respuesta_final += "\n\n¿Por que no pruebas los juegos?. Te ayudaran a distraerte.";
    } else {
        respuesta_final = (respuesta_ia == "" ? "Cuentame mas sobre eso." : respuesta_ia);
    }

    return Napi::String::New(env, respuesta_final);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("chat", Napi::Function::New(env, ChatWrapped));
    return exports;
}
NODE_API_MODULE(Diezus, Init)