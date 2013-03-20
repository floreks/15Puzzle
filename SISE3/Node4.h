/*
 * Node4.h
 *
 *  Created on: 20-03-2013
 *      Author: Adam Kopaczewski 165443
 */

#ifndef NODE4_H_
#define NODE4_H_

#include <iostream>
#include <list>
#include <vector>

typedef long long int LL;

using namespace std;

/*
Numeracja:
0  1  2  3
4  5  6  7
8  9  10 11
12 13 14 15
*/


class Node4 {
public:
  Node4();
	/*
	 * @ptr - 16 elemntowa tablica (wraz z poczatkowym stanem)
	 */
	Node4(int* ptr);

	/*
	 * @v - 16 elemntowy wektor (wraz z poczatkowym stanem)
	 */
	Node4(vector<int> &v);

	/*
	 * stawia na nowo zawartosc wierzcholka
	 * @ptr - 16 elemntowa tablica (wraz z nowym stanem)
	 */
	void setValues(int *ptr);

	/*
	 * ustawia na nowo zawartosc wierzcholka
	 * @v - 16 elemntowy wektor (wraz z nowym stanem)
	 */
	void setValues(vector<int> &v);

	/*
	 * Ustawia na pozycji index wartosc value
	 * gdy wartosc lub indeks przekraczja zakres to nic nie robi
	 * @value - nowa wartosc
	 * @index - pozycja
	 */
	void setValue(int value, int index);

	/*
	 * Ustawia liste poprzednikow
	 * @predecessors - wskaznik na liste poprzednikow
	 */
	void setPredecessors(list<Node4*> *predecessors){
		this->predecessors = *predecessors;
	}

	/*
	* Ustawia liste nastepnikow
	* @successors - wskaznik na liste nastepnikow
	*/
	void setSuccessors(list<Node4*> *successors){
		this->successors = *successors;
	}

	/*
	 * Zwraca zawartosc wierzcholka w postaci 16 elementowej tablicy
	 * @return *int - wskaznik na 16 elementowa tablice
	 */
	int* getValuesTab()const;

	/*
	 * Zwraca zawartosc wierzcholka w postaci 16 elementowego wektora
	 * @return vector<int> - 16 elementowy wektor
	 */
	vector<int> getValuesVect()const;

	/*
	 * Zwraca wartosc na pozycji index. Gdy index wychodzi poza zakres
	 * zwraca -1
	 * @int index - pozycja zadanej wartosci
	 * @return [0,15] lub -1 gdy index poza zakresem
	 */
	int getValue(int index)const;

	/*
	 * Zwraca pozycje zera
	 * @return int - indeks zera
	 */
	int getZeroIndex()const;

	/*
	 * Zwraca indeks podanej wartosci value; gdy value jest poza zakresem
	 * zwraca -1
	 * @return int - pozycja zadanej wartosci value
	 */
	int getIndex(int value)const;

	/*
	 * Zwraca liste nastepnikow
	 * @return list<Node4*> - lista ze wskaznikami na nastepniki
	 */
	list<Node4*> getSuccessors()const{
		return this->successors;
	}

	/*
	 * Zwraca liste poprzednikow
	 * @return - lizsta ze wskaznikami na poprzedniki
	 */
	list<Node4*> getPredecessors()const{
		return this->predecessors;
	}

	/*
	 * Zwraca ilosc nastepnikow
	 * @return int - lista nastepnikow
	 */
	int getSuccessorsCount()const{
		return this->successors.size();
	}

	/*
	 * Zwraca ilosc poprzednikow
	 * @return int - liczba poprzednikow
	 */
	int getPredecessorsCount()const{
		return this->predecessors.size();
	}

	/*
	 * Sprawdza czy dwa wierzcholki sa sobie rowne. Wierzchoki sa sobie rowne gdy
	 * przechowuja elementy ustawione w identycznej kokejnosci.
	 *	@n - porownywany wierzcholek
	 *	@return true - gdy identyczne; false - wrecz przeciwnie
	 */
	bool equals(Node4 n)const;

	/*
	 * Sprawdza czy dwa wierzcholki sa sobie rowne. Wierzchoki sa sobie rowne gdy
	 * przechowuja elementy ustawione w identycznej kokejnosci.
	 *	@n - wskaznik na porownywany wierzcholek
	 *	@return true - gdy identyczne; false - wrecz przeciwnie
	 */
	bool equals(Node4 *n)const;

	/*
	 * Sprawdza czy podany wierzcholek jest poprzedndikiem obecnego
	 * @n sprawdzany wierzcholek
	 * @return true - podany wierzcholek jest poprzednikiem;
	 * false - wrecz przeciwenie
	 */
	bool isPredecessor(Node4 n)const;

	/*
	 * Sprawdza czy podany wierzcholek jest poprzedndikiem obecnego
	 * @n wskaznik na sprawdzany wierzcholek
	 * @return true - podany wierzcholek jest poprzednikiem;
	 * false - wrecz przeciwenie
	 */
	bool isPredecessor(Node4 *n)const;

	/*
	 * Sprawdza czy podany wierzcholek jest nastepnikiem obecnego
	 * @n sprawdzany wierzcholek
	 * @return true - podany wierzcholek jest nastepnikiem;
	 * false - wrecz przeciwenie
	 */
	bool isSuccessor(Node4 n)const;

	/*
	 * Sprawdza czy podany wierzcholek jest nastepnikiem obecnego
	 * @n wskaznik sprawdzany wierzcholek
	 * @return true - podany wierzcholek jest nastepnikiem;
	 * false - wrecz przeciwenie
	 */
	bool isSuccessor(Node4 *n)const;

	/*
	 * Sprawdza czy podana wartosc n jest poprawnym indeksem badz wartoscia, ktora
	 * moze byc przechowywana przez wierzcholek
	 * @n sprawdzany indeks badz wartosc
	 * @return true - parametr nie przekracza zakresu; false - wrecz przeciwnie
	 */
	bool isCorrectValueOrIndex(int n)const{
		return n >= 0 && n <= 15;
	}

	/*
	 * Dodaje podana liste wierzcholkow do listy nastepnikow.
	 * Dodaje tylko te wierzcholki, ktore nie sa jeszce nastepnikami.
	 * @successors - lista wskaznikow na dodawane nstepniki
	 */
	void addSuccessors(list<Node4*> successors);

	/* Dodaje nowy nastepnik (o ile podany wierzcholek jeszcze nim nie jest)
	 * @successor - wskaznik na nowego nastepnika
	 */
	void addSuccessor(Node4 *successor){
		if( !isSuccessor(successor) )
			this->successors.push_back(successor);
	}

	/*
	 * Dodaje podana liste wierzcholkow do listy poprzednikow.
	 * Dodaje tylko te wierzcholki, ktore nie sa jeszce poprzednikami.
	 * @successors - lista wskaznikow na dodawane poprzedniki.
	 */
	void addPredecessors(list<Node4*> predecessors);

	/* Dodaje nowy nastepnik (o ile podany wierzcholek jeszcze nim nie jest)
	 * @predecessor - wskaznik na nowego poprzednika
	 */
	void addPredecessor(Node4 *predecessor){
		if( !isPredecessor(predecessor) )
			this->predecessors.push_back(predecessor);

	}

	/*
	 * Usuwa podany wierzcholek z listy poprzednikow
	 * @predecessor wierzcholek do usuniecia
	 */
	void removePredecessor(Node4 *predecessor){
		this->predecessors.remove(predecessor);
	}

	/*
	 * Usuwa podany wierzcholek z listy nastepnikow
	 * @predecessor wierzcholek do usuniecia
	 */
	void removeSuccessor(Node4 *successor){
		this->successors.remove(successor);
	}

private:
	void init();
	void setNewContent(int *ptr);
	void setNewContent(vector<int> &v);

	LL content;
	LL maski[16];
	list<Node4*> successors;
	list<Node4*> predecessors;
};

ostream& operator<<(ostream& os, Node4 n);
ostream& operator<<(ostream& os, Node4 *n);
ostream& operator<<(ostream& os, list<Node4*> l);

#endif /* NODE4_H_ */
