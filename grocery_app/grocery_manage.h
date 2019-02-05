#ifndef GROCERY_MANAGE_H
#define GROCERY_MANAGE_H

class grocery_manage
{
	int total_items;
	item *head_items;
	item *tail_items;
public:
	grocery_manage();
	~grocery_manage();
	void open_grocery();	
private:
	void add_fruits();
	void import_data();

	void add_vegetables();
	item **find_item(char name[]);
	void display_items();
	void display_items(char name[]);
	void find_item_at_xy(int x,int y);
	template <typename T>
	float check_qty(item **sell,T qty,int size_ptr_arr);
	template <typename T>
	float check_cal(item **sell,float cal,int size_ptr_arr);
	void sell_item();

};


#endif
