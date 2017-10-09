#include <iostream.h>
#include <stdlib.h>

class BigInteger
{
   public:

      BigInteger();                      // default-size constructor
      BigInteger(int);                   // specify-size constructor
     ~BigInteger();                      // destructor
      BigInteger(const BigInteger&);     // copy constructor

      const BigInteger&  operator= (const BigInteger&);
      const BigInteger&  operator= (const int&);
            BigInteger   operator+ (const BigInteger&) const; 
            BigInteger   operator+ (const int&) const;
            BigInteger   operator* (const int&) const;
            BigInteger   operator/ (const int&) const;
            int          operator% (const int&) const;
            bool         operator==(const int&) const;
            bool         operator!=(const int&) const;

     friend ostream&     operator<<(ostream&, const BigInteger&);
     friend istream&     operator>>(istream&, BigInteger&);


   private:

      int  *BigArray;
      int   Size;
};


BigInteger::BigInteger()
{
   int i;

   BigArray = new int[100];
   Size     = 100;

   for (i = 0; i < Size; i++)
      BigArray[i] = 0;
   // end for
}
// end constructor

BigInteger::BigInteger(int MaxDigits)
{
   int i;

   if (MaxDigits < 10)
      MaxDigits = 10;
   // end if

   BigArray = new int[MaxDigits];
   Size     = MaxDigits;

   for (i = 0; i < Size; i++)
      BigArray[i] = 0;
   // end for
}
// end constructor

BigInteger::~BigInteger()
{
   delete [] BigArray;
}
// end destructor

BigInteger::BigInteger(const BigInteger& B)
{
   int i;

   BigArray = new int[B.Size];
   Size     = B.Size;

   for (i = 0; i < Size; i++)
      BigArray[i] = B.BigArray[i];
   // end for

}
// end copy constructor

const BigInteger&
BigInteger::operator=(const BigInteger& B)
{
   int i, SizeDifference;

   if (this != &B)
   {
      if (Size < B.Size)
      {
         delete [] BigArray;
         Size     = B.Size;
         BigArray = new int[Size];
      }
      // end if

      SizeDifference = Size - B.Size;
      if (SizeDifference != 0)
         *this = 0;
      // end if

      for (i = 0; i < B.Size; i++)
         BigArray[i+SizeDifference] = B.BigArray[i];
      // end for
   }
   // end if

   return *this;
}
// end operator=
  
const BigInteger&
BigInteger::operator=(const int& x)
{
   int i, y;

   y = x;

   for (i = Size-1; i >= 0; i--)
   {
      BigArray[i] = y%10;
      y = y/10;
   }
   // end for
   
   return *this;
}
// end operator=

BigInteger
BigInteger::operator+(const BigInteger& C) const
{
   int max, x, i, carry;

   if (Size < C.Size)
      max = C.Size;
   else
      max = Size;
   // end if

   BigInteger First(max), Second(max);

   First  = *this;
   Second = C;

   carry = 0;

   for (i = max-1; i >= 0; i--)
   {
      x = First.BigArray[i] + Second.BigArray[i] + carry;
      First.BigArray[i] = x%10;
      carry = x/10;
   }
   // end for

   if (carry != 0)
   {
      cout << "Addition Overflow of Big Integers!" << endl;
      exit(-1);
   }
   
      return First;
   // end if
}
// end operator+

BigInteger
BigInteger::operator+(const int& n) const
{
   int  x, i, carry;
   int  Second;

   BigInteger First(Size);

   First = *this;
   Second = n;
   carry = 0;

   for (i = Size-1; i >= 0; i--)
   {
      if (Second == 0 && carry == 0)
         break;
      // end if

      x = First.BigArray[i] + Second%10 + carry;
      First.BigArray[i] = x%10;
      carry = x/10;
      Second = Second/10;
   }
   // end for

   if (carry != 0)
   {
      cout << "Addition Overflow of a Big Integer with an int!" << endl;
      exit(-1);
   }
   
      return First;
   // end if
}
// end operator+

BigInteger   
BigInteger::operator*(const int& n) const 
{
   int  x, FrontPart, carry;
   int  i, LastDigit;

   BigInteger CopyOfBig(Size);

   CopyOfBig = *this;
   FrontPart = n/10;
   LastDigit = n%10;
   carry     = 0;
   
   for (i = Size-1; i >= 0; i--)
   {
      x = LastDigit*CopyOfBig.BigArray[i] + carry%10;
      carry = FrontPart*CopyOfBig.BigArray[i] + x/10 + carry/10;
      CopyOfBig.BigArray[i] = x%10;
   }
   // end for

   if (carry != 0)
   {
      cout << "Multiplication Overflow of a Big Integer with an int!" << endl;
      exit(-1);
   }
   
      return CopyOfBig;
   // end if
}
// end operator*
BigInteger   
BigInteger::operator/(const int& n) const 
{
int carry, i;

   BigInteger CopyOfBig(Size);
   int x = n;
   CopyOfBig = *this;
   carry = 0;
   
   if(x==0)
   {
      cout<<"Cannot divide by zero."<<endl;
      exit(-1);
   }
   // end if
   for(i=0; i<Size; i++)
   {
      carry=CopyOfBig.BigArray[i]%x;
     
      CopyOfBig.BigArray[i]=CopyOfBig.BigArray[i]/x;
      
      if(i+1<Size)
      {
      CopyOfBig.BigArray[i+1]=CopyOfBig.BigArray[i+1]+(10*carry);
      }
   }
   // end for
   return CopyOfBig;
}
// end operator/
int 
BigInteger::operator%(const int& n) const
{
  int carry, i;

   BigInteger CopyOfBig(Size);
   int x = n;
   CopyOfBig = *this;
   carry = 0;
   
   if(x==0)
   {
      cout<<"Cannot mod by zero."<<endl;
      exit(-1);
   }
   // end if
   for(i=0; i<Size; i++)
   {
      carry=CopyOfBig.BigArray[i]%x;
     
      CopyOfBig.BigArray[i]=CopyOfBig.BigArray[i]/x;
    
      if(i+1<Size)
      {
      CopyOfBig.BigArray[i+1]=CopyOfBig.BigArray[i+1]+(10*carry);
      }
   }
   // end for
   return carry;
}
// end operator%

bool       
BigInteger::operator==(const int& n) const
{
     int firstHalf, secondHalf, x, i,y;

   BigInteger CopyOfBig(Size);

   CopyOfBig = *this;
   y=n;

   for(i=Size-1; i>=0; i--)
   {
      if(CopyOfBig.BigArray[i]==y%10)
      {
         y=y/10;
      }
      else
         return false;
      // end if
   }
   // end for
   return true;
}
// end operator==
bool       
BigInteger::operator!=(const int& n) const
{
     int firstHalf, secondHalf, x, i,y;

   BigInteger CopyOfBig(Size);

   CopyOfBig = *this;
   y=n;

   for(i=Size-1; i>=0; i--)
   {
      if(CopyOfBig.BigArray[i]!=y%10)
      {
         return true;
      }
      else
         y=y/10;
      // end if
   }
   // end for
   return false;
}
// end operator!=
ostream&
operator<<(ostream& OutFile,const BigInteger& B)
{
  bool zero=true;
  BigInteger CopyOfBig(B.Size);
  CopyOfBig = B;

   for(int i=0; i<=CopyOfBig.Size-1; i++)
      {
         if(CopyOfBig.BigArray[i]!=0 && zero)
         {
         zero=false;
         }
         if(!zero || CopyOfBig.Size-1==i)
         {
         OutFile<<CopyOfBig.BigArray[i];
         }
      }

   return OutFile;
}
// end friend operator<<
istream&
operator>>(istream& InFile, BigInteger& B)
{
   int  *TempArray, NumOfDigits=0, i;
   char x = ' ';

   TempArray = new int[B.Size];

   while (isspace(x))
      InFile.get(x);
   // end while

   while (isdigit(x) && NumOfDigits < B.Size)
   {
      TempArray[NumOfDigits++] = x - 48;
      InFile.get(x);
   }
   // end while

   if (NumOfDigits == B.Size && isdigit(x))
   {
      cout << "Illegal Read: Insufficient size for BigInteger!" << endl;
      exit(-1);
   }
   // end if

   if (NumOfDigits <= B.Size && !(isspace(x) || InFile.eof()))
   {
      cout << "Attempt to read illegal character into a BigInteger!" << endl;
      exit(-1);
   }
   // end if

   B = 0;

   for (i = 0; i < NumOfDigits; i++)
      B.BigArray[i+B.Size-NumOfDigits] = TempArray[i];
   // end for

   delete [] TempArray;

   return InFile;
}
// end friend operator>>

