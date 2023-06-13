#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//string --- para usar a funcao strcmp para comparar duas strings
//stdlib --- para usar a funcao system para limpar a tela
typedef struct{
    char denuncias[200];
}denun;
typedef struct{
    int id;
    int quantdenun;
    denun y[50];
    char l[50];
    char s[50];
    int statuslabresp;
    int statuslab;
    int statuscomp;
    int avisos[50];
    int quantavisos;
}user;
//l --- login
//s --- senha
//quantdenun --- quantidade de denuncias que o usuario tem
//quantavisos --- quantidade de avisos que o usuario tem
//statuslabresp --- codigo em numeros para saber se o usuario esta responsavel por um laboratorio
//statuslab --- para saber em que lab o usuario esta
//statuscomp --- para saber em que computador o usuario esta
int i=0;
//i e o numero de usuarios cadastrados
user x[200];

int verif(char z[]){
    //verif e uma funcao usada para verificar se um usuario ja foi logado, e se ja, ela retorna o indice "j" desse usuario dentro do vetor x
    for(int j=0;j<=i;j++){
        if(strcmp(z,x[j].l)==0){
            return j;
        }
    }
    return -1;
}
void cad(){
    int w;
    char t;
    if(i<200){
        //se 199 usuarios foram cadastrados, ninguem mais pode se cadastrar
        FILE *arquivologin;
        arquivologin=fopen("login.txt","a");
        //cria um ponteiro que aponta o endereco de um arquivo de texto, abre e anexa as informacoes do "fprintf"
        if(arquivologin==NULL){
            //arquivologin==NULL significa que teve algum erro na hora de abrir o arquivo
            printf("arquivo nao encontrado");
        }
        do{
            printf("login: ");
            scanf("%c",&t);
            scanf("%[^\n]",x[i].l);
            fprintf(arquivologin,"login %d: %s\n",i,x[i].l);
            //salva cada login no arquivo de texto "arquivologin"
            w=verif(x[i].l);
        }while(w!=-1 && w!=i);
        fclose(arquivologin);
        //fecha e salva as alteracoes no arquivo de texto
        printf("senha: ");
        scanf("%c",&t);
        scanf("%[^\n]",x[i].s);
        i++;
    }
}
void exc(int w){
    //y e uma variavel do tipo user que recebe o ultimo usuario cadastrado
    //o vetor do ultimo usuario vai receber o do usuario a ser excluido
    //o vetor do usuario a ser excluido vai receber o vetor do ultimo usuario
    //a quantidade de usuarios "i" diminui em 1
    user y=x[i];
    x[i]=x[w];
    x[w]=y;
    i--;
}
void senha(int w){
    char temp;
    printf("\nnova senha: \n");
    scanf("%c",&temp);
    scanf("%[^\n]",x[w].s);
}
void alterarlogin(int w){
    int k;
    char temp,aux[50];
    do{
        printf("\nnovo login: \n");
        scanf("%c",&temp);
        scanf("%[^\n]",aux);
        
        k=verif(aux);
        //para garantir que esse login ja nao exista
    }while(k!=-1);

    strcpy(x[w].l,aux);
    //copia a string de aux para dentro do login
    
}
void agendarlab(int w){
    int op;
    if(x[w].quantdenun<5){
        if(x[w].statuslabresp==0){
            do{
                printf("laboratorio 1 ou 2? ");
                scanf("%d",&op);
            }while(op!=1 && op!=2);
            int y=0;
            for(int j=0;j<=i;j++){
                if(x[j].statuslabresp==op){
                    y=-1;
                    //y e usado para comparar se alguem ja ocupa o lab
                    printf("lab ocupado\n");
                    break;
                }
            }
            if(y==0){
                printf("voce esta responsavel pelo lab %d\n",op);
                x[w].statuslabresp=op;
                //statuslabresp e uma variavel usada para saber quem esta responsavel pelo lab
                x[w].statuslab=op;
            }
            y=0;
        }else{
            printf("voce ja alugou um lab\n");
        }
    }else{
        printf("voce tem muitas denuncias :[ nao podera agendar um laboratorio\n");
    }
    FILE *arquivolab;
    arquivolab=fopen("lab.txt","a");
    fprintf(arquivolab,"LAB: %d aberto\n",op);
    fclose(arquivolab);
    printf("pressione ENTER para continuar: ");
    char temp;
    scanf("%c",&temp);
    scanf("%c",&temp);
    //dois scanf ao mesmo porque quando alguem digita algo o enter fica no buffer do teclado, e caso esse buffer nao seja limpado ele pula o proximo scanf
    //ou seja, scanf 1 --- limpa o buffer scanf 2 --- le o enter
}
int sairlab(int w){
    int op,k,p=201,auxcod;
    char aux[50],temp;
    
    if(x[w].statuslab!=0){
        do{
            printf("deseja trocar o lab/computador com alguem?\n1-sim\n2-nao\n");
            scanf("%d",&op);
        }while(op!=1 && op!=2);
        int op2=0;
        
        do{
            printf("1-sair lab\n2-sair pc\n");
            scanf("%d",&op2);
        }while(op2!=1 && op2!=2);
        
        if(op2==2 && x[w].statuscomp==0){
            //para a funcao caso a pessoa nao esteja usando nenhum pc
            printf("voce nao esta utilizando nenhum pc\n");
            printf("pressione ENTER para continuar: ");
            scanf("%c",&temp);
            scanf("%c",&temp);
            return 0;
            //return para parar a funcao
        }else if(op2==1 && x[w].statuslabresp==0){
            //para a funcao caso a pessoa nao esteja responsavel por nenhum lab
            printf("voce nao esta responsavel por nenhum lab");
            printf("pressione ENTER para continuar: ");
            scanf("%c",&temp);
            scanf("%c",&temp);
            return 0;
        }
        if(op==1 && i==1){
            printf("nao ha com quem trocar\n");
            //se o numero de usuarios "i" for 1, significa que somente o usuario 0 foi cadastrado, logo, nao tem com quem trocar
            printf("voce nao esta responsavel por nenhum lab");
            printf("pressione ENTER para continuar: ");
            scanf("%c",&temp);
            scanf("%c",&temp);
            return 0;
        }
        if(op==1 && i>1){
            do{
                printf("login da pessoa: ");
                scanf("%c",&temp);
                scanf("%[^\n]",aux);
                k=verif(aux);
                printf("codigo de troca da pessoa (id): ");
                scanf("%d",&auxcod);
            }while(k==-1 && auxcod!=x[k].id);
            x[k].quantavisos++;
            x[k].avisos[x[k].quantavisos]=2;
            //2 e o codigo de troca do algoritmo
            //envia um aviso para o usuario k que alguem realizou uma troca com ele, ele pode ver seus avisos quando logar
            //caso o usuario tenha feito uma troca de ma fe e o outro nao concorde, ele pode denuncia-lo
                
                    
            if(op2==1){
                if(x[k].statuslabresp==0){
                    //se a pessoa cujo o usuario quer trorcar nao for responsavel por nenhum lab
                    x[k].statuslabresp=x[w].statuslabresp;
                    x[k].statuslab=x[w].statuslab;
                    //troca os status do usuario responsavel do lab pelos status do segundo usuario
                    printf("troca realizada :]\n");
                    //1 e o codigo de troca do algoritmo
                    //envia um aviso para o usuario k que alguem realizou uma troca com ele, ele pode ver seus avisos quando logar
                    //caso o usuario tenha feito uma troca de ma fe e o outro nao concorde, ele pode denuncia-lo
                }else{
                    //tira todos os usuarios do  lab cujo a segunda pessoa e responsavel
                    FILE *arquivolab;
                    arquivolab=fopen("lab.txt","a");
                    fprintf(arquivolab,"LAB: %d fechado",x[k].statuslabresp);
                    fclose(arquivolab);
                    for(int j=0;j<=i;j++){
                        if(x[j].statuslab==x[k].statuslabresp && k!=j){
                            x[j].statuslab=0;
                            x[j].statuscomp=0;
                        }
                    }
                    x[k].statuslabresp=x[w].statuslabresp;
                    x[k].statuslab=x[w].statuslab;
                    x[w].statuslabresp=0;
                    printf("troca realizada :]\n");
                    x[k].quantavisos++;
                    x[k].avisos[x[k].quantavisos]=2;
                    //2---codigo de troca, avisa a pessoa que alguem troca de lab/pc com voce
                    if(x[k].statuscomp==0){
                        x[k].statuslab=0;
                    }
                    //statuslab so vai ser zero se a pessoa quiser sair do computador tbm ou se nao estiver usando nenhum pc
                }
            }else{
                x[k].statuscomp=x[w].statuscomp;
                x[k].statuslab=x[w].statuslab;
                printf("troca realizada :]\n");
                x[k].quantavisos++;
                x[k].avisos[x[k].quantavisos]=2;
                //avisa o usuario que alguem trocou com ele
                if(x[w].statuslabresp==0){
                    x[w].statuslab=0;
                }
                x[w].statuscomp=0;
            }
        }else if(op==2){
            //nao trocar, so sair
            x[w].statuslab=0;
            if(op2==1){
                FILE *arquivolab;
                arquivolab=fopen("lab.txt","a");
                fprintf(arquivolab,"LAB: %d fechado",x[w].statuslabresp);
                fclose(arquivolab);
                for(int j=0;j<=i;j++){
                    if(x[j].statuslab==x[w].statuslabresp && w!=j){
                        x[j].statuslab=0;
                        x[j].statuscomp=0;
                    }
                    //para que quando alguem que agendou o lab (seu responsavel) sair do lab todos saiam tbm
                }
                if(x[w].statuscomp==0){
                    x[w].statuslab=0;
                }
                x[w].statuslabresp=0;
            }else{
                x[w].statuscomp=0;
                if(x[w].statuslabresp==0){
                    x[w].statuslab=0;
                }
            }
        }
    printf("tudo certo :]\n");
    }else{
        printf("voce nao esta em nenhum lab\n");
    }
    printf("pressione ENTER para continuar: ");
    scanf("%c",&temp);
    scanf("%c",&temp);
}
int agendarcomp(int w){
    int op,op2;
    if(x[w].statuscomp==0){
        do{
            printf("laboratorio 1 ou 2? ");
            scanf("%d",&op);
        }while(op!=1 && op!=2);
        do{
            printf("escolha um pc (de 1 a 21): ");
            scanf("%d",&op2);
        }while(op2<1 || op2>21);
        int y=0;
        for(int j=0;j<=i;j++){
            if(x[j].statuslabresp==op){
                //verifica se alguem agendou o lab, se agendou, y=-1, senao y==0
                y=-1;
            }
            if(x[j].statuscomp==op2 && x[j].statuslab==op){
                //verifica se alguem ja esta usando o mesmo computador no mesmo lab
                printf("computador ocupado\n");
                printf("pressione ENTER para continuar: ");
                char temp;
                scanf("%c",&temp);
                scanf("%c",&temp);
                return 0;
            }
        }
        if(y==-1){
            printf("tudo certo :]\n");
            x[w].statuslab=op;
            x[w].statuscomp=op2;
            //a variavel statuslab vai indicar o lab que o usuario escolheu e statuscomp o computador
        }else{
            printf("ninguem agendou esse laboratorio :[\n");
        }
        y=0;
    }else{
        printf("voce ja esta com um pc, saia do pc atual\n");
        printf("pressione ENTER para continuar: ");
        char temp;
        scanf("%c",&temp);
        scanf("%c",&temp);
        sairlab(w);
    }
    printf("pressione ENTER para continuar: ");
    char temp;
    scanf("%c",&temp);
    scanf("%c",&temp);
}
void veravisos(int w){
    for(int j=1;j<=x[w].quantavisos;j++){
        if(x[w].quantavisos==0){
            printf("nenhum aviso, avisos so aparecem apos denuncias e trocas de pc/lab\n");
            break;
        }
        if(x[w].avisos[x[w].quantavisos]==1){
            printf("alguem te denunciou\n");
        }else if(x[w].avisos[x[w].quantavisos]==2){
            printf("alguem trocou de lab com voce\n");
        }
    }
    x[w].quantavisos=0;
    printf("pressione ENTER para continuar: ");
    char temp;
    scanf("%c",&temp);
    scanf("%c",&temp);
    
}
void lab(int w){
    int op;
    do{
        system("clear");
        printf("\n----------------------------------------\nlaboratorio\n----------------------------------------\n");
        printf("\n1-agendar o lab\n2-agendar um computador\n3-sair do lab/computador\n4-voltar\n\n");
        scanf("%d",&op);
        switch(op){
            case 1:
                agendarlab(w);    
            break;
            case 2:
                agendarcomp(w);
            break;
            case 3:
                sairlab(w);
            break;
            case 4:
            break;
            default:
                printf("opcao invalida");
            break;
        }
    }while(op!=4);
}
int login(){
    int w;
    char aux[50],auxs[50],temp;
    if(i>0){
        do{
            printf("login: ");
            scanf("%c",&temp);
            scanf("%[^\n]",aux);
            w=verif(aux);
        }while(w==-1);
        do{
            printf("senha: ");
            scanf("%c",&temp);
            scanf("%[^\n]",auxs);
        }while(strcmp(auxs,x[w].s)!=0);
        int op;
        do{
            system("clear");
            printf("\n----------------------------------------\nLogin\n----------------------------------------\n");
            printf("\n1-alterar senha\n2-alterar login\n3-excluir\n4-usar o laboratorio\n5-avisos(%d)\n6-ver id\n7-voltar\n\n",x[w].quantavisos);
            scanf("%d",&op);
            switch(op){
                case 1:
                    senha(w);
                break;
                case 2:
                    alterarlogin(w);
                break;
                case 3:
                    exc(w);
                    printf("conta excluida");
                    return 0;
                    //op=5 para que quando a conta seja escluida volte para o inicio
                break;
                case 4:
                    lab(w);
                break;
                case 5:
                    veravisos(w);
                break;
                case 6:
                    printf("seu id é: %d\n",w);
                    printf("pressione ENTER para continuar: ");
                    scanf("%c",&temp);
                    scanf("%c",&temp);
                break;
                case 7:
                break;
                default:
                    printf("opcao invalida\n");
                    printf("nenhum usuario cadastrado, cadastre-se :]\n");
                    printf("pressione ENTER para continuar: ");
                    scanf("%c",&temp);
                    scanf("%c",&temp);
                break;
            }
        }while(op!=7);
    }else{
        printf("nenhum usuario cadastrado, cadastre-se :]\n");
        printf("pressione ENTER para continuar: ");
        scanf("%c",&temp);
        scanf("%c",&temp);
        cad();
    }
}
void listar(){
    if(i!=0){
        for(int j=0;j<=i;j++){
            printf("%s\n",x[j].l);
        }
    }else{
        printf("\nnenhum usuario cadastrado :[\n\n");
    }
    printf("pressione ENTER para continuar: ");
    char temp;
    scanf("%c",&temp);
    scanf("%c",&temp);
}
void denunciar(){
    int w;
    char aux[50],temp;
    if(i>1){
        FILE *arquivodenuncias;
        arquivodenuncias=fopen("denuncias.txt","a");
        //cria um arquivo txt com as denuncias de cada usuario
        do{
            printf("\nusuario: ");
            scanf("%c",&temp);
            scanf("%[^\n]",aux);
            w=verif(aux);
            //de novo a funcao verif para garantir que o login existe e poder pegar o indice (w) do usuario
        }while(w==-1);
        printf("denuncia: ");
        scanf("%c",&temp);
        scanf("%[^\n]",x[w].y[x[w].quantdenun].denuncias);
        fprintf(arquivodenuncias,"denuncia %d (login %s): %s\n",x[w].quantdenun,x[w].l,x[w].y[x[w].quantdenun].denuncias);
        //registra as denuncias em um arquivo
        fclose(arquivodenuncias);
        x[w].quantdenun++;
        x[w].quantavisos++;
        x[w].avisos[x[w].quantavisos]=1;
        //codigo de denuncia
    }else{
        printf("ninguem pra denunciar\n");
    }
    printf("pressione ENTER para continuar: ");
    scanf("%c",&temp);
    scanf("%c",&temp);
}
void verdenuncias(){
    char temp,aux[50];
    int w;
    if(i>0){
        do{
            printf("login: ");
            scanf("%c",&temp);
            scanf("%[^\n]",aux);
            w=verif(aux);
        }while(w==-1);
        if(x[w].quantdenun==0){
            printf("esse usuario nao tem denuncias");
        }else{
            for(int j=1;j<=x[w].quantdenun;j++){
                printf("%s\n",x[w].y[j].denuncias);
            }
        }
    }else{
        printf("nao ha ninguem para denunciar\n");
    }
    printf("pressione ENTER para continuar: ");
    scanf("%c",&temp);
    scanf("%c",&temp);
}
int main()
{
    int op;
    do{
        system("clear");
        printf("\n----------------------------------------\nBem vindo ao controle de laboratorio :]\n----------------------------------------\n");
        printf("\n1-cadastro\n2-login\n3-denunciar\n4-listar\n5-ver denuncias\n6-sair\n\n");
        scanf("%d",&op);
        switch(op){
            case 1:
                cad();
            break;
            case 2:
                login();
            break;
            case 3:
                denunciar();
            break;
            case 4:
                listar();
            break;
            case 5:
                verdenuncias();
            break;
            case 6:
            break;
            default:
                printf("opcao invalida\n");
            break;
        }
    }while(op!=6);
    return 0;
}
