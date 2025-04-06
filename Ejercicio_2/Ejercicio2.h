#ifndef EJERCICIO2_H
#define EJERCICIO2_H

#include <iostream>                                // Para entrada y salida de datos
#include <vector>                                  // Para manejar listas dinámicas (vector)
#include <string>                                  // Para trabajar con texto (strings)
#include <algorithm>                               // Para ordenar con std::sort
#include <memory>
#include <iomanip>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

using namespace std;

// Clase Estudiante
class Estudiante {
private:
    string nombre;                               // Nombre completo del estudiante
    int legajo;                                  // Identificador único del estudiante
    vector<pair<string, float>> cursos_notas;    // Lista de cursos con su nota final

public:
    // Constructor que inicializa nombre y legajo
    Estudiante(string nombre, int legajo);

    // Getter para el nombre
    string getNombre() const;

    // Getter para el legajo
    int getLegajo() const;

    
    void agregarCursoYNota(const string& curso, float nota);

    // Calcular el promedio general de notas del estudiante
    float getPromedio() const;

    void mostrarCursosYNotas() const;

    // Sobrecarga del operador '<' para ordenar estudiantes alfabéticamente
    bool operator < (const Estudiante& otro) const;

    // Sobrecarga del operador '<<' para imprimir un estudiante
    friend ostream& operator << (ostream& os, const Estudiante& e);
};


// Clase Curso
class Curso {
private:
    string nombre_curso;                            // Nombre del curso
    vector<shared_ptr<Estudiante>> estudiantes;;   // Lista de punteros a estudiantes
    static const int CAPACIDAD_MAX = 20;       // Capacidad máxima del curso

public:
    //Constructor
    Curso();
    explicit Curso(const string& nombre);

    // Getter para el nombre del curso
    string getNombre() const;

    // Getter para la lista de estudiantes
    vector<shared_ptr<Estudiante>> getEstudiantes() const;

    // Inscribir estudiante si hay cupo y no está inscripto
    bool inscribirEstudiante(shared_ptr<Estudiante> estudiante);

    // Desinscribir estudiante por legajo
    bool desinscribirEstudiante(int legajo);

     // Verificar si estudiante está inscripto por legajo
    bool esta_inscripto(int legajo);

    bool asignarNota(int legajo, float nota);    

    shared_ptr<Estudiante> obtenerEstudiante(int legajo) const;

    // Verificar si el curso llegó a su capacidad máxima
    bool estaCompleto() const;

    // Mostrar lista ordenada alfabéticamente por nombre
    void imprimirListaEstudiantes() const;

     // Constructor de copia profunda
    Curso(const Curso& otro); //Justificación en archivo .txt 

};

// Funciones para el menú interactivo y demostración
void mostrarCursos(const vector<Curso>& cursos);
int seleccionarCurso(const vector<Curso>& cursos);
void menu();
int demo();


//Relación entre los objetos curso y estudiante en archivo .txt


#endif // EJERCICIO2_H
