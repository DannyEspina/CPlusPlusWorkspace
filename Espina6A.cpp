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
   int     RecordNumber;
   string  CurrentWord;
   ifstream ProgramFile;
   fstream RandomFile;
   
   ProgramFile.open("Program6.dat", ios::out);
   RandomFile.open("random.dat", ios::in | ios::out);
   string Dummy ="*********                                          00.00";
   string record, SSN;
   int index;
   bool noConflict;
   for(int i=0; i<=60; i++)
   {
   RandomFile<<Dummy<<endl;
   }
       
   while(!ProgramFile.eof())
   {
    getline(ProgramFile, record);
   SSN = record.substr(0,9);
   noConflict=false;
  
   index = hash(SSN);
   
 
      while(!noConflict)
      {
      RandomFile.seekp(index*58, ios::beg);
      if(RandomFile.peek()=='*')
      {
       RandomFile<<record;
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
}
// end function main

int hash(string S)
{
int index=0;
for(int i=0; i<S.length(); i++)
{
index= index + S[i];

}

return index%60;
}