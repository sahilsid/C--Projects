
#### AUTHOR	:	SAHIL SIDHEEKH
#### DATE	:	28/8/18

#### TO RUN THE CODE :
	1.Extract the 2017CSB1104_LAB1.tgz file to obtain 'grocery_app' folder.
	2.Enter folder 'grocery_app' and open terminal from this window.
	3.Type 'make' in the terminal.
	4.Once the program has been compiled, type './final' to run the program.


#### FEATURES	:
	1.The program can add items dyamically.
	2.It can sel items based on
		A.Quantity :  It is of float type for vegetables and int type for fruits.
					  Incase of multiple items of the same type, the program sells the cheapest item first,and if the prices are same, the item at the nearest location is sold.
					  The nearest location is calculated assuming the user to be at (0,0) ,as the square root of the sum of the squares of the location values.   

		B.Calories :  It is sells the quantity for which the calorie content is greater than or equal to the min calorie requirement specified.					  
					  Incase of multiple items of the same type, the program sells the items such that the quantity is maximimum. 


	3.Dislay the entire inventory.
	4.Display the details of an item inputed by the user.
	5.Display the details of an item at a specified location. The location is inputed as X Y.


##### NOTE	:
	1.Please run in full screen mode
	2.Kindly check the type of input to be inputed before typing.
	3,Do not input characters/strings to integer inputs.  
