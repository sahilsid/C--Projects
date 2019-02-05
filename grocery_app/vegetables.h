#ifndef VEGETABLES_H
#define VEGETABLES_H



class vegetables:private item
{
	float price_per_kg;
	float volume_per_kg;
	float quantity_kg;
	float calories;
public:
	vegetables();
private:
	void get_veg_details();
	void get_veg_details(char *name,int x,int y,float weight,float price,float cal,float qty);

	void display_veg_details();
	float get_cal();
	float check_qty(float a);

	float check_cal(float a);

	float get_price();
	float get_qtyv();

 	friend class grocery_manage;	
};

#endif
