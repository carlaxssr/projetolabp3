#include <iostream>
#include <string>
#include <unordered_map>
#include <limits> 

struct Usuario {
    std::string nome;
    std::string nomePessoal;
    int idade;
    std::string contato;
    double saldo;
    std::string senha;
};

std::unordered_map<std::string, Usuario> usuarios;

bool obterIdadeValida(Usuario& novoUsuario) {
    std::cout << "Digite a IDADE: ";

    std::string input;
    std::cin >> input;

    try {
        size_t pos;
        novoUsuario.idade = std::stoi(input, &pos);

        if (pos != input.size()) {
            throw std::invalid_argument("Contem caracteres invalidos.");
        }

        if (novoUsuario.idade > 0) {
            if (novoUsuario.idade < 16) {
                std::cout << "Desculpe, voce nao possui idade suficiente para abrir uma conta na carteira digital.\n";
                return false;
            }
            return true; // Retorna true se a idade for válida
        } else {
            std::cout << "Idade invalida. Insira um valor nao-negativo.\n";
        }
    } catch (const std::invalid_argument& e) {
        std::cout << "Entrada invalida. " << e.what() << "\n";
        std::cin.clear(); // Limpar o estado de erro
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar entrada inválida
    }

    return false; // Retorna false se a entrada for inválida
}

void cadastrarUsuario() {
    Usuario novoUsuario;

    std::cout << "Digite o nome de USUARIO: ";
    std::cin >> std::ws;
    std::getline(std::cin, novoUsuario.nome);

    // Verificar se o nome de usuário já existe
    if (usuarios.find(novoUsuario.nome) != usuarios.end()) {
        std::cout << "Nome de usuario ja existe. Escolha outro.\n";
        return;
    }

    std::cout << "Digite o seu NOME: ";
    std::cin >> std::ws;
    std::getline(std::cin, novoUsuario.nomePessoal);
    
    while (!obterIdadeValida(novoUsuario)) {
        // Continua pedindo até obter uma idade válida
    }

    std::cout << "Digite o CONTATO (email): ";
    std::cin >> novoUsuario.contato;

    std::cout << "Digite a SENHA: ";
    std::cin >> novoUsuario.senha;

    novoUsuario.saldo = 0.0;

    // Armazenar o novo usuário no mapa de usuários
    usuarios[novoUsuario.nome] = novoUsuario;

    std::cout << "\nCadastro realizado com sucesso!\n\n";
}

Usuario* fazerLogin() {
    std::string nomeUsuario, senha;
    std::cout << "Digite o nome de usuario: ";
    std::cin >> std::ws;
    std::getline(std::cin, nomeUsuario);

    std::cout << "Digite a senha: ";
    std::cin >> senha;

    // Verificar se o usuário existe e a senha está correta
    auto it = usuarios.find(nomeUsuario);
    if (it != usuarios.end() && it->second.senha == senha) {
        std::cout << "\nLogin realizado com sucesso!\n\n";
        return &it->second;
    } else {
        std::cout << "\nNome de usuario ou senha incorretos.\n\n";
        return nullptr;
    }
}

void alterarDadosUsuario(Usuario& usuario) {
    std::cout << "Alterar Dados Pessoais:\n";
    std::cout << "1. Usuario\n";
    std::cout << "2. Nome\n";
    std::cout << "3. Idade\n";
    std::cout << "4. Contato (E-mail)\n";
    std::cout << "5. Senha\n";
    std::cout << "Escolha uma opcao: ";

    int escolha;
    std::cin >> escolha;
   

    switch (escolha) {
        case 1: {
            std::cout << "Novo Nome de USUARIO: ";
            std::cin >> std::ws;
            std::string novoNomeUsuario;
            std::getline(std::cin, novoNomeUsuario);

            // Verificar se o novo nome de usuário já existe
            if (usuarios.find(novoNomeUsuario) != usuarios.end()) {
                std::cout << "Nome de usuario ja existe. Escolha outro.\n";
                return;
            }

            usuario.nome = novoNomeUsuario;
            break;
        }
        
        case 2:
            std::cout << "Novo Nome: ";
            std::cin >> std::ws;
            std::getline(std::cin, usuario.nomePessoal);
            break;

        case 3:
            std::cout << "Nova Idade: ";
            std::cin >> usuario.idade;
            break;

        case 4:
            std::cout << "Novo E-mail: ";
            std::cin >> usuario.contato;
            break;

        case 5:
            std::cout << "Nova Senha: ";
            std::cin >> usuario.senha;
            break;
        
        default:
            std::cout << "Opcao invalida.\n";
            break;
    }
}

void realizarDeposito(Usuario& usuario) {
    double quantia;
    std::string senha;

    std::cout << "Digite a quantia a ser depositada: ";
    std::cin >> quantia;

    std::cout << "Digite sua senha para autorizar o deposito: ";
    std::cin >> senha;

    if (senha == usuario.senha) {
        usuario.saldo += quantia;
        std::cout << "Deposito realizado com sucesso. Novo saldo: " << usuario.saldo << "\n";
    } else {
        std::cout << "Senha incorreta. Deposito nao autorizado.\n";
    }
}

void realizarTransferencia(Usuario& usuario) {
    std::string destinatario;
    double quantia;
    std::string senha;

    std::cout << "Digite o nome de usuario do destinatario: ";
    std::cin >> std::ws;
    std::getline(std::cin, destinatario);

    auto it = usuarios.find(destinatario);
    if (it != usuarios.end()) {
        std::cout << "Digite a quantia a ser transferida: ";
        std::cin >> quantia;

        std::cout << "Digite sua senha para autorizar a transferencia: ";
        std::cin >> senha;

        if (senha == usuario.senha) {
            if (usuario.saldo >= quantia) {
                usuario.saldo -= quantia;
                it->second.saldo += quantia;
                std::cout << "Transferencia realizada com sucesso.\n";
            } else {
                std::cout << "Saldo insuficiente. Transferencia nao realizada.\n";
            }
        } else {
            std::cout << "Senha incorreta. Transferencia nao autorizada.\n";
        }
    } else {
        std::cout << "Usuario destinatario nao encontrado.\n";
    }
}

void exibirMenu(Usuario& usuario) {
    while (true) {
        std::cout << "\n1. Exibir dados pessoais\n"
                  << "2. Alterar dados pessoais\n"
                  << "3. Realizar depósito\n"
                  << "4. Realizar transferência\n"
                  << "5. Mostrar usuario e senha\n"
                  << "6. Sair\n"
                  << "Escolha uma opcao: ";

        int escolha;
        std::cin >> escolha;
        std::cout << "\n";
        
        switch (escolha) {
            case 1:
              std::cout << "Nome: " << usuario.nomePessoal << "\n"
                        << "Idade: " << usuario.idade << "\n"
                        << "Contato: " << usuario.contato << "\n"
                        << "Saldo: " << usuario.saldo << "\n";
              break;

            case 2:
                alterarDadosUsuario(usuario);
                break;
            
            case 3:
                realizarDeposito(usuario);
                break;

            case 4:
                realizarTransferencia(usuario);
                break;
            
            case 5:
                std::cout << "Usuario: " << usuario.nome << "\n"
                        << "Senha: " << usuario.senha << "\n";
                break;

            case 6:
                std::cout << "Saindo...\n";
                std::cout << "---------------------------------\n";
                return;

            default:
                std::cout << "Opcao invalida. Tente novamente.\n";
        }
    }
}


int main() {
    while (true) {
        std::cout << "\n1. Cadastro\n"
                  << "2. Login\n"
                  << "3. Sair\n"
                  << "Escolha uma opcao: ";

        int escolha;
        //std::cin >> escolha;

        while (!(std::cin >> escolha) || std::cin.peek() != '\n') {
            std::cin.clear(); // Limpar o estado de erro
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar entrada inválida
            std::cout << "Entrada invalida. Por favor, insira um numero inteiro: ";
        }

        std::cout << "\n";

        switch (escolha) {
            case 1:
                cadastrarUsuario();
                break;

            case 2: {
                Usuario* usuarioLogado = fazerLogin();
                if (usuarioLogado != nullptr) {
                    exibirMenu(*usuarioLogado);
                }
                break;
            }

            case 3:
                std::cout << "Saindo...\n";
                std::cout << "--------------------------------\n";
                return 0;

            default:
                std::cout << "Opcao invalida. Tente novamente.\n";
        }
    }

    return 0;
}
