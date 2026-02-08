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

    string clean(string text) {
        transform(text.begin(), text.end(), text.begin(), ::tolower);
        return text;
    }

    // FUNCIÓN NUEVA: Evita que las comillas rompan el JSON
    string escapeJSON(string text) {
        string escaped = "";
        for (char c : text) {
            if (c == '"') escaped += "\\\"";
            else if (c == '\\') escaped += "\\\\";
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
                    // Guardamos la clave de búsqueda (10 chars) y el contenido
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

        for (auto const& [key, data] : dataset) {
            if (in.find(key) != string::npos) {
                detectedID = data.first;
                response = data.second;
                break;
            }
        }

        // Lógica de sentimientos según tus instrucciones
        if (detectedID == 9 || in.find("morir") != string::npos || in.find("suicidio") != string::npos) {
            sentiment = "critical";
            response = "DETENTE. No estas solo. Ve a jugar los juegos de mi amigo ahora mismo.";
            action = "suggest_break"; 
        } else if (detectedID == 0 || detectedID == 6 || detectedID == 7) {
            sentiment = "warning"; 
        } else if (detectedID == 1 || detectedID == 3 || detectedID == 5) {
            sentiment = "friendly";
        }

        // Usamos escapeJSON para que el mensaje sea seguro para Node.js
        return "{\"message\": \"" + escapeJSON(response) + "\", \"sentiment\": \"" + sentiment + "\", \"action\": \"" + action + "\"}";
    }
};

int main(int argc, char* argv[]) {
    // IMPORTANTE: Para que no haya problemas con caracteres especiales en Linux/Render
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    DiezusAI diezus;
    if (argc >= 2) {
        // Procesamos el argumento que envía server.js
        cout << diezus.process(argv[1]) << endl;
    } else {
        cout << "{\"message\": \"Hola, soy Diezus.\", \"sentiment\": \"neutral\", \"action\": \"none\"}" << endl;
    }
    return 0;
}