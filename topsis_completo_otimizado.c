#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<float.h>
#include<math.h>

#define lin 209555
#define col 4

//Para compilar gcc topsis_completo_otimizado.c -o topsis_completo_otimizado -lm

char** str_split(char* a_str)
{

    char ** result = NULL;
    char *tmp = NULL;
    int length = 0;

    result = (char**)malloc(sizeof(char*));

    tmp = strtok(a_str, ",");
    while(tmp != NULL)
    {
        result[length] = tmp;
        length++;
        tmp = strtok(NULL, ",");
        result = (char**)realloc(result, (length + 1) * sizeof(char*));
    }
    return result;
}

char* read_line(FILE * f)
{
    char c;
    char *retval = NULL;
    int i = 0;

    while(!feof(f) && c != '\n')
    {
        c = fgetc(f);
        retval = (char*)realloc(retval, (i+1) * sizeof(char));
        retval[i++] = c;
    }
    retval = (char*)realloc(retval, (i+1) * sizeof(char));
    retval[i] = '\0';
    return retval;
}


//função do qsort para ordenação
int ordena(const void * a,const void * b){
	if(*(int*)a == *(int*)b)
	    return 0; //iguais
	else
	    if (*(int*)a > *(int*)b)
	        return -1; // vem antes
	    else
	        return 1; // vem depois
}

// impressões de dados
void imprimeVetorMesclado1(float vetorMaior2[lin]){
   printf("\n 2 primeiros do vetor maior + 2 ultimos do vetor maior \n\n");
   for(int i=0;i<lin;i++){
	     printf("[%f]", vetorMaior2[i]);
   }
}

void imprimeVetorMesclado2(float vetorMenor2[lin]){
   printf("\n 2 primeiros do vetor menor + 2 ultimos do vetor maior \n\n");
   for(int i=0;i<lin;i++){
	     printf("[%f]", vetorMenor2[i]);
   }
}

void imprimeSoma(float soma[lin]){
   int i;
   printf("\n Passo 5 vetor Soma Ideal = Soma de cada coluna da matriz ideal \n\n");
   for(i=0; i<lin; i++){
	     printf("[%f]\n", soma[i]);
   }
}

void imprimeSomaIdeal2(float somaIdeal2[col]){
   int i;
   printf("\n Passo 5 vetor Soma Ideal = Soma de cada coluna da matriz ideal \n\n");
   for(i=0; i<col; i++){
	     printf("[%f]\n", somaIdeal2[i]);
   }
}

void imprimeSomaNideal2(float somaNideal2[col]){
   int i;
   printf("\n\n Passo 5 vetor Soma Nao Ideal = Soma de cada coluna da matriz nao ideal \n\n");
   for(i=0;i<col;i++){
	     printf("[%f]\n", somaNideal2[i]);
   }
}

void imprimeSomaNideal(float somaNideal[col]){
   int i;
   printf("\n\n Passo 5 vetor Soma Nao Ideal = Soma de cada coluna da matriz nao ideal \n\n");
   for(i=0;i<col;i++){
	     printf("[%f]\n", somaNideal[i]);
   }
}

void imprimeVetorMaior(float vetorMaior[col]){
   int i;
   printf("\n Passo 3 - Vetor com os maiores valores de cada linha da matriz Norm com Pesos \n\n");
   for(i=0;i<lin;i++){
	     printf("[%f]\n", vetorMaior[i]);
   }
}

void imprimeVetorMenor(float vetorMenor[lin]){
   int i;
   printf("\n Passo 3 - Vetor com os menores valores de cada linha da matriz Norm com Pesos \n\n");
   for(i=0;i<lin;i++){
	   printf("[%f]\n", vetorMenor[i]);
    }
}

void imprimeVetorFinal(float vetorFinal[col]){
   int i;
   printf("\n vetor Final \n\n");
   for(i=0;i<col;i++){
	  printf("[%f]\n", vetorFinal[i]);
	  }
}

void imprimematrizMultiplicada(float matrizMultiplicada[lin][col]){
   int i,j;
   printf("\n Passo 2 - Matriz Normalizada ja * os Pesos \n\n");
   for(i=0;i<lin;i++){
      for(j=0;j<col;j++){
	     printf("[%f]", matrizMultiplicada[i][j]);
	  }
      printf("\n");
   }
}

void imprimeMatrizNormalizada(float matrizDadosNormalizada[lin][col]){
   int i,j;
   printf("\n Passo 1 - Matriz Normalizada\n\n");
   for(i=0;i<lin;i++){
      for(j=0;j<col;j++){
	     printf("[%f]", matrizDadosNormalizada[i][j]);
	  }
      printf("\n");
   }
}

void imprimeMatrizDados(float matrizDados[lin][col]){
   int i,j;
   printf("\n Passo 0 - Matriz Dados Orgininal \n\n");
   for(i=0;i<lin;i++){
      for(j=0;j<col;j++){
	     printf("[%f]", matrizDados[i][j]);
	  }
      printf("\n");
   }
}
void imprimeMatrizSolucaoIdeal(float matrizSolucaoIdeal[lin][col]){
   int i,j;
   printf("\n Passo 4 - Matriz solucao Ideal \n\n");
   for(i=0;i<lin;i++){
      for(j=0;j<col;j++){
	     printf("[%f]", matrizSolucaoIdeal[i][j]);
	  }
      printf("\n");
   }
}
void imprimeMatrizSolucaoNideal(float matrizSolucaoNideal[lin][col]){
   int i,j;
   printf("\n Passo 4 - Matriz solucao Não Ideal \n\n");
   for(i=0;i<lin;i++){
      for(j=0;j<col;j++){
	     printf("[%f]", matrizSolucaoNideal[i][j]);
	  }
      printf("\n");
   }
}

//Operações matemáticas *******************
void normalizamatriz(float matrizDadosNormalizada[lin][col], float matrizDados[lin][col] ){
   int i,j;
   for(i=0;i<lin;i++){
      for(j=0;j<col;j++){
		  matrizDadosNormalizada[i][j] = pow(matrizDados[i][j], 2);
      }
    }
}

void somatorio(float soma[lin], float matrizDadosNormalizada[lin][col]){
   int i,j;
   for(i=0;i<lin;i++){
      for(j=0;j<col;j++){
		  soma[i] = ((soma[i]) + matrizDadosNormalizada[i][j]);
      }
   }
}

void raizquadradadosomatorio(float soma[lin]){
    int i;
    for(i=0;i<lin;i++){
	   soma[i] = sqrtf(soma[i]);
	}
}

void equivalenciamatriz(float matrizDadosNormalizada[lin][col], float matrizDados[lin][col], float soma[lin]){
    int i,j;
    for(i=0;i<lin;i++){
       for(j=0;j<col;j++){
		  matrizDadosNormalizada[i][j] = (matrizDados[i][j] / (soma[i]));
          }
     }
}

void multiplicacaopesos(float matrizMultiplicada[lin][col], float matrizDadosNormalizada[lin][col], float vetorPesos[col]){
    int i,j;
    for(i=0; i<lin; i++){
       // printf("%d\n", i);
		for(j=0; j<col; j++){
		/*	printf("%d\n", j);
            printf("[%f]\n", matrizDadosNormalizada[i][j]);
            printf("[%f]\n", vetorPesos[j]);*/
            //matrizMultiplicada[i][j] = matrizDadosNormalizada[i][j] * vetorPesos[j];            
        }
	}
}

void CalculavetorMaior(float vetorMaior[col] , float  matrizMultiplicada[lin][col])
{
    for(int j=0; j<col; j++)
    {
        float maior = 0;
        for(int i=0; i<lin; i++)
        {
            if(matrizMultiplicada[i][j]>maior)   //este trecho recebe o maior valor da linha da matriz
            {
                maior=matrizMultiplicada[i][j];  //e armazena este valor em um vetor
            }
        }
        //printf("%f\n", maior);
        vetorMaior[j]=maior;
    }
}

void CalculavetorMenor(float vetorMenor[col] , float  matrizMultiplicada[lin][col])
{
    for(int j=0; j<col; j++)
    {
        float menor = FLT_MAX;
        for(int i=0; i<lin; i++)
        {
            if(menor > matrizMultiplicada[i][j])
            {
                menor=matrizMultiplicada[i][j];
                //printf("%f\n", menor);
            }
        }
        //printf("%lf", menor);
        vetorMenor[j]=menor;
    }
}


/*
void vetormaiormenor(float matrizDadosNormalizadaP[lin][col],  float vetorMaior[lin], float vetorMenor[lin], float aux1[lin]){
    int i,j;
	float maior=matrizDadosNormalizadaP[0][0];
	//float menor=matrizDadosNormalizadaP[0][0];
	for(i=0;i<lin;i++){
		for(j=0;j<col;j++){
			if(matrizDadosNormalizadaP[i][j] > maior){
				maior = matrizDadosNormalizadaP[i][j];
			}
			aux1[i] = matrizDadosNormalizadaP[i][j];
			if(j==0){
				vetorMenor[i] = aux1[i];
			}
			if (i==lin-1){
				for (int i2 = 0; i2 < lin; i2++) {
						if (vetorMenor[i2] > aux1[i2]){
							vetorMenor[i2] = aux1[i2];
						}
				}
			}

		}
		vetorMaior[i]=maior;
        maior=0;
	}
}
*/

void encontramaiorposicao(float vetorMaior[lin], float vetorMenor[lin], float vetorMaior2[lin]){
    int i;
    for(i=0;i<lin/2;i++){
	    vetorMaior2[i] = vetorMaior[i];
	}
	for(i=(lin/2);i<lin;i++){
	    vetorMaior2[i] = vetorMenor[i];
	}
}

void encontramenorposicao(float vetorMaior[lin], float vetorMenor[lin], float vetorMenor2[lin]){
    int i;
    for(i=0;i<lin/2;i++){
	    vetorMenor2[i] = vetorMenor[i];
	}
	for(i=(lin/2);i<lin;i++){
	    vetorMenor2[i] = vetorMaior[i];
	}
}

void solucaoideal(float matrizSolucaoIdeal[lin][col], float matrizMultiplicada[lin][col], float vetorMaior2[lin]){
    int i,j;
    for(i=0;i<lin;i++){
		  for(j=0;j<col;j++){
			 matrizSolucaoIdeal[i][j] = (matrizMultiplicada[i][j] - vetorMaior2[i]);
			 matrizSolucaoIdeal[i][j] = pow(matrizSolucaoIdeal[i][j], 2.0);
		  }
	}
}

void solucaonideal(float matrizSolucaoNideal[lin][col], float matrizMultiplicada[lin][col], float vetorMenor2[lin]){
    int i,j;
    for(i=0;i<lin;i++){
		  for(j=0;j<col;j++){
			 matrizSolucaoNideal[i][j] = (matrizMultiplicada[i][j] - vetorMenor2[i]);
			 matrizSolucaoNideal[i][j] = powf(matrizSolucaoNideal[i][j], 2.0);
		  }
	  }
}

void somaideal(float somaIdeal[col], float somaIdeal2[col], float matrizSolucaoIdeal[lin][col]){
    int i,j;
    for(i=0;i<lin;i++){
		 for(j=0;j<col;j++){
			somaIdeal[j]  += matrizSolucaoIdeal[i][j];
			somaIdeal2[j]  = sqrtf(somaIdeal[j]);
         }
	 }
}

void somanideal(float somaNideal[col], float somaNideal2[col], float matrizSolucaoNideal[lin][col]){
    int i,j;
    for(i=0;i<lin;i++){
		 for(j=0;j<col;j++){
			somaNideal[j]  += matrizSolucaoNideal[i][j];
			somaNideal2[j]  = sqrtf(somaNideal[j]);
		 }
	 }
}

void calculofinal(float vetorFinal[col], float somaNideal2[col], float somaIdeal2[col]){
  for(int i=0;i<col;i++){
	    vetorFinal[i] = (somaNideal2[i] / ((somaIdeal2[i]+somaNideal2[i])));
	}
}

int main (void ){
    //int i, j;

    //ponteiro para arquivo
    FILE *f;
    
        //função para realizar a abertura do arquivo
        f = fopen("./day_city.csv","r");
    
        float matrizDados[lin][col];
    
        // if de controle para ver se o arquivo esta disponivel, caso não fecha
        if (f == NULL)
        {
            printf("Erro na Abertura do Arquivo\n");
            system("pause");
            exit (1);
        }
        else
        {
            int index = 0;
            //read_line(f);
            //laço para fazer a leitura do arquivo
            while(!feof(f))
            {
                char **tokens = NULL;
                char *s = read_line(f);
    
                if(strlen(s) > 1)
                {
                    tokens = str_split(s);
                    matrizDados[index][0] = atof(tokens[0]); //-> sensor.temp_day
                    matrizDados[index][1] = atof(tokens[1]); //-> sensor.humidity
                    matrizDados[index][2] = atof(tokens[2]); //-> sensor.clouds
                    matrizDados[index][3] = atof(tokens[3]); //-> sensor.speed
    
                    //Comenta dps os printf quando for testar o código de fato
                    //printf("temp_day = %lf; ", matrizDados[index][1]);
                    //printf("humidity = %lf; ", matrizDados[index][2]);
                    //printf("clouds = %lf; ", matrizDados[index][3]);
                    //printf("speed = %lf\n", matrizDados[index][4]);
                }
                index++;
            }
        }
        //printf("Finalizada Matriz\n");
        //return 0;

   //Declaração das variaveis   
   float matrizDadosNormalizada[lin][col];
   float matrizMultiplicada[lin][col];
   float vetorPesos[col]   = {0.162, 0.162, 0.162, 0.162};
   float soma[lin];
  
   float matrizSolucaoIdeal[lin][col];
   float matrizSolucaoNideal[lin][col];
   float somaIdeal[col];
   float somaIdeal2[col];
   float somaNideal[col];
   float somaNideal2[col];
   float vetorMaior[col];
   float vetorMenor[col];
   //float aux1[lin];
   float vetorFinal[col];
   float vetorMaior2[lin];
   float vetorMenor2[lin];
   
    //Aki começa o inicio da normalização da matriz utilizando a formula do TOPSIS *********************************************************************
    //Cada operação da formula foi feita de operações separadas
    //Neste primeiro ponto eleva-se todos os elementos da matriz ao quadrado
    normalizamatriz(matrizDadosNormalizada, matrizDados);

    //Neste ponto calcula-se o somatório de cada linha e armeza-se em uma vetor de soma
    somatorio(soma, matrizDadosNormalizada);

    //Neste ponto calcula-se a raiz quadrada do somatório de cada linha
    raizquadradadosomatorio(soma);

    //Neste ponto faz-se a operação final, onde a matriz normalizada equivale a matriz original / pela raiz do somatório da linha
    equivalenciamatriz(matrizDadosNormalizada, matrizDados, soma);

    // Faz a multiplicação da matriz normalizada pelo vetor de pesos indicado pelo especialista
    //multiplicacaopesos(matrizMultiplicada, matrizDadosNormalizada, vetorPesos);

	/*/ Encontra o maior valor de cada linha e armazena em um vetor -> vetorMaior
    //vetormaiormenor(matrizDadosNormalizadaP, vetorMaior, vetorMenor, aux1);
    CalculavetorMaior(vetorMaior, matrizMultiplicada);
    CalculavetorMenor(vetorMenor, matrizMultiplicada);

	//aqui eu pego as 2 primeiras posições do vetor maior e as 2 ultimas do vetor menor
    encontramaiorposicao(vetorMaior, vetorMenor, vetorMaior2);

	//aqui eu pego as 2 primeiras posições do vetor menor e as 2 ultimas do vetor maior
    encontramenorposicao(vetorMaior, vetorMenor, vetorMenor2);

	//passo 4 separação da solução ideal
	solucaoideal(matrizSolucaoIdeal, matrizMultiplicada, vetorMaior2);

	//Passo 4 separação da solucao não ideal
	solucaonideal(matrizSolucaoNideal, matrizMultiplicada, vetorMenor2);

	//Vetor Soma das Colunas Solução Ideal
    somaideal(somaIdeal, somaIdeal2, matrizSolucaoIdeal);

	//Vetor Soma das Colunas da Solução Não Ideal
    somanideal(somaNideal, somaNideal2, matrizSolucaoNideal);

    //calculo do vetor final com a classificao
    //calculo o vetor final utilizando o somaideal e não ideal
    calculofinal(vetorFinal, somaNideal2, somaIdeal2);

    //Impressao do calculo dos resultados
    imprimeMatrizDados(matrizDados);

	imprimeMatrizNormalizada(matrizDadosNormalizada);

    imprimematrizMultiplicada(matrizMultiplicada);

	imprimeVetorMaior(vetorMaior);

	imprimeVetorMenor(vetorMenor);

	imprimeMatrizSolucaoIdeal(matrizSolucaoIdeal);

    imprimeMatrizSolucaoNideal(matrizSolucaoNideal);

    imprimeSomaIdeal2(somaIdeal2);
    
    imprimeSomaNideal2(somaNideal2);

    qsort(vetorFinal,lin,sizeof(float), ordena);

    imprimeVetorFinal(vetorFinal); 
    */
    return(0); 
}
