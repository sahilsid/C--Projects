#include<bits/stdc++.h>
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
		deleteall(root);
	}
	void displaylOrder( node* rt);
	void displaylOrder();
	void deleteall(node *);
	bool delete_element(string key);
	bool insert(element a);
	element find(string key);
	int getallinrange(string k1,string k2);
	void displayl( node* rt, int l);
    int range(node *rt, string k1, string k2,int &count);
	int size();		
};


int avl_dictionary::size(){
	return _size;
}

void avl_dictionary::displaylOrder( node* rt) 
{ 
	int h = get_height(rt);  
	for (int i=0; i<=h; i++) 
	{ 
		cout<<"\n l : "<<i<<" \n ";
		displayl(rt, i); 
	} 
} 
void avl_dictionary::deleteall(node *r) 
{ 
    if (r == NULL) 
        return; 
  
    deleteall(r->leftchild);  
    deleteall(r->rightchild); 
  	delete r;
}

void avl_dictionary::displaylOrder() 
{ 
	displaylOrder(root);
} 

int avl_dictionary::range(node *rt, string k1, string k2,int &count) 
{ 
   if ( rt==NULL ) 
      return count; 
   if ( k1 < rt->pair.key ) 
     range(rt->leftchild, k1, k2,count); 
  
   if (k2 >= rt->pair.key &&  k1<=rt->pair.key ) 
     count++;
  
   if ( k2 > rt->pair.key ) 
     range(rt->rightchild, k1, k2,count); 

 return count; 
} 

void avl_dictionary::displayl( node* rt, int l) 
{ 
	if (rt == NULL) 
		return; 
	if (l == 0) 
		cout<<"  "<<rt->pair.key; 
	else if (l > 0) 
	{ 
		displayl(rt->leftchild, l-1); 
		displayl(rt->rightchild, l-1); 
	} 
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
	int count=0;
	return range(root,k1,k2,count);
}

typename avl_dictionary::node* avl_dictionary::rotateLeft(node *z){
	node *y = z->rightchild;
	node *x	= y->leftchild;

/*	cout<<"\n Rotating Left ";
	cout<<" z : "<<z->pair.key;
	cout<<" y : "<<y->pair.key<<"\n";

*/
	
	y->leftchild = z;
	z->rightchild = x;

	z->height = max(get_height(z->rightchild),get_height(z->leftchild))+1;
	y->height = max(get_height(y->rightchild),get_height(y->leftchild))+1;

	int zdes=0;
	int ydes=0;
	if(z->rightchild!=NULL)
		zdes+=z->rightchild->no_descendants+1;
	if(z->leftchild!=NULL)
		zdes+=z->leftchild->no_descendants+1;
	
	z->no_descendants=zdes;
	
	if(y->rightchild!=NULL)
		ydes+=y->rightchild->no_descendants+1;
	if(y->leftchild!=NULL)
		ydes+=y->leftchild->no_descendants+1;
	y->no_descendants=ydes;


	return y;
}

typename avl_dictionary::node* avl_dictionary::rotateRight(node *z){
	node *y = z->leftchild;
	node *x	= y->rightchild;

/*	cout<<"\n Rotating Right ";

	
	cout<<"z : "<<z->pair.key;
	cout<<" y : "<<y->pair.key<<"\n";
*/
	y->rightchild = z;
	z->leftchild = x;

	z->height = max(get_height(z->rightchild),get_height(z->leftchild))+1;
	y->height = max(get_height(y->rightchild),get_height(y->leftchild))+1;


	int zdes=0;
	int ydes=0;
	if(z->rightchild!=NULL)
		zdes+=(z->rightchild->no_descendants+1);
	if(z->leftchild!=NULL)
		zdes+=(z->leftchild->no_descendants+1);
	
	z->no_descendants=zdes;
	
	if(y->rightchild!=NULL)
		ydes+= y->rightchild->no_descendants +1;
	if(y->leftchild!=NULL)
		ydes+=y->leftchild->no_descendants+1;
	y->no_descendants=ydes;


	return y;	
}

bool avl_dictionary::insert(element a){
//	cout<<" inserting : "<<a.key<<"\n";
	if(root==NULL){
//		cout<<" root : NULL\n";
		node *temp=new node;
		temp->pair.key=a.key;
		temp->pair.value=a.value;
		root=temp;
		_size=1;
	
		return 1;
	}
	else{
//		cout<<"root : "<<root->pair.key<<"\n";
		int b_size=root->no_descendants;
		root=insert(root,a);
		_size++;
		return 1;
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
	  _size--;
	  return 1;
	}
}

element avl_dictionary::find(string key){
	node *temp =root;
	element p;
	p.key=key;
	p.value=" ";
	while(temp!=NULL){
		if(temp->pair.key==key){
			p.value=temp->pair.value;
			return p;
		}
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
	
	

	int height_difference = difference_height(a);

	if(a->rightchild!=NULL&&height_difference<-1 && b.key > a->rightchild->pair.key){
		 a= (rotateLeft(a));
	}

	if(a->rightchild!=NULL&&height_difference<-1 && b.key < a->rightchild->pair.key){
		a->rightchild = rotateRight(a->rightchild);
		a= (rotateLeft(a));
	}

	if(a->leftchild!=NULL&&height_difference>1 && b.key > a->leftchild->pair.key){
		a->leftchild =  rotateLeft(a->leftchild);
		a= (rotateRight(a));
	}

	if(a->leftchild!=NULL&&height_difference>1 && b.key < a->leftchild->pair.key){
		a= (rotateRight(a));
	}
	a->no_descendants=0;
	if(a->rightchild!=NULL)
		a->no_descendants += a->rightchild->no_descendants +1;
	if(a->leftchild!=NULL)
		a->no_descendants += a->leftchild->no_descendants+1;

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
			cout<<" d "<<a->pair.key;
			a->rightchild=delete_element(a->rightchild,temp->pair);
		}
	}
	
	a->height=max(get_height(a->rightchild),get_height(a->leftchild))+1;
	
	
	int height_difference = difference_height(a);

	if(height_difference<-1 && difference_height(a->rightchild)<=0){
		a = rotateLeft(a);
	
	}

	if(height_difference<-1 && difference_height(a->rightchild)>0){
		a->rightchild = rotateRight(a->rightchild);
		a =rotateLeft(a);
		
	}
	
	if(height_difference>1 && difference_height(a->leftchild)>=0){
		a = rotateRight(a);
	}

	if(height_difference>1 && difference_height(a->leftchild)<0){
		a->leftchild= rotateLeft(a->leftchild);
		a=rotateRight(a);
	}
	a->no_descendants=0;
	if(a->rightchild!=NULL)
		a->no_descendants += a->rightchild->no_descendants+1;
	if(a->leftchild!=NULL)
		a->no_descendants += a->leftchild->no_descendants+1;

	
	return a;
}

	int main(){

		avl_dictionary names;
		vector<string> wrd;
		ifstream ifile;
		string key,value;
		element elem;
			
		ifile.open("words.txt");
		while(!ifile.eof()){
			ifile>>key;
			transform(key.begin(), key.end(), key.begin(), ::tolower);
			getline(ifile,value);
			elem.key=key;
			elem.value=value;
			//cout<<"\n "<<elem.key<<" : "<<elem.value;
			names.insert(elem);
		}
		int choice;
		string word;
		string k1,k2;
		while(1){

			cout<<"\n";
			for(int z=0;z<180;z++)
				cout<<"_";
			cout<<"\n";

			cout<<"\n\n\t\tAVL Dictionary\n\n\t1.Find Meaning of a word.\n\t2.Add a new word.\n\t3.Remove A word.\n\t4.Get No. words in range (k1,k2)\n\t5.No. Of Words In dictionary\n\t6.Display Tree\n\t7.Exit\n\n\t  Enter Your Choice No. : ";
			cin>>choice;
			switch(choice){
				case	1	:	cout<<"\n\n\tEnter the word 	:	";
								cin>>word;
								transform(word.begin(), word.end(), word.begin(), ::tolower); 
								elem=names.find(word);
								if(elem.value==" ")
									cout<<"\n\n\tSorry. Word Not Found.\n";
								else
									cout<<"\n\n\t"<<elem.key<<"	:\t"<<elem.value<<"\n";
								break;
				case	2	:	cout<<"\n\t Enter The Word 	:	 ";
								cin>>word;
								elem.key=word;
								cout<<"\n\t Enter The Meaning :	 ";
								cin>>word;
								elem.value=word;
								if(names.insert(elem))
									cout<<"\n\t  Added Successfully\n\n";
								else
									cout<<"\n\tError. Could Not Add the Word To the Dictionary\n";
								break;
				case	3	:	cout<<"\n\t Enter The Word to be removed 	:	 ";
								cin>>word;
								transform(word.begin(), word.end(), word.begin(), ::tolower);
								if(names.delete_element(word))
									cout<<"\n\n\t Word Removed Successfully\n\n";
								else
									cout<<"\n\n\t Word Not Found";
								break;

				case	4	:	cout<<"\n\n\tEnter the words 	:	\n\tk1	:	";
								cin>>k1;
								cout<<"\n\tk2	:	";
								cin>>k2;
								cout<<"\n\n\tThe no of words in the given range are : "<<names.getallinrange(k1,k2)<<"\n";
								break;
				case	5	:	cout<<"\n\n\t  Current Size of Dictionary	:	"<<names.size()<<"\n";
								break;
				case	6	:	cout<<"\n\n\t  Level Order Display	:	";
								names.displaylOrder();
								cout<<"\n";
								break;
				case 	7	:	return 0;
				default		:	cout<<"\n\n\t  Invalid Choice. \n";
			}
			wrd.clear();
		}

		ifile.close();
		return 0;
	}
		