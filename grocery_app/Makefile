all: final

final:  main.o item.o fruits.o vegetables.o grocery_manage.o 
	g++  main.o item.o fruits.o vegetables.o grocery_manage.o  -o final

main.o: main.cpp
	g++ -c main.cpp

item.o: item.cpp 
	g++ -c item.cpp

fruits.o: item.cpp fruits.cpp 
	g++ -c  fruits.cpp 

vegetables.o: vegetables.cpp
	g++ -c vegetables.cpp

grocery_manage.o: grocery_manage.cpp
	g++ -c grocery_manage.cpp



clean:
	rm *o final
