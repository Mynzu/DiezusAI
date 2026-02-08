#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

vector<string> frases_De_Salida = {
    "Quieres seguir hablando sobre esto? O prefieres escuchar mis chistes malos?",
    "Te gustaría que exploremos otro detalle antes de despedirnos?",
    "Antes de irme, ¿hay algo más que te gustaría saber?",
    "¿Quieres que te cuente un dato curioso antes de terminar?",
    "¿Hay algún otro tema que te interese discutir antes de que me vaya?",
    "Hay algo más en lo que pueda ayudarte hoy?",
    "¿Quieres que te recomiende un libro o una película antes de despedirnos?",
    "¿Te gustaría recibir un consejo útil antes de que me despida?",
    "¿Quieres que te comparta una cita inspiradora antes de irme?",
    "¿Hay alguna otra pregunta que tengas en mente antes de que termine?",
    "Hasta luego, ¡y que tengas un excelente día!",
    "¿Quieres que te cuente un chiste rápido antes de despedirnos?",
    "¿Hay algo más que te gustaría explorar antes de que me vaya?",
    "¿Quieres que te dé una recomendación personalizada antes de irme?",
    "¿Te gustaría que te comparta un dato interesante antes de despedirnos?",
    "¿Hay algún otro tema que te gustaría discutir antes de que termine?",
    "¿Quieres que te sugiera una actividad divertida antes de irme?",
    "¿Hay algo más en lo que pueda asistirte antes de despedirnos?",
    "¿Quieres que te cuente una historia breve antes de irme?",
    "¿Hay algún otro tema que te gustaría discutir antes de que termine?",
    "¿Quieres que te sugiera una actividad divertida antes de irme?",
    "¿Hay algo más en lo que pueda asistirte antes de despedirnos?",
};


string frase_Aleatoria() {
    srand(time(nullptr));
    int indice = rand() % frases_De_Salida.size();
    return frases_De_Salida[indice];
}
int main() {
    cout << "" << frase_Aleatoria() << endl;
    return 0;
}