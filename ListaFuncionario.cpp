#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

struct RegistroFuncionario {
    int id;
    string nomeCompleto;
    double vencimento;
    RegistroFuncionario* proximo;
};

class GerenciadorFuncionarios {
private:
    RegistroFuncionario* cabeca;

    bool existeID(int idBusca) const {
        for (RegistroFuncionario* ptr = cabeca; ptr != nullptr; ptr = ptr->proximo) {
            if (ptr->id == idBusca) return true;
        }
        return false;
    }

public:
    GerenciadorFuncionarios() : cabeca(nullptr) {}

    ~GerenciadorFuncionarios() {
        while (cabeca != nullptr) {
            RegistroFuncionario* temp = cabeca;
            cabeca = cabeca->proximo;
            delete temp;
        }
    }

    void adicionarFuncionario(int idNovo, const string& nomeNovo, double salarioNovo) {
        if (existeID(idNovo)) {
            cout << "Erro: ID já está em uso!" << endl;
            return;
        }

        RegistroFuncionario* novoRegistro = new RegistroFuncionario{idNovo, nomeNovo, salarioNovo, cabeca};
        cabeca = novoRegistro;

        cout << "Novo funcionário cadastrado com sucesso!" << endl;
    }

    void removerFuncionario(int idRemover) {
        RegistroFuncionario* atual = cabeca;
        RegistroFuncionario* anterior = nullptr;

        while (atual && atual->id != idRemover) {
            anterior = atual;
            atual = atual->proximo;
        }

        if (!atual) {
            cout << "Funcionário não localizado." << endl;
            return;
        }

        if (!anterior) {
            cabeca = atual->proximo;
        } else {
            anterior->proximo = atual->proximo;
        }

        delete atual;
        cout << "Registro removido com sucesso." << endl;
    }

    void buscarFuncionario(int idBusca) const {
        RegistroFuncionario* ptr = cabeca;
        while (ptr) {
            if (ptr->id == idBusca) {
                exibirDetalhes(*ptr);
                return;
            }
            ptr = ptr->proximo;
        }
        cout << "Funcionário não encontrado." << endl;
    }

    void exibirLista() const {
        if (!cabeca) {
            cout << "Nenhum registro disponível." << endl;
            return;
        }

        double somaTotal = 0.0;
        RegistroFuncionario* ptr = cabeca;

        cout << "\n--- FUNCIONÁRIOS REGISTRADOS ---" << endl;
        while (ptr) {
            exibirDetalhes(*ptr);
            somaTotal += ptr->vencimento;
            ptr = ptr->proximo;
        }
        cout << "Soma dos salários: R$ " << somaTotal << endl;
    }

private:
    void exibirDetalhes(const RegistroFuncionario& rf) const {
        cout << "ID         : " << rf.id << endl;
        cout << "Nome       : " << rf.nomeCompleto << endl;
        cout << "Salário    : R$ " << rf.vencimento << endl;
        cout << "-------------------------------" << endl;
    }
};

int main() {
    GerenciadorFuncionarios sistemaRH;
    int escolha;

    do {
        cout << "\n== MENU PRINCIPAL ==" << endl;
        cout << "0 - Encerrar" << endl;
        cout << "1 - Adicionar funcionário" << endl;
        cout << "2 - Remover funcionário" << endl;
        cout << "3 - Buscar funcionário" << endl;
        cout << "4 - Exibir todos os registros" << endl;
        cout << "Selecione uma opção: ";
        cin >> escolha;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada inválida. Tente novamente!" << endl;
            continue;
        }

        switch (escolha) {
            case 0:
                break;
            case 1: {
                int id;
                string nome;
                double salario;

                cout << "Informe o ID do funcionário: ";
                cin >> id;
                cin.ignore();

                cout << "Informe o nome completo: ";
                getline(cin, nome);

                cout << "Informe o salário: ";
                cin >> salario;

                sistemaRH.adicionarFuncionario(id, nome, salario);
                break;
            }
            case 2: {
                int id;
                cout << "ID a ser removido: ";
                cin >> id;
                sistemaRH.removerFuncionario(id);
                break;
            }
            case 3: {
                int id;
                cout << "ID a ser buscado: ";
                cin >> id;
                sistemaRH.buscarFuncionario(id);
                break;
            }
            case 4:
                sistemaRH.exibirLista();
                break;
            default:
                cout << "Opção inválida. Escolha entre 0 e 4." << endl;
        }
    } while (escolha != 0);

    return 0;
}
