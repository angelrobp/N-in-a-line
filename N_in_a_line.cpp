/* 
* File:   N_in_a_line.cpp
* Author: angelrobp
* Email: info@angelrobledillo.net
*
* 					GNU GENERAL PUBLIC LICENSE
*                     			   Version 2, June 1991
*
*			Copyright (C) 1989, 1991 Free Software Foundation, Inc., <http://fsf.org/>
*			51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*			Everyone is permitted to copy and distribute verbatim copies
*			of this license document, but changing it is not allowed.
*	
*			....................Read more in LICENCE file...............................
* 
*/

#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

//Variables globales
const int DIM_FIL=10, DIM_COL=10, DIM_JUGADOR=10;

/*
*@brief Función que cambia de jugador a cada turno.
*@param ficha, Tipo de ficha de cada jugador.(E/S)
*@pre Se debe comprobar que el jugador actual ya ha terminado su turno.
*/
void cambiarjugador(char &ficha){

	if (ficha =='X'){

		ficha='O';

	} else if (ficha =='O'){

		ficha='X';
	}
	
}

/*
*@brief Función de tipo booleano que comprueba si queda espacios en el tablero.
*@param m, tablero del juego.(E)
*@param util_fil, número de filas utilizadas.(E)
*@param util_col, número de columnas utilizadas.(E)
*@return espacio, true si hay espacio y false si no lo hay.
*/
bool comprobarespaciotablero(const char m[][DIM_COL], int util_fil, int util_col){

	int contador=0;
	bool espacio=true;

	for (int f=0; f<util_fil; f++){
		for (int c=0; c<util_col; c++){

			if(m[f][c]==' '){

				contador++;
			}
		}
	}
	
	if (contador == 0){

		espacio=false;
	}
return espacio;
}	

/*
*@brief Función de tipo booleano que comprueba si queda espacios en la columna en la que se desea insertar ficha.
*@param m, tablero del juego.(E)
*@param util_fil, número de filas utilizadas.(E)
*@param c, columna en la que se desea insertar ficha.(E)
*@pre se necesita saber la columna deseada.
*@return espacio, true si hay espacio y false si no lo hay.
*/
bool comprobarespaciocolumna(const char m[][DIM_COL], int util_fil, int c){

	int contador=0;
	bool espacio=false;

	for (int f=util_fil-1; (f >= 0); f=f-1){
		
		if (m[f][c]==' '){
	
			contador++;
		}
	}

	if (contador != 0){

		espacio=true;
	}

return espacio;			
}

/*
*@brief Función que inserta la ficha en la columna deseada.
*@param m, tablero del juego.(E)
*@param util_fil, número de filas utilizadas.(E)
*@param ficha, Tipo de ficha de cada jugador.(E)
*@param f, fila en la que se ha insertado la ficha.(E)
*@param c, columna en la que se desea insertar ficha.(E)
*@pre comprobar que hay espacio en el tablero y en la columna.
*/

void insertarficha(char m[][DIM_COL], int util_fil, char ficha, int &f, int &c){

	bool fin=false;
	
	for (int f1 =util_fil-1; ((f1 >= 0)&&(fin == false)); --f1){

		if (m[f1][c]==' '){

			m[f1][c]=ficha;

			fin=true;
			f = f1;
		}
	}
}

/*
*@brief Función que imprime el tablero por pantalla y las fichas en ese momento ya introducidas.
*@param m, tablero del juego.(E)
*@param util_fil, número de filas utilizadas.(E)
*@param util_col, número de columnas utilizadas.(E)
*/

void imprimetablero(const char m[][DIM_COL], int util_col, int util_fil){


	cout << "    ";

	for (int c=0; c<util_col; c++){
	
		std::cout << "\033[1;"<<34<< "m^ \033[0m";
	}
	

	for (int f=0; f<util_fil; f++){

		cout << endl;
		std::cout << "\033[1;"<<34<< "m"<< f <<" < \033[0m";

		for (int c=0; c<util_col; c++){

			if (m[f][c]=='X'){
	
				std::cout << "\033[1;"<<31<< "m"<< m[f][c] << " \033[0m";

			}else {

				std::cout << "\033[1;"<<33<< "m"<< m[f][c] << " \033[0m";
			}
		}
		std::cout <<"\033[1;"<<34 << "m> \033[0m";
	}
	cout << endl;
	cout << "    ";

	for (int c=0; c<util_col; c++){
	
		std::cout << "\033[1;"<<34 << "mv \033[0m";
	}
	cout << endl;
	cout << "    ";

	for (int c=0; c<util_col; c++){
	
		std::cout << "\033[1;"<<34<< "m"<< c <<" \033[0m";
	}
	cout << endl;
}

/*
*@brief Función de tipo booleano que comprueba si hay n en raya en la horizontal.
*@param m, tablero del juego.(E)
*@param util_fil, número de filas utilizadas.(E)
*@param util_col, número de columnas utilizadas.(E)
*@param n, número de fichas en raya necesarias para ganar.(E)
*@param ficha, Tipo de ficha de cada jugador.(E)
*@param f, fila en la que se ha insertado la ficha.(E)
*@param c, columna en la que se desea insertar ficha.(E)
*@return ganador, true si hay n en raya y false si no lo hay.
*/
bool comprobarhorizontal(const char m[][DIM_COL], int util_fil, int util_col, int n, int f, int c, char ficha){

	bool ganador=false;
	int acuh=0;
	
	for (int i=0; ((i<=util_col-1) && (ganador == false)); i++){ //comprueba fila horizontal

		if (m[f][i] == ficha){

			acuh++;

		}else{
			acuh=0;
		}
		if (acuh>=n){
			
			ganador=true;
		}		
	}
return ganador;	
}

/*
*@brief Función de tipo booleano que comprueba si hay n en raya en la vertical.
*@param m, tablero del juego.(E)
*@param util_fil, número de filas utilizadas.(E)
*@param util_col, número de columnas utilizadas.(E)
*@param n, número de fichas en raya necesarias para ganar.(E)
*@param ficha, Tipo de ficha de cada jugador.(E)
*@param f, fila en la que se ha insertado la ficha.(E)
*@param c, columna en la que se desea insertar ficha.(E)
*@return ganador, true si hay n en raya y false si no lo hay.
*/
bool comprobarvertical(const char m[][DIM_COL], int util_fil, int util_col, int n, int f, int c, char ficha){

	bool ganador=false;
	int acuv=0;

	for (int i=0; ((i<util_fil) && (ganador == false)); i++){ //comprueba fila vertical

		if (m[i][c] == ficha){
			
			acuv++;
	
		} else{
			acuv=0;
		}
		if (acuv>=n){
			
			ganador=true;
		}
	}
return ganador;	
}

/*
*@brief Función de tipo booleano que comprueba si hay n en raya en la diagonal.
*@param m, tablero del juego.(E)
*@param util_fil, número de filas utilizadas.(E)
*@param util_col, número de columnas utilizadas.(E)
*@param n, número de fichas en raya necesarias para ganar.(E)
*@param ficha, Tipo de ficha de cada jugador.(E)
*@param f, fila en la que se ha insertado la ficha.(E)
*@param c, columna en la que se desea insertar ficha.(E)
*@return ganador, true si hay n en raya y false si no lo hay.
*/
bool comprobardiagonal(const char m[][DIM_COL], int util_fil, int util_col, int n, int f, int c, char ficha){

	bool ganador=false, fin=false;
	int acud=0;
	int j=c;

	for (int i=f; ((i>=0) && (fin==false) && (j>=0)); i--) { //Comprueba fila diagonal creciente de der a izq

		if (m[i][j] == ficha){

			acud++; 
			j--;

		}else {
			fin=true;
		}
	}

	fin=false;
	j=c+1;
	for (int i=f+1; ((i<util_fil) && (fin == false) && (j<util_col)); i++) { //Comprueba fila diagonal decreciente de izq a der

		if (m[i][j] == ficha){

			acud++; 
			j++;

		}else {
			fin=true;
		}
	} cout << "ACUD: " <<acud<<endl;

	if (acud>=n){

		ganador=true;
	}

	fin=false;
	acud=0;
	j=c;
	for (int i=f; ((i<util_fil) && (fin==false) && (j>=0)); i++) { //Comprueba fila diagonal decreciente de der a izq

		if (m[i][j] == ficha){

			acud++; 
			j--;

		}else {
			fin=true;
		}
	}

	fin=false;
	j=c+1;
	for (int i=f-1; ((i>=0) && (fin == false) && (j<util_col)); i--) { //Comprueba fila diagonal creciente de izq a der

		if (m[i][j] == ficha){

			acud++; 
			j++;

		}else {
			fin=true;
		}
	} cout << "ACUD: " <<acud<<endl;

	if (acud>=n){

		ganador=true;
	}


return ganador;	
}

/*
*@brief Función que pide al usuario la columna en la que desea insertar ficha, avisa de los turnos y del ganador.
*@param m, tablero del juego.(E)
*@param util_fil, número de filas utilizadas.(E)
*@param util_col, número de columnas utilizadas.(E)
*@param jugador1, nombre del jugador 1.(E)
*@param jugador2, nombre del jugador 2.(E)
*@param n, número de fichas en raya necesarias para ganar.(E)
*@pre comprobar si todavia no hay un ganador
*/
void juego(char m[][DIM_COL], int util_col, int util_fil, const char jugador1[], const char jugador2[], int n){
	
	bool ganador=false,vertical=false, horizontal=false, diagonal=false;
	int f, c;
	bool espacio=false, espaciocolumna=false, espaciotablero=true;
	char ficha='O';

	system("clear");//esto borra la pantalla
	do{

		cambiarjugador(ficha);
		do{
			system("clear");
			cout << espaciotablero << endl;
			imprimetablero (m, util_col, util_fil);

			espacio=false;

			if (ficha=='X'){

			cout << "\n"<< "\033[1;"<<31<<"mTurno de " << jugador1 << ". ¿En que columna deseas insertar la ficha X?\033[0m"<<std::endl;
			} else if (ficha=='O') {

			cout << "\n"<< "\033[1;"<<33<<"mTurno de " << jugador2 << ". ¿En que columna deseas insertar la ficha O?\033[0m"<<std::endl;
			}
			espaciotablero=comprobarespaciotablero(m, util_fil, util_col);
			
			if (espaciotablero==true){
		
				cin >> c;
			}

			espaciocolumna=comprobarespaciocolumna(m, util_fil, c);

			cout << espaciotablero << endl;
	
			if (espaciocolumna==true){

				espacio=true;		
			} else if (espaciotablero==false){
		
				espacio=true;
			}

		}while ((espacio==false) || (c<0) || (c>util_col-1));

		if (espaciotablero!=false){

			insertarficha(m, util_fil, ficha, f, c);

			vertical=comprobarvertical(m, util_fil, util_col, n, f, c, ficha);
			horizontal=comprobarhorizontal(m, util_fil, util_col, n, f, c, ficha);		
			diagonal=comprobardiagonal(m, util_fil, util_col, n, f, c, ficha);
	
			if (vertical==true || horizontal==true || diagonal==true){

				ganador=true;
			}
		}
		
	}while(ganador!=true && espaciotablero!=false);
	
	system("clear");

	if (espaciotablero!=false){
	
		if(ficha=='X'){

			cout << "\n"<< "\033[1;"<<31<<"m¡¡"<< jugador1 << " GANA!!\033[0m"<<std::endl;

		}else if(ficha=='O'){

			cout << "\n"<< "\033[1;"<<33<<"m¡¡"<< jugador2 << " GANA!!\033[0m"<<std::endl;
		}
	}else {
		std::cout << "\n"<< "\033[1;"<<37<<"m¡¡EMPATE!!\033[0m"<<std::endl;
	}
	
	imprimetablero (m, util_col, util_fil);
}

int main(){

	char m[DIM_FIL][DIM_COL];
	int util_fil=0, util_col=0;
	char jugador1[DIM_JUGADOR], jugador2[DIM_JUGADOR];
	int n;

	cout << "\n "<< "\033[1;"<<36<<"m¡¡Bienvenido a -N EN RAYA-!!\033[0m"<<std::endl;

	cout << "\n" << "\033[1;"<<31<< "mIntroduzca el nombre del jugador 1: \033[0m"<<std::endl;
		cin.getline(jugador1,10);
	system("clear");

	cout << "\n" << "\033[1;"<<33<< "mIntroduzca el nombre del jugador 2: \033[0m"<<std::endl;
		cin.getline(jugador2,10);
	
	do{	
		system("clear");	
 		cout << "Por favor, introduzca el modo de juego: "<<endl;
		cin >> n;

	} while(n<3);

	do{
		system("clear");
		cout << "\nIntroduzca el numero de filas: ";
		cin >>util_fil;
	}while(util_fil < n+2 || (util_fil > DIM_FIL);

	do{
		system("clear");
		cout << "\nIntroduzca el numero de columnas: ";
		cin >>util_col;

	}while (util_col < n+2 || (util_col > DIM_COL);


	for (int f=0; f<util_fil; f++){
		for (int c=0; c<util_col; c++){

			m[f][c]=' ';
		}
	}
	cout << endl;

	juego (m, util_col, util_fil, jugador1, jugador2, n);
}
