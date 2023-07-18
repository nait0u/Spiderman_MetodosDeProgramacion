#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>

//Funcion que crea el archivo codificado de la ciudad.
//Entrada : Un arreglo a codificar, su largo.
//Salida  : Un archivo de nombre SalidaInverso.txt con la ciudad codificada.
int Inverso(int ** ciudad, int largo){
	FILE * archivo;
	archivo = fopen("SalidaInverso.txt","w");
	//Se ingresa al documento el tamano de la ciudad
	fprintf(archivo,"%d\n", largo );
	//Se recorre las filas de la ciudad 
	for (int i = 0; i < largo; ++i){
		//Contador de conjuntos
		int contadorDeVariaciones = 0;
		int ContadorDeElementos = 0;
		int * secuecia = (int *)malloc(sizeof(int)*(contadorDeVariaciones));
		for (int j = 0; j < largo; ++j){
			if(ciudad[i][j] == 0){
				ContadorDeElementos = 0;
			}
			if(ciudad[i][j]!=0){
				//Sumar contador de elementos 
				ContadorDeElementos+=1;
				if ((j<largo-1 &&  ciudad[i][j+1] == 0 )|| (j == largo-1 && ciudad[i][j]!=0) ){
					contadorDeVariaciones+=1; 
					secuecia= (int*)realloc(secuecia,(contadorDeVariaciones)*sizeof(int));  
					secuecia[contadorDeVariaciones-1]=ContadorDeElementos;					
				}
			}
		}
		if (contadorDeVariaciones>0){
			for (int a = 0; a <contadorDeVariaciones ; ++a){
				fprintf(archivo, "%d", secuecia[a]);
				//printf("%d", secuecia[a]);
				if (a<contadorDeVariaciones-1){
					fprintf(archivo, "-");
				}
			}
			for (int b = 0; b < largo ; ++b){
				if (ciudad[i][b] != 0){
					fprintf(archivo, " %d", ciudad[i][b] );
				}
			}
			fprintf(archivo, "\n");
		}else{
			fprintf(archivo, "0");
			fprintf(archivo, "\n");
		}
	}
	//Se recorre las columnas de la ciudad 
	for (int i = 0; i < largo; ++i){
		//Contador de conjuntos
		int contadorDeVariaciones = 0;
		int ContadorDeElementos = 0;
		int * secuecia = (int *)malloc(sizeof(int)*(contadorDeVariaciones));
		for (int j = 0; j < largo; ++j){
			if(ciudad[j][i] == 0){
				ContadorDeElementos = 0;
			}
			if(ciudad[j][i]!=0){
				//Sumar contador de elementos 
				ContadorDeElementos+=1;
				if ((j<largo-1 &&  ciudad[j+1][i] == 0 )|| (j == largo-1 && ciudad[j][i]!=0) ){
					contadorDeVariaciones+=1; 
					secuecia= (int*)realloc(secuecia,(contadorDeVariaciones)*sizeof(int));  
					secuecia[contadorDeVariaciones-1]=ContadorDeElementos;					
				}
			}
		}
		if (contadorDeVariaciones>0){
			for (int a = 0; a <contadorDeVariaciones ; ++a){
				fprintf(archivo, "%d", secuecia[a]);
				//printf("%d", secuecia[a]);
				if (a<contadorDeVariaciones-1){
					fprintf(archivo, "-");
				}
			}
			for (int b = 0; b < largo ; ++b){
				if (ciudad[b][i] != 0){
					fprintf(archivo, " %d", ciudad[b][i] );
				}
			}
			fprintf(archivo, "\n");
		}else{
			fprintf(archivo, "0");
			fprintf(archivo, "\n");
		}
	}
	fclose(archivo); 
	return 0;
}

