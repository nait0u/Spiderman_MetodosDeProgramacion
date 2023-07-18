int tamanio;

//Función que genera una estampa de tiempo para cada acción exitosa que haga el usuario en el recorrido manual y la imprime en un archivo de registro.
//Entrada: String de la acción.
//Salida: Archivo con todas las acciones exitosas del recorrido manual con su correspondiente estampa de tiempo

void timestamp(char * movimiento){
    FILE * fp;
    fp=fopen("userLog.txt", "a");
    time_t tiempo;
    tiempo=time(NULL); //Se toma el tiempo actual
    fprintf(fp,"\n%s",asctime( localtime(&tiempo) ) );
    fprintf(fp,"\n%s", movimiento);
    fclose(fp);
}

//Función que guarda la última coordenada donde se encuentra el usuario para ocuparla cuando quiera seguir su juego posteriormente
//Entrada: Coordenadas fila y columna de la matriz donde quedó ubicado
//Salida: Impresión de las coordenadas en el archivo designado

void copiaCoordenada(int fila, int columna){
    FILE* archivoCoordenada;
    archivoCoordenada=fopen("LastPlace.txt", "w");
    fprintf(archivoCoordenada, "%d", fila);
    fprintf(archivoCoordenada, " ");
    fprintf(archivoCoordenada, "%d", columna);
    fclose(archivoCoordenada);
}

//Función que reescribe la ciudad actual del usuario en un archivo nuevo.
//Entrada: Direccion del archivo nuevo, matriz que contiene el mapa.
//Salida: Confirmación de la correcta copia de la ciudad en el archivo nuevo.
void copiaCiudad(char * dirMapaNuevo, int** mapa){
    FILE * archivoRecorrido;
    archivoRecorrido= fopen(dirMapaNuevo, "w");
    for (int i=0; i< tamanio; i++){
        for (int j=0; j< tamanio; j++){
            fprintf(archivoRecorrido, "%d",mapa[i][j]);
            fprintf(archivoRecorrido, " ");
        }
    fprintf(archivoRecorrido, "\n");
    }
    printf("El archivo se actualizo correctamente \n");
    fclose(archivoRecorrido);
}


//Función que imprime la matriz de la ciudad actual.
//Entrada: Matriz que contiene el mapa de la ciudad.
//Salida: Matriz impresa por pantalla.
void imprimeCiudad(int** matrz){
    for (int i=0; i<tamanio; i++){
        for(int j=0; j<tamanio; j++){
            printf("%d\t", matrz[i][j]);
        }
        printf("\n");
    }
}


//Función que verifica los alrededores del jugador, ya que de estar encerrado entre ceros, pierde el juego.
//Entrada: Matriz que contiene la ciudad, fila y columna de la posicion a analizar.
//Salida: Valor "booleano", 1 de estar rodeado de ceros, 0 en caso contrario.

int verificar(int ** matriz, int fila, int columna){
    int respuesta=0;
    if (fila-1<0){
        if ((matriz[fila+1][columna]==0) && (matriz[fila][columna+1]==0) && (matriz[fila][columna-1]==0)){
            respuesta= 1;
        }
    }else if(fila+1> tamanio){
        if ((matriz[fila-1][columna]==0) && (matriz[fila][columna+1]==0) && (matriz[fila][columna-1]==0)){
            respuesta= 1;
        }
    }else if(columna+1> tamanio){
        if ((matriz[fila-1][columna]==0) && (matriz[fila+1][columna]==0) && (matriz[fila][columna-1]==0)){
            respuesta= 1;
        }
    }else if (columna-1<0){
        if ((matriz[fila-1][columna]==0) && (matriz[fila+1][columna]==0) && (matriz[fila][columna+1]==0)){
            respuesta= 1;
        }
    }else{
        if((matriz[fila-1][columna]==0) && (matriz[fila+1][columna]==0) && (matriz[fila][columna-1]==0) && (matriz[fila][columna+1]==0));
    }
    return respuesta;
}


//Funcion que ejecuta el recorrido manual de un juego nuevo.
//Entrada: Matriz que contiene el mapa de la ciudad obtenido por BES.
//Salida: Opciones por pantalla para que el usuario interactue.

void juegoNuevo(int** matrizCiudad){
    //Primero se lee la matriz de la ciudad generada
    int caracter, fila, columna, verificador, aux,opcion;
    int contadorEdificios=0;
    char * inputDireccion;
    char filaInput[50], columnaInput[50];

    inputDireccion="recorridoUsuario.txt";
    for (int i=0;i<tamanio;i++){
        for (int j=0;j<tamanio;j++){
            caracter = matrizCiudad[i][j];
            contadorEdificios=contadorEdificios+caracter;
            //printf("%d",matrizCiudad[i][j]);
        }
    }
    //Luego se copia en el archivo que llevará el progreso del jugador registrando su última jugada
    copiaCiudad(inputDireccion, matrizCiudad);
    imprimeCiudad(matrizCiudad);
    printf("Ingrese las coordenadas del punto [fila][columna] de donde quiere partir, considere que solo puede partir en aquellos puntos del mapa distintos a '0' :\n");
    printf("Ingrese el numero de fila:\n");
    do{
        scanf(" %c", filaInput);
        printf("\n");
        fila = atoi(filaInput);
        if (fila == 0){
            printf("Por favor, solo ingrese numeros:");
        }
    }while(fila == 0);
    printf("Ingrese el numero de columna:\n");
     do{
        scanf(" %c", filaInput);
        printf("\n");
        columna = atoi(filaInput);
        if (columna == 0){
            printf("Por favor, solo ingrese numeros:");
        }
    }while(columna == 0);
    fila= fila-1;
    columna= columna-1;
    if (fila>tamanio || fila<0 || columna >tamanio || columna <0){
        printf("Error, por favor ingrese un numero valido");
    }else if(matrizCiudad[fila][columna]==0){
        printf("\nError, por favor no ingreses coordenadas donde hayan ceros.");
    }else{
        do{
            copiaCoordenada(fila,columna);
            contadorEdificios= contadorEdificios-1;
            aux= matrizCiudad[fila][columna];
            matrizCiudad[fila][columna]=aux-1;
            imprimeCiudad(matrizCiudad);
            printf( "\n   5. Arriba.");
            printf( "\n   2. Abajo.");
            printf( "\n   3. Derecha.");
            printf( "\n   1. Izquierda. ");
            printf( "\n   6. Salir. ");
            printf( "\n   Seleccione un movimiento:");
            scanf( "%d", &opcion);
            if (opcion>6 || opcion<1){
                printf("\nError al recibir su decision, por favor ingrese un movimiento valido.");
            }else{
                while(opcion!=6){
                    switch(opcion){
                        case 5:
                            if(fila-1<0){
                                printf("\nHas salido de los bordes de la ciudad!");
                                printf("\nIngresa otra accion(5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                scanf("%d", &opcion);
                                break;
                            }else{
                                fila= fila-1;
                                int aux1= matrizCiudad[fila][columna];
                                if(aux1==0){
                                    fila=fila+1;
                                    printf("\nMovimiento invalido! Recuerda moverte por donde hayan numeros distintos a cero.");
                                    printf("\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
                                    printf("\nIngrese otra accion (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                    scanf("%d", &opcion);
                                    break;
                                }else{
                                    aux1= aux1-1;
                                    copiaCoordenada(fila, columna);
                                    contadorEdificios= contadorEdificios-1;
                                    matrizCiudad[fila][columna]= aux1;
                                    copiaCiudad(inputDireccion, matrizCiudad);
                                    imprimeCiudad(matrizCiudad);
                                    timestamp("Arriba");
                                    verificador= verificar(matrizCiudad, fila, columna);
                                    if (verificador == 1 && contadorEdificios !=0){
                                        printf("\nHas quedado encerrado! GAME OVER.\n");
                                        exit(0);
                                    }else if(verificador==1 && contadorEdificios == 0){
                                        printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
                                        exit(0);
                                    }else{
                                        printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
                                        printf("\nIngrese su siguiente accion (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                        scanf("%d", &opcion);
                                        break;
                                    }
                                }
                            }
                        case 2:
                            if (fila+1>tamanio){
                                printf("\nHas salido de los bordes de la ciudad!");
                                printf("\nIngresa otra accion(5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                scanf("%d", &opcion);
                                break;
                            }else{
                                fila= fila+1;
                                int aux2= matrizCiudad[fila][columna];
                                if(aux2==0){
                                    fila=fila-1;
                                    printf("\nMovimiento invalido! Recuerda moverte por donde hayan numeros distintos a cero.");
                                    printf("\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
                                    printf("\nIngrese otra accion (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                    scanf("%d", &opcion);
                                    break;
                                }else{
                                    aux2= aux2-1;
                                    copiaCoordenada(fila,columna);
                                    contadorEdificios= contadorEdificios-1;
                                    matrizCiudad[fila][columna]= aux2;
                                    copiaCiudad(inputDireccion, matrizCiudad);
                                    imprimeCiudad(matrizCiudad);
                                    timestamp("Abajo");
                                    verificador= verificar(matrizCiudad, fila, columna);
                                    if (verificador == 1 && contadorEdificios !=0){
                                        printf("\nHas quedado encerrado! GAME OVER.\n");
                                        exit(0);
                                    }else if(verificador==1 && contadorEdificios == 0){
                                        printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
                                        exit(0);
                                    }else{
                                        printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
                                        printf("\nIngrese su siguiente accion (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                        scanf("%d", &opcion);
                                        break;
                                    }
                                }
                            }
                        case 3:
                            if(columna+1>tamanio){
                                printf("\nHas salido de los bordes de la ciudad!");
                                printf("\nIngresa otra accion(5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                scanf("%d", &opcion);
                                break;
                            }else{
                                columna= columna+1;
                                int aux3= matrizCiudad[fila][columna];
                                if(aux3==0){
                                    columna=columna-1;
                                    printf("\nMovimiento invalido! Recuerda moverte por donde hayan numeros distintos a cero.");
                                    printf("\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
                                    printf("\nIngrese otra accion (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                    scanf("%d", &opcion);
                                    break;
                                }else{
                                    aux3= aux3-1;
                                    contadorEdificios= contadorEdificios-1;
                                    matrizCiudad[fila][columna]= aux3;
                                    copiaCiudad(inputDireccion, matrizCiudad);
                                    imprimeCiudad(matrizCiudad);
                                    copiaCoordenada(fila, columna);
                                    timestamp("Derecha");
                                    verificador= verificar(matrizCiudad, fila, columna);
                                    if (verificador == 1 && contadorEdificios !=0){
                                        printf("\nHas quedado encerrado! GAME OVER.\n");
                                        exit(0);
                                    }else if(verificador==1 && contadorEdificios == 0){
                                        printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
                                        exit(0);
                                    }else{
                                        printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
                                        printf("\nIngrese su siguiente accion (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                        scanf("%d", &opcion);
                                        break;
                                    }
                                }
                            }
                        case 1:
                            if(columna-1<0){
                                printf("\nHas salido de los bordes de la ciudad!");
                                printf("\nIngresa otra accion(5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                scanf("%d", &opcion);
                                break;
                            }else{
                                columna= columna-1;
                                int aux4= matrizCiudad[fila][columna];
                                if(aux4==0){
                                    columna=columna-1;
                                    printf("\nMovimiento invalido! Recuerda moverte por donde hayan numeros distintos a cero.");
                                    printf("\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
                                    printf("\nIngrese otra accion (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                    scanf("%d", &opcion);
                                    break;
                                }else{
                                    aux4= aux4-1;
                                    contadorEdificios= contadorEdificios-1;
                                    matrizCiudad[fila][columna]= aux4;
                                    copiaCiudad(inputDireccion, matrizCiudad);
                                    imprimeCiudad(matrizCiudad);
                                    copiaCoordenada(fila, columna);
                                    timestamp("Izquierda");
                                    verificador= verificar(matrizCiudad, fila, columna);
                                    if (verificador == 1 && contadorEdificios !=0){
                                        printf("\nHas quedado encerrado! GAME OVER.\n");
                                        exit(0);
                                    }else if(verificador==1 && contadorEdificios == 0){
                                        printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
                                        exit(0);
                                    }else{
                                        printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
                                        printf("\nIngrese su siguiente accion (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                        scanf("%d", &opcion);
                                        break;
                                    }
                                }
                            }
                        default:
                            printf("Ingrese un movimiento valido.\n");
                            break;
                    }
                }
            }
        }
        while(opcion>6 || opcion<1); //En caso de ingresar valores no validos, no se ejecuta ninguna accion
    }
}


//Funcion que permite hacer el recorrido manual con una partida guardada anteriormente
void juegoAnterior(){
    //Primero se lee la matriz de la ciudad guardada en el juego anterior y el que contiene las coordenadas
    FILE * archivoJuegoAnterior;
    FILE * coordenadaAnt;
    char* inputDireccion="recorridoUsuario.txt";
    archivoJuegoAnterior= fopen("recorridoUsuario.txt", "r");
    coordenadaAnt=fopen("LastPlace.txt","r");
    int caracter, fila, columna, verificador, aux;
    int contadorEdificios=0;
    int opcion;
    //Se obtienen las coordenadas donde quedó anteriormente el usuario
    fscanf(coordenadaAnt, "%d %d", &fila, &columna);
    if (archivoJuegoAnterior==NULL){
        printf("\nNo has iniciado ningun juego anteriormente, cerrando programa...");
        exit(0);
    }
    int ** matriz= (int**)malloc(sizeof(int*)*tamanio);
    for (int i=0;i<tamanio;i++){
        matriz[i]=(int*)malloc(sizeof(int)*tamanio);
    }
    for (int i=0;i<tamanio;i++){
        for (int j=0;j<tamanio;){
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
            do{
                imprimeCiudad(matriz);
                printf("\n La ubicación donde quedaste es [%d] [%d]", fila+1, columna+1);
                printf( "\n   5. Arriba.");
                printf( "\n   2. Abajo.");
                printf( "\n   3. Derecha.");
                printf( "\n   1. Izquierda. ");
                printf( "\n   6. Salir. ");
                printf( "\n   Seleccione un movimiento:");
                scanf( "%d", &opcion);
                if (opcion>6 || opcion<1){
                    printf("\nError al recibir su decision, por favor ingrese un movimiento valido.");
                }else{
                    while(opcion!=6){
                        switch(opcion){
                            case 5:
                                if(fila-1<0){
                                    printf("\nHas salido de los bordes de la ciudad!");
                                    printf("\nIngresa otra accion(5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                    scanf("%d", &opcion);
                                    break;
                                }else{
                                    fila= fila-1;
                                    int aux1= matriz[fila][columna];
                                    if(aux1==0){
                                        fila=fila+1;
                                        printf("\nMovimiento invalido! Recuerda moverte por donde hayan numeros distintos a cero.");
                                        printf("\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
                                        printf("\nIngrese otra accion (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                        scanf("%d", &opcion);
                                        break;
                                    }else{
                                        aux1= aux1-1;
                                        contadorEdificios= contadorEdificios-1;
                                        matriz[fila][columna]= aux1;
                                        copiaCiudad(inputDireccion, matriz);
                                        imprimeCiudad(matriz);
                                        verificador= verificar(matriz, fila, columna);
                                        copiaCoordenada(fila, columna);
                                        timestamp("Arriba");
                                        if (verificador == 1 && contadorEdificios !=0){
                                            printf("\nHas quedado encerrado! GAME OVER.\n");
                                            exit(0);
                                        }else if(verificador==1 && contadorEdificios == 0){
                                            printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
                                            exit(0);
                                        }else{
                                            printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
                                            printf("\nIngrese su siguiente accion (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                            scanf("%d", &opcion);
                                            break;
                                        }
                                    }
                                }
                            case 2:
                                if (fila+1>tamanio){
                                    printf("\nHas salido de los bordes de la ciudad!");
                                    printf("\nIngresa otra accion(5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                    scanf("%d", &opcion);
                                    break;
                                }else{
                                    fila= fila+1;
                                    int aux2= matriz[fila][columna];
                                    if(aux2==0){
                                        fila=fila-1;
                                        printf("\nMovimiento invalido! Recuerda moverte por donde hayan numeros distintos a cero.");
                                        printf("\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
                                        printf("\nIngrese otra accion (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                        scanf("%d", &opcion);
                                        break;
                                    }else{
                                        aux2= aux2-1;
                                        contadorEdificios= contadorEdificios-1;
                                        matriz[fila][columna]= aux2;
                                        copiaCiudad(inputDireccion, matriz);
                                        imprimeCiudad(matriz);
                                        copiaCoordenada(fila, columna);
                                        timestamp("Abajo");
                                        verificador= verificar(matriz, fila, columna);
                                        if (verificador == 1 && contadorEdificios !=0){
                                            printf("\nHas quedado encerrado! GAME OVER.\n");
                                            exit(0);
                                        }else if(verificador==1 && contadorEdificios == 0){
                                            printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
                                            exit(0);
                                        }else{
                                            printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
                                            printf("\nIngrese su siguiente accion (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                            scanf("%d", &opcion);
                                            break;
                                        }
                                    }
                                }
                            case 3:
                                if (columna+1>tamanio){
                                    printf("\nHas salido de los bordes de la ciudad!");
                                    printf("\nIngresa otra accion(5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                    scanf("%d", &opcion);
                                }else{
                                    columna= columna+1;
                                    int aux3= matriz[fila][columna];
                                    if(aux3==0){
                                        columna=columna-1;
                                        printf("\nMovimiento invalido! Recuerda moverte por donde hayan numeros distintos a cero.");
                                        printf("\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
                                        printf("\nIngrese otra accion (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                        scanf("%d", &opcion);
                                        break;
                                    }else{
                                        aux3= aux3-1;
                                        contadorEdificios= contadorEdificios-1;
                                        matriz[fila][columna]= aux3;
                                        copiaCiudad(inputDireccion, matriz);
                                        imprimeCiudad(matriz);
                                        copiaCoordenada(fila, columna);
                                        timestamp("Derecha");
                                        verificador= verificar(matriz, fila, columna);
                                        if (verificador == 1 && contadorEdificios !=0){
                                            printf("\nHas quedado encerrado! GAME OVER.\n");
                                            exit(0);
                                        }else if(verificador==1 && contadorEdificios == 0){
                                            printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
                                            exit(0);
                                        }else{
                                            printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
                                            printf("\nIngrese su siguiente accion (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                            scanf("%d", &opcion);
                                            break;
                                        }
                                    }
                                }
                            case 1:
                                if (columna-1<0){
                                    printf("\nHas salido de los bordes de la ciudad!");
                                    printf("\nIngresa otra accion(5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                    scanf("%d", &opcion);
                                }else{
                                    columna= columna-1;
                                    int aux4= matriz[fila][columna];
                                    if(aux4==0){
                                        columna=columna+1;
                                        printf("\nMovimiento invalido! Recuerda moverte por donde hayan numeros distintos a cero.");
                                        printf("\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
                                        printf("\nIngrese otra accion (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                        scanf("%d", &opcion);
                                        break;
                                    }else{
                                        aux4= aux4-1;
                                        contadorEdificios= contadorEdificios-1;
                                        matriz[fila][columna]= aux4;
                                        copiaCiudad(inputDireccion, matriz);
                                        imprimeCiudad(matriz);
                                        copiaCoordenada(fila, columna);
                                        timestamp("Izquierda");
                                        verificador= verificar(matriz, fila, columna);
                                        if (verificador == 1 && contadorEdificios !=0){
                                            printf("\nHas quedado encerrado! GAME OVER.\n");
                                            exit(0);
                                        }else if(verificador==1 && contadorEdificios == 0){
                                            printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
                                            exit(0);
                                        }else{
                                            printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
                                            printf("\nIngrese su siguiente accion (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
                                            scanf("%d", &opcion);
                                            break;
                                        }
                                    }
                                }
                            default:
                                printf("Ingrese un movimiento valido.\n");
                                break;
                        }
                    }
                }
            }
            while(opcion>6 || opcion<1); //En caso de ingresar valores no validos, no se ejecuta ninguna accion
            fclose(archivoJuegoAnterior);
}

//Función que recibe la matriz de la ciudad actual, y da la opcion al usuario de hacer el recorrido manual.
//Entrada: Matriz que contiene la ciudad obtenida del BES.
//Salida: Menú que da las opciones de empezar un juego nuevo o continuar uno anterior.
void recorridoManual(int ** matrizCiudad){
    int decision;
    //Entrando a la función, pregunta si continua con el mapa anterior o empieza uno nuevo
    do{
        printf( "\n   1. Continuar Juego Anterior.");
        printf( "\n   2. Juego Nuevo.");
        printf( "\n   3. Salir.");
        printf( "\n   Introduzca opcion (1-3): ");
        scanf( "%d", &decision);
        switch(decision){
            case 1:
                printf("\nRecuperando Juego Anterior...\n");
                juegoAnterior();

            case 2:
                printf("\nIniciando Juego Nuevo...\n");
                juegoNuevo(matrizCiudad);
        }
    }
    while(decision>3 || decision<1); //En caso de ingresar valores no validos, no se ejecuta ninguna accion
}
