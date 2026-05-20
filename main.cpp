#include <iostream>
#include <string>
#include <stdexcept>

class Conta {
private:
    int numero;
    std::string titular;
    double saldo;

public:
    Conta(int num, std::string tit, double sal = 0.0) 
        : numero(num), titular(tit), saldo(sal) {}

    Conta& operator+=(double valor) {
        if (valor > 0) {
            saldo += valor;
        }
        return *this;
    }

    Conta operator-(double valor) const {
        if (valor > saldo) {
            throw std::runtime_error("Saldo insuficiente para realizar a operacao!");
        }
        return Conta(numero, titular, saldo - valor);
    }

    friend std::ostream& operator<<(std::ostream& os, const Conta& c) {
        os << "Conta: " << c.numero 
           << " | Titular: " << c.titular 
           << " | Saldo: R$ " << c.saldo;
        return os;
    }
};

int main() {
    Conta contaOrigem(101, "Alice", 1000.00);
    Conta contaDestino(202, "Bob", 500.00);

    std::cout << "--- Estado Inicial ---\n";
    std::cout << contaOrigem << "\n";
    std::cout << contaDestino << "\n\n";

    std::cout << "--- Depositando R$ 500 na Conta da Alice ---\n";
    contaOrigem += 500.00;
    std::cout << contaOrigem << "\n\n";

    std::cout << "--- Transferindo R$ 200 da Alice para o Bob ---\n";
    try {
        contaOrigem = contaOrigem - 200.00;
        contaDestino += 200.00;             
        std::cout << "Transferencia realizada com sucesso!\n";
    } catch (const std::exception& e) {
        std::cout << "Erro: " << e.what() << "\n";
    }
    
    std::cout << contaOrigem << "\n";
    std::cout << contaDestino << "\n\n";

    std::cout << "--- Tentando transferir R$ 2000 da Alice para o Bob ---\n";
    try {
        contaOrigem = contaOrigem - 2000.00;
        contaDestino += 2000.00; 
    } catch (const std::exception& e) {
        std::cerr << "Erro na operacao: " << e.what() << "\n";
    }

    return 0;
}