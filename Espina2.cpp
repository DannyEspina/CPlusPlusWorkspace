#include <iostream.h>
#include <conio.h>
#include "louie.h"
#include <ctime.h>
#include <windows.h>
#include <iomanip.h>
typedef  char  TicTacToeBoard[5][5];
//global variables to help keep track of last moves
int playerRow;
int playerColumn;
int compRow;
int compColumn;
int counter=0;
//functions used in this program
void initializeBoard(TicTacToeBoard);
void printBoard(TicTacToeBoard);
void playerTakesTurn(TicTacToeBoard);
void computerTakesTurn(TicTacToeBoard);
int checkWin(TicTacToeBoard); //checks the column, rows and diagonals for wins by passing it to test4
bool gameIsNotOver(TicTacToeBoard);
void announceResult(TicTacToeBoard);
void voiceBox(); //To make to the game more intresting 
int test4(char, char, char, char); //Test 4 character values for a win

int main()
{
   TicTacToeBoard  B;

   initializeBoard(B);
   printBoard(B);

   playerTakesTurn(B);

   while (gameIsNotOver(B))
   {
      printBoard(B);

      computerTakesTurn(B);
      printBoard(B);

      if (gameIsNotOver(B))
         playerTakesTurn(B);
      else
	 break;
      // end if
   }
   // end while

   printBoard(B);
   announceResult(B);

   return 0;
}// end function main

//****************************************************************
void initializeBoard(TicTacToeBoard a)
{
 int i, j, k;
   a[1][0]='1';
   a[2][0]='2';
   a[3][0]='3';
   a[4][0]='4';
   a[0][1]='1';
   a[0][2]='2';
   a[0][3]='3';
   a[0][4]='4';  
   for (i = 1; i <= 4; i++)
      for (j = 1; j <= 4; j++)
      {
      a[i][j] = '*';
      }
  return;
}

//*********************************************************************
void printBoard(TicTacToeBoard a)
{
   clrscr();
   int i, j; 
   for (i=0; i<=4; i++)
   {
      for(j=0; j<=4; j++)
      {
      cout<<setw(3)<<a[i][j];
      }
   cout<< endl;
   }  
return;
}

//**********************************************************************
void playerTakesTurn(TicTacToeBoard a)
{
int row, column;
// turns true if the user enters invalid input
bool error;
cout<<endl;
//prints out only at the start of the game
if(counter==0)
{
cout<<"A wild Computer has appeared!"<<endl<<endl;
}
//to make the game more enjoyable the computer will say various things to the palyer 
if(counter>0)
{
voiceBox();
}

cout<<"Your Turn! Please enter your coordinates from 1-4:"<<endl;
//checks user input. loops around until a correct input is choosen. 
do
{
error=false;
cin>>row;
cin>>column;
//if input is out of bounds
if (row>4 || column>4)
{
cout<<"Computer: Wrong! Input out of bounds! Please try again:"<<endl;
error=true;
}
//if the spot is already taken
else if(a[row][column]!='*')
{
cout<<"Computer: What are you doing?! Spot is already taken! Please try again:"<<endl;
error= true;
}
}
while (error);

a[row][column]='P';
//saves the player last move
playerRow=row;
playerColumn=column;
return;
}
//**************************************************************************************
void computerTakesTurn(TicTacToeBoard a)
{
long seed = time(0);
int randRow, randCol;
//lets the computer think
cout<<"Computer:Hmm";
Sleep(500);
cout<<".";
Sleep(500);
cout<<".";
Sleep(500);
cout<<"."<<endl;
Sleep(500);
//checks if there is a possible winning move and then place it on that spot. 
if(counter>2)
{
//checks the computers last move. Rows
if(test4(a[compRow][1],a[compRow][2],a[compRow][3],a[compRow][4])==1)
{
//finds a empty spot
 for(int i=1; i<=4; i++)
 {
  if(a[compRow][i]=='*')
  {
    a[compRow][i]='C';
    counter++;
    break;
  }
 }
}
//checks player last move. Rows
else if(test4(a[playerRow][1],a[playerRow][2],a[playerRow][3],a[playerRow][4])==1)
{
 for(int i=1; i<=4; i++)
 {
  if(a[playerRow][i]=='*')
  {
    a[playerRow][i]='C';
    counter++;
    break;
  }
 }
}
//checks computer last move. Columns
else if(test4(a[1][compColumn],a[2][compColumn],a[3][compColumn],a[4][compColumn])==1)
{
 for(int i=1; i<=4; i++)
 {
  if(a[i][compColumn]=='*')
  {
    a[i][compColumn]='C';
    counter++;
    break;
  }    
 }
}
//checks player last move. Columns
else if(test4(a[1][playerColumn],a[2][playerColumn],a[3][playerColumn],a[4][playerColumn])==1)
{
 for(int i=1; i<=4; i++)
 {
  if(a[i][playerColumn]=='*')
  {
 
    a[i][playerColumn]='C';
    counter++;
    break;
  } 
 }
}
//checks main diagonal 
else if(compRow==compColumn||playerRow==compColumn)
{
   if(test4(a[1][1],a[2][2],a[3][3],a[4][4])==2)
   {
    for(int i=1; i<=4; i++)
    { 
     if(a[i][i]=='*')
     {
      a[i][i]='C';
      counter++;
      break;
     }
    }
}  
}
//checks anti diagonal
else if((compRow+compColumn)==5||(playerRow+playerColumn)==5)
{
   if(test4(a[1][4],a[2][3],a[3][2],a[4][1])==2)
    {
         for(int i=1, j=4; i<=4; i++,j--)
     { 
      if(a[i][j]=='*')      
      {
       a[i][j]='C';
       counter++;
       break;
      }
     }
    }
}
}
//if no winning move found then place at a random empty spot
do
{
randRow = random(seed)*4+1;
randCol = random(seed)*4+1;
compRow=randRow;
compColumn=randCol;
}
while(a[randRow][randCol]!='*');

a[randRow][randCol]='C';
counter++;
return;
}
//******************************************************************************

bool gameIsNotOver(TicTacToeBoard a)
{
//if theres a win then end the game
  if(checkWin(a)>0)
  {
   return false;
  }
  else if(counter<16)//if the table is not full
  {
   return true;
  }
  
   return false;
  
}
//*******************************************************************************
void announceResult(TicTacToeBoard a)
{
//announces the winner
   if(checkWin(a)==1)
   {
   cout<<"Computer: Nooo!! Impossible! You Win!"<<endl;
   }
   else if(checkWin(a)==2)
   {
   cout<<"Computer: Haha! Take that sucker! You Lose!"<<endl;
   }
   else
   cout<<"Computer: it's a tie! We are equally matched!"<<endl;
}
//*******************************************************************************
int checkWin(TicTacToeBoard a)
{
//checks the whole table for a win
for(int i =0; i<5; i++)
  {
   if(test4(a[i][1],a[i][2],a[i][3],a[i][4])==2)
   {
   return 1;
   }
   else if(test4(a[i][1],a[i][2],a[i][3],a[i][4])==3)
   {
   return 2;
   }
   else if(test4(a[1][i],a[2][i],a[3][i],a[4][i])==2)
   {
   return 1;
   }
   else if(test4(a[1][i],a[2][i],a[3][i],a[4][i])==3)
   {
   return 2;
   }
   else if(test4(a[1][1],a[2][2],a[3][3],a[4][4])==2)
   {
   return 1;
   }
   else if(test4(a[1][1],a[2][2],a[3][3],a[4][4])==3)
   {
   return 2;
   }
   else if(test4(a[4][1],a[3][2],a[2][3],a[1][4])==2)
   {
   return 1;
   }
   else if(test4(a[4][1],a[3][2],a[2][3],a[1][4])==3)
   {
   return 2;
   }
  }
  return 0;
}
//******************************************************************************
int test4(char c1, char c2, char c3, char c4)
{
//converts char values into ascii values to compare
int w=c1, x=c2, y=c3, z=c4;
if (c1+c2+c3+c4==243||c1+c2+c3+c4==256)
   return 1;
else if(w+x+y+z==307)
   return 2; 
else if(w+x+y+z==281)  
   return 3;
else 
   return 0;
}
//*******************************************************************************
//it doesn't hurt to make the game a little more fun. 
void voiceBox()
{
//picks a random prompt for the computer
long seed=time(0);
int rand= random(seed)*7+1;

if(rand==1)
{
cout<<"Computer: You can never beat me human!"<<endl<<endl; 
}
else if(rand==2)
{
cout<<"Computer: My Windows 95 can proccess faster then you!"<<endl<<endl;
}
else if(rand==3)
{
cout<<"Computer:[British Accent] Your defeat is inevitable Mr.Bond."<<endl<<endl;
}
else if(rand==4)
{
cout<<"What are you? A Linux user?!"<<endl<<endl;
}
else if(rand==5)
{
cout<<"Computer: Yo mama is so fat, she sat on a binary tree and flattened it to a"<<endl
<<"linked list in constant time!"<<endl<<endl;
}
else if(rand==6)
{
cout<<"Computer: Really? There?...oh ok"<<endl<<endl;
}
else if(rand==7)
{
cout<<"Computer: 01101100 01101111 01110011 01100101 01110010 00001101 00001010"<<endl<<endl; //Translation: loser
}
}