#include<iostream>
#include<fstream>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<math.h>
#include<iomanip>
#include "item.h"
using namespace std;


	
	item::item(){
		next_item=NULL;
		previous_item=NULL;
	}


	void item::disp_location(){
		cout<<"\t"<<location[0]<<" "<<location[1];
	}
	
	void item::remove_item(item *cur){
		item *temp1,*temp2;
		temp1=cur->next_item;
		temp2=cur->previous_item;
		if(temp2!=NULL)
			temp2->next_item=temp1;	
		
		if(temp1!=NULL)
		temp1->previous_item=temp2;
		delete(cur);
	}
	
	void item::auto_generate_purchase_id(){

		if (this->previous_item==NULL)
			purchase_id=1;
		else
			purchase_id=(this->previous_item->purchase_id+1);

	}


	void item::print_item(){
		char tme[20];
		strftime (tme,20,"%D %R",localtime(&purchase_time));
		cout<<"\n\t"<<item_name;
		cout<<"\t\t"<<setfill('0')<<setw(5)<<purchase_id;
		cout<<"\t\t"<<setfill(' ')<<setw(5)<<location[0]<<" ,"<<setfill(' ')<<setw(4)<<location[1];
		cout<<"\t\t"<<setfill(' ')<<setw(9)<<item_type;
		cout<<"\t\t"<<tme;
	}
	
	void item::update(int *loc,const char *type,char *name){
		location[0]=loc[0];
		location[1]=loc[1];
		strcpy(item_type,type);
		strcpy(item_name,name);
		purchase_time=time(0);

		auto_generate_purchase_id();

	}
	int item::location_check(int x,int y){
		if(location[0]==x&&location[1]==y)
			return 1;
		else
			return 0;
	}
	int item::get_purchase_id(){
		return purchase_id;
	}

	void item::update_previous(item* previous){
		this->previous_item=previous;
	}

	float item::get_distance(){
		float temp=location[0]*location[0]+location[1]*location[1];	
		temp=sqrt(temp);
		return temp;
	}
	bool item::operator > (item &b){
		if(get_distance() > b.get_distance())
			return 1;
		else
			return 0;
	}
	
	void item::update_next(item* next){
		this->next_item=next;
	}

	item* item::get_next_item(){
		return this->next_item;
	}
	item* item::get_previous_item(){
		return this->previous_item;
	}
	char* item::get_item_name(){
		return item_name;
	}
	char* item::get_item_type(){
		return item_type;
	}



