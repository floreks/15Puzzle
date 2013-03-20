/*
 * Node3.cpp
 *
 *  Created on: 20-03-2013
 *      Author: Adam Kopaczewski 165443
 */

#include "Node3.h"

Node3::Node3() {
  init();
	content ^= content;
}
//********************************************************************************

Node3::Node3(int* ptr){
	init();
	setNewContent(ptr);
}
//********************************************************************************

Node3::Node3(vector<int> &v){
	init();
	setNewContent(v);
}
//********************************************************************************

void Node3::setValues(int *ptr){
	setNewContent(ptr);
}
//********************************************************************************

void Node3::setValues(vector<int> &v){
	setNewContent(v);
}
//********************************************************************************

void Node3::setValue(int value, int index){
	if( !isCorrectValueOrIndex(value) || !isCorrectValueOrIndex(index))
		return;
	LL tmp = 0LL;
	for(int i = 0; i < 9; i++){
		if(i == index)
			continue;
		tmp |= maski[i];
	}
	content &= tmp;
	tmp = value;
	tmp <<= (index * 4);
	content |= tmp;
}
//********************************************************************************

int* Node3::getValuesTab()const{
	int* ret = new int[9];

	for(int i = 0; i < 9; i++)
		ret[i] = getValue(i);

	return ret;
}
//********************************************************************************

vector<int> Node3::getValuesVect()const{
	vector<int> ret(9);

	for(int i = 0; i < 9; i++)
		ret[i] = getValue(i);

	return ret;
}
//********************************************************************************

int Node3::getValue(int index)const{
	if( !isCorrectValueOrIndex(index) )
		return -1;

	LL tmp = content & maski[index];
	tmp >>= (index * 4);
	return tmp;
}
//*******************************************************************************

void Node3::setNewContent(int *ptr){
	content ^= content;
	LL tmp;
	for(int i = 0; i < 9; i++){
		tmp = ptr[i];
		tmp <<= (4 * i);
		content |= tmp;
	}
}
//********************************************************************************

void Node3::setNewContent(vector<int> &v){
	content ^= content;
	LL tmp;
	for(int i = 0; i < 9; i++){
		tmp = v[i];
		tmp <<= (4 * i);
		content |= tmp;
	}
}
//********************************************************************************

int Node3::getZeroIndex()const{
	int i;
	for(i ^= i; i < 9; i++)
		if( !(content & maski[i]) )
			break;

	return i;
}
//********************************************************************************

int Node3::getIndex(int value)const{
	if( !isCorrectValueOrIndex(value) )
		return -1;

	int i;
	for(i ^= i; i < 9; i++)
		if(getValue(i) == value)
			break;

	return i;
}
//********************************************************************************

bool Node3::equals(Node3 n)const{
	for(int i = 0; i < 9; i++)
		if( this->getValue(i) != n.getValue(i) )
			return false;

	return true;
}
//********************************************************************************

bool Node3::equals(Node3 *n)const{
	return equals(*n);
}
//********************************************************************************

bool Node3::isPredecessor(Node3 n)const{
	for(list<Node3*>::const_iterator it = predecessors.begin(); it != predecessors.end(); it++)
		if( (*it)->equals(n) )
			return true;

	return false;
}
//********************************************************************************

bool Node3::isPredecessor(Node3 *n)const{
	return isPredecessor(*n);
}
//********************************************************************************

bool Node3::isSuccessor(Node3 n)const{
	for(list<Node3*>::const_iterator it = successors.begin(); it != successors.end(); it++)
		if( (*it)->equals(n) )
			return true;

	return false;
}
//********************************************************************************

bool Node3::isSuccessor(Node3 *n)const{
	return isSuccessor(*n);
}
//********************************************************************************

void Node3::addSuccessors(list<Node3*> successors){
	for(list<Node3*>::iterator it = successors.begin(); it != successors.end(); it++)
		if( !isSuccessor(*it) )
			this->successors.push_back(*it);
}
//********************************************************************************

void Node3::addPredecessors(list<Node3*> predecessors){
	for(list<Node3*>::iterator it = predecessors.begin(); it != predecessors.end(); it++)
		if( !isPredecessor(*it) )
			this->predecessors.push_back(*it);
}
//********************************************************************************

void Node3::init(){
	maski[0] = 0xfLL;
	maski[1] = 0xf0LL;
	maski[2] = 0xf00LL;
	maski[3] = 0xf000LL;
	maski[4] = 0xf0000LL;
	maski[5] = 0xf00000LL;
	maski[6] = 0xf000000LL;
	maski[7] = 0xf0000000LL;
	maski[8] = 0xf00000000LL;
}
//*******************************************************************************

ostream& operator<<(ostream& os, Node3 n){
	for(int i = 0; i < 9; i++){
		if( !(i % 3) && i )
			os << endl;
		os << n.getValue(i) << ' ';
	}

	return os;
}
//*******************************************************************************

ostream& operator<<(ostream& os, Node3 *n){
	for(int i = 0; i < 9; i++){
		if( !(i % 3) && i )
			os << endl;
		os << n->getValue(i) << ' ';
	}

	return os;
}
//*******************************************************************************

ostream& operator<<(ostream& os, list<Node3*> l){
	for(list<Node3*>::iterator it = l.begin(); it != l.end(); it++)
		os << *it << '\n' <<endl;
	return os;
}
