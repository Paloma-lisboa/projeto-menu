#include <stdio.h>
#include <locale.h>
#include <string.h>

#define MAX_USUARIO 50
#define MAX_NOME_USUARIO 25
#define MAX_SENHA 25

struct Usuario {
    char nome[MAX_NOME_USUARIO];
    char senha[MAX_SENHA];
};

void cadastrarUsuario();
void alterarSenha();
void exclusaoDeUsuario();
void sair();

int main() {
    setlocale(LC_ALL, "Portuguese");

    int escolha;

    do {
        printf("=== Menu de Opções ===\n");
        printf("1. Cadastrar um novo usuário\n");
        printf("2. Alterar senha de usuário\n");
        printf("3. Excluir usuário\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer de entrada

        switch (escolha) {
            case 1:
                cadastrarUsuario();
                break;
            case 2:
                alterarSenha();
                break;
            case 3:
                exclusaoDeUsuario();
                break;
            case 4:
                sair();
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (escolha != 4);

    return 0;
}

void cadastrarUsuario() {
    struct Usuario user;
    FILE *arquivo = fopen("usuarios.txt", "a");
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o nome do usuário: ");
    scanf(" %[^\n]", user.nome); // Lê o nome do usuário
    printf("Digite a senha do usuário: ");
    scanf(" %[^\n]", user.senha); // Lê a senha do usuário

    fprintf(arquivo, "%s %s\n", user.nome, user.senha);
    fclose(arquivo);
    printf("Usuário cadastrado com sucesso!\n");
}
void alterarSenha() {
    struct Usuario users[MAX_USUARIO];
    char nome[MAX_NOME_USUARIO], novaSenha[MAX_SENHA];
    FILE *arquivo, *temp;
    int encontrado = 0, i = 0;

    arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário\n");
        fclose(arquivo);
        return;
    }

    // Leitura dos usuários do arquivo
    while (fscanf(arquivo, "%s %s", users[i].nome, users[i].senha) != EOF && i < MAX_USUARIO) {
        i++;
    }

    printf("Digite o nome do usuário que deseja alterar a senha: ");
    scanf(" %[^\n]", nome);

    for (int j = 0; j < i; j++) {
        if (strcmp(users[j].nome, nome) == 0) {
            encontrado = 1;
            printf("Digite a nova senha: ");
            scanf(" %[^\n]", novaSenha);
            strcpy(users[j].senha, novaSenha);
            printf("Senha alterada com sucesso!\n");
        }
        fprintf(temp, "%s %s\n", users[j].nome, users[j].senha); // Escreve os dados no arquivo temporário
    }

    fclose(arquivo);
    fclose(temp);

    if (!encontrado) {
        printf("Usuário não encontrado!\n");
    }

    // Renomear o arquivo temporário
    remove("usuarios.txt");
    rename("temp.txt", "usuarios.txt");
}
void exclusaoDeUsuario() {
    struct Usuario users[MAX_USUARIO];
    char nome[MAX_NOME_USUARIO];
    FILE *arquivo, *temp;
    int encontrado = 0, i = 0;

    arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Usuário excluído com sucesso\n");
        return;
    }

    temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário\n");
        fclose(arquivo);
        return;
    }

    // Leitura dos usuários do arquivo
    while (fscanf(arquivo, "%s %s", users[i].nome, users[i].senha) != EOF && i < MAX_USUARIO) {
        i++;
    }

    printf("Digite o nome do usuário que deseja excluir: ");
    scanf(" %[^\n]", nome);

    for (int j = 0; j < i; j++) {
        if (strcmp(users[j].nome, nome) == 0) {
            encontrado = 1;
            printf("Usuário '%s' excluído com sucesso!\n", nome);
            continue; // Não escreve o usuário no arquivo temporário
        }
        fprintf(temp, "%s %s\n", users[j].nome, users[j].senha); // Escreve os dados no arquivo temporário
    }

    fclose(arquivo);
    fclose(temp);

    if (!encontrado) {
        printf("Usuário não encontrado!\n");
    }

    // Renomear o arquivo temporário
    remove("usuarios.txt");
    rename("temp.txt", "usuarios.txt");
}

void sair() {
    printf("Saindo do programa...\n");
}







