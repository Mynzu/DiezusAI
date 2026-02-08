#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;

class DiezusAI {
private:
    map<int, string> dataset;
    vector<pair<string, int>> searchIndex;
    map<string, string> diccionarioEmocional;

    string clean(string text) {
        transform(text.begin(), text.end(), text.begin(), ::tolower);
        return text;
    }

    string escapeJSON(string text) {
        string escaped = "";
        for (char c : text) {
            if (c == '"') escaped += "\\\"";
            else if (c == '\\') escaped += "\\\\";
            else escaped += c;
        }
        return escaped;
    }

    void cargarDiccionario() {
        // POSITIVOS (Felicidad, Afecto, Compasión, Admiración, Alivio, Confianza, Amor)
        vector<string> pos = {
            "alegria", "felicidad", "dicha", "jubilo", "entusiasmo", "contento", "optimismo", "euforia", "gozo", "regocijo",
            "afecto", "amabilidad", "benevolencia", "solidaridad", "bondad", "cariño", "ternura", "generosidad", "integridad",
            "compasion", "empatia", "piedad", "sensibilidad", "comprension", "altruismo", "humanidad",
            "admiracion", "aprobacion", "estima", "honorabilidad", "agradecimiento", "alivio", "tranquilo", "calma", "serenidad", "armonia",
            "confianza", "valentia", "coraje", "determinacion", "fuerza", "seguridad", "autoestima", "resiliencia",
            "amor", "aprecio", "adoracion", "devocion", "pasion", "romance", "atraccion", "paz"
        };
        for(auto& p : pos) diccionarioEmocional[p] = "positivo";

        // ADVERTENCIA / TRISTEZA / DOLOR (Añoranza, Abandono, Nostalgia, Depresión)
        vector<string> adv = {
            "tristeza", "afliccion", "desanimo", "desmotivacion", "desasosiego", "añoranza", "anhelo", "esperanza", "apego",
            "nostalgia", "melancolia", "saudade", "recuerdo", "depresion", "vacio", "duelo", "derrota", "desaliento",
            "pesimismo", "negatividad", "desesperanza", "abandono", "ausencia", "desamparo", "desolacion", "soledad"
        };
        for(auto& p : adv) diccionarioEmocional[p] = "advertencia";

        // AGITADO / IRA / MOLESTIA (Resentimiento, Injusticia, Celos, Agravio)
        vector<string> agit = {
            "ira", "enojo", "furia", "rabia", "rebeldia", "indignacion", "resentimiento", "repudio", "rencor", "injusticia",
            "insatisfaccion", "celos", "envidia", "recelos", "sospecha", "agravio", "ofensa", "ultraje", "injuria", "desprecio",
            "abuso", "insulto", "agresion", "alteracion", "destruccion", "terquedad", "obstinacion", "rigidez"
        };
        for(auto& p : agit) diccionarioEmocional[p] = "agitado";

        // ABRUMADO / CANSANCIO / SALUD (Estrés, Ansiedad, Fatiga, Incapacidad)
        vector<string> abr = {
            "agobio", "angustia", "ansiedad", "estres", "presion", "sobrecarga", "tension", "fatiga", "agotamiento", "estres academico",
            "cansancio", "exhausto", "desgano", "abatimiento", "enfermedad", "dolor", "fiebre", "nauseas", "mareo", "malestar",
            "incapacidad", "ineptitud", "incompetencia", "inutilidad", "torpeza", "pereza", "flojera", "procastinacion", "insomnio"
        };
        for(auto& p : abr) diccionarioEmocional[p] = "abrumado";

        // CONFUNDIDO / SORPRESA (Duda, Incertidumbre, Desorientación)
        vector<string> conf = {
            "sorpresa", "asombro", "maravilla", "estupor", "incredulidad", "desconcierto", "impresion",
            "confusion", "duda", "desorientacion", "incertidumbre", "turbacion", "inquietud", "ambivalencia", "intriga", "curiosidad"
        };
        for(auto& p : conf) diccionarioEmocional[p] = "confundido";

        // CRÍTICO / PREOCUPANTE (Protocolo de Juego)
        vector<string> crit = {
            "muerte", "suicidio", "asesinato", "matarme", "acabar con todo", "morir", "espanto", "miedo", "terror", "panico", "fobia"
        };
        for(auto& p : crit) diccionarioEmocional[p] = "critico";
        
        // SITUACIONES / TRABAJO (Neutrales)
        vector<string> sit = {
            "examen", "clase", "escuela", "universidad", "profesor", "tarea", "estudio", "nota", "graduacion", "proyecto",
            "trabajo", "empleo", "oficina", "jefe", "salario", "negocio", "reunion"
        };
        for(auto& p : sit) {
            if(diccionarioEmocional.find(p) == diccionarioEmocional.end()) 
                diccionarioEmocional[p] = "neutral";
        }
    }

public:
    DiezusAI() {
        srand(time(0));
        cargarDiccionario();
        
        ifstream ds("dataset.txt");
        string line;
        while (getline(ds, line)) {
            size_t pos = line.find("|");
            if (pos != string::npos) {
                try {
                    int id = stoi(line.substr(0, pos));
                    string contenido = line.substr(pos + 1);
                    dataset[id] = contenido;
                    searchIndex.push_back({clean(contenido), id});
                } catch (...) { continue; }
            }
        }
    }

    string process(string input) {
        string in = clean(input);
        string respuesta = "Como Diezus, proceso tus palabras. Cuéntame más.";
        string sentimiento = "neutral";
        string accion = "none";
        int idDetectado = -1;

        // 1. BUSQUEDA EN DATASET (Prioridad: Frase exacta o palabra clave en dataset)
        for (auto const& item : searchIndex) {
            if (in.find(item.first) != string::npos) {
                idDetectado = item.second;
                respuesta = dataset[idDetectado];
                break;
            }
        }

        // 2. BUSQUEDA EN DICCIONARIO (Sentimiento por palabras sueltas de la lista)
        for (auto const& [palabra, tipo] : diccionarioEmocional) {
            if (in.find(palabra) != string::npos) {
                sentimiento = tipo;
                if (tipo == "critico" || idDetectado == 9) {
                    sentimiento = "critico";
                    accion = "sugerir_juego";
                    respuesta = "DETENTE. Como Diezus, detecto una situación de riesgo. Mi prioridad es tu integridad. No estás solo; ve a jugar ahora mismo.";
                }
                break; 
            }
        }

        // 3. SINCRONIZACIÓN FINAL CON IDS ESPECÍFICOS
        if (idDetectado == 0 || idDetectado == 6 || idDetectado == 7) sentimiento = "advertencia";
        if (idDetectado == 1 || idDetectado == 2 || idDetectado == 3 || idDetectado == 5) sentimiento = "positivo";
        if (idDetectado == 4) sentimiento = "agitado";
        if (idDetectado == 8) sentimiento = "confundido";

        return "{\"respuesta\": \"" + escapeJSON(respuesta) + "\", \"sentimiento\": \"" + sentimiento + "\", \"accion\": \"" + accion + "\"}";
    }
};

int main(int argc, char* argv[]) {
    DiezusAI diezus;
    if (argc >= 2) {
        cout << diezus.process(argv[1]) << endl;
    } else {
        cout << "{\"respuesta\": \"Soy Diezus. Estoy listo.\", \"sentimiento\": \"neutral\", \"accion\": \"none\"}" << endl;
    }
    return 0;
}