#include <iostream>
#include <conio.h>
#include <windows.h>
#include <random>
#include <string.h>
#include <iomanip>

#define R 50 //Resolucion
#define H 10 //Longitud del nombre de usuario

using namespace std;



    // Se iniciacializa el generador de numeros aleatorios

       unsigned semilla =  static_cast<unsigned>(time(0));
       mt19937 gen(semilla);
       uniform_int_distribution<> distribucion(2,R-5);
       uniform_int_distribution<> distribuciongus(1,4);
       uniform_int_distribution<> distribucion_alimento(1,10);

    char cuadricula[R][R/2]; //Se declara el arreglo donde se guardaran todos los elementos en pantalla del juego
    int npiedras=0;
    int nvelocidad=0;
    int nalimento=0;
    int n_max_piedras;
    int n_max_velocidad;
    int n_max_alimento;
    int multiplicador_adiccinal=0;
    int vacio_1=0;
    int vacio_2=0;
    int vacio_3=0;
    float multiplicador=1;
    char nombre[H];
    int banco;
    char configuracion[H];
    char buffer[R*R/2];
    int ubicacion_usuario=-1;

    int tipo_alimento1,tipo_alimento2,tipo_alimento3,tipo_alimento4,tipo_alimento5,tipo_alimento6,tipo_alimento7,tipo_alimento8;
    int x_alimento1,x_alimento2,x_alimento3,x_alimento4,x_alimento5,x_alimento6,x_alimento7,x_alimento8;
    int y_alimento1,y_alimento2,y_alimento3,y_alimento4,y_alimento5,y_alimento6,y_alimento7,y_alimento8;
    int probabilidad_tipo1=5;



typedef struct estructabla{
    char nombre[H];
    int puntaje;
}estructabla;

typedef struct base_usuarios{
    char nombre[H];
    int banco;
    char configuracion[H];
}base_usuarios;

class vivora{

public:

    int largo=2; // largo
    int posicion[R*R][2]; // Se guarda la posicion actual y previa
    int actual=10; // posicion actual
    char entrada;

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
    for(i=0;i<longitud;i++){cuadricula[R/2-longitud/2+i][R/4-1]=text_error[i];}
    longitud=strlen(text_definir_error_1);
    for(i=0;i<longitud;i++){cuadricula[R/2-longitud/2+i][R/4+1]=text_definir_error_1[i];}
    dibujar();
    do{
        entrada=getch();
    }while(entrada!='\r');
    break;

    case 2:

    longitud=strlen(text_definir_error_2);
    definircuadro2(longitud/2+3,2,0,0);

    longitud=strlen(text_error);
    for(i=0;i<longitud;i++){cuadricula[R/2-longitud/2+i][R/4-1]=text_error[i];}
    longitud=strlen(text_definir_error_2);
    for(i=0;i<longitud;i++){cuadricula[R/2-longitud/2+i][R/4+1]=text_definir_error_2[i];}
    dibujar();
    do{
        entrada=getch();
    }while(entrada!='\r');
    break;

default:

    longitud=strlen(text_definir_error_0);
    definircuadro2(longitud/2+3,2,0,0);
    for(i=0;i<longitud;i++){cuadricula[R/2-longitud/2+i][R/4-1]=text_definir_error_0[i];}
    break;
    }

    }

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
        char text_nohayplata[]="Faltan puntos";
        char text_volver[]="Volver";
        char text_multi_adiccional[]="Multiplica.";
        char text_valor_banco[6];

        int precio_velocidad=pow(100,n_max_velocidad/4)+1000*(n_max_velocidad+1);
        int precio_piedras=pow(100,n_max_piedras/4)+1000*(n_max_piedras+1);
        int precio_alimento=pow(100,n_max_alimento/4)+1000*(n_max_alimento+1);
        int precio_multiplicador=pow(100,multiplicador_adiccinal/4)+1000*(multiplicador_adiccinal+1);

        do{
        do{ //Inicia el bucle
        definirmatriz();
        definircuadro(20,8);

        //Se define el cuadro con el valor del banco
        definircuadro2(8,1,-10,0);
        for(i=0;i<6;i++){cuadricula[x+i-7][y-10]=text_banco[i];}
        temp_banco=banco;
        for(i=5;i>-1;i--){
        text_valor_banco[i]=temp_banco%10+48;
        if(temp_banco==0){text_valor_banco[i]='0';}
            temp_banco=temp_banco/10;
            }
        for(i=0;i<6;i++){cuadricula[x+i+2][y-10]=text_valor_banco[i];}
        /////////////////

        definircuadro2(6,2,-5+5*abajo,-13+13*derecha); //Cuadro de seleccion
        for(i=0;i<(int)strlen(text_volver);i++){cuadricula[x+i-16+13][y+5]=text_volver[i];}

        // Velocidad
        temp_precio=precio_velocidad;

        for(i=5;i>-1;i--){
            temp_precio_text[i]=temp_precio%10+48;
            if(temp_precio==0){temp_precio_text[i]=' ';}
            temp_precio=temp_precio/10;
            }

        for(i=0;i<9;i++){cuadricula[x+i-17][y-6]=text_velocidad[i];}
        for(i=0;i<5;i++){cuadricula[x+i-16][y-5]=text_nivel[i];}
        cuadricula[x+i-15][y-5]=char(49+n_max_velocidad);
        cuadricula[x-16][y-4]=char(36);
        for(i=0;i<6;i++){cuadricula[x+i-15][y-4]=temp_precio_text[i];}
        ////////////////////

        // Piedras
        temp_precio=precio_piedras;

        for(i=5;i>-1;i--){
            temp_precio_text[i]=temp_precio%10+48;
            if(temp_precio==0){temp_precio_text[i]=' ';}
            temp_precio=temp_precio/10;
            }

        for(i=0;i<7;i++){cuadricula[x+i-16+13][y-6]=text_piedras[i];}
        for(i=0;i<5;i++){cuadricula[x+i-16+13][y-5]=text_nivel[i];}
        cuadricula[x+i-15+13][y-5]=char(49+n_max_piedras);
        cuadricula[x-16+13][y-4]=char(36);
        for(i=0;i<6;i++){cuadricula[x+i-15+13][y-4]=temp_precio_text[i];}
        ////////////////////

        // Alimentos
        temp_precio=precio_alimento;

        for(i=5;i>-1;i--){
            temp_precio_text[i]=temp_precio%10+48;
            if(temp_precio==0){temp_precio_text[i]=' ';}
            temp_precio=temp_precio/10;
            }

        for(i=0;i<6;i++){cuadricula[x+i-16+26][y-6]=text_alimento[i];}
        for(i=0;i<5;i++){cuadricula[x+i-16+26][y-5]=text_nivel[i];}
        cuadricula[x+i-15+26][y-5]=char(49+n_max_alimento);
        cuadricula[x-16+26][y-4]=char(36);
        for(i=0;i<6;i++){cuadricula[x+i-15+26][y-4]=temp_precio_text[i];}
        ////////////////////

        // Multiplicador adiccional
        temp_precio=precio_multiplicador;

        for(i=5;i>-1;i--){
            temp_precio_text[i]=temp_precio%10+48;
            if(temp_precio==0){temp_precio_text[i]=' ';}
            temp_precio=temp_precio/10;
            }

        for(i=0;i<(int)strlen(text_multi_adiccional);i++){cuadricula[x+i-18+13][y-1]=text_multi_adiccional[i];}
        for(i=0;i<5;i++){cuadricula[x+i-16+13][y]=text_nivel[i];}
        cuadricula[x+i-15+13][y]=char(49+multiplicador_adiccinal);
        cuadricula[x-16+13][y+1]=char(36);
        for(i=0;i<6;i++){cuadricula[x+i-15+13][y+1]=temp_precio_text[i];}
        /////////////////////


        dibujar();
        entrada=getch();

        if(entrada=='a'&&derecha>0){derecha--;}
        else if(entrada=='d'&&derecha<2){derecha++;}
        else if(entrada=='w'&&abajo>0){abajo--;}
        else if(entrada=='s'&&abajo<2){abajo++;}

        }while(entrada!='\r'); //Selecciona

        if(derecha==0&&abajo==0){ //Se selecciona aumentar la valocidad
                if(banco<precio_velocidad){error(1);}
                else if(n_max_velocidad>7){error(2);}
                else{
                     banco=banco-precio_velocidad;
                     n_max_velocidad++;}
        }

        if(derecha==1&&abajo==0){ //Se selecciona aumentar el nivel de piedras
                if(banco<precio_piedras){error(1);}
                else if(n_max_piedras>7){error(2);}
                else{
                     banco=banco-precio_piedras;
                     n_max_piedras++;}
        }

        if(derecha==2&&abajo==0){ //Se selecciona aumentar el nivel de alimento
                if(banco<precio_alimento){error(1);}
                else if(n_max_alimento>7){error(2);}
                else{
                     banco=banco-precio_alimento;
                     n_max_alimento++;}
        }

        if(derecha==1&&abajo==1){ //Se selecciona aumentar el nivel del multiplicador adiccinal
                if(banco<precio_multiplicador){error(1);}
                else if(multiplicador_adiccinal>7){error(2);}
                else{
                     banco=banco-precio_multiplicador;
                     multiplicador_adiccinal++;}
        }

        }while(!(derecha==1&&abajo==2));
        return menu();

    }

    void guardar_config(){
    FILE *manejador;

    manejador=fopen("base_usuarios.txt","r+"); //Se abre el archivo donde se encuentran todos los datos en usuario en modo escritura
    fseek(manejador,sizeof(base_usuarios)*ubicacion_usuario,SEEK_SET); //Se ubica el puntero del archivo en donde empiezan los datos del usuario, despues del nombre

    base_usuarios datos_usuario;

    //Se guarda la nueva configuracion
    configuracion[0]=nvelocidad+48;
    configuracion[1]=npiedras+48;
    configuracion[2]=nalimento+48;
    configuracion[3]=n_max_velocidad+48;
    configuracion[4]=n_max_piedras+48;
    configuracion[5]=n_max_alimento+48;
    configuracion[6]=multiplicador_adiccinal+48;
    configuracion[7]=vacio_1+48;
    configuracion[8]=vacio_2+48;
    configuracion[9]=vacio_3+48;

    datos_usuario.banco=banco;
    strcpy(datos_usuario.nombre,nombre);
    strcpy(datos_usuario.configuracion,configuracion);

    fwrite(&datos_usuario,sizeof (base_usuarios),1,manejador);
    ///////////

    fclose(manejador); //Se cierra el archivo


    }

    void reiniciar(){


        int i;
        definirmatriz(); //Se reinicia la matriz por si el usuario quiere volver a jugar
        for(i=0;i<(R*R);i++){posicion[i][0];posicion[i][1];} //Se reinicia la matriz de posiciones
        //Se definen los parametros iniciales nuevamente
        largo=2;
        actual=10;

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

    void posicionvieja(int x,int y){
        actual++;
        // Guardar posicion actual
    {
        posicion[actual][0]=x;
        posicion[actual][1]=y;
    }

    // Borra posicion vieja
    {
        cuadricula[posicion[actual-largo][0]][posicion[actual-largo][1]]=char(32);
        cuadricula[posicion[actual-largo][0]+1][posicion[actual-largo][1]]=char(32);
        cuadricula[0][0]=char(201);
        cuadricula[1][0]=char(205);

    }
    }

    int devolverlargo(){
    return largo;
    }

    void dibujar(){

    int i,j,k=0;
    for(j=0;j<(R/2)-1;j++){
    for(i=0;i<R;i++){
            buffer[k]=cuadricula[i][j];
            k++;}}

    system("cls");
    cout << buffer;
    }

    void gameover(){
    // Definir cuadro de game over

    int i,x,y,k=0;
    string game_over="Game over";
    string puntaje="Puntaje ";
    int* punt=devolverpuntaje();
    int valor_puntaje=((largo-2)*multiplicador*multiplicador_adiccinal)*50;

    banco= banco+valor_puntaje;


    //Anota el puntaje en la tabla
    FILE *ptabla;
    ptabla=fopen("tabla.txt","a");
    estructabla usuarioypuntaje;
    strcpy(usuarioypuntaje.nombre,nombre);
    usuarioypuntaje.puntaje=valor_puntaje;
    fwrite(&usuarioypuntaje,sizeof (estructabla),1,ptabla);
    fclose(ptabla);
    //////////////////////////////


    x=R/2-10; //Punto de inicio del eje x (x+18 es el punto final)
    y=R/4-3; //Punto de inicio del eje y (y+5 es el punto final)

    definircuadro(12,4); //Se define el cuadro

    // Game over
    char entrada;
    for(i=x+6;i<x+15;i++){
    cuadricula[i][y+2]=game_over[k];
    k++;
    }

    k=0;
    for(i=x+3;i<x+11;i++){
    cuadricula[i][y+4]=puntaje[k];
    k++;
    }
    k=0;
    for(i=x+11;i<x+18;i++){
    cuadricula[i][y+4]=(char)punt[k];
    k++;
    }

    //////////////////

    dibujar();
    free(punt);
    do{
        entrada=getch();
    }while(entrada!='\r');
}

    int* devolverpuntaje(){
        int p=((largo-2)*multiplicador*multiplicador_adiccinal)*50,i;
        int *punt = (int*)calloc(7,sizeof(int));
        for(i=6;i>-1;i--){
            punt[i]=p%10+48;
            p=p/10;
        }
        return punt;
    }

    int menu(){

    char pmenu[10][18]={"- Inicio         ",
                        "- Tabla          ",
                        "- Tienda         ",
                        "- Opciones       ",
                        "- Salir          ",
                        "- Inicio <       ",
                        "- Tabla <        ",
                        "- Tienda <       ",
                        "- Opciones <     ",
                        "- Salir <        "};

    int x=R/2-10; //Punto de inicio del eje x (x+18 es el punto final)
    int y=R/4-5; //Punto de inicio del eje y (y+5 es el punto final)
    char m;

    int i,j;
    int e=0;

    definirmatriz(); //Borra todo lo dibujado en la cuadricula

    // Definir barra superior
    cuadricula[x][y]=char(201);

    for(i=x+1;i<x+18;i++){
    cuadricula[i][y]=char(205);
    }
    cuadricula[x+18][y]=char(187);

    // Definir barra inferior

    cuadricula[x][y+12]=char(200);
    for(i=x+1;i<x+18;i++){
    cuadricula[i][y+12]=char(205);
     }
    cuadricula[x+18][y+12]=char(188);

    ////////////////////////////

    // Definir barras laterales

    do{
    int n=0;
    int k=0;
    int l=0;



    for(j=y+1;j<y+12;j++){
    cuadricula[x][j]=char(186);
    if(n==0){
    for(i=x+1;i<x+18;i++){cuadricula[i][j]=char(32);}
    cuadricula[x+18][j]=char(186);
    n=1;
    }
    else{
        k=0;
        for(i=x+1;i<x+18;i++){
                if(l==e){cuadricula[i][j]=pmenu[l+5][k];}
                else{cuadricula[i][j]=pmenu[l][k];}
        k++;
        }
        cuadricula[x+18][j]=char(186);
        l++;
        n=0;
        }}

    dibujar();
    m=getch();

            if(m=='w'&&e!=0)
                e--;
            else if (m=='s'&&e!=4)
                e++;

    }while(m!='\r');

        // Definir barras laterales
    {


    for(j=1;j<(R/2)-2;j++){
    cuadricula[0][j]=char(186);
    for(i=1;i<R-2;i++){
    cuadricula[i][j]=char(32);
    }
    cuadricula[R-2][j]=char(186);
    cuadricula[R-1][j]=char(10);
    }

    ////////////////////////////
    }

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
        definircuadro(D,A);
        ///////////////////

        // Titulo
        for(k=0;k<(int)strlen(tabla);k++){
            cuadricula[R/2-D+1+k][R/4-A+1]=tabla[k];
        }
        ////////////////////

        // Indice
        for(k=0;k<9;k++){cuadricula[R/2-D+1][R/4-A+3+k]=char(49+k);}
        cuadricula[R/2-D+1][R/4-A+12]=char(49);
        cuadricula[R/2-D+2][R/4-A+12]=char(48);
        ///////////////////

        // Ordena la tabla de posiciones
        for(k=0;k<p;k++){
             maximo=0;
        for(i=k;i<p;i++){
            if(maximo<ptabla[i].puntaje){
                    maximo=ptabla[i].puntaje;
                    imaximo=i;
            }}

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
        if(p>10){p=10;} // Limita la tabla a un maximo de 10 elementos o menos

        for(i=0;i<p;i++){
                strcpy(Nombre,ptabla[i].nombre);
        for(k=0;k<(int)strlen(Nombre);k++) cuadricula[R/2-D+k+5][R/4-A+3+i]=Nombre[k];
        }

        // Puntuacion

        for(i=0;i<p;i++){
        numero=ptabla[i].puntaje;
        for(k=1;k<10;k++){
        resultado=numero%10;
        numero=numero/10;
        cuadricula[R/2-D-k+27][R/4-A+3+i]=char(resultado+48);
        }}

        dibujar();
        getch();
        free(ptabla);
        fclose(archtabla);

        definirmatriz();
        return menu();

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

    void genpiedras(int cantidad,int tamanio){
        int xpie,ypie,i=0,j,h,P;
        if(tamanio%2==0){tamanio--;}

        uniform_int_distribution<> distribucionpie(2,R-7-tamanio); //Se genera al azar el area donde se pueden generar piedras, va de 1 hasta el tamaño maximo ingresado
        //uniform_int_distribution<> distribucionpie_cant(tamanio-(tamanio/2),tamanio); //Se generan las piedras al azar en el area posible
        //uniform_int_distribution<> distribucion_coloc(3,R-6-tamanio);

        do{
      //  do{ //Crea al azar las piedras
            P=0;
            xpie=distribucionpie(gen); //Origen del area de las piedras
            ypie=distribucionpie(gen)/2; //Origen del area de las piedras
            if(xpie%2==0){xpie--;}
        //////////////////

        //Se dibuja en la matriz la piedras
            for(h=0;h<tamanio;h++){
            for(j=0;j<tamanio;j++){
                cuadricula[xpie+j][ypie+h]=char(177);
                cuadricula[xpie+j+1][ypie+h]=char(177);
            }}
        i++;
    }while(i!=cantidad);


    }

    int opciones(){

    int eleccion=-6;
    int multi_decimal;
    int multi_entero=1;
    char salir;
    char piedras[]="Piedras";
    char velocidad[]="Velocidad";
    char vacio[]="Alimento";
    char multi[]="Multiplicador  x";
    int k;


    definirmatriz();

    do{ //Se inicia el bucle para la seleccion de opciones
    definircuadro(15,10); //Se define el cuadro exterior

    definircuadro2(11,2,eleccion,0); //Se define el cuadro de seleccion

    //Se definen las barras de carga de las selecciones
    definircuadro2(9,1,-6,0);
    for(k=0;k<16;k=k+2){cuadricula[R/2+k-7][((R/4)-6)]=char(179);}
    for(k=0;k<16;k=k+2){cuadricula[R/2+k-7][((R/4)-7)]=char(194);}
    for(k=0;k<16;k=k+2){cuadricula[R/2+k-7][((R/4)-5)]=char(193);}
    for(k=2;k<npiedras*2+2;k=k+2){cuadricula[R/2+k-8][((R/4)-6)]=char(219);}
    cuadricula[R/2-8][((R/4)-6)]=char(219);
    definircuadro2(9,1,0,0);
    for(k=0;k<16;k=k+2){cuadricula[R/2+k-7][((R/4))]=char(179);}
    for(k=0;k<16;k=k+2){cuadricula[R/2+k-7][((R/4)-1)]=char(194);}
    for(k=0;k<16;k=k+2){cuadricula[R/2+k-7][((R/4)+1)]=char(193);}
    for(k=2;k<nvelocidad*2+2;k=k+2){cuadricula[R/2+k-8][((R/4))]=char(219);}
    cuadricula[R/2-8][((R/4))]=char(219);
    definircuadro2(9,1,6,0);
    for(k=0;k<16;k=k+2){cuadricula[R/2+k-7][((R/4)+6)]=char(179);}
    for(k=0;k<16;k=k+2){cuadricula[R/2+k-7][((R/4)+5)]=char(194);}
    for(k=0;k<16;k=k+2){cuadricula[R/2+k-7][((R/4)+7)]=char(193);}
    for(k=2;k<nalimento*2+2;k=k+2){cuadricula[R/2+k-8][((R/4)+6)]=char(219);}
    cuadricula[R/2-8][((R/4)+6)]=char(219);
    /////////////////

    // Se definen los titulos de las barras de carga
        for(k=0;k<(int)strlen(piedras);k++){cuadricula[R/2+k-3][((R/4)-8)]=piedras[k];}
        for(k=0;k<(int)strlen(velocidad);k++){cuadricula[R/2+k-4][((R/4)-2)]=velocidad[k];}
        for(k=0;k<(int)strlen(vacio);k++){cuadricula[R/2+k-4][((R/4)+4)]=vacio[k];}
    ////////////

    // Se define el multiplicador
    multiplicador=(1+(float(npiedras+nvelocidad-nalimento*2)/10));
    if(multiplicador>0){}
    else{multiplicador=0;}

    multi_entero=(int)multiplicador;
    multi_decimal=(int)(multiplicador*10)%10;

    for(k=0;k<(int)strlen(multi);k++){cuadricula[R/2+k-8][((R/4)+9)]=multi[k];}
    cuadricula[R/2-8+strlen(multi)][((R/4)+9)]=char(multi_entero+48);
    cuadricula[R/2-7+strlen(multi)][((R/4)+9)]=char(46);
    cuadricula[R/2-6+strlen(multi)][((R/4)+9)]=char(multi_decimal+48);
    ////////////////////

    dibujar(); //Se dibuja todo lo definido anteriormente

    //Se evalua la entrada del usuario
    salir=getch();
    if(salir=='w'&&eleccion!=-6){eleccion=eleccion-6;}
    if(salir=='s'&&eleccion!=6){eleccion=eleccion+6;}
    if(salir=='d'){if(eleccion==-6&&npiedras!=n_max_piedras){npiedras++;}
                   if(eleccion==0&&nvelocidad!=n_max_velocidad){nvelocidad++;}
                   if(eleccion==6&&nalimento!=n_max_alimento){nalimento++;}}
    if(salir=='a'){if(eleccion==-6&&npiedras!=0){npiedras--;}
                   if(eleccion==0&&nvelocidad!=0){nvelocidad--;}
                   if(eleccion==6&&nalimento!=0){nalimento--;}}
    ///////////////////////

    }while(salir!='\r'); //Si el usuario presiona el enter se vuelve al menu principal

    definirmatriz();

    return menu();

    }

    void alimento1(int x,int y){
         int generar=0;
         int eleccion_tipo;
         int i=0,k=0,distancia;

         // Evaluacion
         if(x_alimento1==-1){generar=1;} //Si x_alimento1 toma este valor significa que nunca se a inializado la comida, asique se genera aleatoriamente la primer comida
         else if ((x==x_alimento1||x+1==x_alimento1)&&y==y_alimento1){generar=1;
                                                                      largo=largo+1*tipo_alimento1;}//Evalua si la posicion de la comida es la misma que la posicion actual, lo que significaria que la comida acaba de ser comida
         else {generar=0;
               cuadricula[x_alimento1][y_alimento1]=char(254);} //Si no se cumplen ninguna de las dos condiciones anteriores no se crea nuevo alimento y se sigue generando el actual
         //////////////////////

         // Nuevo alimento
         if(generar==1){
                    // Genera el alimento de forma aleatoria
                    do{
                            x_alimento1= distribucion(gen);
                            if(x_alimento1%2==0){x_alimento1++;}
                            y_alimento1= (int)distribucion(gen)/2;
                    }while(cuadricula[x_alimento1][y_alimento1]!=char(32)||cuadricula[x_alimento1-1][y_alimento1]!=char(32));
                    ////////////////

                    // Elige al azar (con cierta probabilidad pre-establecida) el tipo de alimento
                    eleccion_tipo=distribucion_alimento(gen);
                if(eleccion_tipo<probabilidad_tipo1){
                    tipo_alimento1=1;
                    cuadricula[x_alimento1][y_alimento1]=char(254);}

                else{tipo_alimento1=2;
                     cuadricula[x_alimento1][y_alimento1]=char(220);}}
                    ///////////////
          //////////////////////////////////////////////
          // Si el alimento no fue comido
          if(generar==0){

                if(tipo_alimento1==1){ //Evalua si es del tipo 1
                    cuadricula[x_alimento1][y_alimento1]=char(254); //Sigue definiendo el lugar de la comida actual

                }else{ //Caso contrario es del tipo 2
                    distancia=abs(x-x_alimento1)+abs(y-y_alimento1); //Evalua la distancia de la cabeza de la vivora con respecto a la comida
           if(distancia<10){ //Si esta muy cerca la comida se mueve de forma aleatoria, con el objetivo de alejarse de la vivora
               cuadricula[x_alimento1][y_alimento1]=char(32); //Como el alimento se va a mover se borra su posicion actual antes de actualizar su nueva posicion

               do{ //Se inicia el bucle de la generacion de posicion
               switch(distribuciongus(gen)){ //Se genera un numero del 1 al 4 para determinar a que posicion se va a mover
               case 1: // Si se genero el 1 el alimento se va a mover hacia arriba
                if(cuadricula[x_alimento1][y_alimento1+1]==char(32)){ //Evalua si posicion a donde se quiere mover esta libre, si es asi se sigue con la ejecucion, caso contrario se vuelve a generar un nuevo numero
                    i=1;
                    y_alimento1++;
                if(abs(x-x_alimento1)+abs(y-y_alimento1)<distancia){ //Si la posicion esta libre se evalua si esta nueva posicion hace que el alimento se acerque a la vivora, si es asi se vuelve a generar una nueva comida, esto puede suceder un maximo de 3 veces
                    i=0;
                    y_alimento1--;
                    k++;
                }}
                break;
               case 2:
                if(cuadricula[x_alimento1][y_alimento1-1]==char(32)){
                    i=1;
                    y_alimento1--;
                if(abs(x-x_alimento1)+abs(y-y_alimento1)<distancia){
                    i=0;
                    y_alimento1++;
                    k++;
                }}
                break;
               case 3:
                if(cuadricula[x_alimento1+1][y_alimento1]==char(32)&&x_alimento1+1!=R-3){
                    i=1;
                    x_alimento1++;
                if(abs(x-x_alimento1)+abs(y-y_alimento1)<distancia){
                    i=0;
                    x_alimento1--;
                    k++;
                }}
                break;
               case 4:
                if(cuadricula[x_alimento1-1][y_alimento1]==char(32)&&x_alimento1-1!=R-3){
                    i=1;
                    x_alimento1--;
                if(abs(x-x_alimento1)+abs(y-y_alimento1)<distancia){
                    i=0;
                    x_alimento1++;
                    k++;
                }}
                break;
               }
               }while(!(i==1||k==3));
           }
            cuadricula[x_alimento1][y_alimento1]=char(220);}} //Si esta un poco lejos el alimento no se mueve
          ///////////////////////////////////////////
          }

    void alimento2(int x,int y){
         int generar=0;
         int eleccion_tipo;
         int i=0,k=0,distancia;

         // Evaluacion
         if(x_alimento2==-1){generar=1;} //Si x_alimento1 toma este valor significa que nunca se a inializado la comida, asique se genera aleatoriamente la primer comida
         else if ((x==x_alimento2||x+1==x_alimento2)&&y==y_alimento2){generar=1;
                                                                      largo=largo+1*tipo_alimento2;}//Evalua si la posicion de la comida es la misma que la posicion actual, lo que significaria que la comida acaba de ser comida
         else {generar=0;
               cuadricula[x_alimento2][y_alimento2]=char(254);} //Si no se cumplen ninguna de las dos condiciones anteriores no se crea nuevo alimento y se sigue generando el actual
         //////////////////////

         // Nuevo alimento
         if(generar==1){
                    // Genera el alimento de forma aleatoria
                    do{
                            x_alimento2= distribucion(gen);
                            if(x_alimento2%2==0){x_alimento2++;}
                            y_alimento2= (int)distribucion(gen)/2;
                    }while(cuadricula[x_alimento2][y_alimento2]!=char(32)||cuadricula[x_alimento2-1][y_alimento2]!=char(32));
                    ////////////////

                    // Elige al azar (con cierta probabilidad pre-establecida) el tipo de alimento
                    eleccion_tipo=distribucion_alimento(gen);
                if(eleccion_tipo<probabilidad_tipo1){
                    tipo_alimento2=1;
                    cuadricula[x_alimento2][y_alimento2]=char(254);}

                else{tipo_alimento2=2;
                     cuadricula[x_alimento2][y_alimento2]=char(220);}}
                    ///////////////
          //////////////////////////////////////////////
          // Si el alimento no fue comido
          if(generar==0){

                if(tipo_alimento2==1){ //Evalua si es del tipo 1
                    cuadricula[x_alimento2][y_alimento2]=char(254); //Sigue definiendo el lugar de la comida actual

                }else{ //Caso contrario es del tipo 2
                    distancia=abs(x-x_alimento2)+abs(y-y_alimento2); //Evalua la distancia de la cabeza de la vivora con respecto a la comida
           if(distancia<10){ //Si esta muy cerca la comida se mueve de forma aleatoria, con el objetivo de alejarse de la vivora
               cuadricula[x_alimento2][y_alimento2]=char(32); //Como el alimento se va a mover se borra su posicion actual antes de actualizar su nueva posicion

               do{ //Se inicia el bucle de la generacion de posicion
               switch(distribuciongus(gen)){ //Se genera un numero del 1 al 4 para determinar a que posicion se va a mover
               case 1: // Si se genero el 1 el alimento se va a mover hacia arriba
                if(cuadricula[x_alimento2][y_alimento2+1]==char(32)){ //Evalua si posicion a donde se quiere mover esta libre, si es asi se sigue con la ejecucion, caso contrario se vuelve a generar un nuevo numero
                    i=1;
                    y_alimento2++;
                if(abs(x-x_alimento2)+abs(y-y_alimento2)<distancia){ //Si la posicion esta libre se evalua si esta nueva posicion hace que el alimento se acerque a la vivora, si es asi se vuelve a generar una nueva comida, esto puede suceder un maximo de 3 veces
                    i=0;
                    y_alimento2--;
                    k++;
                }}
                break;
               case 2:
                if(cuadricula[x_alimento2][y_alimento2-1]==char(32)){
                    i=1;
                    y_alimento2--;
                if(abs(x-x_alimento2)+abs(y-y_alimento2)<distancia){
                    i=0;
                    y_alimento2++;
                    k++;
                }}
                break;
               case 3:
                if(cuadricula[x_alimento2+1][y_alimento2]==char(32)&&x_alimento2+1!=R-3){
                    i=1;
                    x_alimento2++;
                if(abs(x-x_alimento2)+abs(y-y_alimento2)<distancia){
                    i=0;
                    x_alimento2--;
                    k++;
                }}
                break;
               case 4:
                if(cuadricula[x_alimento2-1][y_alimento2]==char(32)&&x_alimento2-1!=R-3){
                    i=1;
                    x_alimento2--;
                if(abs(x-x_alimento2)+abs(y-y_alimento2)<distancia){
                    i=0;
                    x_alimento2++;
                    k++;
                }}
                break;
               }
               }while(!(i==1||k==3));
           }
            cuadricula[x_alimento2][y_alimento2]=char(220);}} //Si esta un poco lejos el alimento no se mueve
          ///////////////////////////////////////////
          }

    void alimento3(int x,int y){
         int generar=0;
         int eleccion_tipo;
         int i=0,k=0,distancia;

         // Evaluacion
         if(x_alimento3==-1){generar=1;} //Si x_alimento1 toma este valor significa que nunca se a inializado la comida, asique se genera aleatoriamente la primer comida
         else if ((x==x_alimento3||x+1==x_alimento3)&&y==y_alimento3){generar=1;
                                                                      largo=largo+1*tipo_alimento3;}//Evalua si la posicion de la comida es la misma que la posicion actual, lo que significaria que la comida acaba de ser comida
         else {generar=0;
               cuadricula[x_alimento3][y_alimento3]=char(254);} //Si no se cumplen ninguna de las dos condiciones anteriores no se crea nuevo alimento y se sigue generando el actual
         //////////////////////

         // Nuevo alimento
         if(generar==1){
                    // Genera el alimento de forma aleatoria
                    do{
                            x_alimento3= distribucion(gen);
                            if(x_alimento3%2==0){x_alimento3++;}
                            y_alimento3= (int)distribucion(gen)/2;
                    }while(cuadricula[x_alimento3][y_alimento3]!=char(32)||cuadricula[x_alimento3-1][y_alimento3]!=char(32));
                    ////////////////

                    // Elige al azar (con cierta probabilidad pre-establecida) el tipo de alimento
                    eleccion_tipo=distribucion_alimento(gen);
                if(eleccion_tipo<probabilidad_tipo1){
                    tipo_alimento3=1;
                    cuadricula[x_alimento3][y_alimento3]=char(254);}

                else{tipo_alimento3=2;
                     cuadricula[x_alimento3][y_alimento3]=char(220);}}
                    ///////////////
          //////////////////////////////////////////////
          // Si el alimento no fue comido
          if(generar==0){

                if(tipo_alimento3==1){ //Evalua si es del tipo 1
                    cuadricula[x_alimento3][y_alimento3]=char(254); //Sigue definiendo el lugar de la comida actual

                }else{ //Caso contrario es del tipo 2
                    distancia=abs(x-x_alimento3)+abs(y-y_alimento3); //Evalua la distancia de la cabeza de la vivora con respecto a la comida
           if(distancia<10){ //Si esta muy cerca la comida se mueve de forma aleatoria, con el objetivo de alejarse de la vivora
               cuadricula[x_alimento3][y_alimento3]=char(32); //Como el alimento se va a mover se borra su posicion actual antes de actualizar su nueva posicion

               do{ //Se inicia el bucle de la generacion de posicion
               switch(distribuciongus(gen)){ //Se genera un numero del 1 al 4 para determinar a que posicion se va a mover
               case 1: // Si se genero el 1 el alimento se va a mover hacia arriba
                if(cuadricula[x_alimento3][y_alimento3+1]==char(32)){ //Evalua si posicion a donde se quiere mover esta libre, si es asi se sigue con la ejecucion, caso contrario se vuelve a generar un nuevo numero
                    i=1;
                    y_alimento3++;
                if(abs(x-x_alimento3)+abs(y-y_alimento3)<distancia){ //Si la posicion esta libre se evalua si esta nueva posicion hace que el alimento se acerque a la vivora, si es asi se vuelve a generar una nueva comida, esto puede suceder un maximo de 3 veces
                    i=0;
                    y_alimento3--;
                    k++;
                }}
                break;
               case 2:
                if(cuadricula[x_alimento3][y_alimento3-1]==char(32)){
                    i=1;
                    y_alimento3--;
                if(abs(x-x_alimento3)+abs(y-y_alimento3)<distancia){
                    i=0;
                    y_alimento3++;
                    k++;
                }}
                break;
               case 3:
                if(cuadricula[x_alimento3+1][y_alimento3]==char(32)&&x_alimento3+1!=R-3){
                    i=1;
                    x_alimento3++;
                if(abs(x-x_alimento3)+abs(y-y_alimento3)<distancia){
                    i=0;
                    x_alimento3--;
                    k++;
                }}
                break;
               case 4:
                if(cuadricula[x_alimento3-1][y_alimento3]==char(32)&&x_alimento3-1!=R-3){
                    i=1;
                    x_alimento3--;
                if(abs(x-x_alimento3)+abs(y-y_alimento3)<distancia){
                    i=0;
                    x_alimento3++;
                    k++;
                }}
                break;
               }
               }while(!(i==1||k==3));
           }
            cuadricula[x_alimento3][y_alimento3]=char(220);}} //Si esta un poco lejos el alimento no se mueve
          ///////////////////////////////////////////
    }
    void alimento4(int x,int y){}
    void alimento5(int x,int y){}
    void alimento6(int x,int y){}
    void alimento7(int x,int y){}
    void alimento8(int x,int y){}

    void bienvenido_V2(){

    int x=R/2,y=R/4;//Centro de la pantalla
    int i,k,salida=0,e=0,busqueda=1,encontrado=0;
    char r;
    char text_bienvenido[]="Bienvenido";
    char text_ingrese[]="Ingrese su nombre de usuario";
    char text_noencontrado[]="Usuario no encontrado";
    char text_encontrado[]="Usuario encontrado";
    char text_agregar[]="Agregar usuario";
    char text_volver[]="Volver a escribir";
    char text_agregado[]="Usuario agregado";

    char text_config_default[]="0000000000";
    // Arreglo de caracteres que guarda el valor de la configuracion del usuario
    //text_config_default[0] --> nvelocidad
    //text_config_default[1] --> npiedras
    //text_config_default[2] --> ncomida
    //text_config_default[3] --> n_max_velocidad
    //text_config_default[4] --> n_max_piedras
    //text_config_default[5] --> n_max_comida
    //text_config_default[6] --> multiplicador_adiccional
    //text_config_default[7] --> vacio
    //text_config_default[8] --> vacio
    //text_config_default[0] --> vacio

    FILE *pusuarios;
    do{ //Se inicia el bucle de ingreso de usuario
    for(i=0;i<H;i++){nombre[i]='\0';}
    salida=0;
    e=0;
    busqueda=1;
    encontrado=0;

    // Definir cuadro de bienvenido

    definirmatriz();
    definircuadro(19,6);
    for(i=0;i<(int)strlen(text_bienvenido);i++){cuadricula[x+i-5][y-4]=text_bienvenido[i];}
    for(i=0;i<(int)strlen(text_ingrese);i++){cuadricula[x+i-14][y-2]=text_ingrese[i];}
    dibujar();
    ///////////////////////////////


    // Ingreso del nombre de usuario
    k=0;
    do{
        nombre[k]=getch(); //Se toma la tecla apretada por el usuario

        if(nombre[k]=='\r'){nombre[k]='\0'; //Si la entrada es un "enter" se termina el bucle
                             salida=1;}
        else if ((int)nombre[k]==8&&k!=0){nombre[k]='\0'; //Si la entrada es un "retroceso" se define la entrada actual y la anterior como caracteres nulos, a menos que no haya nada escrito
                                     k--;
                                     nombre[k]='\0';
                                     k--;
                                     definircuadro(19,6);
                                     for(i=0;i<(int)strlen(text_bienvenido);i++){cuadricula[x+i-5][y-4]=text_bienvenido[i];}
                                     for(i=0;i<(int)strlen(text_ingrese);i++){cuadricula[x+i-14][y-2]=text_ingrese[i];}}

        if (!((int)nombre[k]==8&&k==0)){for(i=0;i<(int)strlen(nombre);i++){cuadricula[x+i-1-int(k/2)][y]=nombre[i];} //Se escribe la tecla ingresada a menos que se haya apretado el retroceso y no habia nada escrito.
                                         k++;}

        dibujar();
    }while(salida==0&&k<H-1);
    ///////////////////////////////

    // Se busca el nombre ingresado en el archivo de usuarios existentes
        pusuarios=fopen("base_usuarios.txt","r");
        int n= sizeof(base_usuarios); //Tamaño de un elemento
        fseek(pusuarios,0,SEEK_END); //Coloca el cursor en el final del archivo
        int m=ftell(pusuarios); //Tamaño total de archivo
        int p=m/n; //Cantidad de elementos en el archivo
        base_usuarios *datos_usuario=(base_usuarios*)malloc(p*n); //Reserva la memoria del tamaño del archivo con la estructura "base_usuarios"
        fseek(pusuarios,0,SEEK_SET); //Coloca el curso al inicio del archivo
        fread(datos_usuario,n,p,pusuarios); //Lee todo el archivo y lo guarda en la memoria reservada
        fclose(pusuarios); //Una vez leido el archivo se lo cierra


    i=0;
    do{
            busqueda=strcmp(datos_usuario[i].nombre,nombre); //Se busca el usuario ingresado dentro de la base de usuarios

        if(busqueda==0){ //Si se encuentra el nombre se da aviso al usuario y se almacena la configuracion
            ubicacion_usuario=i;
            //Se guarda la configuracion
            strcpy(configuracion,datos_usuario[i].configuracion);
            banco=datos_usuario[i].banco;

            nvelocidad=(int)configuracion[0]-48;
            npiedras=(int)configuracion[1]-48;
            nalimento=(int)configuracion[2]-48;
            n_max_velocidad=(int)configuracion[3]-48;
            n_max_piedras=(int)configuracion[4]-48;
            n_max_alimento=(int)configuracion[5]-48;

            for(i=0;i<(int)strlen(text_encontrado);i++){cuadricula[x+i-9][y+2]=text_encontrado[i];} //Se escribe el texto en pantalla que se encontro el usuario
            encontrado=1;
            e=2;

            dibujar();
            Sleep(2000);}

            i++;
        }while(ubicacion_usuario!=-1&&i<p);



        if(encontrado==0){ //Si no se encuetra el nombre ingresado:
            ubicacion_usuario=i-1;
            for(i=0;i<(int)strlen(text_noencontrado);i++){cuadricula[x+i-10][y+2]=text_noencontrado[i];} //Se escribe el texto en pantalla que no se encontro el usuario
            dibujar();

            do{
            definircuadro(19,6);

            if(e==0){definircuadro2(8,1,4,-9);}
            if(e==1){definircuadro2(9,1,4,9);}

            for(i=0;i<(int)strlen(text_volver);i++){cuadricula[x+i+1][y+4]=text_volver[i];}
            for(i=0;i<(int)strlen(text_agregar);i++){cuadricula[x+i-16][y+4]=text_agregar[i];}
            for(i=0;i<(int)strlen(text_bienvenido);i++){cuadricula[x+i-5][y-4]=text_bienvenido[i];}
            for(i=0;i<(int)strlen(text_ingrese);i++){cuadricula[x+i-14][y-2]=text_ingrese[i];}
            for(i=0;i<(int)strlen(text_noencontrado);i++){cuadricula[x+i-10][y+2]=text_noencontrado[i];}
            k=strlen(nombre);
            for(i=0;i<k;i++){cuadricula[x+i-1-int(k/2)][y]=nombre[i];}

            dibujar();
            r=getch();
            if(r=='d'&&e==0){e++;}
            else if (r=='a'&&e==1){e--;}
            }while(r!='\r');
            }

    }while(e==1); //Si se elige "volver a escribir" se repite el bucle de inicio de usuario
    if(e==0){ //Si se elige "Agregar usuario" se va agregar el usuario en el archivo de usuarios existentes
    pusuarios=fopen("base_usuarios.txt","a"); //Se abre el archivo en modo escritura
    base_usuarios usuario_datos;
    strcpy(usuario_datos.nombre,nombre);
    usuario_datos.banco=0;
    if(strcmp(usuario_datos.nombre,"Admin")==0){usuario_datos.banco=100000;banco=100000;cout << "Es admin" ; Sleep(1000);}

    strcpy(usuario_datos.configuracion,text_config_default);

    fwrite(&usuario_datos,sizeof (base_usuarios),1,pusuarios);
    fclose(pusuarios);

    definircuadro(19,6);

            for(i=0;i<(int)strlen(text_agregado);i++){cuadricula[x+i-8][y+3]=text_agregado[i];}
            for(i=0;i<(int)strlen(text_ingrese);i++){cuadricula[x+i-14][y-2]=text_ingrese[i];}
            for(i=0;i<(int)strlen(text_bienvenido);i++){cuadricula[x+i-5][y-4]=text_bienvenido[i];}
            k=strlen(nombre);
            for(i=0;i<k;i++){cuadricula[x+i-1-int(k/2)][y]=nombre[i];}

            dibujar();
    Sleep(3000);
    //////////////////////////////
    }


}

};

int main()
{
    // Se declaran las variables que se van a utiliziar en el desarrollo del programa
    int x,y,i;
    char r=' ',v;
    /////////

    vivora vivora1; //Se inicializa el objeto de la clase


    // Fijar tamaño de la pantalla
    {

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD newSize;
    newSize.X = 30; // Número de columnas
    newSize.Y = 25;  // Número de filas

    SetConsoleScreenBufferSize(console, newSize);

    ////////////
}

    vivora1.bienvenido_V2(); // Se da la bienvenida y se pide el nombre de usuario

    do{  //Bucle que da inicio al menu del juego

    vivora1.definirmatriz(); // Se definen los contornos y se limpia la pantalla

    if(vivora1.menu()==4){vivora1.guardar_config();
                          return 4;} // Se muestra el menu, se evalua que opcion eligio el usuario

    do{ //Se inicia el bucle de juego

    if(r==' '){r='d';  //Si es la primera vez que se inicia el juego o acaba de reiniciar luego de un gameover se establecen los parametros iniciales
               v='S';
               vivora1.reiniciar();
               x=(int)R/2;
               y=(int)R/4;
               vivora1.posicionvieja(x,y);
               vivora1.genpiedras(1+npiedras,1+npiedras/2);
               x_alimento1=-1;
               x_alimento2=-1;
               x_alimento3=-1;
               x_alimento4=-1;
               x_alimento5=-1;
               x_alimento6=-1;
               x_alimento7=-1;
               x_alimento8=-1;}


    // Definir posicion
    {
        cuadricula[x][y]=char(219);
        cuadricula[x+1][y]=char(219);
    }



    //vivora1.comida(x,y);
    //vivora1.gusano(x,y);
    for(i=0;i<nalimento+1;i++){
    switch(i){
        case 0:
        vivora1.alimento1(x,y);
        break;
        case 1:
        vivora1.alimento2(x,y);
        break;
        case 2:
        vivora1.alimento3(x,y);
        break;
        case 3:
        vivora1.alimento4(x,y);
        break;
        case 4:
        vivora1.alimento5(x,y);
        break;
        case 5:
        vivora1.alimento6(x,y);
        break;
        case 6:
        vivora1.alimento7(x,y);
        break;
        case 7:
        vivora1.alimento8(x,y);
        break;}}

    vivora1.dibujar();
    cout << "Usuario: "<< nombre << " Puntaje: " << ((vivora1.devolverlargo())-2)*multiplicador*50 << "    Multiplicador x" << multiplicador;



    // Definir posicion

            char m='l'; //Variable que solo sirve para comparar la tecla apretada con la tecla apretada anterior
            Sleep(200-20*nvelocidad); // Velocidad
            if (kbhit()!=0){  // Verifica si se ha presionado una tecla
                m=getch();

            if ((m=='w'&&r=='s')||(m=='a'&&r=='d')||(m=='d'&&r=='a')||(m=='s'&&r=='w')){} //Si se quiere hacer un movimiento inverso al anterior no se guarda ningun cambio
            else{r = m; // Obtiene la tecla presionada
            }}

            if(r=='w')
                y--;
            else if (r=='s')
                y++;
            else if (r=='a')
                x=x-2;
            else if (r=='d')
                x=x+2;


                if((cuadricula[x][y]==char(32)||cuadricula[x][y]==char(254)||cuadricula[x][y]==char(220))&&(cuadricula[x+1][y]==char(32)||cuadricula[x+1][y]==char(254)||cuadricula[x+1][y]==char(220))){}// Se verifica si en la posicion actual hay alguna estructura que no sea comida, si es asi game over
                 else {
                    vivora1.gameover();
                    r=' ';
                    }

    vivora1.posicionvieja(x,y);

        }while(r!=' ');
        }while(v!='N');



    return 0;
}
