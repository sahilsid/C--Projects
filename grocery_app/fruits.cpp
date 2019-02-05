#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include<math.h>
#include<iomanip>
#include "item.h"
#include "fruits.h"
using namespace std;


	fruits::fruits(){
		weight_per_unit=0;
		price_per_unit=0;
		calories=0;
		quantity_units=0;
	}



	void fruits::get_fruit_details(){

		char name[20];
		int location[2];
		cout<<"\n\tFruit Name\t:\t";cin>>name;
		cout<<"\n\tLocation (X Y)\t:\t";cin>>location[0]>>location[1];
		cout<<"\n\tQuantity (units)\t:\t";cin>>quantity_units;
		cout<<"\n\tWeight per unit\t:\t";cin>>weight_per_unit;
		cout<<"\n\tPrice per unit\t:\t";cin>>price_per_unit;
		cout<<"\n\tCalories\t:\t";cin>>calories;
		this->update(location,"fruit",name);
	}
	void fruits::get_fruit_details(char *name,int x,int y,float weight,float price,float cal,float qty){
		int location[2];
		location[0]=x;location[1]=y;
		quantity_units=qty;
		weight_per_unit=weight;
		price_per_unit=price;
		calories=cal;
		this->update(location,"fruit",name);
	}
	float fruits::get_cal(){
		return calories;
	}
	int fruits::get_qtyf(){
		return quantity_units;
	}
	void fruits::display_fruit_details(){
		print_item();
		cout<<"\t\t"<<setfill(' ')<<setw(7)<<quantity_units<<" units";
		cout<<"\t\t"<<setfill(' ')<<setw(7)<<weight_per_unit<<" /unit";
		cout<<"\t\t"<<setfill(' ')<<setw(7)<<price_per_unit<<" /unit";
		cout<<"\t\t"<<calories;
	}

	float fruits::check_qty(float a){
		float price=0;
		if(quantity_units<a)
			return 0;
		else if(quantity_units==a){
			cout<<"\n\tNAME\t\tPURCHASE ID\t   LOCATION\t\tITEM TYPE\t\tPURCHASE TIME\t\t\n";
			print_item();
			cout<<"\n\n\tUnit Price \t:\t"<<price_per_unit;
			cout<<"\n\tCalories /unit \t:\t"<<calories;			
			cout<<"\n\tQuantity Sold\t:\t"<<a;
			price=a*price_per_unit;
			cout<<"\n\tNet Price \t:\t"<<price<<"\n\n";
			cout<<"\n\tThe Above Item will be removed as the stock is over.\n";
			remove_item(this);
			for(int p=0;p<120;p++)
				cout<<"_";
		}
		else{
			cout<<"\n\tNAME\t\tPURCHASE ID\t   LOCATION\t\tITEM TYPE\t\tPURCHASE TIME\t\t \n";
			print_item();
			cout<<"\n\n\t Unit Price \t:\t"<<price_per_unit;
			cout<<"\n\tCalories /unit\t:\t"<<calories;			
			cout<<"\n\tQuantity Sold\t:\t"<<a;
			price=a*price_per_unit;
			cout<<"\n\tNet Price \t:\t"<<price<<"\n\n";
			quantity_units-=a;
			for(int p=0;p<120;p++)
				cout<<"_";
		}
		return price;
	}

	float fruits::check_cal(float a){
		float price,totcal=calories*quantity_units;
		int qty;
		if(totcal<a)
			return 0;
		else if(totcal==a){
			qty=quantity_units;
			cout<<"\n\tNAME\t\tPURCHASE ID\t   LOCATION\t\tITEM TYPE\t\tPURCHASE TIME\t\t\n";
			print_item();
			cout<<"\n\n\tQuantity Sold \t:\t"<<quantity_units;
			cout<<"\n\tCalories /unit\t:\t"<<calories;	
			cout<<"\n\tTotal Calories\t:\t"<<calories*qty;					
			cout<<"\n\tUnit Price \t:\t"<<price_per_unit;
			cout<<"\n\tNet Price \t:\t"<<price_per_unit*qty<<"\n\n";
			cout<<"\n\tThe Above Item will be removed as the stock is over.\n";
			remove_item(this);
			for(int p=0;p<120;p++)
				cout<<"_";
		}
		else{
			qty=ceil(a/calories);
			cout<<"\n\tNAME\t\tPURCHASE ID\t   LOCATION\t\tITEM TYPE\t\tPURCHASE TIME\t\t\n";
			print_item();
			cout<<"\n\n\tQuantity Sold \t:\t"<<qty;	
			cout<<"\n\tCalories /unit\t:\t"<<calories;
			cout<<"\n\tTotal Calories\t:\t"<<calories*qty;						
			cout<<"\n\tUnit Price \t:\t"<<price_per_unit;
			price=qty*price_per_unit;
			cout<<"\n\tNet Price \t:\t"<<price<<"\n\n";
			quantity_units-=qty;
			for(int p=0;p<120;p++)
				cout<<"_";
		}
		return qty;
	}
	
	float fruits::get_price(){
		return price_per_unit;
	}


