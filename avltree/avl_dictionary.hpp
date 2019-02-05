
#ifndef AVL_DICTIONARY_H
#define AVL_DICTIONARY_H


#include<bits/stdc++.h>
#include"element.h"
using namespace std;


class avl_dictionary
{
	struct node
	{
		element pair;
		node *leftchild;
		node *rightchild;
		int no_descendants;
		int height;

		node(){
			leftchild=NULL;
			rightchild=NULL;
			no_descendants=0;
			height=0;
		}
		node(element a){
			pair =a;
			leftchild=NULL;
			rightchild=NULL;
			no_descendants=0;
			height=0;
		}

	};
	node *root;
	int _size;
	int get_height(node* a);
	int difference_height(node* a);
	node *delete_element(node *a,element p);
	node *insert(node *a , element p);
	node *rotateLeft(node *a);
	node *rotateRight(node *a);


public:	
	avl_dictionary(){
		root=NULL;
		_size=0;
	}
	~avl_dictionary(){

	}
	bool delete_element(string key);
	bool insert(element a);
	element find(string key);
	int getallinrange(string k1,string k2);
	int size();		
};


int avl_dictionary::size(){
	return _size;
}

int avl_dictionary::get_height(node*a){
		if(a==NULL)
			return 0;
		else
			return a->height; 
	}

int avl_dictionary::difference_height(node *a){
	return(get_height(a->leftchild)-get_height(a->rightchild));
}

int avl_dictionary::getallinrange(string k1,string k2){

	node *temp=root;
	int range=_size;
	while(temp!=NULL){
		if(temp->pair.key>k2)
			break;
	}
	if(temp!=NULL)
	range-=(temp->no_descendants+1);
	temp=root;
	while(temp!=NULL){
		if(temp->pair.key<k2)
			break;
	}
	if(temp!=NULL)
	range-=(temp->no_descendants+1);
	return range;
}

typename avl_dictionary::node* avl_dictionary::rotateLeft(node *z){
	node *y = z->rightchild;
	node *x	= y->leftchild;

	cout<<"\n Rotating Left \n";
	y->leftchild = z;
	z->rightchild = x;

	z->height = max(get_height(z->rightchild),get_height(z->leftchild))+1;
	y->height = max(get_height(y->rightchild),get_height(y->leftchild))+1;

	return y;
}

typename avl_dictionary::node* avl_dictionary::rotateRight(node *z){
	node *y = z->leftchild;
	node *x	= y->rightchild;

	cout<<"\n Rotating Right \n";

	y->rightchild = z;
	z->leftchild = x;

	z->height = max(get_height(z->rightchild),get_height(z->leftchild))+1;
	y->height = max(get_height(y->rightchild),get_height(y->leftchild))+1;

	return y;	
}

bool avl_dictionary::insert(element a){

	printLevelOrder(root);cout<<"\n __ \n";

	if(root==NULL){
		node *temp=new node;
		temp->pair.key=a.key;
		temp->pair.value=a.value;
		root=temp;
		_size=1;
		return 1;
	}
	else{
		int b_size=root->no_descendants;
		root=insert(root,a);
		_size=root->no_descendants+1;
	}
	return 0;
}
bool avl_dictionary::delete_element(string key){
	element a = find(key);
	if(a.value==" ")
		return 0;
	else
	{
	  root = delete_element(root,a);
	  _size=root->no_descendants+1;
	  return 1;
	}
}

element avl_dictionary::find(string key){
	node *temp =root;
	element p;
	p.key=key;
	p.value=" ";
	while(temp!=NULL){
		if(temp->pair.key==key)
			p.value=temp->pair.value;
		else if(temp->pair.key>key)
			temp=temp->leftchild;
		else
			temp=temp->rightchild;
	}
	return p;
} 

typename avl_dictionary::node* avl_dictionary::insert(node *a,element b){
	if(a==NULL){
		node *temp=new node;
		temp->pair.key=b.key;
		temp->pair.value=b.value;
		return temp;
	}
	else if(b.key > a->pair.key)
		a->rightchild=insert(a->rightchild,b);
	else if(b.key < a->pair.key)
		a->leftchild=insert(a->leftchild,b);
	else {
		a->pair.value=b.value;
		return a;
	}
	
	a->height=max(get_height(a->rightchild),get_height(a->leftchild))+1;
	
	a->no_descendants=0;
	if(a->rightchild!=NULL)
		a->no_descendants += a->rightchild->no_descendants+1;
	if(a->leftchild!=NULL)
		a->no_descendants += a->leftchild->no_descendants+1;

	int height_difference = difference_height(a);

	if(a->rightchild!=NULL&&height_difference<-1 && b.key > a->rightchild->pair.key){
		node *temp = rotateLeft(a);
		return temp;
	}

	if(a->rightchild!=NULL&&height_difference<-1 && b.key < a->rightchild->pair.key){
		node *temp = rotateRight(a->rightchild);
		temp = rotateLeft(a);
		return temp;
	}

	if(a->rightchild!=NULL&&height_difference>1 && b.key > a->rightchild->pair.key){
		node *temp = rotateLeft(a->leftchild);
		temp = rotateRight(a);
		return temp;
	}

	if(a->rightchild!=NULL&&height_difference>1 && b.key < a->rightchild->pair.key){
		node *temp = rotateRight(a);
		return temp;
	}
	return a;
}

typename avl_dictionary::node* avl_dictionary::delete_element(node *a,element b){

	if(a==NULL){
		return a;
	}
	else if(b.key > a->pair.key)
		a->rightchild=delete_element(a->rightchild,b);
	else if(b.key < a->pair.key)
		a->leftchild=delete_element(a->leftchild,b);
	else {
		if(a->rightchild==NULL && a->leftchild == NULL){
			delete a;
			return NULL;
		}

		else if(a->leftchild==NULL){
			node *temp = a->rightchild;
			*a = *temp;
			delete temp;		
		}
		
		else if(a->rightchild==NULL){
			node *temp = a->leftchild;
			*a = *temp;
			delete temp;
		}		
		else{
			node *temp = a->rightchild;
			while(temp->leftchild!=NULL){
				temp=temp->leftchild;
			}
			a->pair=temp->pair;

			a=delete_element(a->rightchild,temp->pair);
		}
	}
	
	a->height=max(get_height(a->rightchild),get_height(a->leftchild))+1;
	
	a->no_descendants=0;
	if(a->rightchild!=NULL)
		a->no_descendants += a->rightchild->no_descendants+1;
	if(a->leftchild!=NULL)
		a->no_descendants += a->leftchild->no_descendants+1;

	int height_difference = difference_height(a);

	if(height_difference<-1 && difference_height(a->rightchild)<=0){
		node *temp = rotateLeft(a);
		return temp;
	}

	if(height_difference<-1 && difference_height(a->rightchild)>0){
		node *temp = rotateRight(a->rightchild);
		temp =rotateLeft(a);
		return temp;
	}
	
	if(height_difference>1 && difference_height(a->leftchild)>=0){
		node *temp = rotateRight(a);
		return temp;
	}

	if(height_difference>1 && difference_height(a->rightchild)<0){
		node *temp = rotateLeft(a->leftchild);
		temp =rotateRight(a);
		return temp;
	}
	
	return a;
}

#endif