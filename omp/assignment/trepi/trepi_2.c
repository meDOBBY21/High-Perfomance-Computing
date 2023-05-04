//Program to find the area under the cure
//Special case:Finding value of pi using 

//f(x)=4/(1+x^2)

//Reminder: This will give area as pi only if the start and end points are 0 and 1 respectively

#include<stdio.h>

void main()
{
	
	double area=3.0,h; //declaring area and h as double 
	int a=0,b=1;
	long n=1000000000; // start(a),end(b) and number of trepeziums(n) are going to be integers 

	h=1.0/n;			//finding the distance between two || lines iin trapezium	//finding function values of 1st and last points and adding it to area

	for(int i=1;i<n;i++)
		area+=4.0/(1+((i*h)*(i*h)));		//calling the function to find the value of f(x) and adding it to area		
	

	area*=h;			//multiplying the diatance betweeen || lines to get the final answer			

	printf("\nArea:%.10f\n",area); //printing the area(value of pi) with 50 digit precision

}
