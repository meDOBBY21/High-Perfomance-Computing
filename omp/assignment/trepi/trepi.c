//Program to find the area under the cure
//Special case:Finding value of pi using 

//f(x)=4/(1+x^2)

//Reminder: This will give area as pi only if the start and end points are 0 and 1 respectively

#include<stdio.h>

//function to find the value of f(x)

double fun(float x)
{
	return 4/(1+(x*x));
}


void main()
{
	
	double area,h; //declaring area and h as double 
	int a=0,b=1;
	long n=1000000000; // start(a),end(b) and number of trepeziums(n) are going to be integers 

	// printf("Enter the start point:");							
	// scanf("%d",&a);									//taking in values of a,b,n from user		
	// printf("Enter the end point:");
	// scanf("%d",&b);
	// printf("Enter the number of iterrations:");
	// scanf("%d",&n);

	h=(b-a)/(double)n;			//finding the distance between two || lines iin trapezium
	area=(fun(a)+fun(b))/2.0;	//finding function values of 1st and last points and adding it to area

	for(int i=1;i<n;i++)
		area+=fun(a+(i*h));		//calling the function to find the value of f(x) and adding it to area		
	

	area*=h;			//multiplying the diatance betweeen || lines to get the final answer			

	printf("\nArea:%.10f\n",area); //printing the area(value of pi) with 50 digit precision

}
