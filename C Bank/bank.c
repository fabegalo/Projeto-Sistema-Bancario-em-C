#include <stdio.h>
#include <mysql.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>


float Deposito(float conta, float deposito){
    conta = conta + deposito;
    //printf("\n ContaD:%f", conta);
    return conta;

}

float Saque(float conta, float saque){

    if (conta >= saque){
        conta = conta - saque;
    }else{
        printf("Saldo Insuficiente!!!!");
    }

    return conta;
}

float Conta(float conta){
    return conta;

}

MYSQL mysql_connect(){
    static char *host = "us-cdbr-iron-east-05.cleardb.net";
    static char *user = "baaf8787ff1507";
    static char *pass = "7ec630fc";
    static char *db_name = "heroku_b481894670aeac7";
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

void mysql_insert(MYSQL conexao, char email2[]){
    int res;
    char email[10];
    char saldo[10];
   
    strcpy(email, email2);
  
    char query[] = "INSERT INTO conta(id, email, saldo) values('NULL','";
    strcat(email, "', '");
  

    strcat(email, "0");
  
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
    MYSQL_ROW resget;

    char query[]="SELECT * FROM conta;";
     if (mysql_query(&conexao,query)){
         printf("Erro: %s\n",mysql_error(&conexao));
     }
      else
      {
         resp = mysql_store_result(&conexao);//recebe a consulta
         resget = mysql_fetch_row(resp);
         //printf(resget);
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

int mysql_update(MYSQL conexao, float conta, char email2[]){
    int res;
    char saldo[10];
    char email[10];
    char saldoo[10];
    

  

    gcvt(conta, 6, saldoo);

   

    strcpy(saldo, saldoo);

    
    char query[] = "UPDATE conta SET saldo = '";
    strcat(query, saldo);

    strcat(query, "' where email = '");
   

    strcat(query, email2);
    
    strcat(query, "';");
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

MYSQL_ROW mysql_result(MYSQL conexao, int escolha, char email2[]){
    int conta;
        MYSQL_ROW linhas;
        MYSQL_FIELD *campos;
        MYSQL_RES *resp;
        MYSQL_ROW *resget;
        MYSQL_RES *resultadoo;

    MYSQL_ROW id;
    MYSQL_ROW saldo;
    MYSQL_ROW email;
    char email22 [10];
    int false;

        strcpy(email22, email2);
         char query[] = "SELECT * FROM conta where email = '";
        //strcat(email, "', '");
        //strcat(email, saldo);
        strcat(query, email22);
        strcat(query, "';");
        puts(query);

        //char query[]="SELECT * FROM conta;";
        if (mysql_query(&conexao, query)){
           printf("Erro: %s\n",mysql_error(&conexao));
        }else{
          resultadoo = mysql_store_result (&conexao);
         // resp = mysql_store_result(&conexao);//recebe a consulta
          resget = mysql_fetch_row(resultadoo);
          //printf("%s", resultadoo);

            if (!resget){
                printf("chama a microsoft");
                return false = 0;
            }else {
                switch (escolha){
                    case 1 :
                        id = resget[0];
                        return id;
                        break;

                    case 2 :
                        email = resget[1];
                        return email;
                        break;

                    case 3 :
                        saldo = resget[2];
                        return saldo;
                        break;

                    case 4 :
                        printf("\n ID: %s", resget[0]);
                        printf("\n email: %s", resget[1]);
                        printf("\n saldo: %s", resget[2]);
                        break;
                    default :
                        printf("morrri");
                        break;
                }
            }


        }
}

MYSQL conexao;
float conta, deposito, saque;


int main (){
char email2[10];
char saldo2[10];
int escolha,stop;
char resultado[20];
MYSQL_ROW returnn;
char *tot;
float val;
int exittt;
int enter = 0;


do {
    stop = 0;
    printf("\n ----Conta_Bancaria_1.0----\n");
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
        returnn = mysql_result(conexao, 3, email2);
        if(returnn != 0){
            printf("Deu Boa");
            tot = returnn;
            val = atof(tot);
            exittt = 0;
            while (exittt == 0){
                printf("\n ----Conta_Bancaria_1.0----\n");
                printf("[1] - Fazer Deposito      \n");
                printf("[2] - Realizar Saque      \n");
                printf("[3] - Visualizar Conta    \n");
                printf("[4] - Sair                \n");
                printf("--------------------------\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &escolha);

                switch (escolha)
                {
                case 1:
                    printf("Insira a quantia de deposito: ");
                    scanf("%f", &deposito);

                    printf("\n Conta:%f", val);
                    printf("\n deposito:%f", deposito);
                    conta = Deposito(val, deposito);

                    printf("\n Conta:%f", conta);

                    if(mysql_update(conexao, conta, email2)){
                        printf("Deposito de %f Realizado com sucesso!!", deposito);
                    }
                    break;

                case 2:
                    printf("Insira a quantia de Saque: ");
                    scanf("%f", &saque);

                    conta = Saque(val, saque);

                    printf("\n Conta:%f", conta);

                    if(mysql_update(conexao, conta, email2)){
                        printf("Deposito de %f Realizado com sucesso!!", deposito);
                    }
                    break;
                case 3:
                    mysql_result(conexao, 4, email2);
                    break;
                case 4:
                    exittt = 1;
                    break;
                default:
                    break;
                }

            }







        }else {
            printf("Deu Ruim!");
            mysql_closee(conexao);
        }


        //printf("return: %f", val);

        break;

    case 2 :
        printf("Insira seu e-mail: ");
        scanf("%s", &email2);
        conexao = mysql_connect();
        //saldo2[0] = "20";
        //printf("Insira seu saldo: ");
        //scanf("%s", &saldo2);
        saldo2[0] = '0';

        //printf("vetor : %d", saldo2[0]);
        //printf("vetor : %d", saldo2[1]);
        //printf("vetor : %d", saldo2[2]);
        //scanf("%s", &saldo2);

        printf("email2: %s", email2);

        mysql_insert(conexao, email2);
        mysql_closee(conexao);
        break;

    case 3 :
        stop = 1;
        break;
    case 4 :
        conexao = mysql_connect();
        //mysql_select(conexao);
        //break;

        int conta;
        MYSQL_ROW linhas;
        MYSQL_FIELD *campos;
        MYSQL_RES *resp;
        MYSQL_ROW *resget;
        MYSQL_RES *resultadoo;

        char query[]="SELECT * FROM conta;";
        if (mysql_query(&conexao, query)){
           printf("Erro: %s\n",mysql_error(&conexao));
        }
         else
         {
          resultadoo = mysql_store_result (&conexao);
         // resp = mysql_store_result(&conexao);//recebe a consulta
          resget = mysql_fetch_row(resultadoo);
          printf("Oi");
          printf("\n ID: %s", resget[0]);
          printf("\n email: %s", resget[1]);
          printf("\n saldo: %s", resget[2]);
         }
    case 5 :



        //contat = 35.50;
        //contat = contat + 25.00;
        //printf("Conta:%f", contat);

        //gcvt(contat, 6, saldoo);

        //printf("\n saldoo: %s", saldoo);

        break;

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
