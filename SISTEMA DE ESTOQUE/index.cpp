    #include <iostream>
    #include <map>
    #include <fstream>
    #include <sstream>
    #include <limits>
    #include <ctime>
    #include <iomanip>

    using namespace std;

    struct Produto {
        string nome;
        int quantidade;
        string validade;
        string fornecedor;
        float custo;
        float precoVenda;
        int estoqueMinimo;
        bool descontoAplicado;
        float desconto;
        string categoria;
        string historicoAlteracoes;
    };

    map<string, Produto> estoque;

    void limparBuffer() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void salvarEstoque() {
        ofstream arquivo("estoque.txt");
        if (!arquivo.is_open()) {
            cout << "Erro ao salvar estoque." << endl;
            return;
        }
        for (const auto& item : estoque) {
            const Produto& produto = item.second;
            arquivo << produto.nome << ";" << produto.quantidade << ";" 
                    << produto.validade << ";" << produto.fornecedor << ";" 
                    << produto.custo << ";" << produto.precoVenda << ";" 
                    << produto.estoqueMinimo << ";" << produto.descontoAplicado << ";"
                    << produto.desconto << ";" << produto.categoria << ";"
                    << produto.historicoAlteracoes << endl;
        }
        arquivo.close();
        cout << "Estoque salvo com sucesso!" << endl;
    }

    void carregarEstoque() {
        ifstream arquivo("estoque.txt");
        if (!arquivo.is_open()) {
            cout << "Nenhum estoque salvo foi encontrado." << endl;
            return;
        }
        Produto produto;
        string linha;
        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            getline(ss, produto.nome, ';');
            ss >> produto.quantidade;
            ss.ignore();
            getline(ss, produto.validade, ';');
            getline(ss, produto.fornecedor, ';');
            ss >> produto.custo;
            ss.ignore();
            ss >> produto.precoVenda;
            ss.ignore();
            ss >> produto.estoqueMinimo;
            ss.ignore();
            ss >> produto.descontoAplicado;
            ss.ignore();
            ss >> produto.desconto;
            ss.ignore();
            getline(ss, produto.categoria, ';');
            getline(ss, produto.historicoAlteracoes);

            estoque[produto.nome] = produto;
        }
        arquivo.close();
        cout << "Estoque carregado com sucesso!" << endl;
    }

    bool validarData(const string& data) {
        struct tm tm = {};
        stringstream ss(data);
        ss >> get_time(&tm, "%d/%m/%Y");
        return !ss.fail();
    }

    void adicionarProduto() {
        Produto produto;

        cout << "Digite o nome do produto: ";
        cin.ignore();
        getline(cin, produto.nome);

        cout << "Digite a quantidade do produto: ";
        while (!(cin >> produto.quantidade) || produto.quantidade < 0) {
            cout << "Quantidade invalida. Tente novamente: ";
            cin.clear();
            limparBuffer();
        }

        cout << "Digite a data de validade do produto (dd/mm/aaaa): ";
        cin >> produto.validade;
        if (!validarData(produto.validade)) {
            cout << "Data de validade invalida. Tente novamente." << endl;
            return;
        }

        cout << "Digite o nome do fornecedor do produto: ";
        cin.ignore();
        getline(cin, produto.fornecedor);

        cout << "Digite o custo do produto: ";
        while (!(cin >> produto.custo) || produto.custo < 0) {
            cout << "Custo invalido. Tente novamente: ";
            cin.clear();
            limparBuffer();
        }

        cout << "Digite a margem de lucro (%): ";
        float margem;
        while (!(cin >> margem) || margem < 0) {
            cout << "Margem invalida. Tente novamente: ";
            cin.clear();
            limparBuffer();
        }
        produto.precoVenda = produto.custo * (1 + margem / 100);

        cout << "Digite o estoque minimo para alerta: ";
        while (!(cin >> produto.estoqueMinimo) || produto.estoqueMinimo < 0) {
            cout << "Estoque minimo invalido. Tente novamente: ";
            cin.clear();
            limparBuffer();
        }

        cout << "Digite a categoria do produto (Ex: Alimentos, Bebidas, Higiene): ";
        cin.ignore();
        getline(cin, produto.categoria);

        cout << "Deseja aplicar um desconto no produto? (1 - Sim, 0 - Não): ";
        int descontoEscolha;
        cin >> descontoEscolha;
        produto.descontoAplicado = (descontoEscolha == 1);

        if (produto.descontoAplicado) {
            cout << "Digite o percentual de desconto: ";
            while (!(cin >> produto.desconto) || produto.desconto < 0 || produto.desconto > 100) {
                cout << "Desconto invalido. Tente novamente: ";
                cin.clear();
                limparBuffer();
            }
            produto.precoVenda -= produto.precoVenda * (produto.desconto / 100);
        }

        produto.historicoAlteracoes = "Produto adicionado ao estoque.";

        estoque[produto.nome] = produto;

        cout << "Produto adicionado com sucesso!" << endl;
    }

    void buscarProduto() {
        string nome;
        cout << "Digite o nome do produto que deseja buscar: ";
        cin.ignore();
        getline(cin, nome);

        if (estoque.find(nome) != estoque.end()) {
            Produto produto = estoque[nome];
            cout << "Nome: " << produto.nome << endl;
            cout << "Quantidade: " << produto.quantidade << endl;
            cout << "Data de Validade: " << produto.validade << endl;
            cout << "Fornecedor: " << produto.fornecedor << endl;
            cout << "Custo: R$ " << produto.custo << endl;
            cout << "Preco de Venda: R$ " << produto.precoVenda << endl;
            cout << "Estoque Minimo: " << produto.estoqueMinimo << endl;
            cout << "Categoria: " << produto.categoria << endl;
            cout << "Desconto Aplicado: " << (produto.descontoAplicado ? "Sim" : "Não") << endl;
            cout << "Historico de Alteracoes: " << produto.historicoAlteracoes << endl;
            cout << "--------------------------" << endl;
        } else {
            cout << "Produto nao encontrado." << endl;
        }
    }

    void exibirEstoque() {
        if (estoque.empty()) {
            cout << "O estoque esta vazio." << endl;
            return;
        }

        cout << "Estoque atual:" << endl;
        for (const auto& item : estoque) {
            const Produto& produto = item.second;
            cout << "Nome: " << produto.nome << endl;
            cout << "Quantidade: " << produto.quantidade << endl;
            cout << "Data de Validade: " << produto.validade << endl;
            cout << "Fornecedor: " << produto.fornecedor << endl;
            cout << "Custo: R$ " << produto.custo << endl;
            cout << "Preco de Venda: R$ " << produto.precoVenda << endl;
            cout << "Estoque Minimo: " << produto.estoqueMinimo << endl;
            cout << "Categoria: " << produto.categoria << endl;
            cout << "Desconto Aplicado: " << (produto.descontoAplicado ? "Sim" : "Não") << endl;
            cout << "Historico de Alteracoes: " << produto.historicoAlteracoes << endl;
            cout << "--------------------------" << endl;
        }
    }

    void gerarRelatorioTXT() {
        ofstream relatorio("relatorio.txt");
        if (!relatorio.is_open()) {
            cout << "Erro ao criar arquivo de relatorio." << endl;
            return;
        }

        relatorio << "Relatorio de Estoque" << endl;
        for (const auto& item : estoque) {
            const Produto& produto = item.second;
            relatorio << "Nome: " << produto.nome << endl;
            relatorio << "Quantidade: " << produto.quantidade << endl;
            relatorio << "Data de Validade: " << produto.validade << endl;
            relatorio << "Fornecedor: " << produto.fornecedor << endl;
            relatorio << "Custo: R$ " << produto.custo << endl;
            relatorio << "Preco de Venda: R$ " << produto.precoVenda << endl;
            relatorio << "Estoque Minimo: " << produto.estoqueMinimo << endl;
            relatorio << "Categoria: " << produto.categoria << endl;
            relatorio << "Desconto Aplicado: " << (produto.descontoAplicado ? "Sim" : "Não") << endl;
            relatorio << "Historico de Alteracoes: " << produto.historicoAlteracoes << endl;
            relatorio << "--------------------------" << endl;
        }
        relatorio.close();
        cout << "Relatorio gerado com sucesso!" << endl;
    }

    int main() {
        carregarEstoque();
        int opcao;

        do {
            cout << "Menu:" << endl;
            cout << "1. Adicionar Produto" << endl;
            cout << "2. Buscar Produto" << endl;
            cout << "3. Exibir Estoque" << endl;
            cout << "4. Gerar Relatorio" << endl;
            cout << "5. Salvar Estoque" << endl;
            cout << "6. Sair" << endl;
            cout << "Escolha uma opcao: ";
            cin >> opcao;

            switch (opcao) {
                case 1:
                    adicionarProduto();
                    break;
                case 2:
                    buscarProduto();
                    break;
                case 3:
                    exibirEstoque();
                    break;
                case 4:
                    gerarRelatorioTXT();
                    break;
                case 5:
                    salvarEstoque();
                    break;
                case 6:
                    cout << "Saindo..." << endl;
                    break;
                default:
                    cout << "Opcao invalida!" << endl;
            }
        } while (opcao != 6);

        return 0;
    }
