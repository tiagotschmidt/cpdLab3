// Tarefa Semana 5 ERE - Tiago Torres Schmidt - TAD Header Lista Duplamente Encadeada.
#define MAX_CHAR 20

struct nodeStruct { //Estruturas do nó.
    char info[MAX_CHAR];
    struct nodeStruct* nextNode;
    struct nodeStruct* prevNode;
};
typedef struct nodeStruct NodeItem;

NodeItem* Inicializa_Lista();
//Inicializa a lista.
void imprime(NodeItem* firstNode,NodeItem* auxNode, FILE* output);

NodeItem* insertItem(NodeItem* pt_list, char info[MAX_CHAR]);

NodeItem* lastItem(NodeItem* pt_list);
