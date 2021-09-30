#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#define TAM 20
#define FUNC 1000
#define LETRA 50

typedef struct{
    int codigo;
    char nomedepar[50],sigla[20];
}departamento;

typedef struct{
    int matricula,codep/*C�digo do departamento*/;
    char nomefun[50],data[11],salario[15],sigladep[20],cpf[12];
}Funcionarios;

int valida_data(int dia, int mes, int ano){
    if ((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && (ano >= 1900 && ano <= 2100)) //verifica se os n�meros s�o v�lidos
        {
            if ((dia == 29 && mes == 2) && ((ano % 4) == 0) && ((ano % 100)!=0) || ((ano % 400) ==0)) //verifica se o ano � bissexto
            {
                return 1;
            }
            if (dia <= 28 && mes == 2) //verifica o m�s de fevereiro
            {
                return 1;
            }
            if ((dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11)) //verifica os m�ses de 30 dias
            {
                return 1;
            }
            if ((dia <=31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes ==8 || mes == 10 || mes == 12)) //verifica os m�ses de 31 dias
            {
                return 1;
            }
            else
            {
                return 0;
            }
      }
       else
           {
                return 0;
           }
}
int validarCPF(char cpf[]){

    int i, j, digito1 = 0, digito2 = 0;
    if(strlen(cpf) != 11)
        return 0;
    else if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) || (strcmp(cpf,"22222222222") == 0) ||
            (strcmp(cpf,"33333333333") == 0) || (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
            (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) || (strcmp(cpf,"88888888888") == 0) ||
            (strcmp(cpf,"99999999999") == 0))
        return 0;
    else
    {
        //digito 1
        for(i = 0, j = 10; i < strlen(cpf)-2; i++, j--)
            digito1 += (cpf[i]-48) * j;
        digito1 %= 11;
        if(digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if((cpf[9]-48) != digito1)
            return 0;
        else
        //digito 2
        {
            for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--)
                    digito2 += (cpf[i]-48) * j;
        digito2 %= 11;
        if(digito2 < 2)
            digito2 = 0;
        else
            digito2 = 11 - digito2;
        if((cpf[10]-48) != digito2)
            return 0;
        }
    }
    return 1;
}

/*Fun��o para pesquisa sequencial dos departamentos*/
int pesquisa(departamento dep[],int cod,int ultimaPos){
    int i;
    for (int i=0;i<=ultimaPos;i++){
        if(dep[i].codigo==cod)
            return i;
    }
    return -1;
}
int Pesquisafunc(Funcionarios fu[],int mat,int ultimaPos){
    int i;
    for(i=0;i<=ultimaPos;i++){
        if(fu[i].matricula==mat)
            return i; /*Retorma a posi��o do vetor quando o matr�cula j� est� cadastrada*/
    }
    return -1; /*Retorma -1 a matr�cula n�o est� cadastrada*/
}
int PesquisaDep(Funcionarios fu[],int codep,int ultimaPos){
    int i;
    for(i=0;i<ultimaPos;i++){
        if(fu[i].codep==codep)
            return i;
    }
    return -1;
}

/*Permite que o usu�rio digite APENAS letras*/
void Verificaletra(char * palavra){
    int cont;
    char letra;
    do{
        letra=getch();
        setbuf(stdin,NULL);
        if(isalpha(letra)!=0 || letra==32){
            palavra[cont]=letra;
            cont++;
            printf("%c",letra);
        }
        else if(letra==8&&cont){
            palavra[cont]='\0';
            cont--;
            printf("\b \b");
        };
    }while(letra!=13);
    palavra[cont]='\0';
}
/*Permite que o usu�rio digite APENAS n�meros*/

void VerificaNumero(char * num){
    int cont;
    char digitado;
    do{
        digitado=getch();
        setbuf(stdin,NULL);
        if(isdigit(digitado)!=0){
            num[cont]=digitado;
            cont++;
            printf("%c",digitado);
        }
        else if(digitado==8&&cont){
            num[cont]='\0';
            cont--;
            printf("\b \b");
        }
    }while(digitado!=13);
    num[cont]='\0';
}

int lestring(char *sa, int max){
    int i = 0;
    char letra;

    for (i = 0; i < (max - 1); i++) {
    letra = fgetc(stdin);


   /* Veja que se encontrou um ENTER (\n) mas n�o leu nenhum caractere v�lido,
         * n�o aceita. Precisa ler algo. Decrementa o i para anular o efeito do i++
         * do la�o e volta no la�o com continue
    */
   if (((letra == '\n') && (i == 0)) || ((letra== ' ') && (i == 0))) {
       i = i - 1;
       continue;
   }

   /* Agora se leu um enter j� tendo lido caracteres v�lidos, ent�o
    * o usu�rio terminou de digitar sua string e ela possui ao menos
    * um caractere v�lido
    */
   if (letra == '\n')
       break;
    sa[i] = letra;
    }

    /* Finaliza a string */
        sa[i] = 0;

    /* retorna a quantidade de cars lidos (pode ser �til). Ent�o, esta fun��o
       l� uma string e retorna o seu tamanho
     */
    return (i);
}


void cadastro1(departamento dep[],int *up,int Tamanho){
    int cod,sair;
    char numero[20];

    if(*up<=Tamanho){
        do{
            printf("Forne�a o c�digo desse departamento pelo qual voc� deseja cadastrar:");
            lestring(numero,20);
            cod = atoi(numero);
            setbuf(stdin,NULL);

            if (pesquisa(dep,cod,*up)==-1){
                (*up)++;
                dep[*up].codigo = cod;
                printf("\nForne�a o nome do departamento:");

                lestring(dep[*up].nomedepar,50);
                setbuf(stdin,NULL);

                printf("\nForne�a agora a sigla desse departamento:");
                lestring(dep[*up].sigla,20);
                setbuf(stdin,NULL);


            }
            else{
                printf("\nC�digo de departamento repetido!!!!");
            };

            if(*up<Tamanho){
                printf("\nO n�mero de departamentos cadastrados � %d\n",*up);
                printf("\nDeseja sair??\n 1 - Sim \n 2 - N�o:");
                scanf("%d",&sair);
                setbuf(stdin,NULL);
            };
        }while(*up<Tamanho && sair !=1);
    }
    else
        printf("Todos departamentos j� foram cadastrados");
};

void Cadastrofunc(Funcionarios fu[],departamento dep[],int *pos,int *ulti,int Tamanho){
    int mat,cod,sair,com,saida,dia,mes,ano,salario,num;
    char numero[20],numeral[20],name[50],cpf[12],date[7],pagamento[15];
    if(*ulti<Tamanho){
        do{
            /*Verificando o c�digo de departamento para onde o funcion�rio ser� cadastrado*/
            printf("\nForne�a o c�digo de departamento de onde voc� deseja cadastrar esse funcion�rio:");
            lestring(numero,20);
            cod= atoi(numero);
            setbuf(stdin,NULL);


            if(pesquisa(dep,cod,*pos)!=-1){

                printf("\nForne�a o n�mero da matr�cula desse funcion�rio:");
                lestring(numeral,20);
                mat= atoi(numeral);
                setbuf(stdin,NULL);

                    if(Pesquisafunc(fu,mat,*ulti)==-1){
                        (*ulti)++;
                        fu[*ulti].codep = cod; /*C�digo de departamento onde o funcion�rio est� cadastrado*/
                        fu[*ulti].matricula = mat;
                        setbuf(stdin,NULL);

                        printf("\nA matricula desse funcion�rio � %d",fu[*ulti].matricula);

                        printf("\nForne�a o nome do funcion�rio:");
                        lestring(fu[*ulti].nomefun,LETRA);
                        setbuf(stdin,NULL);

                        printf("\nO nome desse funcion�rio � %s\n",fu[*ulti].nomefun);

                        do {
                            printf("\nForne�a o n�mero de CPF desse funcion�rio: ");
                            scanf("%s",fu[*ulti].cpf);
                            setbuf(stdin,NULL);

                            validarCPF(fu[*ulti].cpf);
                            if(validarCPF(fu[*ulti].cpf)==0){

                                com=1;
                                printf("\nCPF inv�lido\n\nPor favor digite o CPF novamente");
                            }
                            else{
                                com=0;
                                printf("\nCPF V�lido, e cadastrado!");
                            };

                        }while(com==1);

                    do{
                        printf("\nInforme a data de nascimento desse Funcion�rio (ex: 18/04/1992):");
                        lestring(fu[*ulti].data,11);

                        date[0] = fu[*ulti].data[0];
                        date[1] = fu[*ulti].data[1];
                        date[2] = '\0';
                        dia = atoi(date);
                        date[0] = fu[*ulti].data[3];
                        date[1] = fu[*ulti].data[4];
                        date[2] = '\0';
                        mes = atoi(date);
                        date[0] = fu[*ulti].data[6];
                        date[1] = fu[*ulti].data[7];
                        date[2] = fu[*ulti].data[8];
                        date[3] = fu[*ulti].data[9];
                        date[4] = '\0';
                        ano = atoi(date);
                        valida_data(dia,mes,ano);

                        if(valida_data(dia,mes,ano)==0){
                            saida=1;
                            printf("Data de nascimento inv�lida\n");
                        }
                        else{
                            saida=0;
                            printf("\nData cadastrada com sucesso!!");
                            printf("\nA Data digitada foi:%s",fu[*ulti].data);
                        };

                    }while(saida==1);


                    do{
                        printf("\nInforme agora o sal�rio desse funcion�rio:");
                        lestring(fu[*ulti].salario,15);
                        salario=atoi(fu[*ulti].salario);
                        if(salario>0){

                            printf("\nSal�rio Cadastrado com sucesso!!!");
                            printf("\nSal�rio � %s",fu[*ulti].salario);
                            saida=0;
                        }
                        else{
                          printf("\nSal�rio Inv�lido");
                          saida=1;
                        };

                    }while(saida==1);
                    }
                    else
                        printf("\nN�mero de matr�cula j� cadastrado!!");
            }
            else{
                printf("\nDepartamento n�o encontrado!!!!");
            };

            if(*ulti<Tamanho){
                printf("\nO n�mero de funcion�rios cadastrados � de :%d\n",*ulti);
                printf("\nDeseja sair??\n 1 - Sim \n 2 - N�o:");
                scanf("%d",&sair);
                setbuf(stdin,NULL);
            };

        }while(*ulti<Tamanho && sair !=1);
    }
    else
        printf("Todos os funcion�rios j� foram cadastrados!!!");
}
void consulta_funcionario(departamento dep[],Funcionarios fu[],int pos,int ulti){
    int matricula,sair,posicao,sigla;
    char numero[20];
    if(ulti>0){
        do{
            printf("\nForne�a a Matr�cula do funcion�rio que voc� deseja consultar:");
            lestring(numero,20);
            matricula= atoi(numero);
            setbuf(stdin,NULL);
            posicao=Pesquisafunc(fu,matricula,ulti);
            sigla=pesquisa(dep,fu[posicao].codep,pos);
            if(posicao!=-1){
                sair=0;
                printf("\nDADOS DO FUNCION�RIO\n");

                printf("\nO departamento onde esse funcion�rio est� cadastrado � %s",dep[sigla].nomedepar);

                printf("\nNome:%s",fu[posicao].nomefun);
                printf("\nData de nascimento:%s",fu[posicao].data);
                printf("\nCPF:%s",fu[posicao].cpf);
                printf("\nMatr�cula:%d",fu[posicao].matricula);
                printf("\nC�digo do departamento:%d",fu[posicao].codep);
                printf("\nSal�rio:R$%s reais\n",fu[posicao].salario);

            }
            else{
                sair=1;
                printf("\nMatr�cula n�o encontrada!!\n");
            };

            if(ulti>=0){
                printf("\nDeseja sair??\n 1 - Sim \n 2 - N�o:");
                scanf("%d",&sair);
                setbuf(stdin,NULL);
            };

        }while(sair==1);
    }
    else
        printf("\nN�o h� funcion�rios cadastrados!!!\n");

}
void consulta_departamento(departamento dep[],Funcionarios fu[],int pos,int ulti){
    int codigo,sair,posicao,sigla,i;
    char numero[20];
    if(pos>0){
        do{
            printf("\nForne�a o C�digo do departamento pelo o qual voc� deseja consultar");
            lestring(numero,20);
            codigo= atoi(numero);
            setbuf(stdin,NULL);
            posicao=pesquisa(dep,codigo,pos);
            if(posicao!=-1){
                printf("\n---------------------------------");
                printf("\nQUADRO DE FUNCION�RIOS\n");
                for(i=0;i<=ulti;i++){
                    if(fu[i].codep==dep[posicao].codigo){
                        printf("\nNome:%s",fu[i].nomefun);
                        printf("\nA data de nascimento:%s",fu[i].data);
                        printf("\nCPF:%s",fu[i].cpf);
                        printf("\nMatr�cula:%d",fu[i].matricula);
                        printf("\nC�digo do departamento:%d",fu[i].codep);
                        printf("\nSal�rio:R$%s reais \n",fu[i].salario);
                    };
                };
            }
            else
                printf("\nDepartamento n�o encontrado!!\n");

            if(pos>=0){
                printf("\nDeseja sair??\n 1 - Sim \n 2 - N�o:");
                scanf("%d",&sair);
                setbuf(stdin,NULL);
            };
        }while(sair==1);
    }
    else
        printf("\nN�o h� departamentos cadastrados!!\n");
}
void excluir_Funcionario(Funcionarios fu[],int *ulti){
    int matricula,sair,posicao;
    char numero[20];
    if(*ulti>0){
        do{
            printf("\nForne�a a Matr�cula do Funcion�rio que voc� deseja excluir:");
            lestring(numero,20);
            matricula= atoi(numero);
            setbuf(stdin,NULL);
            posicao=Pesquisafunc(fu,matricula,*ulti);
            if(posicao!=-1){
                fu[posicao]=fu[*ulti];
                (*ulti)--;
                printf("\nFuncion�rio exclu�do com Sucesso!!");
            }
            else
                printf("\nMatr�cula n�o encontrada!!!\n");
            if(*ulti>=0){
                printf("\nDeseja sair??\n 1 - Sim \n 2 - N�o:");
                scanf("%d",&sair);
            };

        }while(*ulti>=0 && sair !=1);
    }
    else
        printf("\nN�o h� Funcion�rios cadastrados!!\n");
}
void excluir_departamento(Funcionarios fu[],departamento dep[],int *pos,int *ulti){
    int codigo,sair,posicao,posicaoFun,i,ultima;
    char numero[20];
    ultima=*ulti+1;
    if(*pos>0){
        do{
            printf("\nForne�a o c�digo do departamento que voc� deseja excluir:");
            lestring(numero,20);
            codigo= atoi(numero);
            setbuf(stdin,NULL);
            posicao=pesquisa(dep,codigo,*pos);
            if(posicao!=-1){
                dep[posicao]=dep[*pos];
                (*pos)--;
                /*posicaoFun=PesquisaDep(fu,codigo,*ulti);
                if(posicaoFun!=-1){*/
                    printf("\nDepartamento Exclu�do com Sucesso!");
                    for(i=0;i<=ultima;i++){
                        if(fu[i].codep==codigo){
                            fu[i]=fu[*ulti];
                            (*ulti)--;
                        };
                    };
             //   };
            }
            else
                printf("\nDepartamento n�o encontrado!!!");
            if(*pos>=0){
                printf("\nDeseja sair??\n 1 - Sim \n 2 - N�o:");
                scanf("%d",&sair);
            };
        }while(*pos>=0 && sair!=1);


    }
    else
        printf("\nN�o H� Departamentos cadastrados!!!!\n");
}
int main(){
    departamento depar[TAM];
    Funcionarios fun[FUNC];

    char nome[50],leitura[12];
    int codigo,saida,c,ultima,ultimaposicao;
    ultimaposicao=0;
    ultima=0;

    setlocale(LC_ALL,"Portuguese");
    do{
    printf("---------------Empresa---------------");
    printf("\n------O que voc� deseja fazer?-------\n");
    printf("\nCadastrar departamento - 1");
    printf("\nCadastrar funcion�rios - 2");
    printf("\nConsultar funcion�rio - 3");
    printf("\nFuncionarios de um departamento - 4");
    printf("\nExcluir funcion�rio - 5");
    printf("\nExcluir departamento - 6");
    printf("\nPara sair digite - 7 \n");
    printf("\nForne�a o c�digo:");
    scanf("%d",&codigo);
    setbuf(stdin,NULL);
    switch(codigo){
        case 1:
            saida=1;
            cadastro1(depar,&ultimaposicao,TAM);
            break;
        case 2:
            Cadastrofunc(fun,depar,&ultimaposicao,&ultima,FUNC);
            saida=1;
            break;
        case 3:
            consulta_funcionario(depar,fun,ultimaposicao,ultima);
            saida=1;
            break;
        case 4:
            consulta_departamento(depar,fun,ultimaposicao,ultima);
            saida=1;
            break;
        case 5:
            excluir_Funcionario(fun,&ultima);
            saida=1;
            break;
        case 6:
            excluir_departamento(fun,depar,&ultimaposicao,&ultima);
            saida=1;
            break;
        case 7:
            saida=0;
            break;
        default:
            saida=1;
            printf("\nC�digo inv�lido!!!");
            printf("\nTente novamente\n");
    };

    } while(saida == 1);

    return 0;
}
