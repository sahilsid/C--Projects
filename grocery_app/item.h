#ifndef ITEM_H
#define ITEM_H

#include<time.h>
class item
{
	long int purchase_id;
	int location[2];
	char item_type[10];
	char item_name[20];
	time_t purchase_time;
	item *next_item;
	item *previous_item;

	
public:
	
	item();

protected:
	void disp_location();
	
	void remove_item(item *cur);
	void auto_generate_purchase_id();



	virtual void display_veg_details(){}
	virtual void display_fruit_details(){}
	virtual float get_price(){}
	virtual float get_cal(){}
	virtual int get_qtyf(){}
	virtual float get_qtyv(){}
	virtual float check_cal(float a){}
	virtual float check_qty(float a){}

	void print_item();
	void update(int *loc,const char *type,char *name);
	int location_check(int x,int y);
	int get_purchase_id();
	void update_previous(item* previous);
	float get_distance();
	bool operator > (item &a);
	void update_next(item* next);
	item* get_next_item();
	item* get_previous_item();
	char* get_item_name();
	char* get_item_type();

	friend class grocery_manage;

};
#endif
