//Grupo007, Juan Ruiz Jiménez y Javier Cordero Calvo
//Este algoritmo pretende conocer el numero maximo de monedas que puedes usar para pagar una cantidad exacta de dinero
//Para ello nos apollaremos en el metodo quita calderilla, que ira generando una posible cantidad de monedas a introducir y el valor que estas supondrian
//Si este valor no excede la cantidad a pagar, el metodo es_prometedora lo detectará y repetirá la llamada recursiva para la siguiente moneda con los nuevos valores
//como solo será prometedora si la posición actual del vector es menor que su tamaño-1, no nos saldremos de rango
//Si este valor es justo la cantidad a pagar, será una solución, si esta usa mas monedas que la anterior registrada, se actualiará
//Si el valor se excede, podamos

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//coste constante
int calculaValorMoneda(int act) {
	if (act == 0)
		return 1;
	else if (act == 1)
		return 2;
	else if (act == 2)
		return 5;
	else if (act == 3)
		return 10;
	else if (act == 4)
		return 20;
	else if (act == 5)
		return 50;
	else if (act == 6)
		return 100;
	else if (act == 7)
		return 200;
}

//coste constante
int daCantidad(vector<int>& monedas, int sol, int act) {
	int value = calculaValorMoneda(act);
	return value * sol;
}

//coste constante
bool esPrometedora(int cantidad, int cantAct, vector<int>& monedas, int sol, int NumMonedas, int act, int mejorSol) {
	int ult = monedas.size()-1;
	return (act < ult && (cantAct <= cantidad));
}

//coste constante
bool esSolucion(int cantidad, int cantAct, vector<int>& monedas, int sol, int NumMonedas, int act, int mejorSol) {
	return (NumMonedas > mejorSol && (cantAct == cantidad));
}

//teniendo en cuenta que n es el numero de monedas que tenemos de un determinado tipo y m es el tamaño del vector, el coste 
//del método estará en O(n*m)
void quitaCalderilla(int cantidad, int cantAct, vector<int>& monedas, int sol, int NumMonedas, int act, int& mejorSol){
	for (int i = 0; i <= monedas[act]; i++) {
		sol = i;
		int posible_num = NumMonedas + i;
		int posible_cant = cantAct + sol*calculaValorMoneda(act);
		if (esSolucion(cantidad, posible_cant, monedas, sol, posible_num, act, mejorSol)) {
			mejorSol = posible_num;
		}
		else if (esPrometedora(posible_cant, cantAct, monedas, sol, posible_num, act, mejorSol)) {
			quitaCalderilla(cantidad, posible_cant, monedas, sol, posible_num, act + 1, mejorSol);
		}
	}
}

int main() {
	int numCasos = 0;
	int cantidad = 0;
	int cantAct = 0;
	int NumMonedas = 0;
	int act = 0;
	int mejorSol = -1;
	vector <int> monedas;
	int sol = 0;
	cin >> numCasos;
	for (int i = 0; i < numCasos; i++) {
		cin >> cantidad;
		monedas.resize(8);
		for (int j = 0; j < monedas.size(); j++) {
			cin >> monedas[j];
		}
		quitaCalderilla(cantidad, cantAct, monedas, sol, NumMonedas, act, mejorSol);
		if (mejorSol >= 0)
			cout << mejorSol << endl;
		else
			cout << "IMPOSIBLE" << endl;
		monedas.clear();
		mejorSol = -1;
	}

	return 0;
}