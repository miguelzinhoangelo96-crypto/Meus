#include <iostream>
#include <string>
using namespace std;

class ContaBancaria {
protected:
    double saldo;
    string titular;

public:
    ContaBancaria(string nome, double valorInicial) : titular(nome), saldo(valorInicial) {}

    virtual void sacar(double valor) {
        if(valor > saldo) {
            cout << "Saldo insuficiente." << endl;
        } else {
            saldo -= valor;
            cout << "Saque de " << valor << " realizado. Saldo atual: " << saldo << endl;
        }
    }

    virtual void depositar(double valor) {
        saldo += valor;
        cout << "Deposito de " << valor << " realizado. Saldo atual: " << saldo << endl;
    }

    double getSaldo() const { 
        return saldo; 
    }
};

// Conta Corrente
class ContaCorrente : public ContaBancaria {
public:
    ContaCorrente(string nome, double valorInicial) : ContaBancaria(nome, valorInicial) {}

    void sacar(double valor) override {
        double taxa = 2.5;
        double total = valor + taxa;
        if(total > saldo) {
            cout << "Saldo insuficiente para saque com taxa." << endl;
        } else {
            saldo -= total;
            cout << "Saque Conta Corrente: " << valor << " + taxa " << taxa << ". Saldo: " << saldo << endl;
        }
    }
};

// Conta Poupança
class ContaPoupanca : public ContaBancaria {
public:
    ContaPoupanca(string nome, double valorInicial) : ContaBancaria(nome, valorInicial) {}

    void sacar(double valor) override {
        if(valor > saldo) {
            cout << "Saldo insuficiente." << endl;
        } else {
            saldo -= valor;
            cout << "Saque Conta Poupanca: " << valor << ". Saldo: " << saldo << endl;
        }
    }
};

// Conta Salário
class ContaSalario : public ContaBancaria {
public:
    ContaSalario(string nome, double valorInicial) : ContaBancaria(nome, valorInicial) {}

    void sacar(double valor) override {
        if(valor > 1000) {
            cout << "Limite maximo de saque para Conta Salario e 1000." << endl;
        } else if(valor > saldo) {
            cout << "Saldo insuficiente." << endl;
        } else {
            saldo -= valor;
            cout << "Saque Conta Salario: " << valor << ". Saldo: " << saldo << endl;
        }
    }
};

int main() {
    int tipo;
    string nome;
    double saldoInicial;

    cout << "Nome do titular: ";
    getline(cin, nome);

    cout << "\nEscolha o tipo de conta:\n"
         << "1 - Conta Corrente\n"
         << "2 - Conta Poupanca\n"
         << "3 - Conta Salario\n"
         << "Opcao: ";
    cin >> tipo;

    cout << "Saldo inicial: ";
    cin >> saldoInicial;

    ContaBancaria* conta;

    if(tipo == 1)      conta = new ContaCorrente(nome, saldoInicial);
    else if(tipo == 2) conta = new ContaPoupanca(nome, saldoInicial);
    else               conta = new ContaSalario(nome, saldoInicial);

    int opcao;
    double valor;

    do {
        cout << "\n=== MENU ===\n"
             << "1 - Sacar\n"
             << "2 - Depositar\n"
             << "3 - Consultar saldo\n"
             << "0 - Sair\n"
             << "Opcao: ";
        cin >> opcao;

        switch(opcao) {
            case 1:
                cout << "Valor do saque: ";
                cin >> valor;
                conta->sacar(valor);
                break;

            case 2:
                cout << "Valor do deposito: ";
                cin >> valor;
                conta->depositar(valor);
                break;

            case 3:
                cout << "Saldo atual: " << conta->getSaldo() << endl;
                break;

            case 0:
                cout << "Encerrando..." << endl;
                break;

            default:
                cout << "Opcao invalida." << endl;
        }

    } while(opcao != 0);

    delete conta;
    return 0;
}