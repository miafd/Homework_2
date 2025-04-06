#include "Ejercicio2.h"

void menu() {
    vector<Curso> cursos;
    unordered_map<int, shared_ptr<Estudiante>> todosLosEstudiantes;
    int opcion;

    do {
        cout << BOLD << BLUE<<"\n--- MENÚ PRINCIPAL ---\n" << RESET;
        cout << GREEN << "1. " << RESET << "Crear nuevo curso\n";
        cout << GREEN << "2. " << RESET << "Inscribir estudiante en un curso\n";
        cout << GREEN << "3. " << RESET << "Desinscribir estudiante de un curso\n";
        cout << GREEN << "4. " << RESET << "Agregar nota a un estudiante\n";
        cout << GREEN << "5. " << RESET <<"Ver cursos y notas de un estudiante\n";
        cout << GREEN << "6. " << RESET << "Ver lista de estudiantes de un curso\n";
        cout << GREEN << "7. " << RESET << "Ver lista de estudiantes\n";
        cout << RED << "8. " << RESET <<"Salir\n";
        cout << YELLOW << "Seleccione una opción: "<< RESET;
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
            int index = seleccionarCurso(cursos);
            if (index == -1) break;

            cout << "Lista de estudiantes en el curso '" 
                 << cursos[index].getNombre() << "':\n";
            cursos[index].imprimirListaEstudiantes();
            break;
        }
        
        case 7: {
            cout << "Lista de estudiantes y su promedio general:\n";
            for (const auto& [legajo, estudiante] : todosLosEstudiantes) {
                cout << "Estudiante: " << estudiante->getNombre() 
                     << ", Legajo: " << legajo 
                     << ", Promedio General: " << estudiante->getPromedio() << endl;
            }
            break;
        }

        case 8:
            cout << "Saliendo del sistema...\n";
            break;

        default:
            cout << "Opción inválida. Intente de nuevo.\n";
        }

    } while (opcion != 8);
}

int demo() {
    cout << BOLD <<BLUE "\n---Creación de cursos y estudiantes---\n"<<RESET;
    
    Curso matematica("Matemática");
    auto e1 = make_shared<Estudiante>("Bruno Alvarez", 101);
    auto e2 = make_shared<Estudiante>("Loana Gómez", 102);
    auto e3 = make_shared<Estudiante>("Carlos Méndez", 103);
    auto e4 = make_shared<Estudiante>("Ana Torres", 104);

    matematica.inscribirEstudiante(e1);
    matematica.inscribirEstudiante(e2);
    matematica.inscribirEstudiante(e3);
    matematica.inscribirEstudiante(e4);

    cout << BOLD <<BLUE <<"\n---Asignación de notas en Matemática---\n" <<RESET;
    matematica.asignarNota(101, 8.5);
    matematica.asignarNota(102, 9.0);
    matematica.asignarNota(103, 7.5);
    matematica.asignarNota(104, 6.0);

    cout << BOLD << BLUE <<"\n---Creación del curso Física y notas---\n"<<RESET;
    Curso fisica("Física");
    fisica.inscribirEstudiante(e2); // Loana
    fisica.inscribirEstudiante(e3); // Carlos

    fisica.asignarNota(102, 8.0);
    fisica.asignarNota(103, 9.5);
    fisica.asignarNota(101, 7.0); // No inscripto (debería dar advertencia)

    cout << BOLD << BLUE<< "\n---Lista de estudiantes de matemática---\n"<< RESET;
    matematica.imprimirListaEstudiantes();

    cout << BOLD<< BLUE <<"\n---Verificación de inscripción en matemática---\n"<< RESET;
    cout << "¿Legajo 101 está inscripto?: " << (matematica.esta_inscripto(101) ? "Sí" : "No") << endl;
    cout << "¿Legajo 200 está inscripto?: " << (matematica.esta_inscripto(200) ? "Sí" : "No") << endl;

    cout << BOLD <<BLUE << "\n---¿Está completo el curso de matemática?---\n"<< RESET;
    cout << (matematica.estaCompleto() ? "Sí" : "No") << endl;

    cout << BOLD <<BLUE <<"\n---Cursos y notas de cada estudiante---\n"<<RESET;
    e1->mostrarCursosYNotas();
    e2->mostrarCursosYNotas();
    e3->mostrarCursosYNotas();
    e4->mostrarCursosYNotas();

    cout <<BOLD <<BLUE <<"\n---Promedio general de cada estudiante---\n"<< RESET;
    cout << e1->getNombre() << " - Promedio: " << e1->getPromedio() << endl;
    cout << e2->getNombre() << " - Promedio: " << e2->getPromedio() << endl;
    cout << e3->getNombre() << " - Promedio: " << e3->getPromedio() << endl;
    cout << e4->getNombre() << " - Promedio: " << e4->getPromedio() << endl;

    cout << BOLD <<BLUE <<"\n---Verificación de inscripción en Física---\n"<< RESET;
    cout << "Legajo 101 (" << e1->getNombre() << "): " 
         << (fisica.esta_inscripto(101) ? "Sí" : "No") << endl;
    cout << "Legajo 102 (" << e2->getNombre() << "): " 
         << (fisica.esta_inscripto(102) ? "Sí" : "No") << endl;

    cout << BOLD<< BLUE<<"\n---Copia del curso Matemátoca---\n"<<RESET;
    Curso cursoCopia = matematica;

    cout << BOLD << BLUE <<"\n---Desinscripción de legajo 103 de Matemática---\n"<<RESET;
    if (matematica.desinscribirEstudiante(103)) {
        cout << "Desinscripción exitosa.\n";
    } else {
        cout << "No se pudo desinscribir.\n";
    }

    cout <<BOLD <<BLUE<< "\n---Lista de Matemática tras la desinscripción---\n"<<RESET; //Muestra la lista de los estudiantes inscriptos en matematica y 
                                                                                        //su promedio general considerando todos los cursos en los que está 
    matematica.imprimirListaEstudiantes();

    cout << BOLD <<BLUE <<"\n---Lista de Estudiantes en la copia---\n"<< RESET;
    cursoCopia.imprimirListaEstudiantes();

    return 0;
}

int main() {
    int modo;
    cout << BOLD << BLUE <<"Seleccione modo de ejecución:\n" <<RESET;
    cout << GREEN << "1. " << RESET << "Demostración automática\n";
    cout << GREEN << "2. " << RESET << "Modo interactivo (menú)\n";
    cout << BOLD << "Opción: ";
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