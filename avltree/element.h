#ifndef ELEMENT_H
#define ELEMENT_H

using namespace std;

struct element{
	string key;
	string value;
	void operator=( element a ){
		key=a.key;
		value=a.value;
	}
	element(){
		key=" ";
		value=" ";
	}
};
#endif