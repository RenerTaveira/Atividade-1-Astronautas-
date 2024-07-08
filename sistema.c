#include "sistema.h"
#include <iostream>

using namespace std;

// Implementações da classe Astronauta
Astronauta::Astronauta(string _cpf, string _nome, int _idade) 
    : cpf(_cpf), nome(_nome), idade(_idade), disponivel(true), morto(false) {}

string Astronauta::getCPF() const { return cpf; }
string Astronauta::getNome() const { return nome; }
int Astronauta::getIdade() const { return idade; }
bool Astronauta::isDisponivel() const { return disponivel; }
void Astronauta::setDisponivel(bool disponibilidade) { disponivel = disponibilidade; }
bool Astronauta::isMorto() const { return morto; }
void Astronauta::setMorto(bool estado) { morto = estado; }

// Implementações da classe Voo
Voo::Voo(int _codigo) : codigo(_codigo), planejamento(true) {}

int Voo::getCodigo() const { return codigo; }
bool Voo::isPlanejamento() const { return planejamento; }
void Voo::setPlanejamento(bool estado) { planejamento = estado; }

void Voo::adicionarPassageiro(Astronauta* astronauta) {
    if (planejamento) {
        passageiros.push_back(astronauta);
        astronauta->setDisponivel(false);
    }
}

void Voo::removerPassageiro(const string& cpf) {
    if (planejamento) {
        for (auto it = passageiros.begin(); it != passageiros.end(); ++it) {
            if ((*it)->getCPF() == cpf) {
                (*it)->setDisponivel(true);
                passageiros.erase(it);
                break;
            }
        }
    }
}

void Voo::listarPassageiros() const {
    cout << "Passageiros do voo " << codigo << ":" << endl;
    for (const auto& astronauta : passageiros) {
        cout << "CPF: " << astronauta->getCPF() << ", Nome: " << astronauta->getNome() << endl;
    }
}

bool Voo::isAstronautaNoVoo(const string& cpf) const {
    for (const auto& astronauta : passageiros) {
        if (astronauta->getCPF() == cpf) {
            return true;
        }
    }
    return false;
}

const vector<Astronauta*>& Voo::getPassageiros() const {
    return passageiros;
}

// Implementações da classe SistemaGestao
void SistemaGestao::cadastrarAstronauta(const string& cpf, const string& nome, int idade) {
    astronautas.push_back(Astronauta(cpf, nome, idade));
    mapaAstronautas[cpf] = &astronautas.back();
    if (idade < 18) {
        cout << "A idade do astronauta deve ser maior ou igual a 18 anos" << endl;
    }
}

void SistemaGestao::cadastrarVoo(int codigo) {
    voos.push_back(Voo(codigo));
}

void SistemaGestao::adicionarAstronautaEmVoo(const string& cpf, int codigoVoo) {
    if (mapaAstronautas.find(cpf) != mapaAstronautas.end()) {
        Astronauta* astronauta = mapaAstronautas[cpf];
        if (astronauta->isDisponivel()) {
            for (auto& voo : voos) {
                if (voo.getCodigo() == codigoVoo && voo.isPlanejamento()) {
                    voo.adicionarPassageiro(astronauta);
                    cout << "Astronauta adicionado ao voo com sucesso!" << endl;
                    return;
                }
            }
        }
    }
    cout << "Não foi possível adicionar o astronauta ao voo." << endl;
}

void SistemaGestao::removerAstronautaDeVoo(const string& cpf, int codigoVoo) {
    for (auto& voo : voos) {
        if (voo.getCodigo() == codigoVoo && voo.isPlanejamento()) {
            voo.removerPassageiro(cpf);
            cout << "Astronauta removido do voo com sucesso!" << endl;
            return;
        }
    }
    cout << "Não foi possível remover o astronauta do voo." << endl;
}

void SistemaGestao::listarVoosPlanejados() const {
    cout << "Voos Planejados:" << endl;
    for (const auto& voo : voos) {
        if (voo.isPlanejamento()) {
            cout << "Código do Voo: " << voo.getCodigo() << endl;
            voo.listarPassageiros();
            cout << endl;
        }
    }
}

void SistemaGestao::explodirVoo(int codigoVoo) {
    for (auto& voo : voos) {
        if (voo.getCodigo() == codigoVoo) {
            voo.setPlanejamento(false);
            for (auto astronauta : voo.getPassageiros()) {
                astronauta->setMorto(true);
                astronautasMortos.push_back(astronauta);
            }
            cout << "Voo explodido! Todos os astronautas estão mortos." << endl;
            return;
        }
    }
    cout << "Não foi possível encontrar o voo especificado." << endl;
}

void SistemaGestao::listarAstronautasMortos() const {
    cout << "Astronautas Mortos:" << endl;
    for (const auto& astronauta : astronautasMortos) {
        cout << "CPF: " << astronauta->getCPF() << ", Nome: " << astronauta->getNome() << endl;
    }
}

// Função main
int main() {
    SistemaGestao sistema;
    int opcao;

    do {
        cout << "\nEscolha uma opção:" << endl;
        cout << "1. Cadastrar Astronauta" << endl;
        cout << "2. Cadastrar Voo" << endl;
        cout << "3. Adicionar Astronauta em Voo" << endl;
        cout << "4. Remover Astronauta de Voo" << endl;
        cout << "5. Listar Voos Planejados" << endl;
        cout << "6. Explodir Voo" << endl;
        cout << "7. Listar Astronautas Mortos" << endl;
        cout << "0. Sair" << endl;
        cout << "Opção: ";
        cin >> opcao;

        switch(opcao) {
            case 1: {
                string cpf, nome;
                int idade;
                cout << "CPF: ";
                cin >> cpf;
                cout << "Nome: ";
                cin.ignore();
                getline(cin, nome);
                cout << "Idade: ";
                cin >> idade;
                sistema.cadastrarAstronauta(cpf, nome, idade);
                break;
            }
            case 2: {
                int codigo;
                cout << "Código do Voo: ";
                cin >> codigo;
                sistema.cadastrarVoo(codigo);
                break;
            }
            case 3: {
                string cpf;
                int codigoVoo;
                cout << "CPF do Astronauta: ";
                cin >> cpf;
                cout << "Código do Voo: ";
                cin >> codigoVoo;
                sistema.adicionarAstronautaEmVoo(cpf, codigoVoo);
                break;
            }
            case 4: {
                string cpf;
                int codigoVoo;
                cout << "CPF do Astronauta: ";
                cin >> cpf;
                cout << "Código do Voo: ";
                cin >> codigoVoo;
                sistema.removerAstronautaDeVoo(cpf, codigoVoo);
                break;
            }
            case 5: {
                sistema.listarVoosPlanejados();
                break;
            }
            case 6: {
                int codigoVoo;
                cout << "Código do Voo: ";
                cin >> codigoVoo;
                sistema.explodirVoo(codigoVoo);
                break;
            }
            case 7: {
                sistema.listarAstronautasMortos();
                break;
            }
        }
    } while(opcao != 0);

    return 0;
}
