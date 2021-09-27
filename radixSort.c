// Trabalho Laboratório 3 - Classificação e Pesquisa de Dados - Gabriel Castelo Branco Gomes e Tiago Torres Schmidt.
#include <stdio.h>//Bibliotecas utilizadas no projeto.
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "lista.h"

#define MAX_ITEMS 60000//Constantes utilizadas no projeto.
#define MAX_CHAR 20
#define DEFAULT_INPUT "84-0.txt"
#define DEFAULT_OUTPUT1 "fonte.txt"
#define DEFAULT_OUTPUT2 "listaLinear.txt"

void prtInfo(int vectorLength, int swaps, int recursions, float time, FILE* output){//Função prtInfo. Printa informações requisitadas dentro do arquivo apontado por *output.
  fprintf(output,"TAMANHO ENTRADA %d\n",vectorLength);
  fprintf(output,"SWAPS #%d\n",swaps);
  fprintf(output,"RECURSOES #%d\n",recursions);
  fprintf(output,"TEMPO #%f\n",time);
}

void string_toLower (char *s)
{
    int i;
    for (i=0; i<strlen(s); i++){
        s[i]=tolower(s[i]);
    }
}

void indexWords(FILE* input, FILE* output1, FILE* output2, char array[MAX_CHAR][MAX_ITEMS]){
  char line[200];
  char *word;
  char separator[]= {" —’0123456789,.&*%%\?!;/-'@\"$#=~><()][}{:\b\r\a\7\\\"\'“”_"};
  NodeItem* list;

  list = Inicializa_Lista();

  while (fgets(line,200,input)){
    string_toLower(line);
    word = strtok(line, separator); //pega a 1a palavra do tweet

    while (word != NULL){
      if(strlen(word) > 4){
        //printf("%d %s\n",strlen(word),word);
        fprintf(output1,"%s ",word);
        list = insertItem(list,word);
      }
      word = strtok (NULL, separator); //pega a pr�xima palavra do tweet
    }
  }

  imprime(list,list,output2);
	//lê o arquivo 'entrada' de tweets e retorna a árvore montada
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

int main(){//Função main. Executa os testes requisitados.
  setlocale(LC_ALL,"");//Ajusta as configurações de print para console. Usado em DEV.
  char buffer[MAX_CHAR][MAX_ITEMS];//Variáveis utilizadas nos testes.
  int nItems;//Quantifica quantos itens existem no array.
  int i,j,k;//Índices de uso geral.
  FILE* input;//Ponteiros para os arquivos.
  FILE* output1,*output2;

  input = initializeFileR(input,DEFAULT_INPUT);//Inicializa os arquivos .txt
  output1 = initializeFileW(output1,DEFAULT_OUTPUT1);
  output2 = initializeFileW(output2,DEFAULT_OUTPUT2);

  indexWords(input, output1, output2, buffer);
  /*
  while(feof(input)==0){//Enquanto não encontra o fim do arquivo de entrada.
    fscanf(input,"%d ",&nItems);//Resgata o número de itens no array.
    for(i=0;i<nItems;i++){//Para cada item no array, armazena um número lido.
      fscanf(input,"%d ",&buffer[i]);//Executa a leitura do .txt de entrada.
    }

    for(j=0;j<4;j++){//Para cada array lido do .txt, executa as quatro variações do QuickSort.
      for(k=0; k < nItems; k++) {//Copia o buffer para bufferClone.
        bufferClone[k] = buffer[k];
      }
      swaps = 0;//Reseta variáveis de contagem.
      recursions = 0;

      switch(j){//Varia entres os tipos de QuickSort..
        case 0:
          t = clock();//Marca o início.
          quickSortLomutoMedian(bufferClone,0,nItems-1,&swaps,&recursions);//Executa o ordenamento.
          t = clock() - t;//Extrai o tempo total
          cTime = ((double)t)/CLOCKS_PER_SEC;//Cálculo do tempo decorrido.
          prtInfo(nItems,swaps,recursions,cTime,output2);//Printa as informações
          break;
        case 1:
          t = clock();//Marca o início
          quickSortLomutoRandom(bufferClone,0,nItems-1,&swaps,&recursions);//Executa o ordenamento.
          t = clock() - t;//Extrai o tempo total
          cTime = ((double)t)/CLOCKS_PER_SEC;//Cálculo do tempo decorrido.
          prtInfo(nItems,swaps,recursions,cTime,output4);//Printa as informações
          break;
        case 2:
          t = clock();//Marca o início
          quickSortHoareMedian(bufferClone,0,nItems-1,&swaps,&recursions);//Executa o ordenamento.
          t = clock() - t;//Extrai o tempo total
          cTime = ((double)t)/CLOCKS_PER_SEC;//Cálculo do tempo decorrido.
          prtInfo(nItems,swaps,recursions,cTime,output1);//Printa as informações
          break;
        case 3:
          t = clock();//Marca o início
          quickSortHoareRandom(bufferClone,0,nItems-1,&swaps,&recursions);//Executa o ordenamento.
          t = clock() - t;//Extrai o tempo total
          cTime = ((double)t)/CLOCKS_PER_SEC;//Cálculo do tempo decorrido.
          prtInfo(nItems,swaps,recursions,cTime,output3);//Printa as informações
          break;
      }
    }
  }*/
  fclose(output1);//Fecha os ponteiros de leitura e escrita.
  fclose(output2);
  fclose(input);
  return 0;
}
