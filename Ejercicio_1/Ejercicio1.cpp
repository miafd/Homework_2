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

//Funciones para el menu interactivo
void mostrar_menu() {
    cout << "\n--- Menú de opciones ---\n";
    cout << "1. Inicializar sin parámetros (0h, 0m, 0s a.m.)\n";
    cout << "2. Ingresar solo la hora (0m, 0s, a.m.)\n";
    cout << "3. Ingresar hora y minutos (0s, a.m.)\n";
    cout << "4. Ingresar hora, minutos y segundos (a.m.)\n";
    cout << "5. Ingresar hora completa (hh mm ss a/p)\n";
    cout << "6. Cambiar valores individualmente\n";
    cout << "7. Leer valores actuales\n";
    cout << "8. Mostrar hora en formato 12 y 24 horas\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opción: ";
}


void cambiar_individual(Hora& h) {
    int opcion;
    do {
        cout << "\n--- Cambiar campo individual ---\n";
        cout << "1. Cambiar horas\n";
        cout << "2. Cambiar minutos\n";
        cout << "3. Cambiar segundos\n";
        cout << "4. Cambiar AM/PM\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int hh;
                cout << "Ingrese nueva hora (0-12): ";
                cin >> hh;
                h.set_horas(hh);
                break;
            }
            case 2: {
                int mm;
                cout << "Ingrese nuevos minutos (0-59): ";
                cin >> mm;
                h.set_minutos(mm);
                break;
            }
            case 3: {
                int ss;
                cout << "Ingrese nuevos segundos (0-59): ";
                cin >> ss;
                h.set_segundos(ss);
                break;
            }
            case 4: {
                char ap;
                cout << "Ingrese 'a' para a.m. o 'p' para p.m.: ";
                cin >> ap;
                h.set_esAM(ap == 'a' || ap == 'A');
                break;
            }
        }
    } while (opcion != 0);
}

void leer_valores(Hora& h) {
    cout << "\n--- Valores actuales ---\n";
    cout << "Hora: " << h.get_horas() << "h\n";
    cout << "Minutos: " << h.get_minutos() << "m\n";
    cout << "Segundos: " << h.get_segundos() << "s\n";
    cout << "AM/PM: " << (h.get_esAM() ? "a.m." : "p.m.") << "\n";
}

void menu_interactivo() {
    Hora hora; // Hora inicial por defecto
    int opcion;

    do {
        mostrar_menu();
        cin >> opcion;

        switch (opcion) {
            case 1: {
                // Inicializa sin parámetros
                hora = Hora(); // Reinicializa a 0h, 0m, 0s a.m.
                cout << "Hora inicializada por defecto.\n";
                break;
            }
            case 2: {
                int hh;
                cout << "Ingrese la hora: ";
                cin >> hh;
                hora.set_horas(hh);
                hora.set_minutos(0);
                hora.set_segundos(0);
                hora.set_esAM(true);
                break;
            }
            case 3: {
                int hh, mm;
                cout << "Ingrese hora y minutos: ";
                cin >> hh >> mm;
                hora.set_horas(hh);
                hora.set_minutos(mm);
                hora.set_segundos(0);
                hora.set_esAM(true);
                break;
            }
            case 4: {
                int hh, mm, ss;
                cout << "Ingrese hora, minutos y segundos: ";
                cin >> hh >> mm >> ss;
                hora.set_horas(hh);
                hora.set_minutos(mm);
                hora.set_segundos(ss);
                hora.set_esAM(true);
                break;
            }
            case 5: {
                int hh, mm, ss;
                char ap;
                cout << "Ingrese hora, minutos, segundos y a/p: ";
                cin >> hh >> mm >> ss >> ap;
                hora.set_horas(hh);
                hora.set_minutos(mm);
                hora.set_segundos(ss);
                hora.set_esAM(ap == 'a' || ap == 'A');
                break;
            }
            case 6:
                cambiar_individual(hora);
                break;

            case 7:
                leer_valores(hora);
                break;

            case 8:
                cout << "\nFormato 12 horas: ";
                hora.imprimir_hora_12();
                cout << "Formato 24 horas: ";
                hora.imprimir_hora_24();
                break;

            case 0:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opción inválida. Intente de nuevo.\n";
        }

    } while (opcion != 0);
}


// El main queda simple y limpio
int main() {
    menu_interactivo();
    return 0;
}
