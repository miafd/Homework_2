#include "Ejercicio3.h"

Numero* Entero::suma (const Numero* otro) {
    const Entero* e = dynamic_cast<const Entero*>(otro);  // Convierte 'otro' en un Entero*
    if (e) {
        return new Entero(this->valor + e->valor);  // Usa 'this' y 'e' (que es 'otro')
    }
    return nullptr;
}
Numero* Entero::resta (const Numero* otro) {
    const Entero* e = dynamic_cast<const Entero*>(otro);
    if (e) {
        return new Entero(this->valor - e->valor);
    }
    return nullptr;
}
Numero* Entero::multiplicacion (const Numero* otro) {
    const Entero* e = dynamic_cast<const Entero*>(otro);
    if (e) {
        return new Entero(this->valor * e->valor);
    }
    return nullptr;
}
string Entero::toString() {
    return to_string(valor);
}

Numero* Real::suma(const Numero*otro){
    const Real* r = dynamic_cast<const Real*>(otro);
    if (r) {
        return new Real(this->valor + r->valor);
    }
    return nullptr;
}
Numero* Real::resta(const Numero*otro){
    const Real* r = dynamic_cast<const Real*>(otro);
    if (r) {
        return new Real(this->valor - r->valor);
    }
    return nullptr;
}
Numero* Real::multiplicacion(const Numero*otro){
    const Real* r = dynamic_cast<const Real*>(otro);
    if (r) {
        return new Real(this->valor * r->valor);
    }
    return nullptr;
}
string Real::toString() {
    return to_string(valor);
}

Numero* Complejo::suma(const Numero* otro) {
    const Complejo* c = dynamic_cast<const Complejo*>(otro);
    if (c) {
        return new Complejo(this->real + c->real, this->imaginario + c->imaginario);
    }
    return nullptr;
}
Numero* Complejo::resta(const Numero* otro) {
    const Complejo* c = dynamic_cast<const Complejo*>(otro);
    if (c) {
        return new Complejo(this->real - c->real, this->imaginario - c->imaginario);
    }
    return nullptr;
}
Numero* Complejo::multiplicacion(const Numero* otro) {
    const Complejo* c = dynamic_cast<const Complejo*>(otro);
    if (c) {
        return new Complejo(this->real * c->real - this->imaginario * c->imaginario,
                            this->real * c->imaginario + this->imaginario * c->real);
    }
    return nullptr;
}
string Complejo::toString() {
    return to_string(real) + " + " + to_string(imaginario) + "i";
}

int main() {
    cout << BOLD << MAGENTA <<"OPERACIONES CON ENTEROS"<<RESET<<endl;
    Entero e1(5), e2(3);
    Numero* sumaEntero = e1.suma(&e2);
    Numero* restaEntero = e1.resta(&e2);
    Numero* multiplicacionEntero = e1.multiplicacion(&e2);
    cout <<BLUE<< "e1 = 5, e2 = 3\n"<<RESET;
    cout << BOLD << "Suma:            " << RESET << sumaEntero->toString() << endl;
    cout << BOLD <<"Resta:           " << RESET<< restaEntero->toString() << endl;
    cout << BOLD <<"Multiplicación:  " << RESET<< multiplicacionEntero->toString() << endl;

    delete sumaEntero;
    delete restaEntero;
    delete multiplicacionEntero;

    cout << BOLD << MAGENTA<< "OPERACIONES CON REALES" <<RESET<<endl;
    Real r1(5.3), r2(2.7);
    Numero* sumaReal = r1.suma(&r2);
    Numero* restaReal = r1.resta(&r2);
    Numero* multiplicacionReal = r1.multiplicacion(&r2);
    cout << BLUE << "r1 = 5.3, r2 = 2.7\n"<< RESET;
    cout << BOLD << "Suma:            " << RESET << sumaReal->toString() << endl;
    cout << BOLD <<"Resta:           " << RESET<< restaReal->toString() << endl;
    cout << BOLD <<"Multiplicación:  " << RESET<< multiplicacionReal->toString() << endl;

    delete sumaReal;
    delete restaReal;
    delete multiplicacionReal;

    cout << BOLD << MAGENTA<< "OPERACIONES CON COMPLEJOS" <<RESET<<endl;
    Complejo c1(3, 2), c2(1, 4);
    Numero* sumaComplejo = c1.suma(&c2);
    Numero* restaComplejo = c1.resta(&c2);
    Numero* multiplicacionComplejo = c1.multiplicacion(&c2);
    cout << BLUE << "c1 = (3 + 2i), c2 = (1 + 4i)\n" << RESET;
    cout << BOLD << "Suma:            " << RESET << sumaComplejo->toString() << endl;
    cout << BOLD <<"Resta:           " << RESET<< restaComplejo->toString() << endl;
    cout << BOLD <<"Multiplicación:  " << RESET<< multiplicacionComplejo->toString() << endl;

    delete sumaComplejo;
    delete restaComplejo;
    delete multiplicacionComplejo;

    return 0;
}
