
int correlativo = 0;

//Creamos un Structure con :
//id del estado
//id de donde viene 
//mapa actual con el estado cambiado 
//posicion de x del estado (Posicion x de Spiderman en ese estado)
//posicion de y del estado (Posicion y de Spiderman en ese estado)
//contenido del estado 
typedef struct estado estado;
struct estado{
	int id;
	int idAnterior;
	int ** arreglo;
	int px;
	int py;
	int contenido;
	char dedondeviene;
};

//Funcion que lee una matriz de un archivo.
//Entrada : El nombre de el archivo.
//Salida  : La matriz del archivo. 
int ** ObtenerMatriz(int largo){
	//Primero se lee la matriz de la ciudad guardada en el juego anterior
	FILE * archivoJuegoAnterior;
	int caracter, fila, columna, verificador, aux;
	int contadorEdificios=0;
	char * inputDireccion;
	inputDireccion="ciudad.txt";
	int opcion;
	archivoJuegoAnterior= fopen(inputDireccion, "r");
	if (archivoJuegoAnterior==NULL){
		printf("\n No hay ningun archivo con el nombre: ciudad.txt");		
		exit(1);
	}
	int ** matriz= (int**)malloc(sizeof(int*)*largo);
	for (int i=0;i<largo;i++){
		matriz[i]=(int*)malloc(sizeof(int)*largo);
	}
	for (int i=0;i<largo;i++){
		for (int j=0;j<largo;){
			caracter = fgetc(archivoJuegoAnterior);
			if (caracter!=32 && caracter != 10){
				caracter=caracter-48;
				contadorEdificios= contadorEdificios + caracter;
				matriz[i][j]=caracter;
				j++;
			}
		}
		caracter=fgetc(archivoJuegoAnterior);
	}
	return matriz;
}

//Funcion que crea un estado
//Entrada : Id actual del estado a crear, id del estado del que viene , posicionx, posiciony en este estado, mapa anterior.
//Salida  : Estado nuevo en base a los parametros entregados. 
estado CrearEstado(int * idn, int idAnteriorn, int pxn, int pyn,char dedondevienen, int ** Matrizanteriorn, int fila, int columna ){
	estado nuevoEstado;
	nuevoEstado.arreglo =  (int**)malloc(sizeof(int*)*fila);
	for (int i = 0; i < fila; ++i){
		nuevoEstado.arreglo[i]=(int*)malloc(sizeof(int)*columna);
	}
	nuevoEstado.id = *idn;
	nuevoEstado.idAnterior = idAnteriorn;
	nuevoEstado.px = pxn;
	nuevoEstado.py = pyn;
	nuevoEstado.dedondeviene = dedondevienen;
	for (int i = 0; i < fila; ++i){
		for (int j = 0; j < columna; ++j){
			nuevoEstado.arreglo[i][j] = Matrizanteriorn[i][j];
		}
	}
	nuevoEstado.arreglo[pyn][pxn] -=1;
	return nuevoEstado;
};

//Funcion agregar un estado a un arreglo.
//Entrada : El estado a agregar, la lista a la que se va a añadir ese estado y su tamaño.
//Salida  : Lista nueva con el estado agregado.
estado *AgregarEstado(estado * lista, int * largolista, estado estadoaAgregar){
    estado * nuevaLista = (estado *)malloc(sizeof(estado)*(*largolista+1));
    if (*largolista != 0){
        for (int i = 0; i < *largolista; ++i){
            nuevaLista[i]=lista[i];
        }
    }
    nuevaLista[*largolista] = estadoaAgregar;
    *largolista += 1;
    free(lista);
    return nuevaLista;
}

//Funcion que borra el primer estado de un arreglo
//Entrada : Lista a eliminar el primer elemento y el largo de respectivo arreglo.
//Salida  : Arreglo pero sin su primer elemento.
estado *BorrarEstado(estado *lista,int * largolista){
	estado * nuevaLista = (estado *)malloc(sizeof(estado)*(*largolista-1));
    for (int i = 1 ; i < *largolista ; ++i){
        nuevaLista[i-1] = lista[i];
    }
    *largolista -= 1;
    free(lista);
    return nuevaLista;
}

//Conjunto de funciones que revisan si exite un moviento posible a la direccion señalada en el nombre de la funcion.
//Entrada : Un estado a evaluar.
//Salida  : Respectivamente un booleano 1 si exite movimiento posible en esa direccion, 0 para lo contrario.
int revisarN(estado EstadoActual, int fila, int columna){
	// Retorna que si hay movimiento
	if (EstadoActual.py > 0){
		if(EstadoActual.arreglo[EstadoActual.py-1][EstadoActual.px] != 0 ){
	        return 1;
	    }
	}
	// Retorna que no hay moviento  
    return 0;
}
int revisarS(estado EstadoActual, int fila, int columna){
	if (EstadoActual.py < fila-1){
		if (EstadoActual.arreglo[EstadoActual.py+1][EstadoActual.px] != 0){
	        return 1;
		}
    }
    return 0;
}
int revisarE(estado EstadoActual, int fila, int columna){
    if (EstadoActual.px < columna-1){
    	if (EstadoActual.arreglo[EstadoActual.py][EstadoActual.px+1] != 0){
	        return 1;
    	}
    }
    return 0;
}
int revisarO(estado EstadoActual, int fila, int columna){
    if (EstadoActual.px > 0){
    	if (EstadoActual.arreglo[EstadoActual.py][EstadoActual.px-1] != 0){
	        return 1;
    	} 
    }
    return 0;
}

//Funcion que transforma la posicion de un estado a su antecesor, en relacion de dondev viene.
//Entrada : Un estado.
//Salida  : La posicion en X e Y rescpectivo al nombre de la funcion del estado de donde viene.
int ConversionX(estado EstadoActual){
	if (EstadoActual.dedondeviene == 'O'){
		return EstadoActual.px-1; 
	}
	if (EstadoActual.dedondeviene == 'E'){
		return EstadoActual.px+1;
	}
	else{
		return EstadoActual.px;
	}
}
int ConversionY(estado EstadoActual){
	if (EstadoActual.dedondeviene == 'S'){
		return EstadoActual.py+1; 
	}
	if (EstadoActual.dedondeviene == 'N'){
		return EstadoActual.py-1;
	}
	else{
		return EstadoActual.py;
	}
}

//Funcion que revisa si la matriz de un estado contiene la solucion final.
//Entrada : Un estado.
//Salida  : Un booleano, cero si tiene algun edificion con un numero distinto de 0; 1 si ya todo está en cero.
int EncontroSolucionFinal(estado EstadoActual, int fila, int columna){
	for (int i = 0; i < fila; ++i){
		for (int j = 0; j < columna; ++j){
			if (EstadoActual.arreglo[i][j] != 0){
				return 0;
			}
		}
	}
	return 1;
}

//Funcion busca la posicion de un estado que da origen al estado que estamos revisando en un arreglo.
//Entrada : Una arreglo de estados, el largo de ese arreglo y el estado a buscar su predecesor.
//Salida  : Un entero que es la posicion en el arreglo del estado predecesor del estado entregado.
int Anterior(estado * lista,int largolista,estado Estadofinal){
    for (int i = 0; i<largolista ; ++i){
        if((lista[i].id == Estadofinal.idAnterior)){
        	if (lista[i].px == ConversionX(Estadofinal) && lista[i].py == ConversionY(Estadofinal)){
        		return i;
        	}  
        }
    }
}

//Funcion que entrega un arreglo con la solucion de pasos a seguir.
//Entrada : El arreglo de los estados cerrados para buscar el camino a devolver y el estado Final.  
//Salida  : Un arreglo con las instruciones para salir.
char * mostrarsolucion(estado * lista, int largolista, estado Estadofinal){
	int contador = 0;
	char * Solucion = (char*)malloc(contador*sizeof(char));
	if (Estadofinal.dedondeviene == 'N'){
		Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
		Solucion[contador] = 'S';
		contador+= 1;
		printf("\n Ve hacia el : Sur");
	}
	if (Estadofinal.dedondeviene == 'S'){
		Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
		Solucion[contador] = 'N';
		contador+= 1;
		printf("\n Ve hacia el : Norte");
	}
	if (Estadofinal.dedondeviene == 'O'){
		Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
		Solucion[contador] = 'E';
		contador+= 1;
		printf("\n Ve hacia el : Este");
	}
	if (Estadofinal.dedondeviene == 'E'){
		Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
		Solucion[contador] = 'O';
		contador+= 1;
		printf("\n Ve hacia el : Oeste");
	}
	int ultimo = Anterior(lista,largolista,Estadofinal);
    while(lista[ultimo].dedondeviene != 'I'){
        if (lista[ultimo].dedondeviene == 'N'){
        	Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
			Solucion[contador] = 'S';
			contador+= 1;
            printf("\n Ve hacia el : Sur");
        }
        if (lista[ultimo].dedondeviene == 'S'){
        	Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
			Solucion[contador] = 'N';
			contador+= 1;
            printf("\n Ve hacia el : Norte");
        }
        if (lista[ultimo].dedondeviene == 'E'){
        	Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
			Solucion[contador] = 'O';
			contador+= 1;
            printf("\n Ve hacia el : Oeste");
        }
        if (lista[ultimo].dedondeviene == 'O'){
        	Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
			Solucion[contador] = 'E';
			contador+= 1;
            printf("\n Ve hacia el : Este");
        }
        ultimo = Anterior(lista,largolista,lista[ultimo]);
    }
    FILE * archivo;

    archivo = fopen("Salida.txt","w");
    Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
	Solucion[contador] = lista[ultimo].py+ '0';
	contador+= 1;
	Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
	Solucion[contador] = lista[ultimo].px+ '0';
	contador+= 1;
	Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
	Solucion[contador] = 'I';
	contador+= 1;
    printf("\n Este es el inicio I(%d,%d) la instruccion de arriba te llevará a la salida !! \n",lista[ultimo].px+1,lista[ultimo].py+1);
    char parD = '(';
    char parI = ')';
    char esp = ' ';
    char com = ',';
    fwrite(&Solucion[contador-1],sizeof(char),1,archivo);
    fwrite(&parD,sizeof(char),1,archivo);
    fwrite(&Solucion[contador-2],sizeof(char),1,archivo);
    fwrite(&com,sizeof(char),1,archivo);
    fwrite(&Solucion[contador-3],sizeof(char),1,archivo);
    fwrite(&parI,sizeof(char),1,archivo);
    fwrite(&esp,sizeof(char),1,archivo);
    for (int i = contador-4; -1 < i; --i)
    {
    	fwrite(&Solucion[i],sizeof(char),1,archivo);
    	fwrite(&com,sizeof(char),1,archivo);
    	printf("%c, ",Solucion[i]);
    }
    printf("\n");
    fclose(archivo);
}

//Revisa si el estado a Analizar contiene 2 conjuntos separados de edificios para asi ignorar estos casos dado que no hay solucion para ellos.
//Entrada : Un estado a analizar.
//Salida  : Un booleano, 1 para cuando exista 2 conjuntos separados, 0 para un estado que solo tenga un unico conjunto a recorrer.
int DiscriminarEstados(estado EAR, int fila, int columna){
	int auxA = 0;
	int auxF[fila];
	for (int i = 0; i < fila-1; ++i){
		auxA = 0;
		for (int j = 0; j < columna-1; ++j){
			if (EAR.arreglo[i][j] != 0){
				auxA = 1;
			} 
		}
		auxF[i] = auxA;
	}
	//Revisamos la lista que exista una secuencia 1-0-1 en filas.
	for (int i = 0; i < fila-1; ++i){
		if (i<fila-4){
			if (auxF[i]==1 && auxF[i+1]==0 && auxF[i+2]==1){
				return 1;
			}
		}
	}
	int auxB = 0;
	int auxC[columna];
	for (int i = 0; i < fila-1; ++i){
		auxB = 0;
		for (int j = 0; j < columna-1; ++j){
			if (EAR.arreglo[j][i] != 0){
				auxB = 1;
			} 
		}
		auxC[i] = auxB;
	}
	//Revisamos la lista que exista una secuencia 1-0-1 en columnas.
	for (int i = 0; i < columna-1; ++i){
		if (i<columna-4){
			if (auxC[i]==1 &&auxC[i+1]==0 && auxC[i+2]==1){
				return 1;
			}
		}
	}
	return 0;
}

//Funcion que entrega las posiciones validas para iniciar.
//Entrada : Un arreglo, el cual representa la ciudad.
//Salida  : Un arreglo con las posiciones validas para iniciar en la fila superior que contenga edificos.
int ** IniciosPosibles(int ** arreglo, int * aux, int fila, int columna){
	int ** comienzosPosibles =  (int**)malloc(sizeof(int*)*1);
    comienzosPosibles[0]=(int*)malloc(sizeof(int)*2);
	for (int i = 0; i < fila; ++i){
		for (int j = 0; j < columna; ++j){
			if (arreglo[i][j] != 0){
				comienzosPosibles[*aux][0]= i;
				comienzosPosibles[*aux][1]= j;
				*aux+=1;
                comienzosPosibles = (int**)realloc(comienzosPosibles,(*aux+1)*sizeof(int*));
                comienzosPosibles[*aux]=(int*)malloc(sizeof(int)*2);
			}
		}
		if(*aux != 0){
			return comienzosPosibles;
		}
	}
}

int * crearconjuntosolucion(int tamano){
	int*lista = (int*)malloc(sizeof(int)*tamano);
	return lista;
}

//Funcion que realiza la Busqueda en Espacio de Estados.
//Entrada : La matriz a recorrer, las filas de la matriz, las columnas , la posicion inicial en x y la posicion inicial en "y" para comenzar a recorrer ademas de 1 o 0 si quiere o no entregar la solucion.
//Salida  : Un booleano con 1 si encontró la forma de recorrer y dejar todo en cero, de lo contrario un 0.
int BEE(int ** Matriz,int fila,int columna, int posicionIX,int posicionIY,int entegarsolucion){
	int canAbiertos = 0;
    int canCerrados = 0;
    //LEA lista estados abiertos
    estado * LEA = (estado *)malloc(sizeof(estado)*canAbiertos);
    //LER lista estados recorridos
    estado * LER = (estado *)malloc(sizeof(estado)*canCerrados);
    //Se crea el estado inicial 
    estado inicial = CrearEstado(&correlativo,posicionIX,posicionIY,0,'I',Matriz,fila,columna);
    //Agregamos a la lista de los estados 
    LEA = AgregarEstado(LEA,&canAbiertos,inicial);
	while(canAbiertos > 0){
		estado eActual = LEA[0];
		//Revisamos si este estado contiene la solucion, es decir deja el mapa en 0 
		//No borramos este estado para que no acuse luego que no encontramos solucion
		if (EncontroSolucionFinal(LEA[0],fila,columna) == 1){
			//Muestra la solucion 
			//Devolver pasos para salir
			printf("El Estado  Inicial es : \n");
			for (int i = 0; i < fila; ++i){
				for (int j = 0; j < columna; ++j){
					printf(" %d," ,inicial.arreglo[i][j]);
				}
				printf("\n");
			}
			printf("----------------------------------------------\n"); 
			printf("Llegué mi rey !!!!!\n");
			printf("El Arreglo quedo como : \n");
			for (int i = 0; i < fila; ++i){
				for (int j = 0; j < columna; ++j){
					printf(" %d," ,eActual.arreglo[i][j]);
				}
				printf("\n");
			}
			printf("----------------------------------------------\n");
			if (entegarsolucion == 1){
				mostrarsolucion(LER,canCerrados,eActual);
			}
			//Liberar Toda la memoria almacenada
			return 1;
		}
		correlativo+=1;
		if (revisarN(eActual,fila,columna) == 1){
			//Creamos un estado nuevo al norte del actual copiando el mapa anterior restando una a la llegada
			estado norte = CrearEstado(&correlativo,eActual.id,eActual.px,eActual.py-1,'S',eActual.arreglo,fila,columna);
			if(DiscriminarEstados(norte,fila,columna)==0){
				//Agregamos el Estado a ListaEstadoAbierto
				LEA = AgregarEstado(LEA,&canAbiertos,norte);
			}
		}
		if (revisarS(eActual,fila,columna) == 1){
			//Creamos un estado nuevo 
			estado sur = CrearEstado(&correlativo,eActual.id,eActual.px,eActual.py+1,'N',eActual.arreglo,fila,columna);
			if(DiscriminarEstados(sur,fila,columna)==0){
				//Agregamos el Estado a ListaEstadoAbierto
				LEA = AgregarEstado(LEA,&canAbiertos,sur);
			}
		}
		if (revisarO(eActual,fila,columna) == 1){
			//Creamos un estado nuevo 
			estado oeste = CrearEstado(&correlativo,eActual.id,eActual.px-1,eActual.py,'E',eActual.arreglo,fila,columna);
			if(DiscriminarEstados(oeste,fila,columna)==0){
				//Agregamos el Estado a ListaEstadoAbierto
				LEA = AgregarEstado(LEA,&canAbiertos,oeste);
			}
		}
		if (revisarE(eActual,fila,columna) == 1){
			//Creamos un estado nuevo 
			estado este = CrearEstado(&correlativo,eActual.id,eActual.px+1,eActual.py,'O',eActual.arreglo,fila,columna);
			if(DiscriminarEstados(este,fila,columna)==0){
				//Agregamos el Estado a ListaEstadoAbierto
				LEA = AgregarEstado(LEA,&canAbiertos,este);
			}
		}
		//Borramos este estado de Abiertos y lo agregamos a cerrados y aumentamos el contador de cerrados en 
		LER = AgregarEstado(LER,&canCerrados,eActual);
		LEA = BorrarEstado(LEA,&canAbiertos);
	}
	//Condicion que no encontramos solucion 
	if(canAbiertos == 0){
		printf("No encontré solucion con el inicio en %d,%d lo generaré en otro punto \n",posicionIX+1,posicionIY+1);
		return 0 ; 
	}
}
