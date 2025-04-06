#include "Ejercicio2.h"

void menu() {
    vector<Curso> cursos;
    unordered_map<int, shared_ptr<Estudiante>> todosLosEstudiantes;
    int opcion;

    do {
        cout << "\n--- MENÚ PRINCIPAL ---\n";
        cout << "1. Crear nuevo curso\n";
        cout << "2. Inscribir estudiante en curso\n";
        cout << "3. Desinscribir estudiante de curso\n";
        cout << "4. Agregar nota a un estudiante\n";
        cout << "5. Ver cursos y notas de un estudiante\n";
        cout << "6. Ver lista de estudiantes por curso\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada inválida.\n";
            continue;
        }

        switch (opcion) {
        case 1: {
            string nombreCurso;
            cin.ignore();
            cout << "Ingrese el nombre del nuevo curso: ";
            getline(cin, nombreCurso);
            cursos.emplace_back(nombreCurso);
            cout << "Curso '" << nombreCurso << "' creado.\n";
            break;
        }

        case 2: {
            int index = seleccionarCurso(cursos);
            if (index == -1) break;

            string nombre;
            int legajo;
            cin.ignore();
            do {
                cout << "Nombre del estudiante (<Enter> para salir): ";
                getline(cin, nombre);
                if (nombre.empty()) break;

                do {
                    cout << "Legajo: ";
                    cin >> legajo;
                    if (legajo == 0)
                        cout << "Legajo inválido.\n";
                } while (legajo == 0);

                shared_ptr<Estudiante> estudiante;

                auto it = todosLosEstudiantes.find(legajo);
                if (it != todosLosEstudiantes.end()) {
                    estudiante = it->second;  // Ya existe, lo reutilizamos
                } else {
                    estudiante = make_shared<Estudiante>(nombre, legajo); // Nuevo
                    todosLosEstudiantes[legajo] = estudiante;
                }

                if (cursos[index].inscribirEstudiante(estudiante)) {
                    cout << "Estudiante inscripto.\n";
                } else {
                    cout << "No se pudo inscribir.\n";
                }

                cin.ignore();
            } while (!nombre.empty());
            break;
        }

        case 3: {
            int index = seleccionarCurso(cursos);
            if (index == -1) break;

            int legajo;
            cout << "Legajo del estudiante a desinscribir (0 para salir): ";
            cin >> legajo;
            if (legajo == 0) break;

            if (cursos[index].desinscribirEstudiante(legajo))
                cout << "Estudiante desinscripto.\n";
            else
                cout << "No se encontró el estudiante.\n";
            break;
        }

        case 4: {
            int index = seleccionarCurso(cursos);
            if (index == -1) break;

            int legajo;
            float nota;
            cout << "Legajo del estudiante: ";
            cin >> legajo;

            if (!cursos[index].esta_inscripto(legajo)) {
                cout << "El estudiante no está inscripto.\n";
                break;
            }

            cout << "Nota final: ";
            cin >> nota;

            if (cursos[index].asignarNota(legajo, nota))
                cout << "Nota asignada.\n";
            break;
        }

        case 5: {
            int legajo;
            cout << "Ingrese legajo del estudiante: ";
            cin >> legajo;
        
            auto it = todosLosEstudiantes.find(legajo);
            if (it != todosLosEstudiantes.end()) {
                it->second->mostrarCursosYNotas();
            } else {
                cout << "Estudiante no encontrado.\n";
            }
            break;
        }
        

        case 6: {
            cout << "Lista de estudiantes y su promedio general:\n";
            for (const auto& [legajo, estudiante] : todosLosEstudiantes) {
                cout << "Estudiante: " << estudiante->getNombre() 
                     << ", Legajo: " << legajo 
                     << ", Promedio General: " << estudiante->getPromedio() << endl;
            }
            break;
        }

        case 7:
            cout << "Saliendo del sistema...\n";
            break;

        default:
            cout << "Opción inválida. Intente de nuevo.\n";
        }

    } while (opcion != 7);
}


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
    int modo;
    cout << "Seleccione modo de ejecución:\n";
    cout << "1. Demostración automática\n";
    cout << "2. Modo interactivo (menú)\n";
    cout << "Opción: ";
    cin >> modo;

    if (modo == 1) {
        demo(); // función con el código automático
    } else if (modo == 2) {
        menu(); // función con el menú interactivo
    } else {
        cout << "Opción no válida.\n";
    }
    

    return 0;
}