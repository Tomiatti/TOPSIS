#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<float.h>
#include<limits.h>
#define lin 4
#define col 4

#define NUM_THREADS 8

//Para compilar gcc topsis_openmp.c -fopenmp -o topsis_openmp -lm

//função do qsort para ordenação
int Ordena(const void * a,const void * b){
	if(*(int*)a == *(int*)b)
	    return 0; //iguais
	else
	    if (*(int*)a > *(int*)b)
	        return -1; // vem antes
	    else
	        return 1; // vem depois
}

void ImprimeVetorMaior(float VetorMaior[lin]){
   int i;
   printf("\n\n Vetor maior \n\n");
   for(i=0;i<lin;i++){
	     printf("[%.3f]\n", VetorMaior[i]);
   }
}

void ImprimeVetorMenor(float VetorMenor[lin]){
   int i;
   printf("\n\n Vetor menor \n\n");
   for(i=0;i<lin;i++){
	   printf("[%.3f]\n", VetorMenor[i]);
    }
}

void ImprimeMatrizDados(float MatrizDados[lin][col]){
   int i,j;
   printf("\n\n Matriz Dados \n\n");
   for(i=0; i<lin; i++)
    {
        for(j=0; j<col; j++)
        {
             printf("Elemento[%d]= %.3f \n", i,  MatrizDados[i][j]);
        }
   }
}

void ImprimeMatrizNormalizada(float MatrizDadosNormalizada[lin][col]){
   int i,j;
   printf("\n\n Matriz Normalizada \n\n");
   for(i=0;i<lin;i++){
      for(j=0;j<col;j++){
	     printf("[%.3f]", MatrizDadosNormalizada[i][j]);
	  }
      printf("\n");
   }
}

void ImprimeMatrizSolucaoIdeal(float MatSolucaoIdealPositiva[lin][col]){
   int i,j;
   printf("\n\n");
		for(int i=0; i<lin; i++){
			for(int j=0; j<col; j++){
				printf("[%.3f]", MatSolucaoIdealPositiva[i][j]);
			}
			printf("\n");
        }
}

void ImprimeVetorSolucaoIdeal(float VetorSolucaoPositiva[col]){
   int i,j;
    printf("Solucao Positiva\n\n");
		for(int i=0; i<col; i++){
			 printf("[%.3f]", VetorSolucaoPositiva[i]);
		}
        printf("\n");
}

void ImprimeMatrizSolucaoNIdeal(float MatSolucaoIdealNegativa[lin][col]){
   int i,j;
printf("\n\n");
		for(int i=0; i<lin; i++){
			for(int j=0; j<col; j++){
				printf("[%.3f]", MatSolucaoIdealNegativa[i][j]);
			}
		printf("\n");
    }
}

void ImprimeVetorSolucaoNIdeal(float VetorSolucaoNegativa[col]){
   int i,j;
		printf("Solucao Negativa\n\n");
		for(int i=0; i<col; i++){
			 printf("[%.3f]", VetorSolucaoNegativa[i]);
		}
		printf("\n\n");
}
    
void ImprimeProximidadeRelativa(float ProximidadeRelativa[col]){    
    printf("\n");
		for(int i=0; i<col; i++){
			 printf("Elemento[%d] = %.3f \n", i, ProximidadeRelativa[i]);
		}
		printf("\n");
}

//Operações matemáticas *******************
void NormalizaMatriz(float MatrizDadosNormalizada[lin][col], float MatrizDados[lin][col], float VetorPesos[col]){
   int i,j;
   float raiz = 0;
   float soma = 0;
   for(i=0;i<lin;i++){
	   soma = 0;
      for(j=0;j<col;j++){
		  MatrizDadosNormalizada[i][j] = pow(MatrizDados[i][j], 2);
		  soma += (MatrizDadosNormalizada[i][j]);
      }
      raiz = sqrtf(soma);
      //printf("soma = %.3f \n", soma);
      //printf("raiz = %.3f \n", raiz);
      for(j=0;j<col;j++){
		  MatrizDadosNormalizada[i][j] = MatrizDados[i][j] / raiz;
		  //printf("%.2f\n", MatrizDadosNormalizada[i][j]);
      }
   }
   //Multiplica a matriz ja normalizada pelo vetor de pesos
   for(i=0; i<lin; i++){
		for(j=0;j<col;j++){
			MatrizDadosNormalizada[i][j] = MatrizDadosNormalizada[i][j] * VetorPesos[i];
        }
	}
    
}

/*void MultiplicacaoPesos(float MatrizDadosNormalizada[lin][col], float VetorPesos[col]){
    int i,j;
    for(i=0; i<lin; i++){
		for(j=0;j<col;j++){
			MatrizDadosNormalizada[i][j] = MatrizDadosNormalizada[i][j] * VetorPesos[i];
        }
	}
}*/



void CalculaVetorMaior(float VetorMaior[lin], float  MatrizDadosNormalizada[lin][col]){
   for(int i=0; i<lin; i++){
      float Maior = 0;
      for(int j=0; j<col; j++){
         if(MatrizDadosNormalizada[i][j] > Maior){
            Maior = MatrizDadosNormalizada[i][j];  //e armazena este valor em um vetor
         }
      }
      VetorMaior[i] = Maior;
     //Maior=0;
    }
}

void CalculaVetorMenor(float VetorMenor[lin], float  MatrizDadosNormalizada[lin][col]){
    for(int i=0; i<lin; i++){
      float Menor = FLT_MAX;
      for(int j=0; j<col; j++){
         if(Menor > MatrizDadosNormalizada[i][j]){
             Menor = MatrizDadosNormalizada[i][j];
         }
      }
      VetorMenor[i] = Menor;
     // Menor=0;
    }
}


void SolucaoIdealPositiva(float MatrizDadosNormalizada[lin][col], float VetorMaior[lin], float MatSolucaoIdealPositiva[lin][col], float VetorSolucaoPositiva[col]){
    int i,j;   
    // Calcula o Vetor de Solucão Positiva Ideal___________________________________________________________________________________
    for(i=0;i<lin;i++){
		  for(j=0;j<col;j++){
			 MatSolucaoIdealPositiva[i][j] = MatrizDadosNormalizada[i][j] - VetorMaior[i];
			 MatSolucaoIdealPositiva[i][j] = pow(MatSolucaoIdealPositiva[i][j], 2.0);
			 VetorSolucaoPositiva[j] += MatSolucaoIdealPositiva[i][j];
		  }		   	
	}
	for(i=0; i<col; i++){
		VetorSolucaoPositiva[i] = sqrtf(VetorSolucaoPositiva[i]); 	
	} //fim do trecho ________________________________________________________________________________________________________________ 

}

void SolucaoIdealNegativa(float MatrizDadosNormalizada[lin][col], float VetorMenor[lin], float MatSolucaoIdealNegativa[lin][col], float VetorSolucaoNegativa[col]){
    int i,j;
    // Calcula o Vetor de Solucão Negativa Ideal____________________________________________________________________________________
    for(i=0;i<lin;i++){
		  for(j=0;j<col;j++){
			 MatSolucaoIdealNegativa[i][j] = MatrizDadosNormalizada[i][j] - VetorMenor[i];
			 MatSolucaoIdealNegativa[i][j] = pow(MatSolucaoIdealNegativa[i][j], 2.0);
			 VetorSolucaoNegativa[j] += MatSolucaoIdealNegativa[i][j];
		  }		   	
	}
	for(i=0; i<col; i++){
		VetorSolucaoNegativa[i] = sqrtf(VetorSolucaoNegativa[i]); 	
	} //fim do trecho ________________________________________________________________________________________________________________
}

void FunProximidadeRelativa(float ProximidadeRelativa[col] , float VetorSolucaoNegativa[col], float VetorSolucaoPositiva[col]){

    for(int i = 0; i < col; i++){
			ProximidadeRelativa[i] = (VetorSolucaoNegativa[i]/(VetorSolucaoPositiva[i] - VetorSolucaoNegativa[i]));
    }
}
int main (void ){
   int i,j;
   float MatrizDadosNormalizada[lin][col];
   float VetorMenor[lin];
   float VetorMaior[lin];
   float VetorPesos[col]  = {1,2 ,3 ,4};

   float MatSolucaoIdealPositiva[lin][col];
   float MatSolucaoIdealNegativa[lin][col];
   float VetorSolucaoPositiva[col] = { };
   float VetorSolucaoNegativa[col] = { };
   float ProximidadeRelativa[col] = { };

   float MatrizDados[lin][col] ={{1,2,3,4},
                                {5,6,7,8},
                                {9,10,11,12},
                                {13,14,15,16}};

    omp_set_num_threads(NUM_THREADS);    
    int chunk = lin*col/NUM_THREADS;

    //NormalizaMatriz(MatrizDadosNormalizada, MatrizDados,VetorPesos);
    
	//CalculaVetorMaior(VetorMaior, MatrizDadosNormalizada);
    //CalculaVetorMenor(VetorMenor, MatrizDadosNormalizada);
    
    //ImprimeMatrizDados(MatrizDados);
	
   // ImprimeMatrizNormalizada(MatrizDadosNormalizada);

   float raiz = 0;
   float soma = 0;

   for(i=0;i<lin;i++){
	   soma = 0;
      for(j=0;j<col;j++){
		  MatrizDadosNormalizada[i][j] = pow(MatrizDados[i][j], 2);
		  soma += (MatrizDadosNormalizada[i][j]);
      }
      raiz = sqrtf(soma);
      //printf("soma = %.3f \n", soma);
      //printf("raiz = %.3f \n", raiz);
      for(j=0;j<col;j++){
		  MatrizDadosNormalizada[i][j] = MatrizDados[i][j] / raiz;
		  //printf("%.2f\n", MatrizDadosNormalizada[i][j]);
      }
   }
   //Multiplica a matriz ja normalizada pelo vetor de pesos
   for(i=0; i<lin; i++){
		for(j=0;j<col;j++){
			MatrizDadosNormalizada[i][j] = MatrizDadosNormalizada[i][j] * VetorPesos[i];
        }
    }
    

    ImprimeMatrizNormalizada(MatrizDadosNormalizada);

    #pragma omp barrier

    #pragma omp for schedule(dynamic,chunk)
    for(int i=0; i<lin; i++){
      float Maior = 0;
      for(int j=0; j<col; j++){
         if(MatrizDadosNormalizada[i][j] > Maior){
            Maior = MatrizDadosNormalizada[i][j];  //e armazena este valor em um vetor
         }
      }
      VetorMaior[i] = Maior;
     //Maior=0;
    }

    #pragma omp for schedule(dynamic,chunk)
    for(int i=0; i<lin; i++){
      float Menor = FLT_MAX;
      for(int j=0; j<col; j++){
         if(Menor > MatrizDadosNormalizada[i][j]){
             Menor = MatrizDadosNormalizada[i][j];
         }
      }
      VetorMenor[i] = Menor;
     // Menor=0;
    }

    #pragma omp barrier
    ImprimeVetorMaior(VetorMaior);
    ImprimeVetorMenor(VetorMenor);

   #pragma omp for schedule(dynamic,chunk)
    // Calcula o Vetor de Solucão Positiva Ideal___________________________________________________________________________________
    for(i=0;i<lin;i++){
		for(j=0;j<col;j++){
			MatSolucaoIdealPositiva[i][j] = MatrizDadosNormalizada[i][j] - VetorMaior[i];
			MatSolucaoIdealPositiva[i][j] = pow(MatSolucaoIdealPositiva[i][j], 2.0);             
		}		   	
    }
    
    #pragma omp for schedule(dynamic,chunk)
	for(i=0; i<lin; i++){ 
        for(j=0;j<col;j++){
            VetorSolucaoPositiva[j] += MatSolucaoIdealPositiva[i][j];
            VetorSolucaoPositiva[j] = sqrtf(VetorSolucaoPositiva[j]); 
        }	
	} //fim do trecho ________________________________________________________________________________________________________________ 

    #pragma omp barrier

    ImprimeVetorSolucaoIdeal(VetorSolucaoPositiva);    
  
    #pragma omp for schedule(dynamic,chunk)
    // Calcula o Vetor de Solucão Negativa Ideal____________________________________________________________________________________
    for(i=0;i<lin;i++){
		for(j=0;j<col;j++){
		    MatSolucaoIdealNegativa[i][j] = MatrizDadosNormalizada[i][j] - VetorMenor[i];
			MatSolucaoIdealNegativa[i][j] = pow(MatSolucaoIdealNegativa[i][j], 2.0);
		}		   	
    }
    
    #pragma omp for schedule(dynamic,chunk)
	for(i=0; i<lin; i++){
        for(j=0;j<col;j++){ 
            VetorSolucaoNegativa[j] += MatSolucaoIdealNegativa[i][j];             
            VetorSolucaoNegativa[j] = sqrtf(VetorSolucaoNegativa[j]);
        }	
    } //fim do trecho ________________________________________________________________________________________________________________
    
    #pragma omp barrier

    ImprimeVetorSolucaoNIdeal(VetorSolucaoNegativa);       

    #pragma omp for schedule(dynamic,chunk)
    //Calcula vetor Final de Proximidade Relativa
	for(int i = 0; i < col; i++){
		ProximidadeRelativa[i] = (VetorSolucaoNegativa[i]/(VetorSolucaoPositiva[i] - VetorSolucaoNegativa[i]));
	}
   // FunProximidadeRelativa(ProximidadeRelativa, VetorSolucaoNegativa, VetorSolucaoPositiva);
	//qsort(ProximidadeRelativa,col,sizeof(float), Ordena);	
		
	ImprimeProximidadeRelativa(ProximidadeRelativa);			
		
    return(0);
}
