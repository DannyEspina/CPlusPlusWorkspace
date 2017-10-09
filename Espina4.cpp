/**************************************************************************
*                                                                         *
*     Program Filename:  Espina4.cpp                                      *
*     Author          :  Daniel Espina                                    *
*     Date Written    :  March 27, 2016                                   *
*     Purpose         :  To solve the "Dog and Cat Problem"               *
*     Input from      :  Console                                          *
*     Output to       :  Screen                                           *
*                                                                         *
**************************************************************************/
#include <iostream.h>
#include "Point.h"
int main()
{
Point Cat;
Point Dog;

float X, Y, Z, A, B, dogStepSize, catStepSize;
bool stop= false;

cout<<"Please enter X: ";
cin>>X;
cout<<endl<<"Please enter Y: ";
cin>>Y;
cout<<endl<<"Please enter Z: ";
cin>>Z;
cout<<endl<<"Please enter A: ";
cin>>A;
cout<<endl<<"Please enter B: ";
cin>>B;
dogStepSize=.5;
catStepSize=(B/A)*dogStepSize;

Dog.setX(X);
Dog.setY(Y);

while(!stop)
{
Dog.moveTowardPoint(Cat.getX(), Cat.getY(), dogStepSize);
Cat.moveInDirection(0.0, catStepSize);

Z-= catStepSize;

if(Z<0)
{
stop=true;
cout<<endl<<"The cat made it safely to the tree."<<endl;
}
else if(Dog.getY()<=0&&Dog.getX()>=Cat.getX())
{
stop=true;
cout<<endl<<"The dog caught the cat."<<endl;
}
//end if
}
//end while
}
//end main function