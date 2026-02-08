#include <iostream>
#include <string>

using namespace std;

struct Usuario {
    string nombre;
    string password;
};

int main() {
    Usuario db[5]; // Arreglo para 5 usuarios

    // Registro
    cout << "Registro de nuevo usuario:\n";
    cout << "Nombre: "; cin >> db[0].nombre;
    cout << "Password: "; cin >> db[0].password;

    string userTry, passTry;
    cout << "\n--- Login ---\nUsuario: "; cin >> userTry;
    cout << "Password: "; cin >> passTry;

    if(userTry == db[0].nombre && passTry == db[0].password) {
        cout << "¡Acceso concedido!";
    } else {
        cout << "Datos incorrectos.";
    }

    return 0;
}