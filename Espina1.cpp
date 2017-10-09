
#include <iostream.h>
#include <conio.h>
#include <math.h>
#include <iomanip.h>

int main()
{
   float   Amount, Interest, Months, Payment, Principal, PayInterest, 
   TotalInterest=0, TotalPrincipal=0,TotalMonths, Balance;
   int pageNum =1,Mon=1;
   
  
   bool finished = false; 
   
   clrscr();

   cout << "Please enter the amount of the loan: ";
   cin  >> Amount;
   cout << endl << "Please enter the annual rate of interest: ";
   cin  >> Interest;
   cout << endl << "Please enter the number of months of financing: ";
   cin  >> Months;

   Balance = Amount;
   TotalMonths=Months;
   
   Interest = Interest/100;
   Payment  = Amount*Interest/(12*(1 - pow(1 + Interest/12, -Months)));
   
do
{
//Asks user to enter the appropriate information to calculate the monthly payment
cout << "Page " << pageNum <<endl;
cout << "======"<<"\n\n";

cout << setprecision(0)<<fixed;
cout << "Amount Borrowed: " << Amount <<endl;

cout << setprecision(2)<<fixed;
cout << "Annual Interset Rate: " <<(Interest*100)<<"%"<<endl;

cout << setprecision(0)<<fixed;
cout << "Months of Financing: "<< Months<<endl;

cout << setprecision(2)<<fixed;
cout << endl << endl << "The monthly payments will be $" << Payment <<endl;
cout <<"=================================================================="<<"\n\n";

//Header for schedule 
cout <<setw(37)<<"TOTAL"<<setw(12)<<"TOTAL"<<endl;
cout <<"MON"<<setw(12)<<"PRINCIPAL"<<setw(10)<<"INTEREST"<<setw(13)
<<"PRINCIPAL"<<setw(12)<<"INTEREST"<<setw(14)<<"BALANCE"<<endl;

cout <<"==="<<setw(12)<<"========="<<setw(10)<<"========"<<setw(13)
<<"========="<<setw(13)<<"========="<<setw(14)<<"========="<<endl; 
 
//Displays schedule 12 months at a time
  for (int i=0; i<12; i++)
  {
  //Interest
  PayInterest=Balance*(Interest/12);
  
  //Principal
  Principal=Payment-PayInterest;
  
  //Total Principal
  TotalPrincipal+=Principal;
  
  //Totla Interest
  TotalInterest+=PayInterest;
  
  //Balance
  Balance-=Principal;
 
  cout << setprecision(2)<<fixed;
  //This will add a space before numbers less then 10
  if(Mon<10)
  {
   cout<<" ";
  }
  //displays the appropriate information
  cout<<Mon<<"."<<setw(10)<<Principal<<setw(11)<<PayInterest<<setw(13)
  <<TotalPrincipal<<setw(13)<<TotalInterest<<setw(15)<<Balance<<endl;
  Mon++;
  
  } 
  
   cout << "press any key to continue..." <<"\n\n";
   //this will pause the program untill a key is pressed
   getch();
   
   //if months is bigger then 12 then keep going else stop
   if(TotalMonths>12)
   {
   TotalMonths-=12;
   pageNum++;
   }
   else
   {
   finished = true;
   }
   
}
while(!finished);
   return 0;
}