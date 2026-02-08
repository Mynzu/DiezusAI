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
    map<string, int> keywordIndex;
    map<string, string> diccionarioEmocional;
    string logArchivo = "sentimientos_semana.txt";

    string clean(string text) {
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
        vector<string> pos = {"alegria", "felicidad", "amor", "paz", "bien", "genial", "excelente"};
        for(auto& p : pos) diccionarioEmocional[p] = "positivo";

        vector<string> crit = {"muerte", "suicidio", "matarme", "morir", "terror", "desesperanza"};
        for(auto& p : crit) diccionarioEmocional[p] = "critico";
    }

    // Función solicitada: Guardar memoria en archivo para persistencia
    void guardarMemoria(string sentimiento) {
        ofstream memoria(logArchivo, ios::app);
        if (memoria.is_open()) {
            time_t now = time(0);
            memoria << now << "|" << sentimiento << endl;
            memoria.close();
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
                int id = stoi(line.substr(0, pos));
                string contenidoOriginal = line.substr(pos + 1);
                string contenidoLimpio = clean(contenidoOriginal);
                dataset[id] = contenidoOriginal;

                stringstream ss(contenidoLimpio);
                string word;
                while (ss >> word) {
                    if (word.length() > 3) keywordIndex[word] = id; 
                }
            }
        }
    }

    string process(string input) {
        string in = clean(input);
        string respuesta = "Entiendo tu mensaje. Como Diezus, analizo tus palabras con seriedad.";
        string sentimiento = "neutral";
        string accion = "none";
        int idDetectado = -1;

        stringstream ss(in);
        string word;
        
        while (ss >> word) {
            if (keywordIndex.count(word)) {
                idDetectado = keywordIndex[word];
                respuesta = dataset[idDetectado];
            }
            if (diccionarioEmocional.count(word)) {
                sentimiento = diccionarioEmocional[word];
            }
        }

        // Prioridad de sentimiento por ID (Lógica de Ares/Hades/Pedro según dataset)
        if (idDetectado != -1) {
            if (idDetectado == 0 || idDetectado == 6 || idDetectado == 7) sentimiento = "advertencia";
            else if (idDetectado == 1 || idDetectado == 2 || idDetectado == 3 || idDetectado == 5) sentimiento = "positivo";
            else if (idDetectado == 4) sentimiento = "agitado";
            else if (idDetectado == 8) sentimiento = "confundido";
        }

        // Protocolo de seguridad y redirección a juegos
        if (sentimiento == "critico" || idDetectado == 9) {
            sentimiento = "critico";
            accion = "sugerir_juego"; // Acción para la interfaz de tu amigo
            respuesta = "ALERTA. Diezus detecta inestabilidad. He activado el acceso a los juegos programados para tu bienestar. Por favor, úsalos ahora.";
        }

        guardarMemoria(sentimiento);

        // Formato JSON optimizado para conectar con Render
        return "{\"respuesta\": \"" + escapeJSON(respuesta) + 
               "\", \"sentimiento\": \"" + sentimiento + 
               "\", \"accion\": \"" + accion + "\"}";
    }
};

int main(int argc, char* argv[]) {
    DiezusAI diezus;
    if (argc >= 2) {
        cout << diezus.process(argv[1]) << endl;
    }
    return 0;
}