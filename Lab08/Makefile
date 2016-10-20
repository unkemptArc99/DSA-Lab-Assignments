######################################################
#This Makefile is created to help IC250 students
#Created By:
#Aditya Nigam
#SCEE
#IIT Mandi
#Please modify according to your need 
######################################################

inc =  -lm 

all: my_fun.o main.o
	gcc -w -o my_exe my_fun.o main.o -Wno-deprecated -I ${inc} 

main.o: main.c
	gcc -c main.c -Wno-deprecated -I ${inc}

my_fun.o: my_lib.h my_fun.c
	gcc -c my_fun.c -Wno-deprecated -I ${inc}
clean:
	rm -f *.o
