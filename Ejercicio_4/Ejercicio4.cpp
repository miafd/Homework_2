#include "Ejercicio4.h"

CuentaBancaria::CuentaBancaria(double b, string t) : balance(b), titularCuenta(t) {}
void CuentaBancaria::depositar(double cantidad){
    balance += cantidad;
}

CajaDeAhorro:: CajaDeAhorro(string titular, double balance) : CuentaBancaria(balance,titular){}

void CajaDeAhorro::retirar(double cantidad) {
    if (cantidad>balance) {
        cout<< "Fondos Insuficientes en Caja de Ahorro" <<endl;
    } else balance-=cantidad;

}

void CajaDeAhorro:: mostrarInfo () const{
    cout << "Cuenta: Caja de Ahorro\nTitular: " << titularCuenta << "\nBalance: $" << balance << endl;
    contadorMostrar++;
    if (contadorMostrar > 2) {
        cout << "Se descuenta $20 por mostrar la información más de 2 veces." << endl;
        const_cast<CajaDeAhorro*>(this)->balance -= 20;  // Eliminamos $20 usando const_cast
    }
}

CuentaCorriente::CuentaCorriente(string titular, double balance, CajaDeAhorro* ahorro) : CuentaBancaria(balance, titular), ahorro(ahorro) {}

void CuentaCorriente:: retirar(double cantidad){
    if (cantidad <= balance) balance -= cantidad;
    else if (ahorro->balance >= cantidad) {
        ahorro->retirar(cantidad);
        cout << "Fondos retirados desde la Caja de Ahorro." << endl;
    } else 
        cout << "No hay fondos suficientes en ninguna cuenta." << endl;
}

void CuentaCorriente:: mostrarInfo() const{
    cout << "Cuenta: Cuenta Corriente\nTitular: " << titularCuenta << "\nBalance: $" << balance << endl;
}

int main() {
    CajaDeAhorro caja("Juan Pérez", 100);
    CuentaCorriente cuenta("Juan Pérez", 50, &caja);

    // Depósitos
    cout << "\nDepósito de $50 en la cuenta corriente...\n";
    cuenta.depositar(50);

    // Mostrar información de ambas cuentas
    cout << "\nInformación de la Caja de Ahorro:" << endl;
    caja.mostrarInfo();
    cout << "\nInformación de la Cuenta Corriente:" << endl;
    cuenta.mostrarInfo();

    // Intentar retirar más de lo permitido
    cout << "\nIntentando retirar $200 desde la cuenta corriente...\n";
    cuenta.retirar(200);

    // Intentar retirar una cantidad válida
    cout << "\nRetirando $80 desde la cuenta corriente...\n";
    cuenta.retirar(80);
    cuenta.mostrarInfo();

     // Intentar retirar una cantidad válida (va a retirar de la caja)
     cout << "\nRetirando $30 desde la cuenta corriente...\n";
     cuenta.retirar(30);
     cuenta.mostrarInfo();
     caja.mostrarInfo();

    // Mostrar más de 2 veces la info de Caja de Ahorro
    cout << "\nMostrando información varias veces...\n";
    caja.mostrarInfo(); //Tercera vez que muestra la información, descontará 20
    caja.mostrarInfo(); //Muestra que tiene 20 menos (volverá a descontar 20)


    return 0;
}




