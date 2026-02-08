#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

class DiezusAI {
private:
    // Guardamos el contenido completo para búsquedas más profundas
    map<int, string> dataset;
    vector<pair<string, int>> searchIndex; 

    string clean(string text) {
        transform(text.begin(), text.end(), text.begin(), ::tolower);
        // Eliminamos espacios extra al inicio/final
        text.erase(0, text.find_first_not_of(" \t\r\n"));
        text.erase(text.find_last_not_of(" \t\r\n") + 1);
        return text;
    }

    string escapeJSON(string text) {
        string escaped = "";
        for (char c : text) {
            if (c == '"') escaped += "\\\"";
            else if (c == '\\') escaped += "\\\\";
            else if (c == '\n') escaped += " "; // Evita saltos de línea en el JSON
            else escaped += c;
        }
        return escaped;
    }

public:
    DiezusAI() {
        ifstream ds("dataset.txt");
        string line;
        while (getline(ds, line)) {
            size_t pos = line.find("|");
            if (pos != string::npos) {
                try {
                    int id = stoi(line.substr(0, pos));
                    string content = line.substr(pos + 1);
                    dataset[id] = content;
                    // Guardamos la versión limpia para comparar
                    searchIndex.push_back({clean(content), id});
                } catch (...) { continue; } 
            }
        }
    }

    string process(string input) {
        if (input.empty()) return "{\"message\": \"...\", \"sentiment\": \"neutral\", \"action\": \"none\"}";
        
        string in = clean(input);
        string response = "No tengo un registro exacto, pero sigo aprendiendo de ti.";
        string sentiment = "neutral";
        string action = "none";
        int detectedID = -1;

        // BÚSQUEDA MEJORADA: Busca si el mensaje del usuario está contenido en alguna frase
        // O si alguna palabra clave del dataset está en el mensaje.
        for (auto const& item : searchIndex) {
            if (in.find(item.first) != string::npos || item.first.find(in) != string::npos) {
                detectedID = item.second;
                response = dataset[detectedID];
                break;
            }
        }

        // LÓGICA DE SENTIMIENTOS (Prioridad: Instrucciones de Diezus)
        if (detectedID == 9 || in.find("morir") != string::npos || in.find("suicidio") != string::npos) {
            sentiment = "critical";
            response = "DETENTE. No estas solo. Ve a jugar los juegos de mi amigo ahora mismo. Estoy aqui para ti.";
            action = "suggest_break"; 
        } else if (detectedID == 0 || detectedID == 6 || detectedID == 7) {
            sentiment = "warning"; 
        } else if (detectedID == 1 || detectedID == 3 || detectedID == 5) {
            sentiment = "friendly";
        }

        return "{\"message\": \"" + escapeJSON(response) + "\", \"sentiment\": \"" + sentiment + "\", \"action\": \"" + action + "\"}";
    }
};

int main(int argc, char* argv[]) {
    // Sincronización para Linux/Render
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    DiezusAI diezus;
    if (argc >= 2) {
        cout << diezus.process(argv[1]) << endl;
    } else {
        cout << "{\"message\": \"Hola, soy Diezus. El sistema esta listo.\", \"sentiment\": \"neutral\", \"action\": \"none\"}" << endl;
    }
    return 0;
}