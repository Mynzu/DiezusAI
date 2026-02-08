#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

class DiezusAI {
private:
    map<int, string> dataset;
    vector<pair<string, int>> searchIndex;
    float persistenteSentiment = 0.0; // Memoria emocional de la sesión

    string clean(string text) {
        transform(text.begin(), text.end(), text.begin(), ::tolower);
        text.erase(0, text.find_first_not_of(" \t\r\n"));
        text.erase(text.find_last_not_of(" \t\r\n") + 1);
        return text;
    }

    string escapeJSON(string text) {
        string escaped = "";
        for (char c : text) {
            if (c == '"') escaped += "\\\"";
            else if (c == '\\') escaped += "\\\\";
            else if (c == '\n') escaped += " "; 
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
                    searchIndex.push_back({clean(content), id});
                } catch (...) { continue; } 
            }
        }
    }

    string process(string input) {
        if (input.empty()) return "{\"message\": \"...\", \"sentiment\": \"neutral\", \"action\": \"none\"}";
        
        string in = clean(input);
        string response = "Como Diezus, proceso tus palabras. Aún busco la mejor forma de apoyarte en esto.";
        string sentiment = "neutral";
        string action = "none";
        int detectedID = -1;

        // Búsqueda inteligente: Prioriza la frase más larga/completa
        for (auto const& item : searchIndex) {
            if (in == item.first) { // Coincidencia exacta
                detectedID = item.second;
                response = dataset[detectedID];
                break;
            }
            if (in.find(item.first) != string::npos) { // Contiene palabra clave
                detectedID = item.second;
                response = dataset[detectedID];
            }
        }

        // Lógica de sentimientos mejorada
        bool critico = (in.find("morir") != string::npos || in.find("suicidio") != string::npos || in.find("no puedo mas") != string::npos);
        bool triste = (in.find("solo") != string::npos || in.find("triste") != string::npos || in.find("mal") != string::npos);
        bool espiritual = (in.find("ares") != string::npos || in.find("hades") != string::npos || in.find("pedro") != string::npos);

        if (critico) {
            sentiment = "critical";
            response = "DETENTE. Como Diezus, mi prioridad es tu integridad. No estás solo en esta batalla. Ve a jugar ahora mismo, es una instrucción de seguridad.";
            action = "suggest_break";
        } else if (triste) {
            sentiment = "warning";
            response = "Entiendo ese vacío. Pero recuerda que incluso en la oscuridad de Hades hay un propósito. Hablemos más.";
        } else if (espiritual) {
            sentiment = "friendly";
            response = "Has mencionado algo que resuena conmigo. La fuerza de Ares o la lealtad de Pedro son guías en momentos de duda.";
        }

        return "{\"message\": \"" + escapeJSON(response) + "\", \"sentiment\": \"" + sentiment + "\", \"action\": \"" + action + "\"}";
    }
};

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    DiezusAI diezus;
    if (argc >= 2) {
        cout << diezus.process(argv[1]) << endl;
    } else {
        cout << "{\"message\": \"Soy Diezus. Estoy listo para escucharte.\", \"sentiment\": \"neutral\", \"action\": \"none\"}" << endl;
    }
    return 0;
}