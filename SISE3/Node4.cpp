/*
 * Node4.cpp
 *
 *  Created on: 20-03-2013
 *      Author: Adam Kopaczewski 165443
 */

#include "Node4.h"

Node4::Node4() {
  init();
	content ^= content;
}
//********************************************************************************

Node4::Node4(int* ptr){
	init();
	setNewContent(ptr);
}
//********************************************************************************

Node4::Node4(vector<int> &v){
	init();
	setNewContent(v);
}
//********************************************************************************

void Node4::setValues(int *ptr){
	setNewContent(ptr);
}
//********************************************************************************

void Node4::setValues(vector<int> &v){
	setNewContent(v);
}
//********************************************************************************

void Node4::setValue(int value, int index){
	if( !isCorrectValueOrIndex(value) || !isCorrectValueOrIndex(index))
		return;
	LL tmp = 0LL;
	for(int i = 0; i < 16; i++){
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

int* Node4::getValuesTab()const{
	int* ret = new int[16];

	for(int i = 0; i < 16; i++)
		ret[i] = getValue(i);

	return ret;
}
//********************************************************************************

vector<int> Node4::getValuesVect()const{
	vector<int> ret(16);

	for(int i = 0; i < 16; i++)
		ret[i] = getValue(i);

	return ret;
}
//********************************************************************************

int Node4::getValue(int index)const{
	if( !isCorrectValueOrIndex(index) )
		return -1;

	LL tmp = content & maski[index];
	tmp >>= (index * 4);
	return tmp;
}
//*******************************************************************************

void Node4::setNewContent(int *ptr){
	content ^= content;
	LL tmp;
	for(int i = 0; i < 16; i++){
		tmp = ptr[i];
		tmp <<= (4 * i);
		content |= tmp;
	}
}
//********************************************************************************

void Node4::setNewContent(vector<int> &v){
	content ^= content;
	LL tmp;
	for(int i = 0; i < 16; i++){
		tmp = v[i];
		tmp <<= (4 * i);
		content |= tmp;
	}
}
//********************************************************************************

int Node4::getZeroIndex()const{
	int i;
	for(i ^= i; i < 16; i++)
		if( !(content & maski[i]) )
			break;

	return i;
}
//********************************************************************************

int Node4::getIndex(int value)const{
	if( !isCorrectValueOrIndex(value) )
		return -1;

	int i;
	for(i ^= i; i < 16; i++)
		if(getValue(i) == value)
			break;

	return i;
}
//********************************************************************************

bool Node4::equals(Node4 n)const{
	for(int i = 0; i < 16; i++)
		if( this->getValue(i) != n.getValue(i) )
			return false;

	return true;
}
//********************************************************************************

bool Node4::equals(Node4 *n)const{
	return equals(*n);
}
//********************************************************************************

bool Node4::isPredecessor(Node4 n)const{
	for(list<Node4*>::const_iterator it = predecessors.begin(); it != predecessors.end(); it++)
		if( (*it)->equals(n) )
			return true;

	return false;
}
//********************************************************************************

bool Node4::isPredecessor(Node4 *n)const{
	return isPredecessor(*n);
}
//********************************************************************************

bool Node4::isSuccessor(Node4 n)const{
	for(list<Node4*>::const_iterator it = successors.begin(); it != successors.end(); it++)
		if( (*it)->equals(n) )
			return true;

	return false;
}
//********************************************************************************

bool Node4::isSuccessor(Node4 *n)const{
	return isSuccessor(*n);
}
//********************************************************************************

void Node4::addSuccessors(list<Node4*> successors){
	for(list<Node4*>::iterator it = successors.begin(); it != successors.end(); it++)
		if( !isSuccessor(*it) )
			this->successors.push_back(*it);
}
//********************************************************************************

void Node4::addPredecessors(list<Node4*> predecessors){
	for(list<Node4*>::iterator it = predecessors.begin(); it != predecessors.end(); it++)
		if( !isPredecessor(*it) )
			this->predecessors.push_back(*it);
}
//********************************************************************************

void Node4::init(){
	maski[0] = 0xfLL;
	maski[1] = 0xf0LL;
	maski[2] = 0xf00LL;
	maski[3] = 0xf000LL;
	maski[4] = 0xf0000LL;
	maski[5] = 0xf00000LL;
	maski[6] = 0xf000000LL;
	maski[7] = 0xf0000000LL;
	maski[8] = 0xf00000000LL;
	maski[9] = 0xf000000000LL;
	maski[10] = 0xf0000000000LL;
	maski[11] = 0xf00000000000LL;
	maski[12] = 0xf000000000000LL;
	maski[13] = 0xf0000000000000LL;
	maski[14] = 0xf00000000000000LL;
	maski[15] = 0xf000000000000000LL;
}
//*******************************************************************************

ostream& operator<<(ostream& os, Node4 n){
	for(int i = 0; i < 16; i++){
		if( !(i % 4) && i )
			os << endl;
		os << n.getValue(i) << ' ';
	}

	return os;
}
//*******************************************************************************

ostream& operator<<(ostream& os, Node4 *n){
	for(int i = 0; i < 16; i++){
		if( !(i % 4) && i )
			os << endl;
		os << n->getValue(i) << ' ';
	}

	return os;
}
//*******************************************************************************

ostream& operator<<(ostream& os, list<Node4*> l){
	for(list<Node4*>::iterator it = l.begin(); it != l.end(); it++)
		os << *it << '\n' <<endl;
	return os;
}


