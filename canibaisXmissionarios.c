// O problema dos 3 canibais e 3 missionários//

#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
typedef int bool;
 
typedef struct No{
    int estado[5];//(C,M,C,M) 
    int lado,nivel; 
    struct No* esq, *dir;
}No;
typedef struct no {
    No guardado;
    struct no* proximo;
}no_fila;
typedef struct{
    no_fila *inicio;
}fila;
typedef No* Pont;
 
void Criar_fila(fila* l){
    l->inicio = NULL;
}
bool Vazia(fila* l)
{
    if(l->inicio == NULL) return true;
    return false;
}
bool enfileirar(fila* l, No* g){
 
    no_fila* novo, *atual;
    if (Vazia(l) == true){
        novo = (no_fila*) malloc(sizeof(no_fila));
        if (novo == NULL) return false;
        l->inicio = novo;
 
        novo->guardado.estado[0] = g->estado[0];
        novo->guardado.estado[1] = g->estado[1];
        novo->guardado.estado[2] = g->estado[2];
        novo->guardado.estado[3] = g->estado[3];
        novo->guardado.lado= g->lado;
        novo->guardado.nivel = g->nivel;
        novo->guardado.esq = g->esq;
        novo->guardado.dir = g->dir;
        novo->proximo = NULL;
        return true;
    }
 
    atual = l->inicio;
    while (atual->proximo != NULL){
        atual = atual->proximo;
    }
 
    novo = (no_fila*) malloc(sizeof(no_fila));
    if (novo == NULL) return false;
 
    atual->proximo = novo;
    novo->guardado.estado[0] = g->estado[0];
    novo->guardado.estado[1] = g->estado[1];
    novo->guardado.estado[2] = g->estado[2];
    novo->guardado.estado[3] = g->estado[3];
    novo->guardado.lado= g->lado;
    novo->guardado.nivel = g->nivel;
    novo->guardado.esq = g->esq;
    novo->guardado.dir = g->dir;
    novo->proximo = NULL;
    return true;
}
void percorrer_fila(fila* l){
    no_fila *atual;
    no_fila *prox;
    int c = 0;
 
    if (l->inicio == NULL){
        return;
    }
    else{
        for (atual = l->inicio; atual != NULL; atual = atual->proximo){
            printf("------------------------------------\n");
            printf("Canibais: %d     | Canibais: %d\n", atual->guardado.estado[0], atual->guardado.estado[2]);
            printf("Missionários: %d | Missionários: %d\n", atual->guardado.estado[1], atual->guardado.estado[3]);
            printf("------------------------------------\n");
 
            prox = atual->proximo;
            if (prox == NULL)
            {
                printf("Travessia concluída com sucesso!!\n");
                break;
            }
            else {
                if (atual->guardado.lado == 0)
                {
                    printf("     |))\n");
                    printf("...|_%d_ %d_/.........\n", (atual->guardado.estado[0] - prox->guardado.estado[0]), (atual->guardado.estado[1] - prox->guardado.estado[1]));
                    printf("__________________________________\n\n");
                }
                else
                {
                    printf("             ((|\n");
                    printf(".........\\_%d_%d_|...\n", (atual->guardado.estado[2] - prox->guardado.estado[2]), (atual->guardado.estado[3] - prox->guardado.estado[3]));
                    printf("__________________________________\n\n");
                }
            }
 
        }
    }
        return;
}
 
Pont criar_arvore(){
    return NULL;
}
 
Pont inserir_arvore(Pont raiz, Pont no, int cont){
    if (raiz == NULL){
        return (no);
    } 
    if (no->lado == 0){
            cont++;
            no->nivel = cont;
            raiz->esq = inserir_arvore(raiz->esq,no,cont);
    }
    else if(no->lado == 1){
        cont++;
        no->nivel = cont;
        raiz->dir = inserir_arvore(raiz->dir,no,cont);
    }
    return (raiz);    
}
Pont criaNovoNo(int elem[],int l){ 
    Pont novoNo = (Pont) malloc(sizeof(No));
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    for (int i = 0; i < 4; i++)
    {
        novoNo->estado[i] = elem[i];
    }
    novoNo->lado = l;
    return(novoNo);
}
void busca_largura(Pont raiz,fila*l,int lado,int *Cx,int *Mx,int *Cy,int *My,int *Esq_diminui, int *Dir_aumenta, int esq_anterior[], int dir_anterior[]){//0 é canibal e 1 é missionario
    if(raiz == NULL) return; 
    int quant_barco;
    if(lado == 0){
        raiz = raiz->esq;
        if((raiz->estado[0] <= raiz->estado[1] && raiz->estado[2] <= raiz->estado[3]) || raiz->estado[1] == 0 ||  raiz->estado[3] == 0){//saber se canibais é menor que missionarios dos dois lados ou se miss for igual a 0
            if((*Cx + *Mx) < (raiz->estado[0] + raiz->estado[1]) && (*Cy + *My) > (raiz->estado[2] + raiz->estado[3])){     
                quant_barco =  ((raiz->estado[0] + raiz->estado[1]) - ( *Cx + *Mx));//quantidade de pessoas que veio no barco    
                if(quant_barco <= 2 &&  raiz->estado[0] + raiz->estado[1] <= *Esq_diminui){//pode sair 2 ou 1 da direita e preciso checar se a esquerda ta diminuindo
                    if((*Cy + *My) - (raiz->estado[2] + raiz->estado[3]) == quant_barco && (raiz->estado[2] <= *Cy && raiz->estado[3] <= *My)){//a diferença de quem tava na margem esquerda com a margem esquerda atual precisa diminuir pois alguem foi pro outro lado com o barco
                        int cont = 0;
                        for (int z = 0; z < 4; z++)//checar se é igual
                        {
                            if (esq_anterior[z] == raiz->estado[z]){
                                cont++;
                            }
                        }
                        if(cont < 4){
                            enfileirar(l,raiz);//colocar na fila
                            for (int i = 0; i < 4; i++)//renovar o array como o novo esquerda
                            {
                                esq_anterior[i] = raiz->estado[i];
                            }
                            *Esq_diminui = raiz->estado[0] + raiz->estado[1];
                            *Cx = raiz->estado[0];
                            *Mx = raiz->estado[1];
                            *Cy = raiz->estado[2];
                            *My = raiz->estado[3];
                            return;
                        }    
                    }
                }
            }
        }
        busca_largura(raiz,l,lado,Cx,Mx,Cy,My,Esq_diminui,Dir_aumenta,esq_anterior,dir_anterior);
    }
    else if(lado == 1){
        raiz = raiz->dir;
        if((raiz->estado[0] <= raiz->estado[1] && raiz->estado[2] <= raiz->estado[3]) || raiz->estado[1] == 0 ||  raiz->estado[3] == 0){//saber se canibais é menor que missionarios dos dois lados ou se miss for igual a 0
            if((*Cx+*Mx) > raiz->estado[0] + raiz->estado[1] && (*Cy + *My) < (raiz->estado[2] + raiz->estado[3])){//Se a diferença de canibais e missionario anterior que vem da margem esquerda for <= 2, pois so pode entrar no maximo 2 no barco
                quant_barco =  abs((raiz->estado[0] + raiz->estado[1]) - (*Cx+ *Mx));
                if(quant_barco == 2 && raiz->estado[2] + raiz->estado[3] >= *Dir_aumenta){//so pode vir 2 da esquerda e checar se a direita ta aumentando
                    if(abs((*Cy + *My) - (raiz->estado[2] + raiz->estado[3])) == quant_barco && (raiz->estado[2]>= *Cy && raiz->estado[3]>= *My)){//pq to sempre adicionando alguem a margem direita então n pode ser menor que o estado de antes
                        int cont = 0;
                        for (int z = 0; z < 4; z++)//checar se é igual
                        {
                            if (dir_anterior[z] == raiz->estado[z]){
                                cont++;
                            }
                        }
                        if(cont < 4){
                            enfileirar(l,raiz);//colocar na fila
                            for (int i = 0; i < 4; i++)//renovar o array como o novo esquerda
                            {
                                dir_anterior[i] = raiz->estado[i];
                            }
                            *Dir_aumenta = raiz->estado[2] + raiz->estado[3];
                            *Cx = raiz->estado[0];
                            *Mx = raiz->estado[1];
                            *Cy = raiz->estado[2];
                            *My = raiz->estado[3];
                            return;
                        }
                    }
                }
            }
        }            
        busca_largura(raiz,l,lado,Cx,Mx,Cy,My,Esq_diminui,Dir_aumenta,esq_anterior,dir_anterior);
    }
}
void preencher_arvore(Pont r){
    //esquerda---->direita
    int estd[5];
    int cont = 0;
    int lado;
    for (int i = 3; i >= 0; i--)//canibais
    {
        for (int j = 3; j >= 0; j--)//missionarios
        {
            estd[0] = i;
            estd[1] = j;
            estd [2] = 3-i;
            estd[3] = 3-j;
            lado = 0;//esquerda
            Pont no = criaNovoNo(estd,lado);
            r = inserir_arvore(r,no,0);
            cont++;
        }
    }
    for (int i = 3; i >= 0; i--)//canibais
    {
        for (int j = 3; j >= 0; j--)//missionarios
        {
            estd[0] = i;
            estd[1] = j;
            estd [2] = 3-i;
            estd[3] = 3-j;
            lado = 1;//direita
            Pont no = criaNovoNo(estd,lado);
            r = inserir_arvore(r,no,-1);
            cont++;
        }
    }
    int ld = 1;//para ficar trocando de lado na arvore
    fila l;
    Criar_fila(&l);
    enfileirar(&l,r);//colocando na raiz o primeiro estado
    int C = r->estado[0];
    int M = r->estado[1];
    int C1 = r->estado[2];
    int M1 = r->estado[3];
    int *Cx = &C;//guardar anterior
    int *Mx = &M;
    int *Cy = &C1;//guardar anterior
    int *My = &M1;
    int d = 0; 
    int e = 6;
    int *Esq_diminui = &e;
    int *Dir_aumenta = &d;
    int esq_anterior[4] = {0,0,0,0};//para comparar se é igual a anterior, pois n pode, se n significa que não houve movimento
    int dir_anterior[4] = {0,0,0,0};
    for (int i = 0; i < 11; i++)
    {
        busca_largura(r,&l,ld,Cx,Mx,Cy,My,Esq_diminui,Dir_aumenta,esq_anterior,dir_anterior);
        ld--;
        if(ld < 0){
            ld = 1;
        }
    }
    percorrer_fila(&l);
}    
int main(){
    Pont r = criar_arvore();
    preencher_arvore(r);
    return 0;
}
