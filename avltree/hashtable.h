#ifndef HASHTABLE_H
#define HASHTABLE_H

#include<bits/stdc++.h>
using namespace std;



template<typename key_,typename val>
	class hashmap{


	public:
		struct node{
			key_ key;
			val	value;
		};
		hashmap(){

			hashtable.resize(1000);
			deleted = new node;
			_size=0;

		}
		hashmap(long size_){
			hashtable.resize(2*size_);
			deleted = new node;
			_size=0;
		}

		void insert(key_ a,val b);
		bool insert(node a);
		node* find(key_ a);
		bool remove(key_ a);
		long size();
		vector<string> spellcheck(string a);
		~hashmap(){
			while(!hashtable.empty()){
				node* temp=hashtable.back();
				hashtable.pop_back();
				delete temp;
			}
			delete deleted;
		}
	private:
		vector<node*> hashtable;
		unsigned long long hash1(key_ a);
		unsigned long long hash2(key_ a);
		int checkadjacency(string a, string b);
		int minEditDistance(string a, string b);
		long _size;
		node *deleted;
	};

template<typename key_,typename val>
	bool hashmap<key_,val>::insert(node a){
		unsigned long long hashval=hash1(a.key);
		long pos=hashval%(hashtable.capacity());
		int counter=0;
		if(hashtable[pos]==NULL||hashtable[pos]==deleted){
			node *temp=new node;
			temp->key=a.key;
			temp->value=a.value;
			hashtable[pos]=temp;
			_size++;
		}
		else{
			while(hashtable[pos]!=NULL &&hashtable[pos]!=deleted&& counter<(hashtable.capacity())){
				if(hashtable[pos]->key==a.key){
					hashtable[pos]->value=a.value;
					return 1;
				}
				counter++;
				pos=(hashval + counter*hash2(a.key))%hashtable.capacity();	

			}
			if(counter<hashtable.capacity()){
				node *temp=new node;
				temp->key=a.key;
				temp->value=a.value;
				hashtable[pos]=temp;
				_size++;	
				return 1;			
			}
		}
		return 0;
	}
template<typename key_,typename val>
	void hashmap<key_,val>::insert(key_ a, val b){
		node temp;
		temp.key=a;
		temp.value=b;
		insert(temp);
	}

template<typename key_,typename val>
	long hashmap<key_,val>::size(){
		return _size;
	}

template<typename key_,typename val>
	unsigned long long hashmap<key_,val>::hash1(key_ a){
		unsigned long long int prime=31,i,temp;
		unsigned long long poly_sum=0;
		for(i=0;i<a.size();i++){
			temp=tolower(a[i])-'a';
			//cout<<"\n temp : "<<temp;
			poly_sum+= temp*pow(prime,i);
			//cout<<"\n polysum : "<<poly_sum;

		}
		//cout<<"\n hash 1 : "<<(poly_sum);
		return poly_sum%99991;
	}

template<typename key_,typename val>
	unsigned long long hashmap<key_,val>::hash2(key_ a){
		unsigned long long prime=31,i,temp;
		unsigned long long poly_sum=0;
		for(i=0;i<a.size();i++){
			temp=tolower(a[i])-'a';
			poly_sum+= temp*pow(prime,i);
		}
		//cout<<"\n hash 2 : "<<(poly_sum%99991+1);
		return (poly_sum%99991 + 1);
	}

template<typename key_,typename val>
	int hashmap<key_,val>::checkadjacency(string a, string b){
		sort(a.begin(),a.end());
		sort(b.begin(),b.end());
		if(a==b){
	//		cout<<"\n a : "<<a<<"\t b : "<<b<<"\n";
			return 1;
		}
		else
			return 0;
	}

template<typename key_,typename val>
	int hashmap<key_,val>::minEditDistance(string a, string b){
		
		for(int i=0;i<a.size();i++)
			a[i]=tolower(a[i]);

		for(int i=0;i<b.size();i++)
			b[i]=tolower(b[i]);

		if(checkadjacency(a,b))
			return 1;

		if(a.size()<b.size()){
			string temp =a;
			a=b;
			b=temp;
		}
		int m=a.size();
		int n=b.size();
		int matrix[m+1][n+1];
		for(int i=0;i<=m;i++){
			for(int j=0;j<=n;j++){

				if(i==0)
					matrix[i][j]=j;
				else if(j==0)
					matrix[i][j]=i;
				else if(a[i-1]==b[j-1])
						matrix[i][j]=matrix[i-1][j-1];
				else{
						matrix[i][j]=min(matrix[i][j-1],matrix[i-1][j-1]);
						matrix[i][j]=min(matrix[i][j],matrix[i-1][j])+1;
				}
			}
		}
		if(matrix[m][n]==1){ 
			return 1;
		}
		else
			return 0;
	}

template<typename key_,typename val>
	typename hashmap<key_,val>::node* hashmap<key_,val>::find(key_ a){
		unsigned long long hashval=hash1(a);
		long pos=hashval%(hashtable.capacity());
		int counter=0;

			while((hashtable[pos]==deleted)||hashtable[pos]!=NULL&&hashtable[pos]->key!=a && counter<hashtable.capacity()){
				counter++;
				pos=(hashval + counter*hash2(a))%hashtable.capacity();			
			}

			if(hashtable[pos]!=NULL&&hashtable[pos]->key==a){
				return hashtable[pos];
			}
			return NULL;
	}

template<typename key_,typename val>
	vector<string> hashmap<key_,val>::spellcheck(string a){
		vector<string> possible_words;
		int words=0;

		if(find(a)!=NULL){
			cout<<"\n\t"<<a<<" : "<<find(a)->value<<"\n";
		}
		else
			for(int i=0;i<hashtable.capacity();i++){
				if(hashtable[i]!=NULL)
					words++;
				if((hashtable[i]!=NULL)&&hashtable[i]!=deleted&&minEditDistance(hashtable[i]->key,a)){
					possible_words.push_back(hashtable[i]->key);
		//			cout<<"\n pushing : "<<hashtable[i]->key;
				}
			}
		//	cout<<"\n "<<words<<"\n";
		return possible_words;
	}

template<typename key_,typename val>
	bool hashmap<key_,val>::remove(key_ a){
		unsigned long long hashval=hash1(a);
		long pos=hashval%hashtable.capacity();
		int counter=0;

		while((hashtable[pos]==deleted)||hashtable[pos]!=NULL&&hashtable[pos]->key!=a && counter<hashtable.capacity()){
			counter++;
			pos=(hashval + counter*hash2(a))%hashtable.capacity();				
		}
		if(hashtable[pos]!=NULL&&hashtable[pos]->key==a){
			node* temp=hashtable[pos];
			delete temp;
			hashtable[pos]=deleted;
			_size--;
			return 1;
		}
		else
			return 0;
	}


#endif

