#include <iostream>
#include <string>
using namespace std;

class CuentaBancaria{
    protected:
    double balance;
    string titularCuenta;

    public: 

    //Constructor 
    CuentaBancaria(double b, string t);

    //Métodos
    virtual void depositar(double cantidad);
    virtual void retirar(double cantidad) = 0; // Método virtual puro
    virtual void mostrarInfo() const = 0; // Método virtual puro
    virtual ~CuentaBancaria() {} // Destructor virtual	

    friend class CuentaCorriente;
};

//Subclase CajaDeAhorro
class CajaDeAhorro : public CuentaBancaria{
    private:
    mutable int contadorMostrar = 0;  // mutable permite modificarlo en métodos const

    public:
    CajaDeAhorro(string titular, double balance);

    void retirar(double cantidad) override;
    void mostrarInfo() const override;
};

class CuentaCorriente : public CuentaBancaria{
    private:
    CajaDeAhorro* ahorro; // Puntero CajaDeAhorro

    public:
    CuentaCorriente(string titular, double balance, CajaDeAhorro* ahorro);

    //Métodos
    void retirar(double cantidad) override;
    void mostrarInfo() const override;
    void verificarFondos(const CuentaCorriente& cc);
};