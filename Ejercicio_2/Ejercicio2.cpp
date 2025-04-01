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

class Curso{
    private:
    string nombre_curso;
    vector<Estudiante*> estudiantes; // Vector de punteros a estudiantes
    static const int MAX_ALUMNOS = 20;
    public:
    // Constructor
    Curso(string nombre) : nombre_curso(nombre) {}
    // Métodos
    bool esta_completo() { return estudiantes.size() >= MAX_ALUMNOS; }
    bool esta_inscripto(int legajo) {}
    bool inscribir_estudiante(Estudiante* estudiante) {}
    bool desinscribir_estudiante(Estudiante* estudiante) {}
    void imprimir_curso(Curso* curso){}
};

void Estudiante::agregar_curso(string nombre_curso, double nota_final) {
    if (nota_final < 0 || nota_final > 10) {
        cout << "Error: La nota debe estar entre 0 y 10." << endl;
        return;
    }
    cursos.push_back({nombre_curso, nota_final});
}

bool Curso::esta_inscripto(int legajo){
    for (auto i=estudiantes.begin(); i!=estudiantes.end(); ++i) {
        if((*i)->get_legajo()==legajo){
            return true;
        }
    }
    return false;
}

bool Curso::inscribir_estudiante(Estudiante* estudiante) {
    if (esta_completo()) {
        cout << "Error: No se pueden inscribir más estudiantes en este curso." << endl;
        return false;
    }
    if (esta_inscripto(estudiante->get_legajo())) {
        cout << "Error: El estudiante ya está inscripto en este curso." << endl;
        return false;
    }
    estudiantes.push_back(estudiante);
    return true;
}

bool Curso::desinscribir_estudiante(Estudiante* estudiante) {
    if(esta_inscripto(estudiante->get_legajo())){
            delete estudiante; // Liberar memoria
            auto i = find(estudiantes.begin(), estudiantes.end(), estudiante);
            if (i!= estudiantes.end()) {
                estudiantes.erase(i);
            }
            return true;
        }
    
    cout << "Error: Estudiante no encontrado." << endl;
    return false;
}

void imprimir_curso(Curso* curso){}