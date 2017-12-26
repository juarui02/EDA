//Grupo007, Juan Ruiz Jiménez y Javier Cordero Calvo
//A través del algoritmo de n reinas comprobaremos si es posible colocar n reinas en un tablero nxn sin que se coman entre sí
//Para ello usaremos el metodo n_reinas que irá recorriendo todas las soluciones potenciales (permutaciones) e irá comprobando
//con los metodos es_solucion (si la colocamos la última reina y esta no ataca) y es_completable (si colocamos una reina que no ataca pero quedan más por colocar)
//Para saber si una reina ataca o no está el método ataca que se aprovecha de los métodos diagAscendente y descendente para saber si las reinas comparten diagonal
//Ataca devolverá true si dos reinas comparten diagonal o fila (columna no por como está la representación hecha), además este metodo está mejorado con marcadores

#include <string>
#include <iostream>
#include <vector>

using namespace std;

//DATOS REPRESENTACION: Considerando N reinas en un tablero NxN sin que se coman entre ellas
//damos por seguro que cada reina debe estar en una columna diferente, asi que la solucion la 
//abordaremos con una tupla (representada por un vector) <x1, x2, x3, ..., xN> donde cada elemento
//hara referencia a la fila en la que se encuentra la reina

//coste constante, operaciones simples
int diagDescendente(int x, int y, int N) {
	int a = x - y;
	if (a < 0) {
		a = -a;
		a = a + (N-1);
	}
	return a;
}

//coste constante, operaciones simples
int diagAscendente(int x, int y, int N) {
	return x + y;
}

//gracias a los marcadores que guardan la información de si una reina ocupa fila o diagonal, coste constante, solo son comparaciones
bool ataca(vector<int>&tupla, vector<bool>&filas,
	vector<bool>&d_asc, vector<bool>&d_desc, int act, int N) {
	bool at = (filas[tupla[act]]) ||
		(d_asc[diagAscendente(tupla[act], act, N)] || (d_desc[diagDescendente(tupla[act], act, N)]));
	return at;
}

//coste constante
bool esSolucion(vector<int>&tupla, vector<bool>&filas,
	vector<bool>&d_asc, vector<bool>&d_desc, int act, int &N) {
	bool comp = (act == N - 1 && !ataca(tupla, filas, d_asc, d_desc, act, N));
	return comp;
}

//coste constante
bool esCompletable(vector<int>&tupla, vector<bool>&filas,
	vector<bool>&d_asc, vector<bool>&d_desc, int act, int &N) {
	bool comp = (act < N - 1 && !ataca(tupla, filas, d_asc, d_desc, act, N));
	return comp;
}

//recorre todas las soluciones potenciales, eso son permutaciones, como queremos encontrar todas las soluciones
//no pararemos la busqueda, el algoritmo tiene un coste factorial, pertenece a O(n!) donde n son las filas (o columnas) del tablero
void nReinas(vector<int>&tupla, vector<bool>&filas, 
	vector<bool>&d_asc, vector<bool>&d_desc, int act, int N, int &cont) {
	for (int i = 0; i < N; i++) {
		tupla[act] = i;
		if (esSolucion(tupla, filas, d_asc, d_desc, act, N)) {
			cont++;
		}
		else if (esCompletable(tupla, filas, d_asc, d_desc, act, N)) {
			//marcado
			filas[tupla[act]] = true;
			d_asc[diagAscendente(tupla[act], act, N)] = true;
			d_desc[diagDescendente(tupla[act], act, N)] = true;
			nReinas(tupla, filas, d_asc, d_desc, act + 1, N, cont);
			//desmarcado
			filas[tupla[act]] = false;
			d_asc[diagAscendente(tupla[act], act, N)] = false;
			d_desc[diagDescendente(tupla[act], act, N)] = false;
		}
	}
}

int main() {
	//ENTRADA 
	int numCasos = 0;
	int N = 0;
	int act = 0;
	int cont = 0;
	vector <int> tupla;
	vector <bool> filas;
	vector <bool> d_asc;
	vector <bool> d_desc;
	cin >> numCasos;

	for (int i = 0; i < numCasos; i++) {
		cin >> N;
		tupla.resize(N);
		filas.resize(N*2 -1, false);
		d_asc.resize(N*2 -1, false);
		d_desc.resize(N*2 - 1, false);
		nReinas(tupla, filas, d_asc, d_desc, act, N, cont);
		cout << cont << endl;
		tupla.clear(); act = 0; N = 0; cont = 0;
	}

	return 0;
}