#include "Ejercicio1.h"

// Constructor
Hora::Hora(int h, int m, int s, bool am) : horas(h), minutos(m), segundos(s), esAM(am) {
    validar_datos();
}
// Métodos
void Hora::validar_datos() {
    // Validar horas
    if (horas < 0 || horas > 12) {
        cout << "Error: La hora debe estar entre 0 y 12." << endl;
        horas = 0; // Reiniciar a un valor válido
    }
    // Validar minutos
    if (minutos < 0 || minutos > 59) {
        cout << "Error: Los minutos deben estar entre 0 y 59." << endl;
        minutos = 0; // Reiniciar a un valor válido
    }
    // Validar segundos
    if (segundos < 0 || segundos > 59) {
        cout << "Error: Los segundos deben estar entre 0 y 59." << endl;
        segundos = 0; // Reiniciar a un valor válido
    }
}

void Hora::imprimir_hora_12() {
    cout << setw(2) << setfill('0') << horas << "h,"
         << setw(2) << setfill('0') << minutos << "m,"
         << setw(2) << setfill('0') << segundos <<"s"
         << (esAM ? " a.m" : " p.m") << endl;
}

void Hora::imprimir_hora_24() {
    int hora24 = horas;
    if (!esAM && horas != 12) hora24 += 12;
    if (esAM && horas == 12) hora24 = 0;
    cout << setw(2) << setfill('0') << hora24 << "h,"
         << setw(2) << setfill('0') << minutos << "m,"
         << setw(2) << setfill('0') << segundos << "s" << endl;
}

//Setters
void Hora::set_horas(int h) { horas = h; validar_datos(); }
void Hora::set_minutos(int m) { minutos = m; validar_datos(); }
void Hora::set_segundos(int s) { segundos = s; validar_datos(); }
void Hora::set_esAM(bool am) { esAM = am; }

//Getters
int Hora::get_horas() { return horas; }
int Hora::get_minutos() { return minutos; }
int Hora::get_segundos() { return segundos; }
bool Hora::get_esAM() { return esAM; }

int main() {
    int horas, minutos, segundos;
    char ampm;
    bool datos_validos = false;  // Bandera para controlar la validez de los datos
    
    // Crear el objeto Hora fuera del bucle, inicializado con valores predeterminados
    Hora hora;

    // Bucle para asegurar que los datos ingresados sean correctos
    while (!datos_validos) {
        cout << "Ingrese la hora (hh:mm:ss a.m/p.m): ";
        cin >> horas >> minutos >> segundos >> ampm;

        // Validar si el indicador es 'a' o 'p' para AM/PM
        bool esAM = (ampm == 'a' || ampm == 'A');

        // Actualizar los atributos del objeto hora con los datos ingresados
        hora.set_horas(horas);
        hora.set_minutos(minutos);
        hora.set_segundos(segundos);
        hora.set_esAM(esAM);

        // Si la validación es exitosa, salimos del bucle
        if (horas >= 0 && horas <= 12 && minutos >= 0 && minutos <= 59 && segundos >= 0 && segundos <= 59) {
            datos_validos = true;
        } else {
            cout << "Los datos ingresados son incorrectos. Intente de nuevo." << endl;
        }
    }

    // Imprimir la hora en formato 12 y 24 horas
    cout << "Hora en formato 12 horas: ";
    hora.imprimir_hora_12();

    cout << "Hora en formato 24 horas: ";
    hora.imprimir_hora_24();

    return 0;
}