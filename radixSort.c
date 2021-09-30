// Trabalho Laboratório 3 - Classificação e Pesquisa de Dados - Gabriel Castelo Branco Gomes e Tiago Torres Schmidt.
#include <stdio.h>//Bibliotecas utilizadas no projeto.
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_ITEMS 400000//Constantes utilizadas no projeto.
#define MAX_CHAR 20
#define R 256
#define DEFAULT_INPUT "84-0.txt"
#define DEFAULT_OUTPUT1 "fonte.txt"
#define DEFAULT_OUTPUT2 "fonteFINAL.txt"

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

char** indexWords(FILE* input, char** array, int* nItens){
  char line[200];
  char *word;
  char c;
  int i;
  char separator[]= {" —’0123456789,.&-‘*%%\?!;/-'@\"$#=~><()][}{:\b\r\a\7\\\"\'“”_"};

  i=0;
  c=getc(input);
  c=getc(input);
  c=getc(input);

  while (fgets(line,200,input)){
    string_toLower(line);
    word = strtok(line, separator); //pega a 1a palavra do tweet

    while (word != NULL){
      if(strlen(word) >= 4){
        //printf("%d %s\n",strlen(word),word);
        strcpy(array[i],word);
        i++;
      }
      word = strtok (NULL, separator); //pega a pr�xima palavra do tweet
    }
  }

  *nItens = i;
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

void MSDRadixSort(char** aux, char** array, int low, int high, int index){
  int i,j,r,p,t;

  p=0;
  if(high <= low){
  }else{
    int count[R+2];

    for(i=0;i<R+2;i++){
      count[i] = 0;
    }

    for(i=low;i <= high;i++){
      p = (int)(array[i][index]);
      p = p + 2;
      count[p]++;
    }

    for(r=0;r<R+1;r++){
      count[r+1] += count[r];
    }

    for(i=low;i <= high;i++){
      p = (int)(array[i][index]) + 1;
      t = count[p]++;
      aux[t] = array[i];
    }

    for(i=low;i <= high;i++){
      array[i] = aux[i-low];
    }

    for(r=0;r<R;r++){
      MSDRadixSort(aux,array,low+count[r],low-1+count[r+1],index+1);
    }
  }
}

void sortB(char** array, int nItens){
  char **aux = malloc(MAX_ITEMS * sizeof(char *));
  int i;

  for(i = 0; i < MAX_ITEMS; i++){
    aux[i] = malloc(MAX_CHAR+1 * sizeof(char));
  }//s [indice] [TAMANHCHAR];

  MSDRadixSort(aux,array,0,nItens,0);
}

int main(){//Função main. Executa os testes requisitados.
  setlocale(LC_ALL,"");//Ajusta as configurações de print para console. Usado em DEV.
  int nItems;//Quantifica quantos itens existem no array.
  int i,j,k,t, totalRep;//Índices de uso geral.
  FILE* input;//Ponteiros para os arquivos.
  FILE* output1;
  char **array = malloc(MAX_ITEMS * sizeof(char *));
  char *word;
  char prevWord[MAX_CHAR];
  char line[30];
  char separator[]= {" —’0123456789,.&-‘*%%\?!;/-'@\"$#=~><()][}{:\b\r\a\7\\\"\'“”_"};

  for(i = 0; i < MAX_ITEMS; i++){
    array[i] = malloc(MAX_CHAR+1 * sizeof(char));
  }//s [indice] [TAMANHCHAR];

  input = initializeFileR(input,DEFAULT_INPUT);//Inicializa os arquivos .txt
  output1 = initializeFileW(output1,DEFAULT_OUTPUT1);

  indexWords(input, array, &nItems);

  sortB(array,nItems);

  for(j=1; j < nItems+1; j++){
    fprintf(output1,"%s\n",array[j]);
  }
  fclose(input);
  fclose(output1);

  input = initializeFileR(input,DEFAULT_OUTPUT1);//Inicializa os arquivos .txt
  output1 = initializeFileW(output1,DEFAULT_OUTPUT2);

  strcpy(prevWord,"--%%");

  totalRep = 1;

  while (fgets(line,MAX_CHAR+5,input)){
    word = strtok(line, separator); //pega a 1a palavra do tweet
    if(word == prevWord){
      totalRep++;
      fseek(output1,-(sizeof("%d\n")), SEEK_CUR );
      fprintf(output1,"%d\n",array[j],totalRep);
    }else{
      totalRep = 1;
      fprintf(output1,"%s #%d\n",word,totalRep);
      strcpy(prevWord,word);
    }
  }

  fclose(output1);//Fecha os ponteiros de leitura e escrita.
  fclose(input);
  return 0;
}
