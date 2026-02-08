#include "crow_all.h"
#include <vector>
#include <string>
#include <ctime>

using namespace std;

// Tus vectores de frases se quedan igual
vector<string> frases_De_Inicio = { "Mi plan para hoy: sobrevivir con estilo.", "Llegue con la energia de un gif...", "Buenas Me llamo Diezus..." };
vector<string> frases_De_Salida = { "¿Quieres que te cuente un chiste?", "¿Algo mas antes de irme?" };

string obtenerInicio() {
    return frases_De_Inicio[rand() % frases_De_Inicio.size()];
}

int main() {
    srand(time(nullptr));
    crow::SimpleApp app;

    // RUTA 1: Para obtener la frase de bienvenida al cargar la página
    CROW_ROUTE(app, "/bienvenida")([](){
        crow::json::wvalue x;
        x["frase"] = obtenerInicio();
        
        crow::response res(x);
        res.add_header("Access-Control-Allow-Origin", "*"); 
        return res;
    });

    // RUTA 2: Para procesar lo que el usuario escribe
    CROW_ROUTE(app, "/chat").methods(crow::HTTPMethod::POST)
    ([](const crow::request& req){
        auto input = crow::json::load(req.body);
        string userMsg = input["texto"].s();
        
        crow::json::wvalue resp;
        
        // Tu lógica de "adiós" ahora en el servidor
        if (userMsg == "adios" || userMsg == "bye") {
            resp["respuesta"] = frases_De_Salida[rand() % frases_De_Salida.size()];
        } else {
            resp["respuesta"] = "Diezus dice: " + userMsg + ". Cuéntame más...";
        }

        crow::response res(resp);
        res.add_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    app.port(18080).multithreaded().run();
}