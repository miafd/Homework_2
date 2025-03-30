#include <iostream>  // Para entrada y salida estándar
#include <vector> // Para manejar vectores
#include <string>
#include <algorithm> // Para manejar sort

using namespace std;

class Estudiante {
    private:
    string nombre_completo;
    int legajo;
    vector<pair<string, double>> cursos; // Nombre del curso y nota final
    public:
    // Constructor
    Estudiante(string nombre, int legajo) : nombre_completo(nombre), legajo(legajo) {}

    // Métodos
    void agregar_curso(string nombre_curso, double nota_final); //Agregar curso y nota

    //Getters
    string get_nombre_completo() { return nombre_completo; }
    int get_legajo() { return legajo; }
    double get_promedio_general() {
        if (cursos.empty()) return 0.0;
        double suma = 0;
        for (const auto& curso : cursos) {
            suma += curso.second;
        }
        return suma / cursos.size();
    }
};

class Curso{};

void Estudiante::agregar_curso(string nombre_curso, double nota_final) {
    if (nota_final < 0 || nota_final > 10) {
        cout << "Error: La nota debe estar entre 0 y 10." << endl;
        return;
    }
    cursos.push_back({nombre_curso, nota_final});
}



