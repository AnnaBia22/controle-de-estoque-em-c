#include <stdio.h>
#include <string.h>

int main(){
    int op, q;
    FILE *p;
    char item[100], linha[150], escolha;
    while(1){
    printf("================================\nControle de Estoque\n================================\nSelecione uma opção:\n1. Adicionar Item\n2. Remover Item\n3. Listar Estoque\n4. Sair\nOpção: ");
    do{
    scanf("%d", &op);
    if(op<1 || op>4) {
    printf("Opção inválida! Tente novamente.\n");
    }
    } while(op<1 ||op>4);
    if (op==1){
        printf("Digite o nome do item: ");
        scanf("%s", item);
        printf("Digite a quantidade: ");
        scanf("%d", &q);
        p=fopen("estoque.txt", "a+");
        int encontrado=0;
        while (fgets(linha, sizeof(linha), p)){
            char nome_item[100];
            int quantidade;
            sscanf(linha, "%s %d", nome_item, &quantidade);
            if (strcmp(nome_item, item)==0){
                fseek(p, -strlen(linha), SEEK_CUR);
                fprintf(p, "%s\n%d\n", nome_item, quantidade+q);
                encontrado=1;
                break;
            }
        }
        if(!encontrado){
            fprintf(p, "%s\n%d\n", item, q);
        }
        fclose(p);
        printf("Item adicionado com sucesso!\n");
    }
    else if(op==2){
        printf("Digite o nome do item: ");
        scanf("%s", item);
        printf("Digite a quantidade a ser removida: ");
        scanf("%d", &q);
        p=fopen("estoque.txt", "a+");
        FILE *temp=fopen("temp.txt", "w");
        int encontrado=0, quantidade;
        while(fgets(linha, sizeof(linha), p)){
            char nome_item[100];
            sscanf(linha, "%s %d", nome_item, &quantidade);
            if(strcmp(nome_item, item)==0){
                if(q>quantidade){
                    printf("Estoque insuficiente. Quantidade disponível: %d\n", quantidade);
                    fputs(linha, temp);
                }
                else{
                    quantidade-=q;
                    if(quantidade>0){
                        fprintf(temp, "%s\n%d\n", nome_item, quantidade);
                        printf("Quantidade atualizada com sucesso!\n");
                    } 
                    else{
                        printf("Item removido do estoque!\n");
                    }
                }
                encontrado=1;
            } 
            else{
                fputs(linha, temp);
            }
        }
        if (!encontrado) {
            printf("Item não encontrado.\n");
        }
        fclose(p);
        fclose(temp);
        remove("estoque.txt");
        rename("temp.txt", "estoque.txt");
    }
    else if (op == 3) {
        p = fopen("estoque.txt", "r");
        printf("=============================\n");
        printf("        Estoque Atual        \n");
        printf("=============================\n");
        int estoque_vazio = 1;
        while (fgets(linha, sizeof(linha), p)) {
            char nome_item[100];
            int quantidade;
            sscanf(linha, "%s %d", nome_item, &quantidade);
            printf("Nome: %s\n", nome_item);
            printf("Quantidade: %d\n\n", quantidade);
            estoque_vazio=0;
        }
        if (estoque_vazio) {
            printf("O estoque está vazio.\n");
        }
        fclose(p);
    }
    else if(op==4){
        printf("Obrigado por usar o Controle de Estoques! Até a próxima.");
        break;
    }
    getchar();
    printf("\nDeseja realizar outra operação? (s/n): ");
    do{
        scanf("%c", &escolha);

        if(escolha != 's' && escolha != 'n'){
            printf("Resposta inválida. Por favor, digite 's' para sim ou 'n' para não.\n");
        }
        } while(escolha != 's' && escolha != 'n');

        if(escolha == 'n') {
            printf("Obrigado por usar o Controle de Estoques! Até a próxima.\n");
            break;
        }
    }
    return 0;
}