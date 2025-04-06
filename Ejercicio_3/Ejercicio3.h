#ifndef Ejercicio3_H
#define Ejercicio3_H

#include <iostream>
#include <string>
#include <iostream>


#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define BOLD    "\033[1m"

using namespace std;

class Numero {
    public:
    virtual Numero* suma (const Numero* otro)=0;
    virtual Numero* resta (const Numero* otro)=0;
    virtual Numero* multiplicacion (const Numero* otro)=0;
    virtual string toString()=0;
    virtual ~Numero(){};
};

class Entero : public Numero {
    private:
    int valor;

    public:
    Entero(int v) : valor(v) {}

    Numero* suma (const Numero* otro) override;
    Numero* resta (const Numero* otro) override;
    Numero* multiplicacion (const Numero* otro) override;
    string toString() override;
};

class Real : public Numero {
    private:
    double valor;

    public:
    Real(double v) : valor(v) {}

    Numero* suma (const Numero* otro) override;
    Numero* resta (const Numero* otro) override;
    Numero* multiplicacion (const Numero* otro) override;
    string toString() override;
};

class Complejo : public Numero {
    private:
    double real;
    double imaginario;

    public:
    Complejo(double r, double i) : real(r), imaginario(i) {}

    Numero* suma (const Numero* otro) override;
    Numero* resta (const Numero* otro) override;
    Numero* multiplicacion (const Numero* otro) override;
    string toString() override;
};


#endif