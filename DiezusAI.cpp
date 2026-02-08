#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <sstream>

using namespace std;

class DiezusAI {
private:
    map<int, string> dataset;
    map<string, int> keywordIndex; // Nuevo: Mapa de palabras clave -> ID
    map<string, string> diccionarioEmocional;

    string clean(string text) {
        // Eliminar puntuación básica para mejorar la búsqueda
        string result = "";
        for (char c : text) {
            if (!ispunct(c)) result += tolower(c);
        }
        return result;
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
        // [Tus listas completas de palabras positivas, advertencia, etc. van aquí]
        // (He mantenido la estructura que ya definimos arriba)
        vector<string> pos = {"alegria", "felicidad", "amor", "paz", "bien", "genial"}; // ... etc
        for(auto& p : pos) diccionarioEmocional[p] = "positivo";

        vector<string> crit = {"muerte", "suicidio", "matarme", "morir", "terror"};
        for(auto& p : crit) diccionarioEmocional[p] = "critico";
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
                int id = stoi(line.substr(0, pos));
                string contenido = clean(line.substr(pos + 1));
                dataset[id] = line.substr(pos + 1);

                // Indexamos cada palabra del dataset para que la búsqueda sea flexible
                stringstream ss(contenido);
                string word;
                while (ss >> word) {
                    if (word.length() > 3) keywordIndex[word] = id; 
                }
            }
        }
    }

    string process(string input) {
        string in = clean(input);
        string respuesta = "Entiendo lo que dices. Como Diezus, estoy aquí para escucharte.";
        string sentimiento = "neutral";
        string accion = "none";
        int idDetectado = -1;

        stringstream ss(in);
        string word;
        
        // ANALIZAR PALABRA POR PALABRA
        while (ss >> word) {
            // 1. ¿La palabra está vinculada a un ID del dataset?
            if (keywordIndex.count(word)) {
                idDetectado = keywordIndex[word];
                respuesta = dataset[idDetectado];
            }

            // 2. ¿La palabra tiene un sentimiento asignado?
            if (diccionarioEmocional.count(word)) {
                sentimiento = diccionarioEmocional[word];
            }
        }

        // 3. PROTOCOLO DE SEGURIDAD (Si el sentimiento es crítico o ID 9)
        if (sentimiento == "critico" || idDetectado == 9) {
            sentimiento = "critico";
            accion = "sugerir_juego";
            respuesta = "DETENTE. Como Diezus, detecto una situación de alto riesgo. Tu integridad es lo primero. Ve a jugar ahora mismo para despejar tu mente.";
        }

        // 4. Sincronización de sentimiento por ID (Prioridad sobre la palabra suelta)
        if (idDetectado != -1) {
            if (idDetectado == 0 || idDetectado == 6 || idDetectado == 7) sentimiento = "advertencia";
            else if (idDetectado == 1 || idDetectado == 2 || idDetectado == 3 || idDetectado == 5) sentimiento = "positivo";
            else if (idDetectado == 4) sentimiento = "agitado";
            else if (idDetectado == 8) sentimiento = "confundido";
        }

        return "{\"respuesta\": \"" + escapeJSON(respuesta) + "\", \"sentimiento\": \"" + sentimiento + "\", \"accion\": \"" + accion + "\"}";
    }
};

int main(int argc, char* argv[]) {
    DiezusAI diezus;
    if (argc >= 2) cout << diezus.process(argv[1]) << endl;
    return 0;
}