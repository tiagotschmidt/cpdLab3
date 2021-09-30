// Trabalho Laboratório 3 - Classificação e Pesquisa de Dados - Gabriel Castelo Branco Gomes e Tiago Torres Schmidt.
#include <stdio.h>//Bibliotecas utilizadas no projeto.
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_ITEMS 316000//Constantes utilizadas no projeto.
#define MAX_CHAR 20
#define R 256
#define FRANKENSTEIN "84-0.txt"
#define WAR_AND_PEACE "2600-0.txt"
#define F_OUTPUT "frankenstein_ordenado.txt"
#define W_OUTPUT "war_and_peace_ordenado.txt"

void prtInfo(int vectorLength, int swaps, int recursions, float time, FILE* output){//Função prtInfo. Printa informações requisitadas dentro do arquivo apontado por *output.
  fprintf(output,"TAMANHO ENTRADA %d\n",vectorLength);
  fprintf(output,"SWAPS #%d\n",swaps);
  fprintf(output,"RECURSOES #%d\n",recursions);
  fprintf(output,"TEMPO #%f\n",time);
}

void string_toUpper(char *s)//Função string_toUpper. Converte uma string toda para maiúsculo.
{
    int i;
    for (i=0; i<strlen(s); i++){
        s[i]=toupper(s[i]);
    }
}

char** indexWords(FILE* input, char** array, int* nItens){//Função indexWords. Executa a conversão do .txt puro em uma matriz alocada dinâmicamente.
  char line[200];//Variáveis utilizadas na função.
  char *word;
  char c;
  int i;
  char separator[]= {" —’0123456789,.&-‘*%%\?!;/-'@\"$#=~><()][}{:\b\r\a\7\\\"\'“”_"};

  i=0;//Reseta o índice I. Contará o número de palavras que serão ordenadas.
  c=getc(input);//Pula os primeiros 6 bytes do .txt. Marcador do tipo de arquivo.
  c=getc(input);
  c=getc(input);

  while (fgets(line,200,input)){//Lê linha por linha.
    string_toUpper(line);//Converte para maiúsculo.
    word = strtok(line, separator);//Extrai a primeira palavra.

    while (word != NULL){//Enquanto a palavra da linha não for nula.
      if(strlen(word) >= 4){//Filtra segundo especificação.
        strcpy(array[i],word);//Copia para a matriz.
        i++;//Aumenta o índice.
      }
      word = strtok (NULL, separator);//Busca a próxima palavra.
    }
  }

  *nItens = i;//Retorna o número de palavras.
}

void prtArrayCLI(int array[], int vectorLength){//Função prtArrayCLI. Printa a Array informada dentro do console. Utilizado em DEV.
  int i;
  for(i=0;i<vectorLength;i++){//Iteração básica pelo tamanho do Array.
    printf("%d ",array[i]);
  }
}

FILE* initializeFileR(FILE* input, char* name){//Função initializeFileR. Inicializa o ponteiro de leitura FILE. Em caso de erro, informa.
  if((input = fopen(name,"r")) == NULL){//Tenta abrir o arquivo de entrada,
    printf("Erro ao abrir arquivo %s \n",name);//Caso de falha.
  }
  return input;
}

FILE* initializeFileW(FILE* input, char* name){//Função initializeFileW. Inicializa o ponteiro de escrita FILE. Em caso de erro, informa.
  if((input = fopen(name,"w")) == NULL){//Tenta abrir o arquivo de saída,
    printf("Erro ao abrir arquivo %s \n",name);//Caso de falha.
  }
  return input;
}

void MSDRadixSort(char** aux, char** array, int low, int high, int index){//Função MSDRadixSort. Recursiva. Executa o ordenamento de uma matriz de caracteres.
  int i,j,r,p,t;//Índices utilizados.
  p=0;//Zera p.
  if(high <= low){//Se o menor índice ordenado for maior ou igual ao maior índice, para.
  }else{//Se não, executa:
    int count[R+2];

    for(i=0;i<R+2;i++){//Inicializa o vetor de contagem.
      count[i] = 0;
    }

    for(i=low;i <= high;i++){//Executa a contagem.
      p = (int)(array[i][index]);
      p = p + 2;
      count[p]++;
    }

    for(r=0;r<R+1;r++){//Executa acumulação.
      count[r+1] += count[r];
    }

    for(i=low;i <= high;i++){//Distruibui para uma matriz auxiliar.
      p = (int)(array[i][index]) + 1;
      t = count[p]++;
      aux[t] = array[i];
    }

    for(i=low;i <= high;i++){//Retorna.
      array[i] = aux[i-low];
    }
    for(r=0;r<R;r++){//Recursividade.
      MSDRadixSort(aux,array,low+count[r],low-1+count[r+1],index+1);
    }
  }
}

void sortB(char** array, int nItens){//Função sortB. Base para o radix.
  char **aux = malloc(MAX_ITEMS * sizeof(char *));//Define a matri auxiliar.
  int i;

  for(i = 0; i < MAX_ITEMS; i++){
    aux[i] = malloc(MAX_CHAR+1 * sizeof(char));
  }//s [indice] [TAMANHCHAR];
  MSDRadixSort(aux,array,0,nItens,0);//Roda o MSDRadixSort.
}

int countRep(char** array, int index,char* word){//Função countRep. Recursiva. Conta as repetições da string word no array.
  if((index < MAX_ITEMS)){//Se índice for maior que o máximo, para.
    if((strcmp(array[index],""))){//Se a palavra comparada não for nula, executa:
      if(!(strcmp(array[index],word))){//Se a palavra for igual, executa:
        return 1 + countRep(array,index+1,word);//Retorna 1 repetição + recursividade.
      }else{//Se não, retorna 0. Encerra recursividade.
        return 0;
      }
    }else{//Caso vazio, retorna -1
      return -1;
    }
  }
}

void countArray(char** array,FILE* output1,int nItems){//Função countArray. Conta as repetições de palavras num array ordenado.
  int totalRep = 0;//Zera o contador.
  int i=1;//Começa do primeiro índice.
  while(i<nItems){//Enquanto não terminar de passar por todas as palavras.
    totalRep = countRep(array,i,array[i]);//Conta as repetições.
    fprintf(output1,"%s %d\n",array[i],totalRep);//Salva a informação no txt saida.
    if(totalRep>0){//Caso o totalRep for maior que 0 (caso normal),executa.
      i = i + totalRep;
    }else{//Caso vazio, retorna erro e encerra a contagem.
      i = nItems;
    }
    totalRep = 0;//Zera a repetição, recorrência.
  }
}

int main(){//Função main. Executa os testes requisitados.
  setlocale(LC_ALL,"");//Ajusta as configurações de print para console. Usado em DEV.
  int nItems;//Quantifica quantos itens existem no array.
  int i;//Índices de uso geral.
  FILE* input;//Ponteiros para os arquivos.
  FILE* output;
  char **array = malloc(MAX_ITEMS * sizeof(char *));  

  for(i = 0; i < MAX_ITEMS; i++){
    array[i] = malloc(MAX_CHAR+1 * sizeof(char));
  }//s [indice] [TAMANHCHAR];

  input = initializeFileR(input,WAR_AND_PEACE);//Inicializa os arquivos .txt

  indexWords(input, array, &nItems);

  sortB(array,nItems);
  output = initializeFileW(output,W_OUTPUT);
  countArray(array,output,nItems);

  fclose(input);
  fclose(output);//Fecha os ponteiros de leitura e escrita.
  return 0;
}
