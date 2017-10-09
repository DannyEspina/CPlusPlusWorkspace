/**************************************************************************
*                                                                         *
*     Program Filename:  Espina6A.cpp                                     *
*     Author          :  Daniel Espina                                    *
*     Date Written    :  April 8, 2016                                    *
*     Purpose         :  To map records into a file                       *
*     Input from      :  Keyboard and random.dat                          *
*     Output to       :  Screen and random.dat                            *
*                                                                         *
**************************************************************************/
#include <iostream.h>
#include <fstream.h>

int hash(string);
int main()
{
fstream RandomFile;
char answer='z';
bool notDone=true, noConflict,found,noErrors;
int index,count,spaces;
string SSN,lastName,firstName,major,creditHours,GPA;
string remove, tombSSN, record;
RandomFile.open("random.dat", ios::in | ios::out);
while(notDone)
   {
   cout<<"Please specify the transactons you wish to do "<<endl;
   cout<<"A    Add a record"<<endl;
   cout<<"D    Delete a record"<<endl;
   cout<<"S    Display a record"<<endl;
   cout<<"N    Change last name"<<endl;
   cout<<"M    Change major"<<endl;
   cout<<"H    Change hours"<<endl;
   cout<<"G    Change GPA"<<endl;
   cout<<"X    Stop the program"<<endl;
   cout<<"---------------------------"<<endl;
   cin>>answer;
   
   if(toupper(answer)==65)
      {
      cout<<"Please enter the SSN: "<<endl;
      cin>>SSN;
      cout<<"Please enter the last name: "<<endl;
      cin>>lastName;
      cout<<"Please enter the first name: "<<endl;
      cin>>firstName;
      cout<<"Please enter the major: "<<endl;
      cin>>major;
      cout<<"Please enter total credit hours: "<<endl;
      cin>>creditHours;
      cout<<"Please enter current GPA: "<<endl;
      cin>>GPA;
      cout<<"SSN: "<<SSN<<endl;
      index = hash(SSN);
      cout<<"index: "<<index<<endl;
      noConflict=false;
      while(!noConflict)
      {
      RandomFile.seekp(index*58, ios::beg);
      if(RandomFile.peek()=='*'||RandomFile.peek()=='#')
      {
      RandomFile<<SSN;
      RandomFile.seekp(index*58+9, ios::beg);
      RandomFile<<lastName;
      RandomFile.seekp(index*58+19, ios::beg);
      RandomFile<<firstName;
      RandomFile.seekp(index*58+29, ios::beg);
      RandomFile<<major;
      if(creditHours.length()>2)
         {
         RandomFile.seekp(index*58+49, ios::beg);
         RandomFile<<creditHours;
         }
      else
         {
         RandomFile.seekp(index*58+50, ios::beg);
         RandomFile<<creditHours;
         }
      RandomFile.seekp(index*58+52, ios::beg);
      RandomFile<<GPA;
       noConflict=true;
      }
      else
      {
      index++;
      if(index>60)
         {
         index=0;
         }
       
       }
       }
      }
   else if(toupper(answer)==68)
   {
   noErrors=false;
   count=0;
   cout<<"Please enter the SSN of the record you wish to delete: "<<endl;
   cin>>SSN;
   index =hash(SSN);
 
   while(!noErrors)
   {
   RandomFile.seekg(index*58,ios::beg);
   getline(RandomFile, record);
   tombSSN=record.substr(0,9);
  
   if(SSN.compare(tombSSN)==0)
   {

   RandomFile.seekp(index*58,ios::beg);
   RandomFile<<'#';
   noErrors=true;
   cout<<endl;
   cout<<"Record deleted!"<<endl<<endl;
   }
   else if(count>60)
   {
   cout<<"record not found. Please try again."<<endl;
   cout<<"Please enter the SSN of the record you wish to delete: "<<endl;
   cin>>SSN;
   index =hash(SSN);
   RandomFile.seekg(index*58,ios::beg);
   getline(RandomFile, record);
   tombSSN=record.substr(0,9);
   count=0;
   }
   else
      {
      index++;
      count++;
      if(index>60)
         {
         index=0;
         }
       
       }
   }
   }
   else if(toupper(answer)==83)
   {
   noErrors=false;
   count=0;
   
   cout<<"Please enter the SSN of the record you wish to display: "<<endl;
   cin>>SSN;
   index=hash(SSN);
   while(!noErrors)
   {
   RandomFile.seekg(index*58,ios::beg);
   getline(RandomFile, record);
   tombSSN=record.substr(0,9);
  
   if(SSN.compare(tombSSN)==0)
   {
   cout<<"-------------------------------------------------------------------"<<endl<<endl;
   cout<<record<<endl<<endl;
   cout<<"-------------------------------------------------------------------"<<endl<<endl;
   noErrors=true;
   }
   else if(count>60)
   {
   cout<<"record not found. Please try again."<<endl;
   cout<<"Please enter the SSN of the record you wish to display: "<<endl;
   cin>>SSN;
   index =hash(SSN);
   RandomFile.seekg(index*58,ios::beg);
   getline(RandomFile, record);
   tombSSN=record.substr(0,9);
   count=0;
   }
   else
      {
      index++;
      count++;
      if(index>60)
         {
         index=0;
         }
       
       }
   }

   }
   else if(toupper(answer)==78)
   {
   noErrors=false;
   count=0;
   cout<<"Please enter the SSN of the record you wish to change the last name: "<<endl;
   cin>>SSN;
   index =hash(SSN);
 
   while(!noErrors)
   {
   RandomFile.seekg(index*58,ios::beg);
   getline(RandomFile, record);
   tombSSN=record.substr(0,9);
  
   if(SSN.compare(tombSSN)==0)
   {
   cout<<"Please enter the new last name: "<<endl;
   cin>>lastName;
   RandomFile.seekp(index*58+9, ios::beg);
   RandomFile<<lastName;
   spaces=10-lastName.length();
   cout<<"spaces: "<<spaces;
   if(spaces>0)
      {
      for(int i=lastName.length();i<=spaces; i++)
         {
         RandomFile.seekp((index*58+9+i),ios::beg);
         RandomFile<<" ";
         }
      }
   cout<<endl;
   cout<<"Record changed successfully!"<<endl<<endl;
   noErrors=true;
   }
   else if(count>60)
   {
   cout<<"record not found. Please try again."<<endl;
   cout<<"Please enter the SSN of the record you wish to change the last name: "<<endl;   
   cin>>SSN;
   index =hash(SSN);
   RandomFile.seekg(index*58,ios::beg);
   getline(RandomFile, record);
   tombSSN=record.substr(0,9);
   count=0;
   }
   else
      {
      index++;
      count++;
      if(index>60)
         {
         index=0;
         }
       
       }
   }

   }
   else if(toupper(answer)==77)
   {
   noErrors=false;
   count=0;
   cout<<"Please enter the SSN of the record you wish to change the major: "<<endl;
   cin>>SSN;
   index =hash(SSN);
 
   while(!noErrors)
   {
   RandomFile.seekp(index*58, ios::beg);;
   getline(RandomFile, record);
   tombSSN=record.substr(0,9);
  
   if(SSN.compare(tombSSN)==0)
   {
   cout<<"Please enter the new major: "<<endl;
   cin>>major;
   RandomFile.seekp(index*58+29, ios::beg);
   RandomFile<<major;
   spaces=10-major.length();
   cout<<"spaces: "<<spaces;
   if(spaces>0)
      {
      for(int i=major.length();i<=spaces; i++)
         {
         RandomFile.seekp((index*58+29+i),ios::beg);
         RandomFile<<" ";
         }
      }
   cout<<endl;
   cout<<"Record changed successfully!"<<endl<<endl;
   noErrors=true;
   }
   else if(count>60)
   {
   cout<<"record not found. Please try again."<<endl;
   cout<<"Please enter the SSN of the record you wish to change the major: "<<endl;   
   cin>>SSN;
   index =hash(SSN);
   RandomFile.seekg(index*58,ios::beg);
   getline(RandomFile, record);
   tombSSN=record.substr(0,9);
   count=0;
   }
   else
      {
      index++;
      count++;
      if(index>60)
         {
         index=0;
         }
       
       }
   }

}
   else if(toupper(answer)==72)
   {
    noErrors=false;
   count=0;
   cout<<"Please enter the SSN of the record you wish to change the total credit hours: "<<endl;
   cin>>SSN;
   index =hash(SSN);
 
   while(!noErrors)
   {
   RandomFile.seekp(index*58, ios::beg);;
   getline(RandomFile, record);
   tombSSN=record.substr(0,9);
  
   if(SSN.compare(tombSSN)==0)
   {
   cout<<"Please enter the new total credit hours: "<<endl;
   cin>>creditHours;
   if(creditHours.length()>2)
         {
         
         RandomFile.seekp(index*58+49, ios::beg);
         RandomFile<<creditHours;
         }
      else
         {
         
         RandomFile.seekp(index*58+50, ios::beg);
         RandomFile<<creditHours;
         RandomFile.seekp(index*58+49, ios::beg);
         RandomFile<<" ";

         }
   cout<<endl;
   cout<<"Record changed successfully!"<<endl<<endl;
   noErrors=true;
   }
   else if(count>60)
   {
   cout<<"record not found. Please try again."<<endl;
   cout<<"Please enter the SSN of the record you wish to change the total credit hours: "<<endl;   
   cin>>SSN;
   index =hash(SSN);
   RandomFile.seekg(index*58,ios::beg);
   getline(RandomFile, record);
   tombSSN=record.substr(0,9);
   count=0;
   }
   else
      {
      index++;
      count++;
      if(index>60)
         {
         index=0;
         }
       
       }
   }
   }
   else if(toupper(answer)==71)
   {
   noErrors=false;
   count=0;
   cout<<"Please enter the SSN of the record you wish to change the GPA: "<<endl;
   cin>>SSN;
   index =hash(SSN);
 
   while(!noErrors)
   {
   RandomFile.seekp(index*58, ios::beg);;
   getline(RandomFile, record);
   tombSSN=record.substr(0,9);
  
   if(SSN.compare(tombSSN)==0)
   {
   cout<<"Please enter the new GPA: "<<endl;
   cin>>GPA;
   RandomFile.seekp(index*58+52, ios::beg);
   RandomFile<<GPA;
   cout<<endl;
   cout<<"Record changed successfully!"<<endl<<endl;
   noErrors=true;
   }
   else if(count>60)
   {
   cout<<"record not found. Please try again."<<endl;
   cout<<"Please enter the SSN of the record you wish to change the GPA: "<<endl;   
   cin>>SSN;
   index =hash(SSN);
   RandomFile.seekg(index*58,ios::beg);
   getline(RandomFile, record);
   tombSSN=record.substr(0,9);
   count=0;
   }
   else
      {
      index++;
      count++;
      if(index>60)
         {
         index=0;
         }
       
       }
   }
   }
   else if(toupper(answer)==88)
      {
      notDone=false;
      }
   else
      {
      cout<<"Error: incorrect input try again."<<endl<<endl;
      }
   }
}

int hash(string S)
{
int index=0;
for(int i=0; i<S.length(); i++)
   {
   index= index + S[i];
   }
return index%60;
}