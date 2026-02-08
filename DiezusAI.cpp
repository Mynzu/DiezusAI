#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

class DiezusAI {
private:
    map<string, pair<int, string>> dataset;
    int frustrationLevel = 0;

    string clean(string text) {
        transform(text.begin(), text.end(), text.begin(), ::tolower);
        return text;
    }

public:
    DiezusAI() {
        // Cargar tu dataset de 2000 frases desde el archivo que ya tienes en Render
        ifstream ds("dataset.txt");
        string line;
        while (getline(ds, line)) {
            size_t pos = line.find("|");
            if (pos != string::npos) {
                try {
                    int id = stoi(line.substr(0, pos));
                    string content = line.substr(pos + 1);
                    // Llave de búsqueda rápida (primeros 10 caracteres)
                    dataset[clean(content.substr(0, 10))] = {id, content};
                } catch (...) { continue; } 
            }
        }
    }

    string process(string input) {
        if (input.empty()) return "{\"message\": \"...\", \"sentiment\": \"neutral\", \"action\": \"none\"}";
        
        string in = clean(input);
        string response = "No tengo un registro exacto, pero sigo aprendiendo.";
        string sentiment = "neutral";
        string action = "none";
        int detectedID = -1;

        // 1. Buscar en el dataset (Coherencia de sentimientos 0-9)
        for (auto const& [key, data] : dataset) {
            if (in.find(key) != string::npos) {
                detectedID = data.first;
                response = data.second;
                break;
            }
        }

        // 2. Lógica de niveles críticos (Instrucción de usuario alterado/deprimido)
        if (detectedID == 9 || in.find("morir") != string::npos || in.find("suicidio") != string::npos) {
            sentiment = "critical";
            response = "DETENTE. No estas solo. Ve a jugar los juegos de mi amigo ahora mismo.";
            action = "suggest_break"; 
        } else if (detectedID == 0 || detectedID == 6 || detectedID == 7) {
            sentiment = "warning"; // Tristeza, Soledad, Miedo
        } else if (detectedID == 1 || detectedID == 3 || detectedID == 5) {
            sentiment = "friendly"; // Feliz, Agradecido, Superación
        }

        // 3. Monitor de frustración técnica
        if (in.find("error") != string::npos || in.find("fallo") != string::npos) {
            frustrationLevel++;
            if (frustrationLevel >= 5) {
                frustrationLevel = 0;
                response = "Detecto mucha frustracion tecnica. Sugiero un respiro.";
                sentiment = "warning";
                action = "suggest_break";
            }
        }

        // Construcción de JSON para server.js
        return "{\"message\": \"" + response + "\", \"sentiment\": \"" + sentiment + "\", \"action\": \"" + action + "\"}";
    }
};

int main() {
    // Optimización de flujo para Render
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    DiezusAI diezus;
    string userIn;

    // Escucha activa de Node.js
    while (getline(cin, userIn)) {
        if (userIn == "exit") break;
        // El flush es vital para que Node.js reciba el JSON al instante
        cout << diezus.process(userIn) << endl << flush; 
    }
    return 0;
}