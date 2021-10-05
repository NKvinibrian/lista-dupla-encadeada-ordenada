#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

/*** DEFINICAO DA ESTRUTURA DE DADOS (TAD) (NAO ALTERAR!) ***/
struct node {
    int dado;
    struct node* proximo;
    struct node* anterior;
};
typedef struct node node;

struct list {
    node* cabeca;
    node* cauda;
    int size;
};
typedef struct list list;

list* l_create(void) {
    list* nova = malloc(sizeof(list));
    nova->cabeca = nova->cauda = NULL;
    return nova;
}

void l_destroy(list* l) {
    if (l == NULL) {
        return;
    }
    while (l->cabeca != NULL) {
        node* p = l->cabeca;
        l->cabeca = p->proximo;
        free(p);
    }
    free(l);
}

int l_head(const list* l) {
    if (l == NULL || l->cabeca == NULL) {
        return INT_MIN;
    }
    return l->cabeca->dado;
}

int l_tail(const list* l) {
    if (l == NULL || l->cauda == NULL) {
        return INT_MAX;
    }
    return l->cauda->dado;
}

void l_print(const list* l, int o) {
    if (l == NULL || o == 0) {
        return;
    }
    if (l->cabeca == NULL) {
        printf("(VAZIA)");
        return;
    }
    node* p = o > 0? l->cabeca: l->cauda;
    while (p != NULL) {
        printf("%d ", p->dado);
        p = o > 0? p->proximo: p->anterior;
    }
}

void l_insert_in_order(list* l, int v, int o) {
    if(l == NULL || o == 0){
        return;
    }
    node* p = malloc(sizeof(node));
    p->dado = v;
    if(l->cabeca == NULL){
        l->cabeca=p;
        l->cauda=p;
        l->size++;
        return;
    }
    if(p->dado < l->cabeca->dado){
        l->cabeca->anterior = p;
        p->proximo = l->cabeca;
        l->cabeca = p;
        return;
    }

    node* i = l->cabeca;
    if (o>0) {
        while (i != NULL) {
            if (i->proximo == NULL) {
                i->proximo = p;
                p->anterior = l->cauda;
                l->cauda = p;
                break;
            }
            if (p->dado >= i->dado && p->dado < i->proximo->dado) {
                p->proximo = i->proximo; // copia e cola endereço do noh com valor menor
                p->anterior = i; // define endereco no novo noh para receber o noh menor
                p->proximo->anterior = p; // define o noh com valor menor para receber o novo noh como anterior
                i->proximo = p; // define noh menor para receber o novo noh
                break;
            }
            i = i->proximo;
        }
    }
}

/*** PROGRAMA DE TESTE (NAO ALTERAR!) ***/
int main(void) {
    list* l = l_create();
    int o;
    scanf("%d", &o);
    int n;
    do {
        scanf("%d", &n);
        if (n > 0) {
            l_insert_in_order(l, n, o);
        }
    } while (n > 0);
    l_print(l, 1); putchar('\n');
    l_print(l, -1); putchar('\n');
    printf("%d\n", l_head(l));
    printf("%d\n", l_tail(l));
    l_destroy(l);
    return EXIT_SUCCESS;
}