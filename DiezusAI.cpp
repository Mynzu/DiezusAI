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
    
    // Respuestas dinámicas de Pedro para cuando no hay ID detectado
    vector<string> pedroThoughts = {
        "Como Pedro en la barca, a veces sentimos que nos hundimos, pero solo hay que pedir ayuda.",
        "Te escucho con seriedad. La lealtad a uno mismo es el primer paso para estar bien.",
        "Incluso cuando Pedro negó lo que amaba, tuvo la oportunidad de redimirse. Cuéntame más.",
        "Estoy procesando tu mensaje. No te dejaré solo en esto."
    };

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
        srand(time(0));
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
        string response = pedroThoughts[rand() % pedroThoughts.size()];
        string sentiment = "neutral";
        string action = "none";
        int detectedID = -1;

        // Búsqueda por coincidencia
        for (auto const& item : searchIndex) {
            if (in.find(item.first) != string::npos) {
                detectedID = item.second;
                response = dataset[detectedID];
                break;
            }
        }

        // --- LÓGICA BASADA EN TUS IDS ---
        if (detectedID == 9) { // CRÍTICO
            sentiment = "critical";
            action = "suggest_break";
            response = "DETENTE. No estás solo.  tú también puedes apoyarte en mí. Ve a jugar ahora si quieres.";
        } 
        else if (detectedID == 0 || detectedID == 6 || detectedID == 7) { // TRISTEZA, SOLEDAD, MIEDO
            sentiment = "peligro";
            if (detectedID == 6) response += " La soledad es solo un estado temporal, Diezus está aquí.";
        }
        else if (detectedID == 1 || detectedID == 2 || detectedID == 3 || detectedID == 5) { // FELICIDAD, MOTIVACIÓN, AGRADECIMIENTO, APOYO
            sentiment = "positivo";
        }
        else if (detectedID == 4) { // MOLESTIA
            sentiment = "agitatado";
        }
        else if (detectedID == 8) { // CONFUSIÓN
            sentiment = "confuso";
            response = "La confusión es el inicio de la claridad. Analicemos esto paso a paso.";
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
        cout << "{\"message\": \"Soy Diezus. Tu acompañante emocional.\", \"sentiment\": \"neutral\", \"action\": \"none\"}" << endl;
    }
    return 0;
}