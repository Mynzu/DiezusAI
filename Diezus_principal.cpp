#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;

vector<string> palabras_fragmentadas (const string& frase) {
    //(const string& frase) { esta parte sirve para decir que se trabaja con el vector original todo el tiempo y el tipo de datos, me acabo de enterar jajaja
    vector<string> palabras;
    string palabra;
    istringstream stream(frase);
    //es justo y necesario es lo que desgloza la frase en palabras individuales
    while (stream >> palabra) {
        //justo aqui tenia dudas de como hacerlo, ya que no sabia como colocar que se borre la puntuacion y los signos, pero era una funcion que se llama jajaja es ispunct
        palabra.erase(remove_if(palabra.begin(), palabra.end(), ::ispunct), palabra.end());
        //aqui es lo mismo, pero con las mayusculas y minusculas es tolower
        transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
        //guarda de nuevo la palabra en el mismo vector, pero ya lista o sea sin nada 
        palabras.push_back(palabra);
    }
    return palabras;
}

int analizar_frase(string frase, map<string, int>& emociones_valores, vector<string>& emociones_negativas, vector<string>& emociones_tristes) {
    vector<string> palabras = palabras_fragmentadas(frase);
    int valor_total = 0;
    bool negacion_activa = false;

    for (const string& palabra : palabras) {
        //use lo mismo del anterior
        if (find(emociones_negativas.begin(), emociones_negativas.end(), palabra) != emociones_negativas.end()) {
            //find es para devolver un iterador al elemento encontrado o al final si no se encuentra da treu
            negacion_activa = true;
            //quiere decir que es malo, o sea es negativo el usuario se siente mal :(
            continue;
        }

        auto it = emociones_valores.find(palabra);
        //auto, es que va a pasar por cada parte del vector ya que c++ sabe que es parte del map y no hay que especificarlo
        if (it != emociones_valores.end()) {
            int valor = it->second;
            //esto sirve ya que estaria buscando cada palabra que coloque el usuario en el mapa de emociones y valores tras el desgloce de la frase
            if (negacion_activa) {
                valor = -valor; // esta es la parte negativa que pense jaja
                negacion_activa = false; // esto quiere decir que esta bien, el usuario no se siente mal
            }
            valor_total += valor; //obiamente si esta negado se volvera negativo pidiendo respuestas de  ayuda, pero si esta positivo,, felicitara al usuario
        }

        auto it_triste = find(emociones_tristes.begin(), emociones_tristes.end(), palabra);
        if (it_triste != emociones_tristes.end()) {
            int penalizacion = 10;
            if (negacion_activa) {
                penalizacion = -penalizacion; // convierte tristeza negada en algo positivo
                negacion_activa = false;
            }
            valor_total -= penalizacion;
        }
    }

    return valor_total;
}