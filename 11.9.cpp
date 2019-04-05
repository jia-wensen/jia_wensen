
#include <iostream>
#include "Complex.h"
using namespace std;


Complex::Complex( double realPart, double imaginaryPart )
   : real( realPart ),
   imaginary( imaginaryPart )
{
} 


Complex Complex::operator+( const Complex &operand2 ) const
{
   return Complex( real + operand2.real,
      imaginary + operand2.imaginary );
}


Complex Complex::operator-( const Complex &operand2 ) const
{
   return Complex( real - operand2.real,
      imaginary - operand2.imaginary );
}

Complex Complex::operator*( const Complex &operand2 ) const
{
   return Complex(
      ( real * operand2.real ) + ( imaginary * operand2.imaginary ),
      ( real * operand2.imaginary ) + ( imaginary * operand2.real ) );
} // end function operator*

// Overloaded = operator
Complex& Complex::operator=( const Complex &right )
{
   real = right.real;
   imaginary = right.imaginary;
   return *this;   // enables concatenation
}

bool Complex::operator==( const Complex &right ) const
{ 
   return ( right.real == real ) && ( right.imaginary == imaginary );
} 

bool Complex::operator!=( const Complex &right ) const
{
   return !( *this == right ); 
} 

ostream& operator<<( ostream &output, const Complex &complex )
{
   output << "(" << complex.real << ", " << complex.imaginary << ")";
   return output;
} // end function operator<<

istream& operator>>( istream &input, Complex &complex )
{
   input.ignore(); // skip (
   input >> complex.real;
   input.ignore( 2 ); // skip ',' and space
   input >> complex.imaginary;
   input.ignore(); // skip )
   return input;
} 