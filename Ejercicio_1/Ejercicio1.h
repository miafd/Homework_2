#ifndef HORA_H
#define HORA_H

#include <iostream>   // Para entrada y salida estándar
#include <iomanip>    // Para setw y setfill
#include <string>    // Para manejar el formato a.m./p.m.

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define BOLD    "\033[1m"

class Hora {
private:
    int horas;
    int minutos;
    int segundos;
    bool esAM; // true para AM, false para PM

public:
    // Constructores
    Hora(int h = 0, int m = 0, int s = 0, bool am = true);

    // Métodos
    void validar_datos();
    void imprimir_hora_12();
    void imprimir_hora_24();

    // Setters
    void set_horas(int h);
    void set_minutos(int m);
    void set_segundos(int s);
    void set_esAM(bool am);

    // Getters
    int get_horas();
    int get_minutos();
    int get_segundos();
    bool get_esAM();
};

// Funciones para el menú interactivo
void mostrar_menu();
void cambiar_individual(Hora& h);
void leer_valores(Hora& h);
void menu_interactivo();

#endif // HORA_H
