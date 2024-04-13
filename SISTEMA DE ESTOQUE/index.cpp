#include <iostream>
#include <map>
#include <fstream>

using namespace std;

struct Produto {
    string nome;
    int quantidade;
    string validade;
    string fornecedor;
    float custo;
    float precoVenda;
};

map<string, Produto> estoque; // Mapa para armazenar os produtos

void adicionarProduto() {
    Produto produto;

    cout << "Digite o nome do produto: ";
    cin >> produto.nome;

    cout << "Digite a quantidade do produto: ";
    cin >> produto.quantidade;

    cout << "Digite a data de validade do produto (dd/mm/aaaa): ";
    cin >> produto.validade;

    cout << "Digite o nome do fornecedor do produto: ";
    cin >> produto.fornecedor;

    cout << "Digite o custo do produto: ";
    cin >> produto.custo;

    // Calcula o preço de venda como o dobro do custo
    produto.precoVenda = produto.custo * 2;

    estoque[produto.nome] = produto;

    cout << "Produto adicionado com sucesso!" << endl;
}

void removerProduto() {
    string nome;

    cout << "Digite o nome do produto a ser removido: ";
    cin >> nome;

    if (estoque.find(nome) != estoque.end()) {
        estoque.erase(nome);
        cout << "Produto removido com sucesso!" << endl;
    } else {
        cout << "Produto nao encontrado." << endl;
    }
}

void editarProduto() {
    string nome;

    cout << "Digite o nome do produto a ser editado: ";
    cin >> nome;

    if (estoque.find(nome) != estoque.end()) {
        Produto& produto = estoque[nome];

        cout << "Digite a nova quantidade do produto: ";
        cin >> produto.quantidade;

        cout << "Digite a nova data de validade do produto (dd/mm/aaaa): ";
        cin >> produto.validade;

        cout << "Digite o novo nome do fornecedor do produto: ";
        cin >> produto.fornecedor;

        cout << "Produto editado com sucesso!" << endl;
    } else {
        cout << "Produto nao encontrado." << endl;
    }
}

void exibirEstoque() {
    cout << "Estoque atual:" << endl;
    for (map<string, Produto>::iterator it = estoque.begin(); it != estoque.end(); ++it) {
        cout << "Nome: " << it->second.nome << endl;
        cout << "Quantidade: " << it->second.quantidade << endl;
        cout << "Data de Validade: " << it->second.validade << endl;
        cout << "Fornecedor: " << it->second.fornecedor << endl;
        cout << "Custo: R$ " << it->second.custo << endl;
        cout << "Preco de Venda: R$ " << it->second.precoVenda << endl;
        cout << "--------------------------" << endl;
    }
}

void gerarRelatorioTXT() {
    ofstream relatorio("relatorio.txt");
    if (!relatorio.is_open()) {
        cout << "Erro ao criar arquivo de relatorio" << endl;
        return;
    }

    relatorio << "Relatorio de Estoque" << endl;
    for (map<string, Produto>::iterator it = estoque.begin(); it != estoque.end(); ++it) {
        relatorio << "Nome: " << it->second.nome << endl;
        relatorio << "Quantidade: " << it->second.quantidade << endl;
        relatorio << "Data de Validade: " << it->second.validade << endl;
        relatorio << "Fornecedor: " << it->second.fornecedor << endl;
        relatorio << "Custo: R$ " << it->second.custo << endl;
        relatorio << "Preco de Venda: R$ " << it->second.precoVenda << endl;
        relatorio << "--------------------------" << endl;
    }

    relatorio.close();

    cout << "Relatorio gerado com sucesso (relatorio.txt)" << endl;
}

int main() {
    int escolha;

    do {
        cout << "======================================" << endl;
        cout <<"Sistema de Gerenciamento de Estoque  v1.0"<<endl;
        cout << "Escolha uma opcao:" << endl;
        cout << "1. Adicionar Produto" << endl;
        cout << "2. Remover Produto" << endl;
        cout << "3. Editar Produto" << endl;
        cout << "4. Exibir Estoque" << endl;
        cout << "5. Gerar Relatorio em TXT" << endl;
        cout << "6. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> escolha;

        switch (escolha) {
            case 1:
                adicionarProduto();
                break;
            case 2:
                removerProduto();
                break;
            case 3:
                editarProduto();
                break;
            case 4:
                exibirEstoque();
                break;
            case 5:
                gerarRelatorioTXT();
                break;
            case 6:
                cout << "Saindo do programa..." << endl;
                break;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
        }
    } while (escolha != 6);

    return 0;
}
