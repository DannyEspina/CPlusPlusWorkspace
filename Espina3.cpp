/**************************************************************************
*                                                                         *
*     Program Filename:  Espina3.cpp                                      *
*     Author          :  Daniel J. Espina                                 *
*     Date Written    :  March 18, 2016                                   *
*                                                                         *
**************************************************************************/

#include <fstream.h>
#include <string.h>
#include <conio.h>
#include <iomanip.h>

struct  NameRecord
{
   string  LastName;
   string  FirstName;
   char    MidInit;
};

struct StudentGrades
{
   int Program[6];
   int Test[3];
   int FinalExam;
   double Average;
};
struct  StudentRecord
{
   NameRecord     Name;
   string         SSN;
   string         Major; 
   StudentGrades  Grade;
};

typedef StudentRecord Students[50];
void Average(StudentRecord&); //compute average
void ReadNextStudentRecord(StudentRecord&, ifstream&);
void WriteNextStudentRecord(StudentRecord&, ofstream&);
int main()
{
   ifstream InFile;
   ofstream OutFile;
   Students S;
   int counter=0;
   int highest1=0;
   int highest2=0;
   int highest3=0;
 
   int grade;
   int curve;
   InFile.open("Program3.dat", ios::in);
   OutFile.open("louie.dat", ios::out);
   //Read every Record into a array of strutures
   for(int i=0; !InFile.eof(); i++)
   {
   ReadNextStudentRecord(S[i], InFile);
   counter++;
   }
   //end for
   
   //finds the highest grade from the 3 tests
   for(int i=0;i<counter-1; i++)
   {
      if(highest1<S[i].Grade.Test[0])
      {
      highest1=S[i].Grade.Test[0];
      }
      if(highest2<S[i].Grade.Test[1])
      {
      highest2=S[i].Grade.Test[1];
      }
      if(highest3<S[i].Grade.Test[2])
      {
      highest3=S[i].Grade.Test[2];
      }
   }
   //end for
   
   //adds the curve
   for(int i=0; i<counter;i++)
   {
   
   curve=100-highest1;
   S[i].Grade.Test[0]+=curve;

   curve=100-highest2;
   S[i].Grade.Test[1]+=curve;
 
   curve=100-highest3;
   S[i].Grade.Test[2]+=curve;
   
   }
   // end for
   
   //compute average for every record
   for(int i=0; i<counter-1; i++)
   {
   Average(S[i]);
   }
   //end for 

   //sort records from greatest to least average
   StudentRecord temp;
   for(int i=0;i<counter;i++)
   {
      for(int j=0; j<i; j++)
      {
      if(S[j].Grade.Average<S[j+1].Grade.Average)
      {
      temp=S[j];
      S[j]=S[j+1];
      S[j+1]=temp;
      }
      }
      //end for 
   }  
   //end for
 
   //write infomation into louie.dat
   for(int i=0; i<counter-1; i++)
   {
      WriteNextStudentRecord(S[i], OutFile);
   }
   //end for 
   cout<<"*SUCCESSFUL PROGRAM TERMAINATION*"<<endl;
   return 0;
   
   
}
// end main function

/**************************************************************************
*                                                                         *
*     Function Name   :  ReadNextStudentRecord                            *
*     Purpose         :  To read the entire next StudentRecord            *
*     Called by       :  Main                                             *
*     Functions Called:  None                                             *
*                                                                         *
**************************************************************************/

void ReadNextStudentRecord(StudentRecord& R, ifstream& InFile)
{
   int  i;
   string NextRecord;

   getline(InFile, NextRecord);
   if (InFile.eof())
      return;
   // end if
   
   R.Name.LastName = NextRecord.substr(0, 15);
   R.Name.FirstName = NextRecord.substr(15, 10);
   R.Name.MidInit = NextRecord[25];

   R.SSN = NextRecord.substr(26, 9);
   R.Major = NextRecord.substr(35, 20);

   R.Grade.Program[0]=atoi(NextRecord.substr(55,2).c_str());
   R.Grade.Program[1]=atoi(NextRecord.substr(57,2).c_str());
   R.Grade.Program[2]=atoi(NextRecord.substr(59,2).c_str());
   R.Grade.Program[3]=atoi(NextRecord.substr(61,2).c_str());
   R.Grade.Program[4]=atoi(NextRecord.substr(63,2).c_str());
   R.Grade.Program[5]=atoi(NextRecord.substr(65,2).c_str());

   R.Grade.Test[0]=atoi(NextRecord.substr(67,3).c_str());
   R.Grade.Test[1]=atoi(NextRecord.substr(70,3).c_str());
   R.Grade.Test[2]=atoi(NextRecord.substr(73,3).c_str());
   R.Grade.FinalExam=atoi(NextRecord.substr(76,3).c_str());
 

   // end for

   return;
}
// end function ReadNextStudentRecord

/**************************************************************************
*                                                                         *
*     Function Name   :  WriteNextStudentRecord                           *
*     Purpose         :  To write an entire StudentRecord                 *
*     Called by       :  Main                                             *
*     Functions Called:  None                                             *
*                                                                         *
**************************************************************************/

#include <iomanip.h>

void WriteNextStudentRecord(StudentRecord& R, ofstream& OutFile)
{
   string last4 =R.SSN.substr(5,4);
   char letterGrade=' ';
   if(R.Grade.Average>=90)
      letterGrade='A';
   else if(R.Grade.Average>=80)
      letterGrade='B';
   else if(R.Grade.Average>=70)
      letterGrade='C';
   else if(R.Grade.Average>=60)
      letterGrade='D';
   else
      letterGrade='F';
      
   OutFile<<last4<<setw(10);
   OutFile<<R.Grade.Average<<setw(10);
   OutFile<<letterGrade<<endl;     
   return;
}
// end function WriteNextStudentRecord

/**************************************************************************
*                                                                         *
*     Function Name   :  Average                                          *
*     Purpose         :  To Compute the Average for student               *
*     Called by       :  Main                                             *
*     Functions Called:  None                                             *
*                                                                         *
**************************************************************************/
void Average(StudentRecord& R)
{
double AverageProg=0;
double AverageTests=0;
int FinalExam=R.Grade.FinalExam;
double CompositeAvg;

   for(int i=0; i<6; i++)
   {
    AverageProg+=R.Grade.Program[i];
   }
    AverageProg=AverageProg/6.0;
   
   for(int i=0; i<3; i++)
   {
    AverageTests+=R.Grade.Test[i]; 
   }
    AverageTests=AverageTests/3.0;
    
    CompositeAvg=(AverageProg*5)*.3+AverageTests*.4+FinalExam*.3;
    R.Grade.Average=CompositeAvg;
    return;
    
}