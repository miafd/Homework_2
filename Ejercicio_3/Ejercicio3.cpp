// Escriba una interfaz llamada “Numero” que indique la implementación de las
// operaciones suma, resta y multiplicación de números (si desea, puede también agregar
// la división), así como también un método denominado “toString” que muestra el
// número en formato string.
// a. De esta interfaz, se deben implementar las siguientes tres clases:
// • Clase “Entero”,
// • Clase “Real”,
// • Clase “Complejo”
// b. Verifique el funcionamiento de cada uno de estas clases mediante la
// implementación de cada una de las operaciones con los números que desee e
// imprima el resultado utilizando el método “toString”.

#include <iostream>
#include <string>
using namespace std;

class Numero {
    public:
    virtual Numero* suma (const Numero* num)=0;
    virtual Numero* resta (const Numero* num)=0;
    virtual Numero* multiplicacion (const Numero* num)=0;
    virtual string toString()=0;
    virtual ~Numero(){};
};

class Entero : public Numero {
    private:
    int valor;

    public:
    Entero(int v) : valor(v) {}

    Entero* suma (const Numero* num) override;
    Entero* resta (const Numero* num) override;
    Entero* multiplicacion (const Numero* num) override;
    string toString() override;
};
class Real : public Numero {
    private:
    double valor;

    public:
    Real(double v) : valor(v) {}

    Real* suma (const Numero* num) override;
    Real* resta (const Numero* num) override;
    Real* multiplicacion (const Numero* num) override;
    string toString() override;
};
class Complejo : public Numero {
    private:
    double real;
    double imaginario;

    public:
    Complejo(double r, double i) : real(r), imaginario(i) {}

    Complejo* suma (const Numero* num) override;
    Complejo* resta (const Numero* num) override;
    Complejo* multiplicacion (const Numero* num) override;
    string toString() override;
};

