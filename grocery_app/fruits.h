#ifndef FRUITS_H
#define FRUITS_H



class fruits:public item
{
	float weight_per_unit;
	float price_per_unit;
	float calories;
	int quantity_units;
public:
	fruits();


private:
	void get_fruit_details();
	void get_fruit_details(char *name,int x,int y,float weight,float price,float cal,float qty);
	float get_cal();
	int get_qtyf();
	void display_fruit_details();
	float check_qty(float a);

	float check_cal(float a);
	
	float get_price();
	friend class grocery_manage;

};


#endif
