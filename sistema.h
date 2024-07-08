#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Astronauta {
private:
    string cpf;
    string nome;
    int idade;
    bool disponivel;
    bool morto;

public:
    Astronauta(string _cpf, string _nome, int _idade);

    string getCPF() const;
    string getNome() const;
    int getIdade() const;
    bool isDisponivel() const;
    void setDisponivel(bool disponibilidade);
    bool isMorto() const;
    void setMorto(bool estado);
};

class Voo {
private:
    int codigo;
    vector<Astronauta*> passageiros;
    bool planejamento;

public:
    Voo(int _codigo);

    int getCodigo() const;
    bool isPlanejamento() const;
    void setPlanejamento(bool estado);

    void adicionarPassageiro(Astronauta* astronauta);
    void removerPassageiro(const string& cpf);
    void listarPassageiros() const;

    bool isAstronautaNoVoo(const string& cpf) const;
    const vector<Astronauta*>& getPassageiros() const;
};

class SistemaGestao {
private:
    vector<Astronauta> astronautas;
    vector<Voo> voos;
    unordered_map<string, Astronauta*> mapaAstronautas;
    vector<Astronauta*> astronautasMortos;

public:
    void cadastrarAstronauta(const string& cpf, const string& nome, int idade);
    void cadastrarVoo(int codigo);
    void adicionarAstronautaEmVoo(const string& cpf, int codigoVoo);
    void removerAstronautaDeVoo(const string& cpf, int codigoVoo);
    void listarVoosPlanejados() const;
    void explodirVoo(int codigoVoo);
    void listarAstronautasMortos() const;
};

#endif // SISTEMA_H
