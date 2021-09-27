// Tarefa Semana 5 ERE - Tiago Torres Schmidt - TAD Lista Duplamente Encadeada.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "lista.h"
NodeItem* Inicializa_Lista(){//Inicialização padrão de lista.
  return NULL;
}

void imprime(NodeItem* firstNode,NodeItem* auxNode, FILE* output){
  fprintf(output,"%s ",auxNode->info);//Informa os valores.
  if(auxNode->nextNode != firstNode){
    imprime(firstNode,auxNode->nextNode,output);//Recursivamente, chama a função.
  }
}

NodeItem* insertItem(NodeItem* pt_list, char info[MAX_CHAR]){
    NodeItem* pt_new;

    pt_new = (NodeItem*)(malloc(sizeof(NodeItem))); //aloca espaço para o item inserido
    strcpy(pt_new->info,info);
    pt_new->nextNode = pt_new;
    pt_new->prevNode = pt_new;
    if (pt_list == NULL){
        pt_list = pt_new;   //se for o primeiro, retorna o novo primeiro
    }
    else{
        pt_new->nextNode = pt_list;
        pt_new->prevNode = pt_list->prevNode;
        pt_list->prevNode->nextNode = pt_new;
        pt_list->prevNode = pt_new;
    }
    return pt_list;
}

//retorna o valor do último item da lista
NodeItem* lastItem(NodeItem* pt_list){
    return pt_list->prevNode;
}
