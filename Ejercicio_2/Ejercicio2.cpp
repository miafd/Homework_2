#include "Ejercicio2.h"

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

Curso:: Curso() : nombre_curso("Curso sin nombre") {}
Curso:: Curso(const string& nombre) : nombre_curso(nombre) {}
string Curso::getNombre() const { return nombre_curso; }
vector<shared_ptr<Estudiante>> Curso::getEstudiantes() const {
    return estudiantes;
}
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




void mostrarCursos(const vector<Curso>& cursos) {
    cout << "\nCursos disponibles:\n";
    for (size_t i = 0; i < cursos.size(); ++i) {
        cout << i + 1 << ". " << cursos[i].getNombre() << "\n";
    }
}

int seleccionarCurso(const vector<Curso>& cursos) {
    if (cursos.empty()) {
        cout << "No hay cursos creados aún.\n";
        return -1;
    }
    mostrarCursos(cursos);
    cout << "Seleccione el número del curso: ";
    int seleccion;
    cin >> seleccion;
    if (cin.fail() || seleccion < 1 || seleccion > static_cast<int>(cursos.size())) {
        cin.clear();
        cout << "Selección inválida.\n";
        return -1;
    }
    return seleccion - 1;
}