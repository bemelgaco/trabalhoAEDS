#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_CLIENTES 100
#define MAX_FUNCIONARIOS 50
#define MAX_ESTADIAS 200
#define MAX_QUARTOS 50

typedef struct
{
    int codigo;
    char nome[100];
    char endereco[200];
    char telefone[15];
} Cliente;

typedef struct
{
    int codigo;
    char nome[100];
    char telefone[15];
    char cargo[50];
    float salario;
} Funcionario;

typedef struct
{
    int numero;
    int quantidadeHospedes;
    float valorDiaria;
    char status[10];
} Quarto;

typedef struct
{
    int codigo;
    char dataEntrada[11];
    char dataSaida[11];
    int quantidadeDiarias;
    int codigoCliente;
    int numeroQuarto;
} Estadia;

void lerString(char *str, int tamanho)
{
    fgets(str, tamanho, stdin);
    str[strcspn(str, "\n")] = '\0';
}

int isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int getDaysInMonth(int month, int year) {
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && isLeapYear(year))
        return 29;
    return daysInMonth[month - 1];
}

int dataValida(const char *data)
{
    // formato dd/mm/yyyy
    if (strlen(data) != 10)
        return 0;
    if (data[2] != '/' || data[5] != '/')
        return 0;
    int dia = atoi(data);
    int mes = atoi(data + 3);
    int ano = atoi(data + 6);
    if (dia < 1 || mes < 1 || mes > 12 || ano < 1)
        return 0;
    if (dia > getDaysInMonth(mes, ano))
        return 0;
    return 1;
}

int calcularDiferencaDias(const char *dataInicio, const char *dataFim)
{
    struct tm tm1, tm2;
    memset(&tm1, 0, sizeof(struct tm));
    memset(&tm2, 0, sizeof(struct tm));
    sscanf(dataInicio, "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
    sscanf(dataFim, "%d/%d/%d", &tm2.tm_mday, &tm2.tm_mon, &tm2.tm_year);
    tm1.tm_mon -= 1;
    tm2.tm_mon -= 1;
    tm1.tm_year -= 1900;
    tm2.tm_year -= 1900;
    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);
    return (difftime(time2, time1) / (60 * 60 * 24));
}

void cadastrarCliente(Cliente clientes[], int *numClientes)
{
    if (*numClientes >= MAX_CLIENTES)
    {
        printf("Limite de clientes atingido.\n");
        return;
    }

    Cliente novoCliente;
    novoCliente.codigo = *numClientes + 1;
    printf("Codigo do cliente: %d\n", novoCliente.codigo);

    printf("Nome: ");
    lerString(novoCliente.nome, 100);

    printf("Endereco: ");
    lerString(novoCliente.endereco, 200);

    printf("Telefone: ");
    lerString(novoCliente.telefone, 15);

    clientes[*numClientes] = novoCliente;
    (*numClientes)++;

    printf("Cliente cadastrado com sucesso!\n");
}

void cadastrarFuncionario(Funcionario funcionarios[], int *numFuncionarios)
{
    if (*numFuncionarios >= MAX_FUNCIONARIOS)
    {
        printf("Limite de funcionarios atingido.\n");
        return;
    }

    Funcionario novoFuncionario;
    novoFuncionario.codigo = *numFuncionarios + 1;
    printf("Codigo do funcionario: %d\n", novoFuncionario.codigo);

    printf("Nome: ");
    lerString(novoFuncionario.nome, 100);

    printf("Telefone: ");
    lerString(novoFuncionario.telefone, 15);

    printf("Cargo: ");
    lerString(novoFuncionario.cargo, 50);

    printf("Salario: ");
    scanf("%f", &novoFuncionario.salario);
    getchar();

    funcionarios[*numFuncionarios] = novoFuncionario;
    (*numFuncionarios)++;

    printf("Funcionario cadastrado com sucesso!\n");
}

void cadastrarQuarto(Quarto quartos[], int *numQuartos)
{
    if (*numQuartos >= MAX_QUARTOS)
    {
        printf("Limite de quartos atingido.\n");
        return;
    }

    Quarto novoQuarto;
    printf("Numero do quarto: ");
    scanf("%d", &novoQuarto.numero);
    getchar();

    printf("Quantidade de hospedes: ");
    scanf("%d", &novoQuarto.quantidadeHospedes);
    getchar();

    printf("Valor diaria: ");
    scanf("%f", &novoQuarto.valorDiaria);
    getchar();

    strcpy(novoQuarto.status, "desocupado");

    quartos[*numQuartos] = novoQuarto;
    (*numQuartos)++;

    printf("Quarto cadastrado com sucesso!\n");
}

void cadastrarEstadia(Estadia estadias[], int *numEstadias, Cliente clientes[], int numClientes, Quarto quartos[], int numQuartos)
{
    if (*numEstadias >= MAX_ESTADIAS)
    {
        printf("Limite de estadias atingido.\n");
        return;
    }

    Estadia novaEstadia;
    novaEstadia.codigo = *numEstadias + 1;
    printf("Codigo da estadia: %d\n", novaEstadia.codigo);

    printf("Codigo do cliente: ");
    scanf("%d", &novaEstadia.codigoCliente);
    getchar();

    int clienteEncontrado = 0;
    for (int i = 0; i < numClientes; i++)
    {
        if (clientes[i].codigo == novaEstadia.codigoCliente)
        {
            clienteEncontrado = 1;
            break;
        }
    }
    if (!clienteEncontrado)
    {
        printf("Cliente nao encontrado.\n");
        return;
    }

    printf("Data de entrada (dd/mm/yyyy): ");
    scanf("%10s", novaEstadia.dataEntrada);
    getchar();
    if (!dataValida(novaEstadia.dataEntrada))
    {
        printf("Data de entrada invalida.\n");
        return;
    }

    printf("Data de saida (dd/mm/yyyy): ");
    scanf("%10s", novaEstadia.dataSaida);
    getchar();
    if (!dataValida(novaEstadia.dataSaida))
    {
        printf("Data de saida invalida.\n");
        return;
    }

    novaEstadia.quantidadeDiarias = calcularDiferencaDias(novaEstadia.dataEntrada, novaEstadia.dataSaida);
    if (novaEstadia.quantidadeDiarias <= 0)
    {
        printf("Data de saida deve ser posterior a data de entrada.\n");
        return;
    }

    printf("Quantidade de hospedes: ");
    int quantidadeHospedes;
    scanf("%d", &quantidadeHospedes);
    getchar();

    int quartoEncontrado = 0;
    for (int i = 0; i < numQuartos; i++)
    {
        if (strcmp(quartos[i].status, "desocupado") == 0 && quartos[i].quantidadeHospedes >= quantidadeHospedes)
        {
            novaEstadia.numeroQuarto = quartos[i].numero;
            strcpy(quartos[i].status, "ocupado");
            quartoEncontrado = 1;
            break;
        }
    }
    if (!quartoEncontrado)
    {
        printf("Nenhum quarto disponivel para a quantidade de hospedes.\n");
        return;
    }

    estadias[*numEstadias] = novaEstadia;
    (*numEstadias)++;

    printf("Estadia cadastrada com sucesso!\n");
}

void pesquisarCliente(Cliente clientes[], int numClientes)
{
    printf("Digite o codigo ou nome do cliente: ");
    char busca[100];
    lerString(busca, 100);

    for (int i = 0; i < numClientes; i++)
    {
        if (clientes[i].codigo == atoi(busca) || strstr(clientes[i].nome, busca) != NULL)
        {
            printf("Codigo: %d\n", clientes[i].codigo);
            printf("Nome: %s\n", clientes[i].nome);
            printf("Endereco: %s\n", clientes[i].endereco);
            printf("Telefone: %s\n", clientes[i].telefone);
            return;
        }
    }
    printf("Cliente nao encontrado.\n");
}

void pesquisarFuncionario(Funcionario funcionarios[], int numFuncionarios)
{
    printf("Digite o codigo ou nome do funcionario: ");
    char busca[100];
    lerString(busca, 100);

    for (int i = 0; i < numFuncionarios; i++)
    {
        if (funcionarios[i].codigo == atoi(busca) || strstr(funcionarios[i].nome, busca) != NULL)
        {
            printf("Codigo: %d\n", funcionarios[i].codigo);
            printf("Nome: %s\n", funcionarios[i].nome);
            printf("Telefone: %s\n", funcionarios[i].telefone);
            printf("Cargo: %s\n", funcionarios[i].cargo);
            printf("Salario: %.2f\n", funcionarios[i].salario);
            return;
        }
    }
    printf("Funcionario nao encontrado.\n");
}

void mostrarEstadiasCliente(Estadia estadias[], int numEstadias, Cliente clientes[], int numClientes)
{
    printf("Digite o codigo ou nome do cliente: ");
    char busca[100];
    lerString(busca, 100);

    int clienteCodigo = -1;
    for (int i = 0; i < numClientes; i++)
    {
        if (clientes[i].codigo == atoi(busca) || strstr(clientes[i].nome, busca) != NULL)
        {
            clienteCodigo = clientes[i].codigo;
            break;
        }
    }
    if (clienteCodigo == -1)
    {
        printf("Cliente nao encontrado.\n");
        return;
    }

    printf("Estadias do cliente:\n");
    for (int i = 0; i < numEstadias; i++)
    {
        if (estadias[i].codigoCliente == clienteCodigo)
        {
            printf("Codigo da estadia: %d\n", estadias[i].codigo);
            printf("Data de entrada: %s\n", estadias[i].dataEntrada);
            printf("Data de saida: %s\n", estadias[i].dataSaida);
            printf("Quantidade de diarias: %d\n", estadias[i].quantidadeDiarias);
            printf("Numero do quarto: %d\n", estadias[i].numeroQuarto);
        }
    }
}

int main()
{
    Cliente clientes[MAX_CLIENTES];
    Funcionario funcionarios[MAX_FUNCIONARIOS];
    Estadia estadias[MAX_ESTADIAS];
    Quarto quartos[MAX_QUARTOS];

    int numClientes = 0;
    int numFuncionarios = 0;
    int numEstadias = 0;
    int numQuartos = 0;

    int opcao;

    do
    {
        printf("\nMENU\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Cadastrar Funcionario\n");
        printf("3. Cadastrar Quarto\n");
        printf("4. Cadastrar Estadia\n");
        printf("5. Pesquisar Cliente\n");
        printf("6. Pesquisar Funcionario\n");
        printf("7. Mostrar Estadias de Cliente\n");
        printf("8. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            cadastrarCliente(clientes, &numClientes);
            break;
        case 2:
            cadastrarFuncionario(funcionarios, &numFuncionarios);
            break;
        case 3:
            cadastrarQuarto(quartos, &numQuartos);
            break;
        case 4:
            cadastrarEstadia(estadias, &numEstadias, clientes, numClientes, quartos, numQuartos);
            break;
        case 5:
            pesquisarCliente(clientes, numClientes);
            break;
        case 6:
            pesquisarFuncionario(funcionarios, numFuncionarios);
            break;
        case 7:
            mostrarEstadiasCliente(estadias, numEstadias, clientes, numClientes);
            break;
        case 8:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 8);

    return 0;
}