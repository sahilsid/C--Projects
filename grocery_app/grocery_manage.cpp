#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include<math.h>
#include<iomanip>
#include "item.h"
#include "fruits.h"
#include "vegetables.h"
#include "grocery_manage.h"
using namespace std;


	grocery_manage::grocery_manage(){
		total_items=0;
		head_items=NULL;
		tail_items=NULL;
	}
	grocery_manage::~grocery_manage(){
		item *temp=head_items,*temp2;
		while(temp!=NULL){
			temp2=temp;
			temp=temp->get_next_item();
			delete(temp2);
		}
	}
	
	void grocery_manage:: add_fruits(){
		fruits *temp = new fruits;
		temp->get_fruit_details();
		total_items++;

		if (head_items==NULL){
			head_items=temp;
			tail_items=temp;
		}
		else{
			temp->update_previous(tail_items);
			tail_items->update_next(temp);
			tail_items=temp;
		}
	temp->auto_generate_purchase_id();
	}

	void grocery_manage::import_data(){
		ifstream fruits_file,vegetables_file;
		float price;
		float volume_weight;
		float quantity;
		float calories;
		char name[20];
		int location[2];
		fruits_file.open("fruits.txt");
		vegetables_file.open("vegetables.txt");

		if(fruits_file==NULL)
			cout<<"\n\tImporting Fruits Data failed. File Missing\n\n";
		if(vegetables_file==NULL)
			cout<<"\n\tImporting Vegetables Data failed. File Missing\n\n";

		while(!fruits_file.eof()){
			fruits_file>>name>>location[0]>>location[1]>>volume_weight>>price>>calories>>quantity;
			fruits *temp= new fruits;
			temp->get_fruit_details(name,location[0],location[1],volume_weight,price,calories,quantity);
			total_items++;

			if (head_items==NULL){
				head_items=temp;
				tail_items=temp;
			}
			else{
				temp->update_previous(tail_items);
				tail_items->update_next(temp);
				tail_items=temp;
			}
			temp->auto_generate_purchase_id();
		}
		while(!vegetables_file.eof()){
			vegetables_file>>name>>location[0]>>location[1]>>volume_weight>>price>>calories>>quantity;
			vegetables *temp= new vegetables;
			temp->get_veg_details(name,location[0],location[1],volume_weight,price,calories,quantity);
			total_items++;

			if (head_items==NULL){
				head_items=temp;
				tail_items=temp;
			}
			else{
				temp->update_previous(tail_items);
				tail_items->update_next(temp);
				tail_items=temp;
			}
			temp->auto_generate_purchase_id();
		}
		fruits_file.close();
		vegetables_file.close();
	}

	void grocery_manage::add_vegetables(){
		vegetables *temp= new vegetables;
		temp->get_veg_details();
		total_items++;

		if (head_items==NULL){
			head_items=temp;
			tail_items=temp;
		}
		else{
			temp->update_previous(tail_items);
			tail_items->update_next(temp);
			tail_items=temp;
		}
		temp->auto_generate_purchase_id();
	}

	item** grocery_manage::find_item(char name[]){
		
		item *temp=head_items;
		int no_items=0,i=0;
		while(temp!=NULL){
			if(strcmp(temp->get_item_name(),name)==0)
				no_items++;
			temp=temp->get_next_item();
		}
		item **list=new item*[no_items+1];
		list[no_items]=NULL;
		temp=head_items;
		while(temp!=NULL){
			if(strcmp(temp->get_item_name(),name)==0){
				list[i]=temp;
				i++;
			}
			temp=temp->get_next_item();
		}
		for(i=0;i<no_items;i++){
			for(int j=0;j<no_items-1-i;j++){
				if(list[j]->get_price()>list[j+1]->get_price()){
					temp=list[j];
					list[j]=list[j+1];
					list[j+1]=temp;
				}
				else if(list[j]->get_price()==list[j+1]->get_price()){
					if (*list[j]>*list[j+1])					
					{				
						temp=list[j];
						list[j]=list[j+1];
						list[j+1]=temp;
					}
			}	}
		}
		return list;
	}
	
	

	void grocery_manage::display_items(){
		
		cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\tINVENTORY \n\n\t";
		for(int p=0;p<185;p++)
		cout<<"_";
		cout<<"\n\n\tNAME\t\tPURCHASE ID\t   LOCATION\t\tITEM TYPE\t\tPURCHASE TIME\t\t   QUANTITY    \t\t  WEIGHT    \t\t     PRICE        \tCALORIES\n\t";
		for(int p=0;p<185;p++)
			cout<<"_";
		item *temp=head_items;
		while(temp!=NULL){
			if(strcmp(temp->get_item_type(),"fruit")==0)
				temp->display_fruit_details();
			temp=temp->get_next_item();
		}
		temp=tail_items;
		while(temp!=NULL){
			if(strcmp(temp->get_item_type(),"vegetable")==0)
				temp->display_veg_details();
			temp=temp->get_previous_item();
		}
		cout<<"\n\n\t";
		for(int p=0;p<185;p++)
		cout<<"_";

	}

	void grocery_manage::display_items(char name[]){

				item **sell=find_item(name);
				
				if(sell[0]==NULL)
					cout<<"\n\n\t Item '"<<name<<"' Does Not Exist In the Inventory.\n";

				else{
					cout<<"\n\t";
					for(int p=0;p<185;p++)
					cout<<"_";
					cout<<"\n\n\tNAME\t\tPURCHASE ID\t   LOCATION\t\tITEM TYPE\t\tPURCHASE TIME\t\t   QUANTITY    \t\t  WEIGHT    \t\t     PRICE        \tCALORIES\n\n\t";
					for(int p=0;p<185;p++)
						cout<<"_";
					for(int i=0;sell[i]!=NULL;i++){
						if(strcmp(sell[i]->get_item_type(),"fruit")==0)
							sell[i]->display_fruit_details();
						else if(strcmp(sell[i]->get_item_type(),"vegetable")==0)
							sell[i]->display_veg_details();
					}
			 	}
				delete[] sell;

	}

	void grocery_manage::find_item_at_xy(int x,int y){
		item *temp=head_items;
		int check=0;
		while(temp!=NULL){
			if(temp->location_check(x,y)){
				check=1;
				cout<<"\n\t";
					for(int p=0;p<185;p++)
					cout<<"_";
					cout<<"\n\n\tNAME\t\tPURCHASE ID\t   LOCATION\t\tITEM TYPE\t\tPURCHASE TIME\t\t   QUANTITY    \t\t  WEIGHT    \t\t     PRICE        \tCALORIES\n\n\t";
					for(int p=0;p<185;p++)
						cout<<"_";
				if(strcmp(temp->get_item_type(),"fruit")==0){
					temp->display_fruit_details();
				}
				else if(strcmp(temp->get_item_type(),"vegetable")==0){
					temp->display_veg_details();
				}
				break;
			}
			temp=temp->get_next_item();
		}
		if(check==0)
			cout<<"\n\n\tNo Item Exists at this location.\n";
	}

	template <typename T>
	float grocery_manage::check_qty(item **sell,T qty,int size_ptr_arr){

		int size,i,j=0,check=0;
		float tot=0,tot_price=0;
		T num[size_ptr_arr];
		if(strcmp(sell[0]->get_item_type(),"fruit")==0){
			for(i=0;i<size_ptr_arr;i++){
				num[i]=sell[i]->get_qtyf();
				tot+=num[i];
				if(tot>=qty){
					check=1;
					break;
				}
			}
		}
		else{
			for(i=0;i<size_ptr_arr;i++){
				num[i]=sell[i]->get_qtyv();
				tot+=num[i];
				if(tot>=qty){
					check=1;
					break;
				}
			}	
		}
		if(!check)
			return 0;

		while(j<=i){
			if(num[j]<=qty){
				if(sell[j]->get_purchase_id()==head_items->get_purchase_id())
					head_items=head_items->get_next_item();
				else if(sell[j]->get_purchase_id()==tail_items->get_purchase_id())
					tail_items=tail_items->get_previous_item();

				tot_price+= sell[j]->check_qty(num[j]);
				qty-=num[j];
			}
			else{
				tot_price+= sell[j]->check_qty(qty);
				break;
			}
			j++;
		}
		return tot_price;
	}
	
	template <typename T>
	float grocery_manage::check_cal(item **sell,float cal,int size_ptr_arr){
		int i=0,choice,check=0,j;
		item *temp;
		float tot=0,tot_price=0;
		T num[size_ptr_arr],tot_qty=0,qty,qt[size_ptr_arr];
		
		for(i=0;i<size_ptr_arr;i++)
			for(int j=0;j<size_ptr_arr-1-i;j++)
				if(sell[j]->get_cal()>sell[j+1]->get_cal()){
					temp=sell[j];
					sell[j]=sell[j+1];
					sell[j+1]=temp;
				}
				

		for(i=0;i<size_ptr_arr;i++){
			num[i]=sell[i]->get_cal();
			if(strcmp(sell[0]->get_item_type(),"fruit")==0)
				qt[i]=sell[i]->get_qtyf();
			else
				qt[i]=sell[i]->get_qtyv();

			tot+=num[i]*qt[i];
			if(tot>=cal){
				check=1;
				break;
			}
		}
		if(check==0)
			return 0.0;
		j=0;

		while(j<=i){
			if(num[j]*qt[j]<=cal){

				if(sell[j]->get_purchase_id()==head_items->get_purchase_id())
					head_items=head_items->get_next_item();
				else if(sell[j]->get_purchase_id()==tail_items->get_purchase_id())
					tail_items=tail_items->get_previous_item();

				float price_temp=sell[j]->get_price();
				qty= sell[j]->check_cal(num[j]*qt[j]);
				tot_qty+=qty;
				tot_price+=qty*price_temp;
				cal-=num[j]*qt[j];
			}
			else{
				qty= sell[j]->check_cal(cal);
				tot_qty+=qty;
				tot_price+=qty*(sell[j]->get_price());
				break;
			}
			j++;
		}
		cout<<"\n\n\t\tTotal quantity Sold  \t:\t "<<tot_qty;
		cout<<((strcmp(sell[0]->get_item_type(),"fruit")==0)?" units ":" kg ");
		return tot_price;
	}

	void grocery_manage::sell_item(){
		char name[20],proceed='y';
		float total_price=0,total_sold=0;
		int no_same_item=0,choice,i;

		cout<<"\n\n\t\t\tSell Item";

		while(proceed=='y'||proceed=='Y'){
		
				no_same_item=0;

				cout<<"\n\n\t\tEnter the item name : ";cin>>name;
				item **sell=find_item(name);
				
				for(i=0;sell[i]!=NULL;i++)
					no_same_item++;

				if(sell[0]==NULL){
					cout<<"\n\tSorry. Item Not Found.";
				}
				else{
					if(strcmp(sell[0]->get_item_type(),"fruit")==0){
							
						i=0;
						cout<<"\n\tNAME\t\tPURCHASE ID\t   LOCATION\t\tITEM TYPE\t\tPURCHASE TIME\t\t   QUANTITY    \t\t  WEIGHT    \t\t     PRICE        \tCALORIES\n\n";
						while(i<no_same_item){
							sell[i]->display_fruit_details();
							i++;
						}
					
						cout<<"\n\n\t1.Sell by Quantity (in units)\n\t2.Sell by calories\n\n\tEnter your choice (No.) : ";cin>>choice;
						if(choice==1){
							float price;
							int qty;
							cout<<"\n \n \tEnter the Quantity : ";cin>>qty;
							price=check_qty(sell,qty,no_same_item);
							if(price==0)
								cout<<"\n\tSorry Insufficient Stock.\n\n";
							else{
								cout<<"\n\n\tTotal Price for the item  \t:\t"<<price<<"\n";
								for(int p=0;p<120;p++)
									cout<<"_";
								total_price+=price;
							}
						}
						else if(choice==2){
							float cal,price;
							cout<<"\n \n \tEnter the Min. Required calories : ";cin>>cal;
							price=check_cal<int>(sell,cal,no_same_item);
							if(price==0)
								cout<<"\n\tSorry Insufficient Stock.\n\n";
							else{
								cout<<"\n\n\tTotal Price for the item  \t:\t"<<price<<"\n";
								for(int p=0;p<120;p++)
									cout<<"_";
								total_price+=price;
							}
						}
						else
							cout<<"\n\n\tInvalid Choice.\n";
					}						
					else if(strcmp(sell[0]->get_item_type(),"vegetable")==0){
						i=0;
						cout<<"\n\tNAME\t\tPURCHASE ID\t   LOCATION\t\tITEM TYPE\t\tPURCHASE TIME\t\t   QUANTITY    \t\t  WEIGHT    \t\t     PRICE        \tCALORIES\n\n";
						while(i<no_same_item){
							sell[i]->display_veg_details();
							i++;
						}
						cout<<"\n\n\t1.Sell by Quantity (in units)\n\t2.Sell by calories\n\n\tEnter your choice (No.) : ";cin>>choice;
						if(choice==1){
							float qty,price;
							cout<<"\n \n \tEnter the Quantity : ";cin>>qty;
							price=check_qty(sell,qty,no_same_item);
							if(price==0)
								cout<<"\n\tSorry Insufficient Stock.\n\n";
							else{
								cout<<"\n\n\tTotal Price for the item  \t:\t"<<price<<"\n";
								for(int p=0;p<120;p++)
									cout<<"_";
								total_price+=price;
							}
						}
						else if(choice==2){
							float cal,price;
							cout<<"\n \n \tEnter the Required calories : ";cin>>cal;
							price=check_cal<float>(sell,cal,no_same_item);
							if(price==0)
								cout<<"\n\tSorry Insufficient Stock.\n\n";
							else{
								cout<<"\n\n\tTotal Price for the item  \t:\t"<<price<<"\n";
								for(int p=0;p<120;p++)
									cout<<"_";
								total_price+=price;
							}
						}
						else
							cout<<"\n\n\tInvalid Choice.\n";
					}

					else 
						cout<<"\n ERROR\n";
					
					

				}
			
			cout<<"\n\n\n\t Sell more items ? (y/n) : ";cin>>proceed;
			delete[] sell;
		}
		cout<<"\n\n\t\t Total Items Sold\t:\t"<<total_sold;
		cout<<"\n\t\t Total Amount Tendered\t:\t"<<total_price<<"\n";
		for(int p=0;p<120;p++)
			cout<<"_";

	}

	void grocery_manage::open_grocery(){
		char cont='y',more='y';
		int chc;
		import_data();
		cout<<"\n\n\t\t\t\t\tGROCERY MANAGEMENT SYSTEM\n";
		
		while(tolower(cont)=='y'){
			more='y';
			cout<<"\n\n\n\n\t\t\t1.Add Items to inventory.\n\t\t\t2.Sell Items\n\t\t\t3.Display the Entire Inventory\n\t\t\t4.Get details of an item\n\t\t\t5.Get the item at the location X,Y\n\t\t\t6.Quit Application";
			cout<<"\n\n\n\n\n\t\t\tEnter Your choice (No.)  : ";cin>>chc;
			switch(chc){
				case 	1	:	int val;
								cout<<"\n\n\t\t\tADD ITEM";
								while(tolower(more)=='y'){
									cout<<"\n\n\t1.Add Fruits\n\t2.Add Vegetables\n\n\tEnter you choice : ";cin>>val;
									switch(val){
										case 	1	:	add_fruits();
														break;
										case 	2	:	add_vegetables();
														break;
										default		: cout<<"\n\n\tInvalid Choice\n";
									}	

									cout<<"\n\nAdd More Items ? (y/n) \t:\t ";cin>>more;					
								}
								break;

				case 	2	:	sell_item();
								break;

				case 	3	:	display_items();
								break;


				case 	4	:	
								char name[20];
								cout<<"\n\n\t\t\t\tGET ITEM DETAILS\n";
								while(tolower(more)=='y'){
									cout<<"\n\n\tEnter the Item Name \t:\t ";cin>>name;
									display_items(name);

									cout<<"\n\n\t\tLook For Another item ? (y/n) \t:\t";cin>>more;
								}
								break;

				case 	5	:	
								int location[2];
								cout<<"\n\n\t\t\t\tGET ITEM AT LOCATION  ( X Y ) :\n";
								while(tolower(more)=='y'){
									cout<<"\n\n\tEnter the Location \t:\t ";cin>>location[0]>>location[1];
									find_item_at_xy(location[0],location[1]);

									cout<<"\n\n\t\tLook For Another Location ? (y/n) \t:\t";cin>>more;
								}
								break;
				case	6	:	cont='n';
							break;
				default		:	cout<<"\n\n\tInvalid Choice\n";
			}
		 
		}	
	}
