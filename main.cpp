#include <iostream>
#include <conio.h>
#include <windows.h>
#include <random>
#include <string.h>
#include <iomanip>
//Ultima version 

#define R 50 //Resolucion
#define H 10 //Longitud del nombre de usuario

using namespace std;

typedef struct estructabla{
    char nombre[H];
    int puntaje;
}estructabla;

typedef struct base_usuarios{
    char nombre[H];
    int banco;
    char configuracion[H];
}base_usuarios;

class recurrentes{                              

    private:
    char cuadricula[R][R/2]; //Se declara el arreglo donde se guardaran todos los elementos en pantalla del juego
    char buffer[R*R/2];
    char entrada;

    public:

    void error(int error){
        int i;
        int longitud;
        char text_error[]="Error";
        char text_definir_error_0[]="Error desconocido";
        char text_definir_error_1[]="No tiene suficientes fondos";
        char text_definir_error_2[]="Ya se alcanzo el nivel maximo";

        switch(error){
            case 1:
                longitud=strlen(text_definir_error_1);
                definircuadro2(longitud/2+3,2,0,0);
                longitud=strlen(text_error);
                for(i=0;i<longitud;i++){
                    cuadricula[R/2-longitud/2+i][R/4-1]=text_error[i];
                }
                longitud=strlen(text_definir_error_1);
                for(i=0;i<longitud;i++){
                    cuadricula[R/2-longitud/2+i][R/4+1]=text_definir_error_1[i];
                }
                dibujar();
                do{
                    entrada=getch();
                }while(entrada!='\r');
                break;

            case 2:

                longitud=strlen(text_definir_error_2);
                definircuadro2(longitud/2+3,2,0,0);
                longitud=strlen(text_error);
                for(i=0;i<longitud;i++){
                    cuadricula[R/2-longitud/2+i][R/4-1]=text_error[i];
                }
                longitud=strlen(text_definir_error_2);
                for(i=0;i<longitud;i++){
                    cuadricula[R/2-longitud/2+i][R/4+1]=text_definir_error_2[i];
                }
                dibujar();
                do{
                    entrada=getch();
                }while(entrada!='\r');
                break;

            default:

                longitud=strlen(text_definir_error_0);
                definircuadro2(longitud/2+3,2,0,0);
                for(i=0;i<longitud;i++){
                    cuadricula[R/2-longitud/2+i][R/4-1]=text_definir_error_0[i];
                }
                dibujar();
                break;
        }
    }

    void definircuadro2(int D, int A,int P,int K){

        int x=R/2-D+K; //Punto de inicio del eje x (x+18 es el punto final)
        int y=R/4-A+P; //Punto de inicio del eje y (y+5 es el punto final)
        int i,j;

        // Definir barra superior
        cuadricula[x][y]=char(218);

        for(i=x+1;i<x+2*D;i++){
            cuadricula[i][y]=char(196);
        }
        cuadricula[x+2*D][y]=char(191);

        // Definir barra inferior

        cuadricula[x][y+2*A]=char(192);
        for(i=x+1;i<x+2*D;i++){
            cuadricula[i][y+2*A]=char(196);
        }
        cuadricula[x+2*D][y+2*A]=char(217);

        ////////////////////////////

        // Definir barras laterales

        for(j=y+1;j<y+2*A;j++){
            cuadricula[x][j]=char(179);
            for(i=x+1;i<x+2*D;i++){
                cuadricula[i][j]=char(32);
            }
            cuadricula[x+2*D][j]=char(179);
        }
    }

    void dibujar(){

        int i,j,k=0;
        for(j=0;j<(R/2)-1;j++){
            for(i=0;i<R;i++){
                buffer[k]=cuadricula[i][j];
                k++;
            }
        }
        system("cls");
        cout << buffer;
    }

    void mod_cuadricula(int x,int y,char cont){
        cuadricula[x][y]=cont;
    }

    void definirmatriz(){

        int i,j;

        // Definir barra superior
        cuadricula[0][0]=char(201);
        for(i=1;i<R-2;i++){
            cuadricula[i][0]=char(205);
        }
        cuadricula[R-2][0]=char(187);
        cuadricula[R-1][0]=char(10);

        ////////////////////////////

        // Definir barras laterales

            for(j=1;j<(R/2)-2;j++){
                cuadricula[0][j]=char(186);
                for(i=1;i<R-2;i++){
                    cuadricula[i][j]=char(32);
                }
                cuadricula[R-2][j]=char(186);
                cuadricula[R-1][j]=char(10);
            }

            ////////////////////////////
            // Definir barra inferior

            cuadricula[0][R/2-2]=char(200);
            for(i=1;i<R-2;i++){
                cuadricula[i][R/2-2]=char(205);
            }
            cuadricula[R-2][R/2-2]=char(188);
            cuadricula[R-1][R/2-2]=char(10);

            ////////////////////////////
        }

    void definircuadro(int D, int A){

        int x=R/2-D; //Punto de inicio del eje x (x+18 es el punto final)
        int y=R/4-A; //Punto de inicio del eje y (y+5 es el punto final)
        int i,j;

        // Definir barra superior
        cuadricula[x][y]=char(201);

        for(i=x+1;i<x+2*D;i++){
            cuadricula[i][y]=char(205);
        }
        cuadricula[x+2*D][y]=char(187);

        // Definir barra inferior

        cuadricula[x][y+2*A]=char(200);
        for(i=x+1;i<x+2*D;i++){
            cuadricula[i][y+2*A]=char(205);
        }
        cuadricula[x+2*D][y+2*A]=char(188);

        ////////////////////////////

        // Definir barras laterales

        for(j=y+1;j<y+2*A;j++){
            cuadricula[x][j]=char(186);
            for(i=x+1;i<x+2*D;i++){
                cuadricula[i][j]=char(32);
            }
            cuadricula[x+2*D][j]=char(186);
        }
    }
};

class config{

    private:
    char nombre[H];
    FILE *pusuarios;
    int ubicacion_usuario;
    int banco;
    char configuracion[H];
    // npiedras -> configuracion[0]
    // nvelocidad -> configuracion[1]
    // nalimento -> configuracion[2]
    // n_max_piedras -> configuracion[3]
    // n_max_velocidad -> configuracion[4]
    // n_max_alimento -> configuracion[5]
    // multiplicador_adiccinal -> configuracion[6]
    // vacio_1 -> configuracion[7]
    // vacio_2 -> configuracion[8]
    // vacio_3 -> configuracion[9]
    recurrentes recurrentes;

    public:
    int dev_ubicacion(){
        int busqueda=1;
        int i;

        // Abre el archivo de usuarios para guardar los datos en una memoria reservada
        pusuarios=fopen("base_usuarios.txt","r");
        int n= sizeof(base_usuarios); //Tamaño de un elemento
        fseek(pusuarios,0,SEEK_END); //Coloca el cursor en el final del archivo
        int m=ftell(pusuarios); //Tamaño total de archivo
        int p=m/n; //Cantidad de elementos en el archivo
        base_usuarios *datos_usuario=(base_usuarios*)malloc(p*n); //Reserva la memoria del tamaño del archivo con la estructura "base_usuarios"
        fseek(pusuarios,0,SEEK_SET); //Coloca el curso al inicio del archivo
        fread(datos_usuario,n,p,pusuarios); //Lee todo el archivo y lo guarda en la memoria reservada
        fclose(pusuarios); //Una vez leido el archivo se lo cierra
        ///////////////////////////////////
        i=0;
        do{
            busqueda=strcmp(datos_usuario[i].nombre,nombre); //Se busca el usuario ingresado dentro de la base de usuarios
            cout << ">" << datos_usuario[i].nombre << "<->" << nombre << "<" << endl; Sleep(2000);
            if(busqueda==0){ //Si se encuentra el nombre se da aviso al usuario y se almacena la configuracion
                return i;
            }
            i++;
        }while(i<p); //Si se busco en todos los elementos y no coincide se rompe el bucle
        return -1;
    }

    void actualizar_config(int npiedras,int nvelocidad, int nalimentos, int n_max_piedras, int n_max_velocidad, int n_max_alimento,int multiplicador_adiccinal,int vacio_1,int vacio_2,int vacio_3){
        configuracion[0]=npiedras;
        configuracion[1]=nvelocidad;
        configuracion[2]=nalimentos;
        configuracion[3]=n_max_piedras;
        configuracion[4]=n_max_velocidad;
        configuracion[5]=n_max_alimento;
        configuracion[6]=multiplicador_adiccinal;
        configuracion[7]=vacio_1;
        configuracion[8]=vacio_2;
        configuracion[8]=vacio_3;
    }

    int dev_config(int valor){
        return configuracion[valor];
    }

    void guardar_config(){
        ubicacion_usuario=dev_ubicacion();
        cout << ubicacion_usuario << endl; Sleep(1000);
        FILE *manejador;

        manejador=fopen("base_usuarios.txt","r+"); //Se abre el archivo donde se encuentran todos los datos en usuario en modo escritura
        fseek(manejador,sizeof(base_usuarios)*ubicacion_usuario,SEEK_SET); //Se ubica el puntero del archivo en donde empiezan los datos del usuario, despues del nombre

        base_usuarios datos_usuario;

        //Se guarda la nueva configuracion
        datos_usuario.banco=banco;
        strcpy(datos_usuario.nombre,nombre);
        strcpy(datos_usuario.configuracion,configuracion);
        fwrite(&datos_usuario,sizeof (base_usuarios),1,manejador);
        ///////////

        fclose(manejador); //Se cierra el archivo
    }

    int agregar_usuario(char usuario[H]){
        strcpy(nombre,usuario);
        char text_config_default[]="0000000000";
        pusuarios=fopen("base_usuarios.txt","a"); //Se abre el archivo en modo escritura
        if(pusuarios == NULL){ //Error si no se puede abrir el archivo
            recurrentes.error(50);return -1;
        }
        base_usuarios usuario_datos;
        strcpy(usuario_datos.nombre,nombre);
        usuario_datos.banco=0;
        if(strcmp(usuario_datos.nombre,"Admin")==0){//Si el nombre ingresado es "Admin" se le pone 100000 en el banco
            usuario_datos.banco=100000;
        } 
        strcpy(usuario_datos.configuracion,text_config_default); //Se guarda el usuario con una una configuracion default

        fwrite(&usuario_datos,sizeof (base_usuarios),1,pusuarios); //Se escribe en el archivo
        fclose(pusuarios); // Se cierra el archivo
        return 0;
    }

    int buscar_usuario(char usuario[H]){
        strcpy(nombre,usuario);
        cout << "Se almacena" << nombre << endl; Sleep(1000);
        int busqueda=1;
        int i;

        // Abre el archivo de usuarios para guardar los datos en una memoria reservada
        pusuarios=fopen("base_usuarios.txt","r");
        if(pusuarios == NULL){//Error si no se puede abrir el archivo
            recurrentes.error(50);return -1;
        } 
        int n= sizeof(base_usuarios); //Tamaño de un elemento
        fseek(pusuarios,0,SEEK_END); //Coloca el cursor en el final del archivo
        int m=ftell(pusuarios); //Tamaño total de archivo
        int p=m/n; //Cantidad de elementos en el archivo
        base_usuarios *datos_usuario=(base_usuarios*)malloc(p*n); //Reserva la memoria del tamaño del archivo con la estructura "base_usuarios"
        fseek(pusuarios,0,SEEK_SET); //Coloca el curso al inicio del archivo
        fread(datos_usuario,n,p,pusuarios); //Lee todo el archivo y lo guarda en la memoria reservada
        fclose(pusuarios); //Una vez leido el archivo se lo cierra
        ///////////////////////////////////
        i=0;
        do{
            busqueda=strcmp(datos_usuario[i].nombre,nombre); //Se busca el usuario ingresado dentro de la base de usuarios
            if(busqueda==0){//Si se encuentra el nombre se da aviso al usuario y se almacena la configuracion
                strcpy(configuracion,datos_usuario[i].configuracion);
                banco=datos_usuario[i].banco;
                return i;
            }
            i++;
        }while(i<p); //Si se busco en todos los elementos y no coincide se rompe el bucle
        return -1;
    }

    char* dev_nombre(){
        return nombre;
    }

    int dev_banco(){
        return banco;
    }

    void restar_banco(int valor){
        banco=banco-valor;
    }
};

class IU{

    //Se inician los objetos
    recurrentes recurrentes;
    config config;

    private:
    //Recuperar configuracion
    int npiedras=config.dev_config(0)-16-48;
    int nvelocidad=config.dev_config(1);
    int nalimento=config.dev_config(2);
    int n_max_piedras=config.dev_config(3);
    int n_max_velocidad=config.dev_config(4);
    int n_max_alimento=config.dev_config(5);
    int multiplicador_adiccinal=config.dev_config(6);
    ///////////////////////////

    public:

    int tienda(){
        int i,temp_precio;
        int x=R/2,y=R/4; //Centro de la pantalla
        int derecha=0,abajo=0;
        int temp_banco;
        char temp_precio_text[5];

        char text_piedras[]="Piedras";
        char text_nivel[]="Nivel ";
        char text_velocidad[]="Velocidad";
        char text_alimento[]="Comida";
        char text_banco[]="Banco: ";
        char text_volver[]="Volver";
        char text_multi_adiccional[]="Multiplica.";
        char text_valor_banco[6];
        char entrada;

        do{
            int precio_velocidad=pow(100,n_max_velocidad/4)+1000*(n_max_velocidad+1);
            int precio_piedras=pow(100,n_max_piedras/4)+1000*(n_max_piedras+1);
            int precio_alimento=pow(100,n_max_alimento/4)+1000*(n_max_alimento+1);
            int precio_multiplicador=pow(100,multiplicador_adiccinal/4)+1000*(multiplicador_adiccinal+1);

            do{//Inicia el bucle
                recurrentes.definirmatriz();
                recurrentes.definircuadro(20,8);

                //Se define el cuadro con el valor del banco
                recurrentes.definircuadro2(8,1,-10,0);
                for(i=0;i<6;i++){
                    recurrentes.mod_cuadricula(x+i-7,y-10,text_banco[i]);
                }
                temp_banco=config.dev_banco();
                for(i=5;i>-1;i--){
                    text_valor_banco[i]=temp_banco%10+48;
                    if(temp_banco==0){
                        text_valor_banco[i]='0';
                    }
                    temp_banco=temp_banco/10;
                }
                for(i=0;i<6;i++){
                    recurrentes.mod_cuadricula(x+i+2,y-10,text_valor_banco[i]);
                }
                 /////////////////

                recurrentes.definircuadro2(6,2,-5+5*abajo,-13+13*derecha); //Cuadro de seleccion
                for(i=0;i<(int)strlen(text_volver);i++){
                    recurrentes.mod_cuadricula(x+i-16+13,y+5,text_volver[i]);
                }

                // Velocidad
                temp_precio=precio_velocidad;

                for(i=5;i>-1;i--){
                    temp_precio_text[i]=temp_precio%10+48;
                    if(temp_precio==0){
                        temp_precio_text[i]=' ';
                    }
                    temp_precio=temp_precio/10;
                }

                for(i=0;i<9;i++){recurrentes.mod_cuadricula(x+i-17,y-6,text_velocidad[i]);}
                for(i=0;i<5;i++){recurrentes.mod_cuadricula(x+i-16,y-5,text_nivel[i]);}
                recurrentes.mod_cuadricula(x+i-15,y-5,(char)(n_max_velocidad+49));
                recurrentes.mod_cuadricula(x-16,y-4,char(36));
                for(i=0;i<6;i++){recurrentes.mod_cuadricula(x+i-15,y-4,temp_precio_text[i]);}
                ////////////////////

                // Piedras
                temp_precio=precio_piedras;

                for(i=5;i>-1;i--){
                    temp_precio_text[i]=temp_precio%10+48;
                    if(temp_precio==0){
                        temp_precio_text[i]=' ';
                    }
                    temp_precio=temp_precio/10;
                }

                for(i=0;i<7;i++){
                    recurrentes.mod_cuadricula(x+i-16+13,y-6,text_piedras[i]);
                }
                for(i=0;i<5;i++){
                    recurrentes.mod_cuadricula(x+i-16+13,y-5,text_nivel[i]);
                }
                recurrentes.mod_cuadricula(x+i-15+13,y-5,char(49+n_max_piedras));
                recurrentes.mod_cuadricula(x-16+13,y-4,char(36));
                for(i=0;i<6;i++){
                    recurrentes.mod_cuadricula(x+i-15+13,y-4,temp_precio_text[i]);
                }
                ////////////////////

                // Alimentos
                temp_precio=precio_alimento;

                for(i=5;i>-1;i--){
                    temp_precio_text[i]=temp_precio%10+48;
                    if(temp_precio==0){
                        temp_precio_text[i]=' ';
                    }
                    temp_precio=temp_precio/10;
                }

                for(i=0;i<6;i++){
                    recurrentes.mod_cuadricula(x+i-16+26,y-6,text_alimento[i]);
                }
                for(i=0;i<5;i++){
                    recurrentes.mod_cuadricula(x+i-16+26,y-5,text_nivel[i]);
                }
                recurrentes.mod_cuadricula(x+i-15+26,y-5,char(49+n_max_alimento));
                recurrentes.mod_cuadricula(x-16+26,y-4,char(36));
                for(i=0;i<6;i++){
                    recurrentes.mod_cuadricula(x+i-15+26,y-4,temp_precio_text[i]);
                }
                ////////////////////

                // Multiplicador adiccional
                temp_precio=precio_multiplicador;

                for(i=5;i>-1;i--){
                    temp_precio_text[i]=temp_precio%10+48;
                    if(temp_precio==0){
                        temp_precio_text[i]=' ';
                    }
                    temp_precio=temp_precio/10;
                }

                for(i=0;i<(int)strlen(text_multi_adiccional);i++){
                    recurrentes.mod_cuadricula(x+i-18+13,y-1,text_multi_adiccional[i]);
                }
                for(i=0;i<5;i++){
                    recurrentes.mod_cuadricula(x+i-16+13,y,text_nivel[i]);
                }
                recurrentes.mod_cuadricula(x+i-15+13,y,char(49+multiplicador_adiccinal));
                recurrentes.mod_cuadricula(x-16+13,y+1,char(36));
                for(i=0;i<6;i++){
                    recurrentes.mod_cuadricula(x+i-15+13,y+1,temp_precio_text[i]);
                }
                /////////////////////

                recurrentes.dibujar();
                cout << npiedras << endl;
                cout << nvelocidad << endl;
                cout <<config.dev_config(0)<< endl;
                cout <<config.dev_config(1)<< endl;
                entrada=getch();

                if(entrada=='a'&&derecha>0){
                    derecha--;
                }
                else if(entrada=='d'&&derecha<2){
                    derecha++;
                }
                else if(entrada=='w'&&abajo>0){
                    abajo--;
                }
                else if(entrada=='s'&&abajo<2){
                    abajo++;
                }

            }while(entrada!='\r'); //Selecciona

            if(derecha==0&&abajo==0){ //Se selecciona aumentar la valocidad
                if(config.dev_banco()<precio_velocidad){
                    recurrentes.error(1);
                } else if (n_max_velocidad>7){
                    recurrentes.error(2);
                } else {
                    config.restar_banco(precio_velocidad);
                    n_max_velocidad++;
                }
            }

            if(derecha==1&&abajo==0){ //Se selecciona aumentar el nivel de piedras
                if(config.dev_banco()<precio_piedras){
                recurrentes.error(1);
            } else if(n_max_piedras>7) {
                recurrentes.error(2);
            } else {
                config.restar_banco(precio_piedras);
                n_max_piedras++;
            }
        }

        if(derecha==2&&abajo==0){ //Se selecciona aumentar el nivel de alimento
            if(config.dev_banco()<precio_alimento){
                recurrentes.error(1);
            } else if(n_max_alimento>7) {
                recurrentes.error(2);
            } else {
                config.restar_banco(precio_alimento);
                n_max_alimento++;
            }
        }

        if(derecha==1&&abajo==1){ //Se selecciona aumentar el nivel del multiplicador adiccinal
            if(config.dev_banco()<precio_multiplicador){
                recurrentes.error(1);
            } else if(multiplicador_adiccinal>7) {
                recurrentes.error(2);
            } else {
                config.restar_banco(precio_multiplicador);
                multiplicador_adiccinal++;
            }
        }

    }while(!(derecha==1&&abajo==2));
    config.actualizar_config(npiedras,nvelocidad,nalimento,n_max_piedras,n_max_velocidad,n_max_alimento,multiplicador_adiccinal,0,0,0);
    return menu();
}

    int opciones(){

        int eleccion=-6;
        int multi_decimal;
        int multi_entero=1;
        float multiplicador;
        char salir;
        char piedras[]="Piedras";
        char velocidad[]="Velocidad";
        char vacio[]="Alimento";
        char multi[]="Multiplicador  x";
        int k;

        recurrentes.definirmatriz();

        do{ //Se inicia el bucle para la seleccion de opciones
            recurrentes.definircuadro(15,10); //Se define el cuadro exterior
            recurrentes.definircuadro2(11,2,eleccion,0); //Se define el cuadro de seleccion

            //Se definen las barras de carga de las selecciones
            recurrentes.definircuadro2(9,1,-6,0);
            for(k=0;k<16;k=k+2){
                recurrentes.mod_cuadricula(R/2+k-7,((R/4)-6),char(179));
                }
            for(k=0;k<16;k=k+2){
                recurrentes.mod_cuadricula(R/2+k-7,((R/4)-7),char(194));
            }
            for(k=0;k<16;k=k+2){
                recurrentes.mod_cuadricula(R/2+k-7,((R/4)-5),char(193));
            }
            for(k=2;k<npiedras*2+2;k=k+2){
                recurrentes.mod_cuadricula(R/2+k-8,((R/4)-6),char(219));
            }
            recurrentes.mod_cuadricula(R/2-8,((R/4)-6),char(219));
            recurrentes.definircuadro2(9,1,0,0);
            for(k=0;k<16;k=k+2){
                recurrentes.mod_cuadricula(R/2+k-7,((R/4)),char(179));
            }
            for(k=0;k<16;k=k+2){
                recurrentes.mod_cuadricula(R/2+k-7,((R/4)-1),char(194));
            }
            for(k=0;k<16;k=k+2){
                recurrentes.mod_cuadricula(R/2+k-7,((R/4)+1),char(193));
            }
            for(k=2;k<nvelocidad*2+2;k=k+2){
                recurrentes.mod_cuadricula(R/2+k-8,((R/4)),char(219));
            }
            recurrentes.mod_cuadricula(R/2-8,((R/4)),char(219));
            recurrentes.definircuadro2(9,1,6,0);
            for(k=0;k<16;k=k+2){
                recurrentes.mod_cuadricula(R/2+k-7,((R/4)+6),char(179));
            }
            for(k=0;k<16;k=k+2){
                recurrentes.mod_cuadricula(R/2+k-7,((R/4)+5),char(194));
            }
            for(k=0;k<16;k=k+2){
                recurrentes.mod_cuadricula(R/2+k-7,((R/4)+7),char(193));
            }
            for(k=2;k<nalimento*2+2;k=k+2){
                recurrentes.mod_cuadricula(R/2+k-8,((R/4)+6),char(219));
            }
            recurrentes.mod_cuadricula(R/2-8,((R/4)+6),char(219));
            /////////////////

            // Se definen los titulos de las barras de carga
                for(k=0;k<(int)strlen(piedras);k++){
                    recurrentes.mod_cuadricula(R/2+k-3,((R/4)-8),piedras[k]);
                }
                for(k=0;k<(int)strlen(velocidad);k++){
                    recurrentes.mod_cuadricula(R/2+k-4,((R/4)-2),velocidad[k]);
                }
                for(k=0;k<(int)strlen(vacio);k++){
                    recurrentes.mod_cuadricula(R/2+k-4,((R/4)+4),vacio[k]);
                }
            ////////////

            // Se define el multiplicador
            multiplicador=(1+(float(npiedras+nvelocidad-nalimento*2)/10));
            if(multiplicador>0){
            } else {
                multiplicador=0;
            }

            multi_entero=(int)multiplicador;
            multi_decimal=(int)(multiplicador*10)%10;

            for(k=0;k<(int)strlen(multi);k++){
                recurrentes.mod_cuadricula(R/2+k-8,((R/4)+9),multi[k]);
            }
            recurrentes.mod_cuadricula(R/2-8+strlen(multi),((R/4)+9),char(multi_entero+48));
            recurrentes.mod_cuadricula(R/2-7+strlen(multi),((R/4)+9),char(46));
            recurrentes.mod_cuadricula(R/2-6+strlen(multi),((R/4)+9),char(multi_decimal+48));
            ////////////////////

            recurrentes.dibujar(); //Se dibuja todo lo definido anteriormente

            //Se evalua la entrada del usuario
            salir=getch();
            if(salir=='w'&&eleccion!=-6){
                eleccion=eleccion-6;
            }
            if(salir=='s'&&eleccion!=6){
                eleccion=eleccion+6;
            }
            if(salir=='d'){
                if(eleccion==-6&&npiedras!=n_max_piedras){
                    npiedras++;
                }
                if(eleccion==0&&nvelocidad!=n_max_velocidad){
                    nvelocidad++;
                }
                if(eleccion==6&&nalimento!=n_max_alimento){
                    nalimento++;
                }
            }
            if(salir=='a'){
                if(eleccion==-6&&npiedras!=0){
                    npiedras--;
                }
                if(eleccion==0&&nvelocidad!=0){
                    nvelocidad--;
                }
                if(eleccion==6&&nalimento!=0){
                    nalimento--;
                }
            }
            ///////////////////////

        }while(salir!='\r'); //Si el usuario presiona el enter se vuelve al menu principal

        recurrentes.definirmatriz();
        return menu();
    }

    int tabla(){

        FILE *archtabla;
        char tabla[]="    Tabla de posiciones    ";
        char Nombre[H];
        int i,k,numero,resultado,h=0;
        int maximo=0;
        int imaximo;

        archtabla = fopen("tabla.txt","r");
        int n= sizeof(estructabla); //Tamaño de un elemento
        fseek(archtabla,0,SEEK_END);
        int m=ftell(archtabla); //Tamaño total de archivo
        int p=m/n; //Cantidad de elementos en el archivo
        estructabla *ptabla=(estructabla*)malloc((p+1)*n); //Reserva la memoria del tamaño del archivo mas un elemento mas
        fseek(archtabla,0,SEEK_SET);
        fread(ptabla,n,p,archtabla); //Lee todo el archivo y lo guarda en la memoria reservada

        // Define el cuadro
        int D=14; //Distancia
        int A=7;  //Alto
        recurrentes.definircuadro(D,A);
        ///////////////////

        // Titulo
        for(k=0;k<(int)strlen(tabla);k++){
            recurrentes.mod_cuadricula(R/2-D+1+k,R/4-A+1,tabla[k]);
        }
        ////////////////////

        // Indice
        for(k=0;k<9;k++){
            recurrentes.mod_cuadricula(R/2-D+1,R/4-A+3+k,char(49+k));
        }
        recurrentes.mod_cuadricula(R/2-D+1,R/4-A+12,char(49));
        recurrentes.mod_cuadricula(R/2-D+2,R/4-A+12,char(48));
        ///////////////////

        // Ordena la tabla de posiciones
        for(k=0;k<p;k++){
            maximo=0;
            for(i=k;i<p;i++){
                if(maximo<ptabla[i].puntaje){
                    maximo=ptabla[i].puntaje;
                    imaximo=i;
                }
            }

            ptabla[p].puntaje=ptabla[k].puntaje;
            ptabla[k].puntaje=ptabla[imaximo].puntaje;
            ptabla[imaximo].puntaje=ptabla[p].puntaje;

            strcpy(ptabla[p].nombre,ptabla[k].nombre);
            strcpy(ptabla[k].nombre,ptabla[imaximo].nombre);
            strcpy(ptabla[imaximo].nombre,ptabla[p].nombre);
            h++;

        }
        /////////////////////////

        // Nombres
        if(p>10){
            p=10;
        } // Limita la tabla a un maximo de 10 elementos o menos

        for(i=0;i<p;i++){
            strcpy(Nombre,ptabla[i].nombre);
            for(k=0;k<(int)strlen(Nombre);k++){
                recurrentes.mod_cuadricula(R/2-D+k+5,R/4-A+3+i,Nombre[k]);
            }
        }

        // Puntuacion

        for(i=0;i<p;i++){
            numero=ptabla[i].puntaje;
            for(k=1;k<10;k++){
                resultado=numero%10;
                numero=numero/10;
                recurrentes.mod_cuadricula(R/2-D-k+27,R/4-A+3+i,char(resultado+48));
            }
        }

        recurrentes.dibujar();
        getch();
        free(ptabla);
        fclose(archtabla);

        recurrentes.definirmatriz();
        return menu();

    }

    int menu(){

        char pmenu[10][18]={
            "- Inicio         ",
            "- Tabla          ",
            "- Tienda         ",
            "- Opciones       ",
            "- Salir          ",
            "- Inicio <       ",
            "- Tabla <        ",
            "- Tienda <       ",
            "- Opciones <     ",
            "- Salir <        "
        };

        int x=R/2-10; //Punto de inicio del eje x (x+18 es el punto final)
        int y=R/4-6; //Punto de inicio del eje y (y+5 es el punto final)
        char m;

        int i,j;
        int e=0;

        recurrentes.definirmatriz(); //Borra todo lo dibujado en la cuadricula

        recurrentes.definircuadro(10,6); //Se define el recuadro contenedor

        //Se define el recuadro de seleccion
        do{
            int n=0;
            int k=0;
            int l=0;

            for(j=y+1;j<y+12;j++){
                if(n==0){
                    for(i=x+1;i<x+18;i++){recurrentes.mod_cuadricula(i,j,char(32));}
                    n=1;
                } else {
                    k=0;
                    for(i=x+1;i<x+18;i++){
                        if(l==e){recurrentes.mod_cuadricula(i,j,pmenu[l+5][k]);}
                        else{recurrentes.mod_cuadricula(i,j,pmenu[l][k]);}
                        k++;
                    }
                l++;
                n=0;
                }
            } 

            recurrentes.dibujar();

            m=getch();

            if(m=='w'&&e!=0){
                e--;
            } else if(m=='s'&&e!=4) {
                e++;
            }

        }while(m!='\r');
        //////////////////////

        if(e==1){
            e=tabla();
            return e;
        }
        if(e==2){
            e=tienda();
            return e;
        }
        if(e==3){
            e=opciones();
            return e;
        }
        return e;
    }

    int bienvenido_V2(){

        int x=R/2,y=R/4;//Centro de la pantalla
        int i,k,salida=0,e=0;
        char nombre[H];
        char r;
        char text_bienvenido[]="Bienvenido";
        char text_ingrese[]="Ingrese su nombre de usuario";
        char text_noencontrado[]="Usuario no encontrado";
        char text_encontrado[]="Usuario encontrado";
        char text_agregar[]="Agregar usuario";
        char text_volver[]="Volver a escribir";
        char text_agregado[]="Usuario agregado";


        do{ //Se inicia el bucle de ingreso de usuario
            for(i=0;i<H;i++){
                nombre[i]='\0';
            }
            salida=0;
            e=0;

            // Definir cuadro de bienvenida
            recurrentes.definirmatriz();
            recurrentes.definircuadro(19,6);
            for(i=0;i<(int)strlen(text_bienvenido);i++){
                recurrentes.mod_cuadricula(x+i-5,y-4,text_bienvenido[i]);
            }
            for(i=0;i<(int)strlen(text_ingrese);i++){
                recurrentes.mod_cuadricula(x+i-14,y-2,text_ingrese[i]);
            }
            recurrentes.dibujar();
             ///////////////////////////////
            
             // Ingreso del nombre de usuario
            k=0;
            do{
                nombre[k]=getch(); //Se toma la tecla apretada por el usuario

                if(nombre[k]=='\r'){
                    nombre[k]='\0'; //Si la entrada es un "enter" se termina el bucle
                    salida=1;
                } else if ((int)nombre[k]==8&&k!=0) {
                    nombre[k]='\0'; //Si la entrada es un "retroceso" se define la entrada actual y la anterior como caracteres nulos, a menos que no haya nada escrito
                    k--;
                    nombre[k]='\0';
                    k--;
                    recurrentes.definircuadro(19,6);
                    for(i=0;i<(int)strlen(text_bienvenido);i++){
                        recurrentes.mod_cuadricula(x+i-5,y-4,text_bienvenido[i]);
                    }
                    for(i=0;i<(int)strlen(text_ingrese);i++){
                        recurrentes.mod_cuadricula(x+i-14,y-2,text_ingrese[i]);
                    }
                }

                if (!((int)nombre[k]==8&&k==0)){
                    for(i=0;i<(int)strlen(nombre);i++){
                        recurrentes.mod_cuadricula(x+i-1-int(k/2),y,nombre[i]);
                    } //Se escribe la tecla ingresada a menos que se haya apretado el retroceso y no habia nada escrito.
                    k++;
                }

                recurrentes.dibujar();
            }while(salida==0&&k<H-1);
            ///////////////////////////////

            // Se busca el nombre ingresado en el archivo de usuarios existentes
            cout << "Se busca" <<nombre << endl ; Sleep(1500);
            if(config.buscar_usuario(nombre)!=-1){//Si se encuentra el nombre ingresado:

                for(i=0;i<(int)strlen(text_encontrado);i++){
                    recurrentes.mod_cuadricula(x+i-9,y+2,text_encontrado[i]);
                } //Se escribe el texto en pantalla que se encontro el usuario
                e=2;
                recurrentes.dibujar();
                Sleep(2000);
            } else {//Si no se encuetra el nombre ingresado:
                for(i=0;i<(int)strlen(text_noencontrado);i++){
                    recurrentes.mod_cuadricula(x+i-10,y+2,text_noencontrado[i]);
                } //Se escribe el texto en pantalla que no se encontro el usuario
                recurrentes.dibujar();

                do{// Se le da eleccion al usuario si elegir entre volver a escribir el usuario o de agregarlo a la base de datos
                    recurrentes.definircuadro(19,6);

                    if(e==0){
                        recurrentes.definircuadro2(8,1,4,-9);
                    } //Seleccion sobre Agregar Usuario
                    if(e==1){
                        recurrentes.definircuadro2(9,1,4,9);
                    } //Seleccion sobre Volver a escribir

                    //Se vuelven a definir todos los objetos en pantalla
                    for(i=0;i<(int)strlen(text_volver);i++){
                        recurrentes.mod_cuadricula(x+i+1,y+4,text_volver[i]);
                    }
                    for(i=0;i<(int)strlen(text_agregar);i++){
                        recurrentes.mod_cuadricula(x+i-16,y+4,text_agregar[i]);
                    }
                    for(i=0;i<(int)strlen(text_bienvenido);i++){
                        recurrentes.mod_cuadricula(x+i-5,y-4,text_bienvenido[i]);
                    }
                    for(i=0;i<(int)strlen(text_ingrese);i++){
                        recurrentes.mod_cuadricula(x+i-14,y-2,text_ingrese[i]);
                    }
                    for(i=0;i<(int)strlen(text_noencontrado);i++){
                        recurrentes.mod_cuadricula(x+i-10,y+2,text_noencontrado[i]);
                    }
                    k=strlen(nombre);
                    for(i=0;i<k;i++){
                        recurrentes.mod_cuadricula(x+i-1-int(k/2),y,nombre[i]);
                    }
                    ////////////////////////////

                    recurrentes.dibujar();
                    r=getch(); //Espera la entrada del usuario
                    if(r=='d'&&e==0){
                        e++;
                    }
                    else if (r=='a'&&e==1){
                        e--;
                    }
                }while(r!='\r'); //Se rompe el bucle cuando el usuario apreta el enter
            }

        }while(e==1); //Si se elige "volver a escribir" se repite el bucle de inicio de usuario

        if(e==0){ //Si se elige "Agregar usuario" se va agregar el usuario en el archivo de usuarios existentes
            config.agregar_usuario(nombre); //Se agrega el usuario

            //Se confirma en la pantalla la opcion ingresada
            recurrentes.definirmatriz();
            for(i=0;i<(int)strlen(text_agregado);i++){
                recurrentes.mod_cuadricula(x+i-8,y+3,text_agregado[i]);
            }
            for(i=0;i<(int)strlen(text_ingrese);i++){
                recurrentes.mod_cuadricula(x+i-14,y-2,text_ingrese[i]);
            }
            for(i=0;i<(int)strlen(text_bienvenido);i++){
                recurrentes.mod_cuadricula(x+i-5,y-4,text_bienvenido[i]);
            }
            k=strlen(nombre);
            for(i=0;i<k;i++){
                recurrentes.mod_cuadricula(x+i-1-int(k/2),y,nombre[i]);
            }
            recurrentes.dibujar();
            Sleep(2000);
            //////////////////////////////
        }
        return 0;
    }
};

int main(){
    //Se inician los objetos
    IU IU;
    recurrentes recurrentes;
    config config;
    ////////////////////

    recurrentes.definirmatriz();
    IU.bienvenido_V2();

    if(IU.menu()==4){
        config.guardar_config();
        return 0;
    }
    return 0;
}
