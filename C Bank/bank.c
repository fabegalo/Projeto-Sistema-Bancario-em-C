#include <stdio.h>
#include <mysql.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>


float Deposito(conta, deposito){
    conta = conta + deposito;
    return deposito;

}

float Saque(conta, saque){
    conta = conta - saque;
    return saque;
}

float Conta(conta){
    return conta;

}

MYSQL mysql_connect(){
    static char *host = "localhost";
    static char *user = "root";
    static char *pass = "";
    static char *db_name = "banco";
    MYSQL conexao;
    mysql_init(&conexao);
    if ( mysql_real_connect(&conexao, host, user, pass, db_name, 0, NULL, 0) ){
         printf("conectado com sucesso!\n");
         return conexao;
    }
    else
    {
        printf("Falha de conexao\n");
        printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
    }
}

void mysql_insert(MYSQL conexao, char email2[], char saldo2[]){
    int res;
    char email[10];
    char saldo[10];
    strcpy(email, email2);
    strcpy(saldo, saldo2);
    char query[] = "INSERT INTO conta(id, email, saldo) values('2', '";
    strcat(email, "', '");
    strcat(email, saldo);
    strcat(query, email);
    strcat(query, "');");
    puts(query);
    res = mysql_query(&conexao, query);
            if (!res){
                printf("Registros inseridos %d\n", mysql_affected_rows(&conexao));
            }

            else
            {
                printf("Erro na insercao %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
            }


}

char mysql_select(conexao){
    int conta;
    MYSQL_ROW linhas;
    MYSQL_FIELD *campos;
    MYSQL_RES *resp;
    char query[]="SELECT * FROM conta;";
     if (mysql_query(&conexao,query)){
         printf("Erro: %s\n",mysql_error(&conexao));
     }
      else
      {
         resp = mysql_store_result(&conexao);//recebe a consulta
      }
      if (resp){ //se houver consulta
         campos = mysql_fetch_fields(resp);

         for (conta=0;conta<mysql_num_fields(resp);conta++) {
              printf("%s",(campos[conta]));
              if (mysql_num_fields(resp)>1)
                  printf("\t");
             }

             printf("\n");
              while ((linhas = mysql_fetch_row(resp)) != NULL)
              {
                for (conta = 0;conta<mysql_num_fields(resp);conta++)
                   printf("%s\t",linhas[conta]);
                   //myArray[conta] = linhas[conta];
                printf("\n");
                //x++;
              }
                //
        }
    //return val;
}

void mysql_closee(conexao){
    mysql_close(&conexao);
}

MYSQL conexao;
float conta, deposito, saque;



int main (){
char email2[10];
char saldo2[10];
int escolha,stop;
char resultado[20];


do {
    stop = 0;
    printf("----Conta_Bancaria_1.0----\n");
    printf("[1] - Fazer Login         \n");
    printf("[2] - Realizar Cadastro   \n");
    printf("[3] - Sair                \n");
    printf("--------------------------\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &escolha);

    switch (escolha)
    {
    case 1 :
        printf("Insira seu e-mail: ");
        scanf("%s", &email2);
        conexao = mysql_connect();
        mysql_select(conexao);
        mysql_closee(conexao);

    case 2 :
        printf("Insira seu e-mailCASE2: ");
        scanf("%s", &email2);
        conexao = mysql_connect();
        saldo2[0] = "0";
        mysql_insert(conexao, email2, saldo2);
        mysql_closee(conexao);
        break;

    case 3 :
        stop = 1;
    default :
        break;
    }


    //printf("Digite seu email: ");
    //scanf("%s" , &email2);

    //printf("Digite seu saldo: ");
    //scanf("%s" , &saldo2);

    //conexao = mysql_connect();
    //mysql_insert(conexao, email2, saldo2);
    //resultado[0] = mysql_select(conexao);
    //mysql_closee(conexao);


}while(stop != 1);

return 0;
}
