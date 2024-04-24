/****************************************************************************************************************************

Alunos: Lucas Bruck;
        Marcelo Yuji Ruiz; 
        Maria Julia Pedroso de Oliveira Souza.

Data: 20/11/2023.

Pojeto: Fazer um programa em Linguagem C (ANSI C) que simule um Gerenciador de Pet Shop, conforme as ações listada a seguir.

****************************************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <time.h>
#define QNTCLI 50
#define QNTPET 50

int icli=5; 
int iserv=4;

typedef struct Data{
    int dia;
    int mes;
    int ano;
} TpData;

typedef struct Cliente{
    char nome[51];
    char tel[16];
} TpCliente;

typedef struct Animal{
    TpCliente cliente;
    char nomeani[51];
    int especie;
    TpData nascimento;
    char agressivo;
} TpAnimal;

typedef struct Servico{
    TpData dtserv;
    TpAnimal pet;
    int tpserv;
    char pago;
    int ident;
} TpServico;

TpData dataAtual() {
    time_t tempo=time(NULL); 
    struct tm dataAtual=*localtime(&tempo);

    TpData data;
    data.dia=dataAtual.tm_mday;
    data.mes=dataAtual.tm_mon + 1; 
    data.ano=dataAtual.tm_year + 1900; 

    return data;
}

int valtel(char tel[16]){       
    int i = 0, tam = 0, contnum = 0;
    if(tel[0] != '0'){
        return 0;
    }
    
    tam = strlen(tel);
    
    for(i = 0; i < tam; i++){
        if(tel[i] >= '0' && tel[i] <= '9'){
            contnum++;
        }
    }
    if(contnum == 11 || contnum == 12){
        return 1;
    } else {
        return 0;
    }
    
}

int chenome(char a[]){
    int tamanho = 0, i= 0;
    tamanho = strlen(a);
    
    if (a[0]!=' ' && tamanho>3){
        for(;i<tamanho;i++){
            if(a[i]>=0 && a[i]<'A' && a[i]!= ' ' || a[i]>'Z' && a[i]<'a'|| a[i]>'z'){
                return 0;
            }
            }
        return 1;
        }
    else{
        return 0;
    } 
}

int checdata(TpData a){
    TpData atual;
    atual = dataAtual();

    if(a.ano == atual.ano){
        if (a.mes==atual.mes){
            if(a.dia<=atual.dia && a.dia>0){
                return 1;
            }
        }
    }

    else if(a.mes % 2 !=0 && a.mes < 8 || a.mes % 2 == 0 && a.mes > 7){
        if (a.dia > 0 && a.dia < 32 && a.mes>0 && a.mes<13 && a.ano>1800 && a.ano<atual.ano){
            return 1;
        }
    }

    else if(a.mes % 2 == 0 && a.mes<7 && a.ano % 4 != 0 || a.mes % 2 != 0 && a.mes>7 && a.ano % 4 != 0){
        if (a.mes == 2){
            if (a.dia > 0 && a.dia < 29 && a.ano>1800 && a.ano<atual.ano){
                return 1;
            }
        }
          else if (a.dia > 0 && a.dia < 31 && a.mes>0 && a.mes<13 && a.ano>1800 && a.ano<atual.ano){
              return 1;
        }
    }
    else if(a.mes == 2 && a.ano % 4 == 0){
            if (a.dia > 0 && a.dia < 30 && a.ano>1800 && a.ano<atual.ano){
                return 1;
            }
    }
    else{
        return 0;
    }
}

TpCliente cadcliente(){
    TpCliente cliente;
    
    while(1){
        printf("Digite seu nome: ");
        fgets(cliente.nome, 51, stdin);
        cliente.nome[strlen(cliente.nome) - 1] = '\0';
        
        if(chenome(cliente.nome) == 0){
            printf("Nome invalido\n");
            continue;
        }
        else{
            break;
        }
    }
    while(1){
        printf("Digite seu telefone: ");
        fgets(cliente.tel, 16, stdin);
        cliente.tel[strlen(cliente.tel) - 1] = '\0';
        
        if(valtel(cliente.tel) == 0){
        printf("Telefone invalido\n");
            continue;
        }
        else{
            break;
        }
    }
        return cliente;
}

void buscacli(char nomecli[], TpAnimal Vet[]){
    int i=0, j=0;
    
    for(;i<QNTCLI;i++){
        if (strcmp(Vet[i].cliente.nome, nomecli)==0){
            printf("\nNome: %s\nTelefone:%s\nNome Animal:%s\nRaca Animal:%d\nNascimento Animal:%d/%d/%d\nAgressivo? %c\n", Vet[i].cliente.nome,Vet[i].cliente.tel, 
                    Vet[i].nomeani, Vet[i].especie, Vet[i].nascimento.dia,Vet[i].nascimento.mes, Vet[i].nascimento.ano,Vet[i].agressivo);
            j++;
        }
    }
    if(j==0){
        printf("Nome nao cadastrado\n");
    }
}

int busposcli(char nomecli[], TpAnimal Vet[]){
    int i=0, j=-1;
    
    for(;i<icli;i++){
        if (strcmp(Vet[i].cliente.nome, nomecli)==0){
            return i;
        }
    }
    if(j==-1){
        printf("Nome nao cadastrado\n");
        return j;
    }
}

TpAnimal cadanimal() {
    TpAnimal animal;
    char nom[51];  
    while(1){
        printf("Digite o nome do animal: ");
        fgets(animal.nomeani, 51, stdin);
        animal.nomeani[strlen(animal.nomeani) - 1] = '\0';
        
        if(chenome(animal.nomeani) == 0){
            printf("Nome invalido\n");
            continue;
        }
        else{
            break;
        }
    }
        printf("Digite a especie: ");
        scanf("%d", &animal.especie);

    while(1){
        printf("Digite a data de nascimento: ");
        scanf("%d %d %d", &animal.nascimento.dia, &animal.nascimento.mes, &animal.nascimento.ano);

        if (checdata(animal.nascimento)==1){
            break;
        }
        else{
            printf("Data invalida\n");
            continue;
        }
        }
        printf("O animal e agressivo? 'S' para sim, 'N' para nao: ");
        scanf(" %c", &animal.agressivo);
    
    return animal;
}
void buscaani(char nome[], TpAnimal Vet[]){
    int i=0, j=0;
    
    for(;i<icli;i++){
        if (strcmp(Vet[i].nomeani, nome)==0){
            printf("Nome: %s\nTelefone:%s\nNome Animal:%s\nRaca Animal:%d\nNascimento Animal:%d/%d/%d\nAgressivo? %c\n", Vet[i].cliente.nome,Vet[i].cliente.tel, 
                    Vet[i].nomeani, Vet[i].especie, Vet[i].nascimento.dia,Vet[i].nascimento.mes, Vet[i].nascimento.ano,Vet[i].agressivo);
            j++;
        }
    }
    if(j==0){
        printf("Pet nao cadastrado\n");
    }
}

void citaranima(TpAnimal Vet[]){
    int i=0;
    char a ='a', A='A';
    
    for(;a<='z';a++, A++){
        for(i=0;i<icli;i++){
            if(Vet[i].nomeani[0]==a || Vet[i].nomeani[0]==A){
                printf("Nome Animal:%s      Nome dono:%s        Tel:%s\n", Vet[i].nomeani, Vet[i].cliente.nome, Vet[i].cliente.tel);
            }
        }
    }
}

int qntagre(TpAnimal Vet[]){
    int i=0, h=0;
    
    for(;i<icli;i++){
        if (Vet[i].agressivo=='S' || Vet[i].agressivo == 's'){
            h++;
        }
    }
    return h;
}

int buscaposani(char nome[], TpAnimal Vet[]){
    int i=0, j=-1;
    
    for(;i<icli;i++){
        if (strcmp(Vet[i].nomeani, nome)==0){
            return i;
        }
    }
    if(j==-1){
        printf("Pet nao cadastrado\n");
        return j;
    }
}

TpServico ofeserv(TpAnimal Vet[]){
    int nomecadsn=0, opc=0;
    TpServico servico;
    char simounao, nome[50];

    servico.dtserv = dataAtual();
   
    printf("(1)Banho    (2)Tosa\t(3)Vacina\n");
    scanf("%d", &servico.tpserv);
    getchar();
    printf("Pago?\n");
    scanf("%c", &servico.pago);

    servico.ident=iserv + 1 ;
    printf("Identificador do servico %d\n", servico.ident);
    
    return servico;
}

int servicon (TpServico servi[]) {

    int servmais1 = 0,
    servmais2 = 0,
    servmais3 = 0,
    i = 0;
    
    for (i = 0; i < iserv; i++) {
    if(servi[i].tpserv == 1) {
        servmais1++;
        } 
    if(servi[i].tpserv == 2) {
        servmais2++;
        } 
    if(servi[i].tpserv == 3) {
        servmais3++;
        }
    } 
    if(servmais1 > servmais2 && servmais1 > servmais3) {
        return 1;
    } 
    else if(servmais2 > servmais1 && servmais2 > servmais3) {
        return 2;
    } 
    else if(servmais3 > servmais1 && servmais3 > servmais2) {
        return 3;
    }
    else if(servmais1 == servmais2) {
        return 12;
    }
    else if(servmais1 == servmais3) {
        return 13;
    }
    else if(servmais2 == servmais3) {
        return 23;
    }
    else if(servmais1 == servmais2 && servmais1 == servmais3) {
        return 123;
    }
} 

void pagarconta(char nome[], TpServico serv[]){
    int i=0, conta=0;
    char sn;

    for(;i<iserv;i++){
        if((strcmp(nome, serv[i].pet.cliente.nome)==0 && serv[i].pago=='n') || (strcmp(nome, serv[i].pet.cliente.nome)==0 && serv[i].pago=='N')){
            printf("Servico %d com numero %d. Adicionar a conta?", serv[i].tpserv, serv[i].ident);
            scanf("%c", &sn);
            getchar();

            if(sn=='s'|| sn=='S'){
                if(serv[i].tpserv==1){
                    conta+=40;
                }
                else if(serv[i].tpserv==2){
                    conta+=65;
                }
                else if(serv[i].tpserv==3){
                    conta+=120;
                }
                serv[i].pago='s';
            } 
        }
        
    }
    printf("Total pago:%d\n", conta);
}

void valpend(TpServico servico[]){
    int i = 0, j = 0,k=0, limlist=0,valtotal = 0,valdad=0;
    char nomesusa[iserv][51];

    for(i = 0;i<iserv; i++, valtotal = 0,valdad=0){
        for(k=0;k<limlist;k++){
          if(strcmp(nomesusa[k],servico[i].pet.nomeani)==0){
            valdad=1;
            break;
          }
        }
        if(valdad==1){
          continue;
        }
        if(servico[i].pago == 'n' || servico[i].pago == 'N'){
            for(j = 0; j < iserv; j++){
                if((servico[j].pago == 'n' && strcmp(servico[i].pet.nomeani, servico[j].pet.nomeani) == 0 )
                    ||(servico[j].pago == 'N' && strcmp(servico[i].pet.nomeani, servico[j].pet.nomeani) == 0)){
                        if(servico[j].tpserv==1){
                            valtotal+=40;
                        }
                        else if(servico[j].tpserv==2){
                            valtotal+=65;
                        }
                        else if(servico[j].tpserv==3){
                            valtotal+=120;
                        }
                    }
            }
        }
       printf("Animal: %s\nValor a se pagar:%d\n", servico[i].pet.nomeani, valtotal);
       strcpy(nomesusa[limlist],servico[i].pet.nomeani);
       limlist++;       
    }
}

void mostraranimais(TpAnimal animal[]){
    int i = 0, tipo = 0;
    for(tipo = 1; tipo < 5; tipo++){
        printf("Especie: %d\t", tipo);
        for(i = 0; i < icli; i++){
            if(tipo == animal[i].especie)
            printf("Nome: %s\tNascimento: %0d/%d/%d\tAgressividade: %c | ", animal[i].nomeani, animal[i].nascimento.dia, animal[i].nascimento.mes,
                                                                        animal[i].nascimento.ano, animal[i].agressivo);
        }
        printf("\n");
    }
}

void promocao(int dia, int mes, TpAnimal animal[]){
    int diamax = dia + 7, mesmax = mes,i =0;
    
    if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10){
            if(diamax > 31){
                diamax -=31;
                mesmax++;
            }
        }
    else if(mes == 4||mes == 6||mes == 9||mes == 11){
      if(diamax >30){
        diamax -=30;
                mesmax++;
            }
        }
     else if(mes==2){
            if(diamax>28){
                diamax -=28;
                mesmax++;
            }
        }
        if(mes == 12){
            if(diamax > 31){
                diamax -=31;
                mesmax=1;
            }
        }

    for(; i < icli; i++){
        if(animal[i].nascimento.mes == mes){
            if(animal[i].nascimento.dia >= dia){
            printf("\nNome do dono: %s\nTelefone: %s\nNome do animal: %s\nEspecie: %d\nNascimento: %0d/%d\nAgressivo: %c\n", animal[i].cliente.nome, animal[i].cliente.tel, animal[i].nomeani, animal[i].especie, animal[i].nascimento.dia, animal[i].nascimento.mes, animal[i].agressivo);
            }
        }
        else if(animal[i].nascimento.mes == mesmax){
            if(animal[i].nascimento.dia <= diamax){
            printf("\nNome do dono: %s\nTelefone: %s\nNome do animal: %s\nEspecie: %d\nNascimento: %0d/%d\nAgressivo: %c\n", animal[i].cliente.nome, animal[i].cliente.tel, animal[i].nomeani, animal[i].especie, animal[i].nascimento.dia, animal[i].nascimento.mes, animal[i].agressivo);
            }
        }
    }
}

int main() {
    int opc = 0, i2 = 0, agre = 0, a=0, qnt=0, i=0, z = 0, dia = 0, mes = 0;
    char nome[51];
    TpCliente aux;
    TpAnimal animal[QNTCLI];
    TpServico servico[51];
    
    TpData dati;
    dati.dia=10;
    dati.mes=8;
    dati.ano=2015;
    strcpy(animal[0].cliente.nome, "Lucas");
    strcpy(animal[0].cliente.tel, "011 94221 3404");
    strcpy(animal[0].nomeani, "Kate");
    animal[0].nascimento.dia=3;
    animal[0].nascimento.mes=10;
    animal[0].nascimento.ano=2008;
    animal[0].agressivo='s';
    animal[0].especie = 2;
    strcpy(animal[1].cliente.nome, "Marcelo");
    strcpy(animal[1].cliente.tel, "043 998066200");
    strcpy(animal[1].nomeani, "Robson");
    animal[1].nascimento.dia=3;
    animal[1].nascimento.mes=1;
    animal[1].nascimento.ano=2005;
    animal[1].agressivo='n';
    animal[1].especie = 3;
    strcpy(animal[2].cliente.nome, "Maju");
    strcpy(animal[2].cliente.tel, "043 998637050");
    strcpy(animal[2].nomeani, "Olivia");
    animal[2].nascimento.dia=30;
    animal[2].nascimento.mes=4;
    animal[2].nascimento.ano=2004;
    animal[2].agressivo='s';
    animal[2].especie = 1;
    strcpy(animal[3].cliente.nome, "Maju");
    strcpy(animal[3].cliente.tel, "043 998637050");
    strcpy(animal[3].nomeani, "Frajola");
    animal[3].nascimento.dia=23;
    animal[3].nascimento.mes=8;
    animal[3].nascimento.ano=2020;
    animal[3].agressivo='n';
    animal[3].especie = 2;
    strcpy(animal[4].cliente.nome, "Lucas");
    strcpy(animal[4].cliente.tel, "011 94221 3404");
    strcpy(animal[4].nomeani, "Piupiu");
    animal[4].nascimento.dia=18;
    animal[4].nascimento.mes=3;
    animal[4].nascimento.ano=2019;
    animal[4].agressivo='s';
    animal[4].especie = 3;
    servico[0].dtserv = dataAtual();
    servico[0].pet = animal[0];
    servico[0].tpserv = 3;
    servico[0].pago = 'n';
    servico[0].ident = 1;
    servico[1].dtserv = dataAtual();
    servico[1].pet = animal[1];
    servico[1].tpserv = 2;
    servico[1].pago = 'n';
    servico[1].ident = 2;
    servico[2].dtserv = dataAtual();
    servico[2].pet = animal[2];
    servico[2].tpserv = 1;
    servico[2].pago = 'n';
    servico[2].ident = 3;
    servico[3].dtserv = dataAtual();
    servico[3].pet = animal[0];
    servico[3].tpserv = 1;
    servico[3].pago = 'n';
    servico[3].ident = 4;
    
    
    while(1) {
        printf("\n1)Cadastrar cliente\t\t2)Buscar cliente\n3)Cadastrar pet\t\t\t4)Buscar pet\n5)Listar pets\t\t\t6)Qntd agressivos\n"
                "7)Oferecer servico\t\t8)Servico mais utilizado\t\t\t\n9)Pagar conta pendente\t\t10)Valores pendentes\n11)Listar animais por especie\t12)Sistema de promocoes\n");
        scanf("%d", &opc);
        getchar();
        
        switch(opc){
            case 1:
                animal[icli].cliente = cadcliente();
                animal[icli].nomeani[0] = '.';
                icli++;
                break;
                
            case 2:
                printf("Nome do cliente: ");
                fgets(nome, 51, stdin);
                nome[strlen(nome) - 1] = '\0';
                buscacli(nome, animal);
                break;
                
            case 3:
                printf("Nome do dono:");
                fgets(nome, 51, stdin);
                nome[strlen(nome) - 1] = '\0';

                a=busposcli(nome, animal);
                if (a !=-1 && animal[a].nomeani[0] == '.'){
                    aux = animal[a].cliente;
                    animal[a] = cadanimal();
                    animal[a].cliente = aux;
                }
                else if(a != -1 && animal[a].nomeani[0] != '.'){
                    animal[icli] = cadanimal();
                    animal[icli].cliente = animal[a].cliente;
                    icli++;
                }
                else{
                    aux = cadcliente();
                    animal[icli] = cadanimal();
                    animal[icli].cliente=aux;
                    icli++;
                }
                break;
            
            case 4:
                printf("Nome do pet: ");
                fgets(nome, 51, stdin);
                nome[strlen(nome) - 1] = '\0';
                buscaani(nome, animal);
                break;
            
            case 5:
                citaranima(animal);
                break;
        
            case 6:
                agre = qntagre(animal);
                printf("%d animal(is) agressivo(s)\n", agre);
                break;
            
            case 7:
                printf("Nome do animal: ");
                fgets(nome, 51, stdin);
                nome[strlen(nome) - 1] = '\0';

                a=buscaposani(nome, animal);
                if(a==-1){
                    continue;
                }
                servico[iserv] = ofeserv(animal);
                servico[iserv].pet = animal[a];
                iserv++;
                break;

            case 8:
                qnt = servicon(servico);

                if (qnt == 1 ||qnt == 2 || qnt == 3 ){
                    printf("O servico mais pedido foi o %d\n", qnt);
                }
                else if(qnt == 12){
                    printf("Os servicos mais pedidos foram os 1 e 2\n");
                }
                else if(qnt == 13){
                    printf("Os servicos mais pedidos foram os 1 e 3\n");
                }
                else if(qnt == 23){
                    printf("Os servicos mais pedidos foram os 2 e 3\n");
                }
                else if(qnt == 123){
                    printf("Todos os pedidos foram feitos a mesma quantidade de vezes\n");
                }
                break;
                
            case 9:
                printf("Nome do dono:");
                fgets(nome, 51, stdin);
                nome[strlen(nome) - 1] = '\0';
                pagarconta(nome, servico);
                break;
            
            case 10:
                valpend(servico);
                break;
            
            case 11:
                mostraranimais(animal);
                break;
            
            case 12:
                printf("Parametros: ");
                scanf("%d %d", &dia, &mes);
                promocao(dia, mes, animal);
        }
    }
    
}
