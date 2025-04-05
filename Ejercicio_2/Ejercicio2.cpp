#include <iostream>                                // Para entrada y salida de datos
#include <vector>                                  // Para manejar listas dinámicas (vector)
#include <string>                                  // Para trabajar con texto (strings)
#include <algorithm>                               // Para ordenar con std::sort
#include <memory>

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

Estudiante:: Estudiante(string nombre, int legajo) : nombre(move(nombre)), legajo(legajo) {}
string Estudiante::getNombre() const { return nombre; }
int Estudiante::getLegajo() const { return legajo; }
void Estudiante::agregarCursoYNota(const string& curso, float nota) {
    cursos_notas.push_back({curso, nota});
}
float Estudiante::getPromedio() const {
    if (cursos_notas.empty()) return 0;
    float suma = 0;
    for (const auto& cn : cursos_notas) {
        suma += cn.second;
    }
    return suma / cursos_notas.size();
}
void Estudiante:: mostrarCursosYNotas() const {
    if (cursos_notas.empty()) {
        cout << "No hay cursos registrados para este estudiante.\n";
        return;
    }
    cout << "Cursos y notas de " << nombre << ":\n";
    for (const auto& cn : cursos_notas) {
        cout << " - " << cn.first << ": " << cn.second << endl;
    }
}
bool Estudiante:: operator < (const Estudiante& otro) const {
    return nombre < otro.nombre;
}
ostream& operator << (ostream& os, const Estudiante& e) {
    os << "Nombre: " << e.nombre << ", Legajo: " << e.legajo << ", Promedio: " << e.getPromedio();
    return os;
}



// Clase Curso
class Curso {
private:
    string nombre_curso;                               // Nombre del curso
    vector<shared_ptr<Estudiante>> estudiantes;;           // Lista de punteros a estudiantes
    static const int CAPACIDAD_MAX = 20;       // Capacidad máxima del curso

public:
    //Constructor
    Curso();
    explicit Curso(const string& nombre);

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

     // Constructor de copia profunda (copia el contenido, no los punteros)
    Curso(const Curso& otro);
        /* Justificación:
        Se realiza una copia profunda de la estructura del curso, es decir, 
        se crea un nuevo objeto Curso con su propia lista de punteros a estudiantes. 
        Sin embargo, los estudiantes no se copian individualmente (no se crean nuevos objetos Estudiante),
        sino que se mantienen como `shared_ptr`, por lo que los cursos comparten los mismos estudiantes en memoria.

        Esto es adecuado en este diseño porque los estudiantes existen independientemente del curso 
        y pueden estar inscriptos en varios a la vez. La copia profunda garantiza que 
        cada curso puede modificar su lista de inscripción sin afectar a los demás cursos,
        pero cualquier cambio en los datos del estudiante (como agregar una nota) 
        será visible desde todos los cursos en los que esté inscripto.
         Esto evita conflictos, como doble eliminación de memoria o modificaciones no deseadas compartidas entre cursos.
         */

};

Curso:: Curso() : nombre_curso("Curso sin nombre") {}
Curso:: Curso(const string& nombre) : nombre_curso(nombre) {}

bool Curso::inscribirEstudiante(shared_ptr<Estudiante> estudiante) {
    if (estudiante->getLegajo() == 0) return false;
    if (esta_inscripto(estudiante->getLegajo())) {
        cout << "Error: El estudiante ya está inscripto en este curso." << endl;
        return false;
    }
    if (estudiantes.size() >= CAPACIDAD_MAX) {
        cout << "Error: No se pueden inscribir más estudiantes en este curso." << endl;
        return false;
    }
    estudiantes.push_back(estudiante);
    return true;
}
bool Curso::desinscribirEstudiante(int legajo) {
    auto it = remove_if(estudiantes.begin(), estudiantes.end(),
        [&](const std::shared_ptr<Estudiante>& e) { return e->getLegajo() == legajo; });
    if (it != estudiantes.end()) {
        estudiantes.erase(it, estudiantes.end());
        return true;
    }
    return false;
}
bool Curso:: esta_inscripto(int legajo){
    for (auto i=estudiantes.begin(); i!=estudiantes.end(); ++i) {
        if((*i)->getLegajo()==legajo){
            return true;
        }
    }
    return false;
}
bool Curso::asignarNota(int legajo, float nota) {
    if (nota < 0 || nota > 10) {
        cout << "Error: La nota debe estar entre 0 y 10.\n";
        return false;
    }
    auto estudiante = obtenerEstudiante(legajo);
    if (!estudiante) {
        cout << "Error: El estudiante no está inscripto en este curso.\n";
        return false;
    }
    estudiante->agregarCursoYNota(nombre_curso, nota);  // Usamos esta nueva función privada
    return true;
}


shared_ptr<Estudiante> Curso::obtenerEstudiante(int legajo) const {
    for (const auto& e : estudiantes) {
        if (e->getLegajo() == legajo) return e;
    }
    return nullptr;
}
bool Curso:: estaCompleto() const {
    return estudiantes.size() >= CAPACIDAD_MAX;
}

void Curso::imprimirListaEstudiantes() const {
    vector<shared_ptr<Estudiante>> copia = estudiantes;
    sort(copia.begin(), copia.end(), [](const shared_ptr<Estudiante>& a, const shared_ptr<Estudiante>& b) {
        return *a < *b;
    });
    for (const auto& e : copia) {
        cout << *e << endl;
    }
}
Curso::Curso(const Curso& otro) : nombre_curso(otro.nombre_curso) {
    for (const auto& e : otro.estudiantes) {
        estudiantes.push_back(make_shared<Estudiante>(*e));  // Copia profunda
    }
}



// Menú interactivo de prueba del programa
// void menu() {
//     Curso curso;
//     int opcion;
//     cout << "\n--- ADMINISTRACIÓN DE CURSOS ---\n";
//     cout << "1. Inscribir estudiante\n";
//     cout << "2. Desinscribir estudiante\n";
//     cout << "3. Ver si estudiante está inscripto\n";
//     cout << "4. Ver si el curso está completo\n";
//     cout << "5. Imprimir lista de estudiantes\n";
//     cout << "6. Agregar nota a un estudiante\n";
//     cout << "7. Ver cursos y notas de un estudiante\n";
//     cout << "8. Salir\n";

//     do {
//         cout << "Seleccione una opción: ";

//         cin >> opcion;
//         if (cin.fail()) {
//             cin.clear();
//             cout << "Entrada inválida. Por favor ingrese un número.\n";
//             continue;
//         }

//         if (opcion == 1) {
//             string nombre;
//             int legajo;
//             do {
//                 cout << "Ingrese nombre del estudiante, <Enter> para finalizar:";
//                 cin.ignore();
//                 getline(cin, nombre);
//                 if (nombre.empty()) {
//                     break; // Sale del do-while
//                 }

//                 do {
//                     cout << "Ingrese legajo: ";
//                     cin >> legajo;
//                     if (legajo == 0) {
//                         cout << "Legajo inválido. No puede ser cero.\n";
//                     }
//                 } while (legajo == 0);
            
//                 auto* estudiante = new Estudiante(nombre, legajo);
//                 if (curso.inscribirEstudiante(estudiante)) {
//                     cout << "Estudiante inscripto correctamente.\n";
//                 } else {
//                     cout << "No se pudo inscribir al estudiante.\n";
//                     delete estudiante;
//                 }
//             } while (nombre != "");
//         } else if (opcion == 2) {
//             int legajo;
//             do {
//                 cout << "Nro. de Legajo a desinscribir (0 para salir): ";
//                 cin.ignore();
//                 cin >> legajo;

//                 if (legajo == 0) {
//                     break;
//                 }

//                 if (curso.desinscribirEstudiante(legajo)) {
//                     cout << "Estudiante desinscripto.\n";
//                 } else {
//                     cout << "No se encontró el estudiante.\n";
//                 }

//             } while (legajo != 0);

//         } else if (opcion == 3) {
//             int legajo;
//             cout << "Ingrese legajo a buscar: ";
//             cin >> legajo;
//             if (curso.esta_inscripto(legajo)) {
//                 cout << "El estudiante está inscripto.\n";
//             } else {
//                 cout << "El estudiante no está inscripto.\n";
//             }
//         } else if (opcion == 4) {
//             if (curso.estaCompleto()) {
//                 cout << "El curso está completo.\n";
//             } else {
//                 cout << "El curso aún tiene cupo.\n";
//             }
//         } else if (opcion == 5) {
//             curso.imprimirListaEstudiantes();
//         } else if (opcion == 6) {
//             int legajo;
//             string curso_nombre;
//             float nota;
//             cout << "Ingrese legajo del estudiante: ";
//             cin >> legajo;
//             Estudiante* e = curso.obtenerEstudiante(legajo);
//             if (e) {
//                 cout << "Ingrese nombre del curso: ";
//                 cin.ignore();
//                 getline(cin, curso_nombre);
//                 cout << "Ingrese nota final: ";
//                 cin >> nota;
//                 e->agregarNota(curso_nombre, nota);
//                 cout << "Nota agregada con éxito.\n";
//             } else {
//                 cout << "Estudiante no encontrado.\n";
//             }
//         } else if (opcion == 7) {
//             int legajo;
//             cout << "Ingrese legajo del estudiante: ";
//             cin >> legajo;
//             Estudiante* e = curso.obtenerEstudiante(legajo);
//             if (e) {
//                 e->mostrarCursosYNotas();
//             } else {
//                 cout << "Estudiante no encontrado.\n";
//             }
//         }
//           else {
//             cout << "La opción debe estar entre 1 y 8\n";
//             continue;              
//         }
//     } while (opcion != 8);
// }


int demo() {
    cout << "\n========== CREACIÓN DE CURSOS Y ESTUDIANTES ==========\n";
    
    Curso matematica("Matemática");
    auto e1 = make_shared<Estudiante>("Bruno Alvarez", 101);
    auto e2 = make_shared<Estudiante>("Loana Gómez", 102);
    auto e3 = make_shared<Estudiante>("Carlos Méndez", 103);
    auto e4 = make_shared<Estudiante>("Ana Torres", 104);

    matematica.inscribirEstudiante(e1);
    matematica.inscribirEstudiante(e2);
    matematica.inscribirEstudiante(e3);
    matematica.inscribirEstudiante(e4);

    cout << "\n========== ASIGNACIÓN DE NOTAS EN MATEMÁTICA ==========\n";
    matematica.asignarNota(101, 8.5);
    matematica.asignarNota(102, 9.0);
    matematica.asignarNota(103, 7.5);
    matematica.asignarNota(104, 6.0);

    cout << "\n========== CREACIÓN DEL CURSO FÍSICA Y NOTAS ==========\n";
    Curso fisica("Física");
    fisica.inscribirEstudiante(e2); // Loana
    fisica.inscribirEstudiante(e3); // Carlos

    fisica.asignarNota(102, 8.0);
    fisica.asignarNota(103, 9.5);
    fisica.asignarNota(101, 7.0); // No inscripto (debería dar advertencia)

    cout << "\n========== LISTA DE ESTUDIANTES EN MATEMÁTICA ==========\n";
    matematica.imprimirListaEstudiantes();

    cout << "\n========== VERIFICACIÓN DE INSCRIPCIÓN EN MATEMÁTICA ==========\n";
    cout << "¿Legajo 101 está inscripto?: " << (matematica.esta_inscripto(101) ? "Sí" : "No") << endl;
    cout << "¿Legajo 200 está inscripto?: " << (matematica.esta_inscripto(200) ? "Sí" : "No") << endl;

    cout << "\n========== ¿ESTÁ COMPLETO EL CURSO DE MATEMÁTICA? ==========\n";
    cout << (matematica.estaCompleto() ? "Sí" : "No") << endl;

    cout << "\n========== CURSOS Y NOTAS DE CADA ESTUDIANTE ==========\n";
    e1->mostrarCursosYNotas();
    e2->mostrarCursosYNotas();
    e3->mostrarCursosYNotas();
    e4->mostrarCursosYNotas();

    cout << "\n========== PROMEDIO GENERAL DE CADA ESTUDIANTE ==========\n";
    cout << e1->getNombre() << " - Promedio: " << e1->getPromedio() << endl;
    cout << e2->getNombre() << " - Promedio: " << e2->getPromedio() << endl;
    cout << e3->getNombre() << " - Promedio: " << e3->getPromedio() << endl;
    cout << e4->getNombre() << " - Promedio: " << e4->getPromedio() << endl;

    cout << "\n========== VERIFICACIÓN DE INSCRIPCIÓN EN FÍSICA ==========\n";
    cout << "Legajo 101 (" << e1->getNombre() << "): " 
         << (fisica.esta_inscripto(101) ? "Sí" : "No") << endl;
    cout << "Legajo 102 (" << e2->getNombre() << "): " 
         << (fisica.esta_inscripto(102) ? "Sí" : "No") << endl;

    cout << "\n========== DESINSCRIPCIÓN DEL LEGAJO 103 EN MATEMÁTICA ==========\n";
    if (matematica.desinscribirEstudiante(103)) {
        cout << "Desinscripción exitosa.\n";
    } else {
        cout << "No se pudo desinscribir.\n";
    }

    cout << "\n========== LISTA EN MATEMÁTICA TRAS DESINSCRIPCIÓN ==========\n";
    matematica.imprimirListaEstudiantes();

    cout << "\n========== COPIA PROFUNDA DEL CURSO MATEMÁTICA ==========\n";
    Curso cursoCopia = matematica;

    cout << "\n========== LISTA DE ESTUDIANTES EN LA COPIA ==========\n";
    cursoCopia.imprimirListaEstudiantes();

    return 0;
}




int main() {
    // int modo;
    // cout << "Seleccione modo de ejecución:\n";
    // cout << "1. Demostración automática\n";
    // cout << "2. Modo interactivo (menú)\n";
    // cout << "Opción: ";
    // cin >> modo;

    // if (modo == 1) {
    //     demo(); // función con el código automático
    // } else if (modo == 2) {
    //     menu(); // función con el menú interactivo
    // } else {
    //     cout << "Opción no válida.\n";
    // }
    demo();

    return 0;
}

