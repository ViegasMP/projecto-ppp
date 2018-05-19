#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int identificador;
    int prioridade;
    char descricao[140];
    char responsavel[50];
    Data data_de_criacao;
    Data prazo;
    Data data_de_conclusao;
} Cartao;

typedef struct noT *ListT;
typedef struct noT {
    Cartao cartao;
    ListT next;
}NoT;

typedef struct {
    char nome[50];
    char email[50];
    int id;
} Pessoa;

typedef struct noP *ListP;
typedef struct noP {
    Pessoa pessoa;
    ListT cartao;
    ListP next;
}NoP;

typedef struct noD *ListD;
typedef struct noD {
    ListT cartao;
    ListD next;
}NoD;

/*int procura_pessoa (ListP l, int num) {
    ListP atual = l;
    while (atual != NULL && atual->pessoa.id != num) {
        printf("A\n");
        if (atual->pessoa.id == num) {
            printf("B\n");
            return 1;
        }
        atual = atual -> next;
    }
    return 0;
}*/

ListP adiciona_inicio (ListP l, ListP novo_no) {
    novo_no -> next = l;
    l = novo_no;
    return l;
}

void le_info_pessoa (Pessoa* pessoa, ListP l) {
    int numId=0;
    printf("Nome da Pessoa: ");
    scanf(" %[^\n]s", pessoa->nome);
    printf("email: ");
    scanf(" %[^\n]s", pessoa->email);
    printf ("identificador: ");
    scanf ("%d", &numId);
    /*if (procura_pessoa (l, numId) == 1) {
        printf("Ja existe uma pessoa com esse identificador. Tente novamente.\n");
    } else {
        pessoa->id = numId;
    }*/
}

void le_ficheiro_de_pessoas (ListP l, char nome_fch[]) {
    FILE *fp;
    ListP aux;
    int pos = 0;
    char* linha = (char*)malloc(sizeof(char)*500);
    char* nome = (char*)malloc(sizeof(char)*255);
    char* email = (char*)malloc(sizeof(char)*255);
    int id;
    char *token;

    fp = fopen(nome_fch, "r");
    while (fgetc (fp) != EOF) {
        fseek (fp, pos, SEEK_SET);
		/*fscanf (fp, "%s | %s | %d", aux->pessoa.nome, aux ->pessoa.email,  aux ->pessoa.id);*/
		fgets(linha, 255, fp);
        token = strtok(linha, " | ");
		printf("%s\n", linha);


        pos = ftell(fp);
    }
    fclose(fp);
}

int le_cartao_inicio (Cartao* cartao, int id) {
    printf("Descreva sucintamente a tarefa: ");
    scanf(" %[^\n]s", cartao->descricao);
    cartao->identificador = id;
    while (cartao->prioridade < 1 || cartao->prioridade > 10) {
        printf ("Prioridade da tarefa (sendo 1 = minimo e 10 = maxima): ");
        scanf ("%d", &cartao->prioridade);
    }
    printf ("Data de criacao da tarefa(dd/mm/aaaa): ");
    scanf ("%d/%d/%d", &cartao->data_de_criacao.dia, &cartao->data_de_criacao.mes, &cartao->data_de_criacao.ano);
    return id+1;
}

void le_cartao_doing (Cartao* cartao, int check_responsavel) {
    if (check_responsavel == 0) {
        printf("Insira o responsavel: ");
        scanf(" %[^\n]s", cartao->responsavel);
    }
    printf ("Insira o prazo para a conclusao: ");
    scanf ("%d/%d/%d", &cartao->prazo.dia, &cartao->prazo.mes, &cartao->prazo.ano);
}

void listarT (ListT l) {
    printf("\n\n");
    while (l) {
        printf("Tarefa: %s\n", l -> cartao.descricao);
        printf("Identificador: %d\n", l -> cartao.identificador);
        printf("Prioridade: %d\n", l -> cartao.prioridade);
        printf("Data de Criacao: %d/%d/%d\n", l -> cartao.data_de_criacao.dia, l -> cartao.data_de_criacao.mes, l -> cartao.data_de_criacao.ano);
        printf("\n");
        l = l->next;
    }
    printf("\n\n");
}

void listarP (ListP l) {
    printf("\n\n");
    while (l) {
        printf("Nome: %s\n", l -> pessoa.nome);
        printf("e-Mail: %s\n", l -> pessoa.email);
        printf("Identificador: %d\n", l -> pessoa.id);
        printf("\n");
        l = l->next;
    }
    printf("\n\n");
}

/*    ListD atual = l;
    ListD anterior = NULL;
    while (atual != NULL && atual -> cartao.prioridade < novo_no -> cartao.prioridade) {
        anterior = atual;
        atual = atual -> next;
    }
    novo_no -> next = atual;
    if (anterior != NULL) {
        anterior -> next = novo_no;
    } else {
        l = novo_no;
    }
    return l;
}*/

int compara_datas(ListT l, ListT n){
    int aux1, aux2;
    aux1 = (10000 * (l -> cartao.data_de_criacao.ano)) + (100*(l -> cartao.data_de_criacao.mes)) + (l -> cartao.data_de_criacao.dia);
    aux2 = (10000 * (n -> cartao.data_de_criacao.ano)) + (100*(n -> cartao.data_de_criacao.mes)) + (n -> cartao.data_de_criacao.dia);

    if (aux1 > aux2) {
        return 1;
    } else {
        return 0;
    }
}

ListT inserir_ordenado_data (ListT l, ListT novo_no) {
    ListT atual = l;
    ListT anterior = NULL;
    while (atual != NULL && compara_datas(atual, novo_no) == 1) {
        anterior = atual;
        atual = atual -> next;
    }
    novo_no -> next = atual;
    if (anterior != NULL) {
        anterior -> next = novo_no;
    } else {
        l = novo_no;
    }
    return l;
}

void lista_de_comandos(){
    printf("\t\t\t\tQuadro Kaban!\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("\tPara listar pessoas, insira 1;\n");
    printf("\tPara introduzir uma nova pessoa, insira 2;\n");
    printf("\tPara editar as informacoes pessoais de alguem, insira 3;\n");
    printf("\tPara definir o numero maximo de tarefas para cada pessoa, insira 4;\n");
    printf("\tPara introduzir uma nova tarefa em ""To Do"", insira 5;\n");
    printf("\tPara deslocar os cartoes entre ""To Do"" e ""Doing"", insira 6;\n");
    printf("\tPara alterar o responsavel por um cartao, insira 7;\n");
    printf("\tPara marcar uma tarefa como ""Done"", insira 8;\n");
    printf("\tPara deslocar uma tarefa de ""Done"" para ""To Do"", insira 9;\n");
    printf("\tPara visualizar o quadro, insira 10;\n");
    printf("\tPara visualizar as tarefas de uma pessoa, insira 11;\n");
    printf("\tPara visualizar as tarefas por ordem de criacao, insira 12;\n");
    printf("\tPara visualizar a lista de comandos, insira 13;\n");
    printf("\tPara terminar o programa, insira 14;\n");
    printf("---------------------------------------------------------------------------------\n");
}

int main() {
    int comando=0;
    int max=0;
    int n=0, i=0;
    int idCartao=1;
    int check_responsavel = 0;
    int check_max = 0;
    char nome_fch[] = "lista_de_pessoas.txt";
    ListT lista_de_tarefas = NULL, nova_tarefa;
    /*ListD to_do = NULL, doing = NULL, done = NULL;*/
    ListP lista_de_pessoas = NULL, nova_pessoa;
    lista_de_comandos();

    le_ficheiro_de_pessoas(lista_de_pessoas, nome_fch);

    while (comando != 14){
        printf("Comando desejado (13 para visualizar a lista de comandos): ");
        scanf("%d", &comando);
        switch (comando) {
            case 1:
                listarP(lista_de_pessoas);
            break;
            case 2:
                /*Adicionar uma nova pessoa a lista_de_pessoas*/
                nova_pessoa = (ListP) malloc (sizeof (NoP));
                le_info_pessoa(&nova_pessoa -> pessoa, lista_de_pessoas);
                lista_de_pessoas = adiciona_inicio(lista_de_pessoas, nova_pessoa);
            break;
            case 3:
            break;
            case 4:
                /*Definir o aximo de tarefas por pessoa*/
                if (check_max == 0) {
                    printf("Defina o numero maximo de tarefas por pessoa:");
                    scanf("%d", &max);
                    printf("\nANTENCAO!\nSe tiver CERTEZA do maximo a ser definido, INSIRA 1. Caso CONTRARIO, INSIRA 0.\nLembre-se que esse maximo nao podera ser alterado mais tarde.\n");
                    printf("1 ou 0? ");
                    scanf("%d", &check_max);
                    printf("\n\n");
                } else {
                    printf("\n\nO maximo de tarefas por pessoa ja foi definido como %d.\n\n\n", max);
                }
            break;
            case 5:
                /*Adicionar tarefas a lista_de_tarefas*/
                printf("Quantas tarefas deseja adicionar? ");
                scanf("%d", &n);
                for (i = 0; i < n; i++) {
                    nova_tarefa = (ListT) malloc (sizeof (NoT));
                    idCartao = le_cartao_inicio(&nova_tarefa -> cartao, idCartao);
                    lista_de_tarefas = inserir_ordenado_data(lista_de_tarefas, nova_tarefa);
                    printf("Deseja atribuir um responsavel a essa tarefa agora? (1 = SIM, 0 = NAO):");
                    scanf("%d", &check_responsavel);
                    if (check_responsavel == 1) {

                    }
                    /*to_do = inserir_ordenado_to_do(to_do, &nova_tarefa);*/
                }
            break;

            case 6:
                printf("Qual tarefa esta a ser realizada? ");
                scanf("%d", &n);
                /*no = procura_cartao(to_do, n);*/
                /*doing = inserir_ordenado(doing, no);*/
            break;
            case 7:
            break;
            case 8:
            break;
            case 9:
            break;
            case 10:
                printf("\n\n\t\t\t\tQUADRO KANBAN!\n");
                printf("\tTO DO:\n");
                printf("\tDOING:\n");
                printf("\tDONE:\n");
            break;
            case 11:
            break;
            case 12:
                listarT(lista_de_tarefas);
            break;
            case 13:
                lista_de_comandos();
            break;
            case 14:
                /*ficheiro_para_quadro(to_do, doing, done, lista_de_tarefas, "quadro.txt");*/
            break;
            default:
                printf("O comando digitado eh invalido!\n");
            break;
        }
    }

    return 0;
}
