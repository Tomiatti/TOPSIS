// para compilar: mpicc topsis_mpi.c -o topsis_mpi -lm -Wall
// para rodar: mpirun -np 2 topsis_mpi

#include <mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<float.h>
#include<limits.h>

//209554
#define lin 4
#define col 4

/*vetor de pesos que todos deverão ter acesso*/
float VetorPesos[col]  = {1,2,3,4};

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
   printf("\n\n Vetor maior \n\n");
   for(int i=0;i<lin;i++){
	     printf("[%.3f]\n", VetorMaior[i]);
   }
}

void ImprimeVetorMenor(float VetorMenor[lin]){
   printf("\n\n Vetor menor \n\n");
   for(int i=0;i<lin;i++){
	   printf("[%.3f]\n", VetorMenor[i]);
    }
}

void ImprimeMatrizDados(float MatrizDados[lin][col]){
   printf("\n\n Matriz Dados \n\n");
   for(int i=0; i<lin; i++)
    {
        for(int j=0; j<col; j++)
        {
             printf("Elemento[%d]= %.3f \n", i,  MatrizDados[i][j]);
        }
   }
}

void ImprimeMatrizNormalizada(float MatrizDadosNormalizada[lin][col]){
   printf("\n\n Matriz Normalizada \n\n");
   for(int i=0;i<lin;i++){
      for(int j=0;j<col;j++){
	     printf("[%.3f]", MatrizDadosNormalizada[i][j]);
	  }
      printf("\n");
   }
}

void ImprimeMatrizSolucaoIdeal(float MatSolucaoIdealPositiva[lin][col]){
   printf("\n\n");
		for(int i=0; i<lin; i++){
			for(int j=0; j<col; j++){
				printf("[%.3f]", MatSolucaoIdealPositiva[i][j]);
			}
			printf("\n");
        }
    }

void ImprimeVetorSolucaoIdeal(float VetorSolucaoPositiva[col]){
    printf("Solucao Positiva\n\n");
		for(int i=0; i<col; i++){
			 printf("[%.3f]", VetorSolucaoPositiva[i]);
		}
        printf("\n");
    }

void ImprimeMatrizSolucaoNIdeal(float MatSolucaoIdealNegativa[lin][col]){
printf("Solucao Negativa \n\n");
		for(int i=0; i<lin; i++){
			for(int j=0; j<col; j++){
				printf("[%.3f]", MatSolucaoIdealNegativa[i][j]);
			}
		printf("\n");
    }
}

void ImprimeVetorSolucaoNIdeal(float VetorSolucaoNegativa[col]){
		printf("Solucao Negativa\n\n");
		for(int i=0; i<col; i++){
			 printf("[%.3f]", VetorSolucaoNegativa[i]);
		}
		printf("\n\n");
    }
void ImprimeProximidadeRelativa(float ProximidadeRelativa[col]){    
    printf("Proximidade Relativa \n\n");
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

void MultiplicacaoPesos(float MatrizDadosNormalizada[lin][col], float VetorPesos[col]){
    for(int i=0; i<lin; i++){
		for(int j=0;j<col;j++){
			MatrizDadosNormalizada[i][j] = MatrizDadosNormalizada[i][j] * VetorPesos[i];
        }
	}
}



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
			ProximidadeRelativa[i] = (VetorSolucaoNegativa[i] / (VetorSolucaoPositiva[i] - VetorSolucaoNegativa[i]) );
    }
}

int main (int argc, char** argv){
    
    int world_rank;
    int world_size;
    //MPI_Status status;
    const int root=0;

   int i,j;
   //Declaracao da Matriz e vetores
   //float MatrizDados[lin][col];
   float MatrizDadosNormalizada[lin][col];
   float VetorMenor[lin];
   float VetorMaior[lin];

   float MatSolucaoIdealPositiva[lin][col];
   float MatSolucaoIdealNegativa[lin][col];
   float VetorSolucaoPositiva[col] = { };
   float VetorSolucaoNegativa[col] = { };
   float ProximidadeRelativa[col];

   float MatrizDados[lin][col] ={{1,2,3,4},
                                {5,6,7,8},
                                {9,10,11,12},
                                {13,14,15,16}};

    MPI_Init(&argc, &argv);
        //MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        MPI_Scatter(MatrizDados, lin*col/world_size, MPI_FLOAT, &MatrizDadosNormalizada, lin*col/world_size, MPI_FLOAT, 0, MPI_COMM_WORLD);

                NormalizaMatriz(MatrizDadosNormalizada, MatrizDados,VetorPesos);        
            
            MPI_Barrier(MPI_COMM_WORLD);
        
        MPI_Gather(&MatrizDadosNormalizada, lin*col/world_size, MPI_FLOAT, MatrizDados, lin*col/world_size, MPI_FLOAT, 0, MPI_COMM_WORLD);

            if(world_rank == root) {
                    CalculaVetorMaior(VetorMaior, MatrizDadosNormalizada);
                    CalculaVetorMenor(VetorMenor, MatrizDadosNormalizada);         
                }
          MPI_Bcast(VetorMaior, col, MPI_FLOAT, root, MPI_COMM_WORLD);
          MPI_Bcast(VetorMenor, col, MPI_FLOAT, root, MPI_COMM_WORLD);    
              
       
        //ImprimeMatrizNormalizada(MatrizDadosNormalizada);
        //ImprimeVetorMaior(VetorMaior);
        //ImprimeVetorMenor(VetorMenor);
        /*tudo certo até aqui*/
    MPI_Barrier(MPI_COMM_WORLD); 
    MPI_Scatter(MatrizDadosNormalizada, lin*col/world_size, MPI_FLOAT, &MatSolucaoIdealPositiva, lin*col/world_size, MPI_FLOAT, root, MPI_COMM_WORLD);
        for(i=0;i<lin;i++){
            for(j=0;j<col;j++){
                MatSolucaoIdealPositiva[i][j] = MatrizDadosNormalizada[i][j] - VetorMaior[i];
                MatSolucaoIdealPositiva[i][j] = pow(MatSolucaoIdealPositiva[i][j], 2.0);                
            }		   	
        }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(&MatSolucaoIdealPositiva, lin*col/world_size, MPI_FLOAT, MatrizDadosNormalizada, lin*col/world_size, MPI_FLOAT, root, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
   // ImprimeMatrizSolucaoIdeal( MatSolucaoIdealPositiva);
   //MPI_Scatter(MatSolucaoIdealPositiva, lin*col/world_size, MPI_FLOAT, &VetorSolucaoPositiva, lin, MPI_FLOAT, root, MPI_COMM_WORLD); 
   
    //MPI_Barrier(MPI_COMM_WORLD);
   // MPI_Barrier(MPI_COMM_WORLD);
  // MPI_Gather(&VetorSolucaoPositiva, lin, MPI_FLOAT, MatSolucaoIdealPositiva, lin, MPI_FLOAT, root, MPI_COMM_WORLD);
   
 //  MPI_Barrier(MPI_COMM_WORLD);

   // ImprimeVetorSolucaoIdeal(VetorSolucaoPositiva);       
    MPI_Scatter(MatrizDadosNormalizada, lin*col/world_size, MPI_FLOAT, &MatSolucaoIdealNegativa, lin*col/world_size, MPI_FLOAT, root, MPI_COMM_WORLD);
    for(i=0;i<lin;i++){
        for(j=0;j<col;j++){
                MatSolucaoIdealNegativa[i][j] = MatrizDadosNormalizada[i][j] - VetorMenor[i];
                MatSolucaoIdealNegativa[i][j] = pow(MatSolucaoIdealNegativa[i][j], 2.0);  
            }		   	
        }
    MPI_Barrier(MPI_COMM_WORLD); 
    MPI_Gather(&MatSolucaoIdealNegativa, lin*col/world_size, MPI_FLOAT, MatrizDadosNormalizada, lin*col/world_size, MPI_FLOAT, root, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    
  //  MPI_Scatter(MatSolucaoIdealNegativa, lin*col/world_size, MPI_FLOAT, &VetorSolucaoNegativa, lin, MPI_FLOAT, root, MPI_COMM_WORLD);
    
   // MPI_Barrier(MPI_COMM_WORLD);
     
  //  MPI_Gather(&VetorSolucaoNegativa, lin, MPI_FLOAT, MatSolucaoIdealNegativa, lin*col/world_size, MPI_FLOAT, root, MPI_COMM_WORLD);
    //ImprimeVetorSolucaoNIdeal(VetorSolucaoNegativa);
    //MPI_Barrier(MPI_COMM_WORLD);
       
         
        
    
        for(i=0; i<lin; i++){ 
            for(j=0;j<col;j++){           
                VetorSolucaoPositiva[j] += MatSolucaoIdealPositiva[i][j];
                VetorSolucaoPositiva[j] = sqrtf(VetorSolucaoPositiva[j]); 
                
            }	
        }   
        
        ImprimeVetorSolucaoIdeal(VetorSolucaoPositiva);
        ImprimeVetorSolucaoNIdeal(VetorSolucaoNegativa);      
   
        for(i=0; i<lin; i++){
            for(j=0;j<col;j++){ 
                VetorSolucaoNegativa[j] += MatSolucaoIdealNegativa[i][j];
                VetorSolucaoNegativa[j] = sqrtf(VetorSolucaoNegativa[j]);
                
            }	
        } 
    
     MPI_Barrier(MPI_COMM_WORLD);


    for(int i = 0; i < col; i++){
		ProximidadeRelativa[i] = (VetorSolucaoNegativa[i]/(VetorSolucaoPositiva[i] - VetorSolucaoNegativa[i]));
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
      
    MPI_Finalize();
      
    
    
    //qsort(ProximidadeRelativa,col,sizeof(float), Ordena);	
	ImprimeProximidadeRelativa(ProximidadeRelativa);			
		
    return(0);
}
