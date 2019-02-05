#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include<math.h>
#include<iomanip>
using namespace std;
#include "item.h"
#include "vegetables.h"



	vegetables::vegetables(){
		price_per_kg=0;
		volume_per_kg=0;
		quantity_kg=0;
	}

	void vegetables::get_veg_details(){
		char name[20];
		int location[2];
		cout<<"\n\tName\t:\t";cin>>name;
		cout<<"\n\tLocation (X Y)\t:\t";cin>>location[0]>>location[1];
		cout<<"\n\tQuantity (in kg)\t:\t";cin>>quantity_kg;
		cout<<"\n\tVolume per kg\t:\t";cin>>volume_per_kg;
		cout<<"\n\tPrice per kg\t:\t";cin>>price_per_kg;
		cout<<"\n\tCalories\t:\t";cin>>calories;
		this->update(location,"vegetable",name);
	}
	void vegetables::get_veg_details(char *name,int x,int y,float weight,float price,float cal,float qty){
		int location[2];
		location[0]=x;location[1]=y;
		quantity_kg=qty;
		volume_per_kg=weight;
		price_per_kg=price;
		calories=cal;
		this->update(location,"vegetable",name);
	}

	void vegetables::display_veg_details(){
		print_item();
		cout<<"\t\t"<<setfill(' ')<<setw(7)<<quantity_kg<<" kg";
		cout<<"\t\t"<<setfill(' ')<<setw(7)<<volume_per_kg<<" /kg";
		cout<<"\t\t"<<setfill(' ')<<setw(7)<<price_per_kg<<" /kg";
		cout<<"\t\t"<<calories;
	}
	float vegetables::get_cal(){
		return calories;
	}

	float vegetables::check_qty(float a){
		float price;
		if(quantity_kg<a)
			return 0;
		else if(quantity_kg==a){
			cout<<"\n\tNAME\t\tPURCHASE ID\t   LOCATION\t\tITEM TYPE\t\tPURCHASE TIME\t\t\n";
			print_item();
			cout<<"\n\n\t Unit Price \t:\t"<<price_per_kg;
			cout<<"\n\t Calories /kg \t:\t"<<calories;
			cout<<"\n\t Quantity Sold\t:\t"<<a;
			cout<<"\n\t Total Calories\t:\t"<<calories*a;					
			price=a*price_per_kg;
			cout<<"\n\t Net Price \t:\t"<<price<<"\n\n";
			cout<<"\n\tThe Above Item will be removed as the stock is over.\n";
			remove_item(this);
			for(int p=0;p<120;p++)
				cout<<"_";
		}
		else{
			cout<<"\n\tNAME\t\tPURCHASE ID\t   LOCATION\t\tITEM TYPE\t\tPURCHASE TIME\t\t \n";
			print_item();
			cout<<"\n\n\t Unit Price \t:\t"<<price_per_kg;
			cout<<"\n\t Calories /kg\t:\t"<<calories;
			cout<<"\n\t Quantity Sold\t:\t"<<a;
			cout<<"\n\t Total Calories \t:\t"<<calories*a;					
			price=a*price_per_kg;
			cout<<"\n\t Net Price \t:\t"<<price<<"\n\n";
			quantity_kg-=a;
			for(int p=0;p<120;p++)
				cout<<"_";
			
		}
		return price;
	} 

	float vegetables::check_cal(float a){
		float price,totcal=calories*quantity_kg,qty;
		if(totcal<a)
			return 0;
		else if(totcal==a){
			qty=quantity_kg;
			cout<<"\n\tNAME\t\tPURCHASE ID\t   LOCATION\t\tITEM TYPE\t\tPURCHASE TIME\t\t\n";
			print_item();
			cout<<"\n\n\t Calories /kg\t:\t"<<calories;							
			cout<<"\n\t Unit Price \t:\t"<<price_per_kg;
			cout<<"\n\t Quantity Sold \t:\t"<<quantity_kg;
			cout<<"\n\t Total Calories\t:\t"<<calories*qty;
			cout<<"\n\t Net Price \t:\t"<<price_per_kg*qty<<"\n\n";
			cout<<"\n\tThe Above Item will be removed as the stock is over.\n";
			remove_item(this);
			for(int p=0;p<120;p++)
				cout<<"_";
		}
		else{
			qty=a/calories;
			cout<<"\n\tNAME\t\tPURCHASE ID\t   LOCATION\t\tITEM TYPE\t\tPURCHASE TIME\t\t \n";
			print_item();
			cout<<"\n\n\t Calories /kg\t:\t"<<calories;		
			cout<<"\n\t Unit Price \t:\t"<<price_per_kg;
			cout<<"\n\t Quantity Sold\t:\t"<<qty;
			cout<<"\n\t Total Calories\t:\t"<<calories*qty;					
			price=qty*price_per_kg;
			cout<<"\n\t Net Price \t:\t"<<price<<"\n\n";
			quantity_kg-=qty;
			for(int p=0;p<120;p++)
				cout<<"_";
		}
		return qty;
	}

	float vegetables::get_price(){
		return price_per_kg;
	}
	float vegetables::get_qtyv(){
		return quantity_kg;
	}

