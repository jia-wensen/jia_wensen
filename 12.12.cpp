
#include <iostream> 
#include <iomanip> 
#include "Polynomial.h"
using namespace std;

Polynomial::Polynomial()
{
   for ( int t = 0; t < maxTerms; t++ )
   {
      coefficients[ t ] = 0;
      exponents[ t ] = 0;
   } 

   numberOfTerms = 0;
}

void Polynomial::printPolynomial() const
{
   int start;
   bool zero = false;

   if ( coefficients[ 0 ] ) 
   {
      cout << coefficients[ 0 ];
      start = 1;
      zero = true; 
   }
   else
   {
      if ( coefficients[ 1 ] )
      {
         cout << coefficients[ 1 ] << 'x';            
                                      
         if ( ( exponents[ 1 ] != 0 ) && ( exponents[ 1 ] != 1 ) )
            cout << '^' << exponents[ 1 ];

         zero = true;  
      } 
      
      start = 2;
   } 
   for ( int x = start; x < maxTerms; x++ )
   {
      if ( coefficients[ x ] != 0 )
      {
         cout << showpos << coefficients[ x ] << noshowpos << 'x'; 

         if ( ( exponents[ x ] != 0 ) && ( exponents[ x ] != 1 ) )
            cout << '^' << exponents[ x ];

         zero = true; // at least one term exists
      } 
   }

   if ( !zero ) // no terms exist in the polynomial
      cout << '0';

   cout << endl;
} // end function printPolynomial

Polynomial &Polynomial::operator=( const Polynomial &r )
{
   exponents[ 0 ] = r.exponents[ 0 ];
   coefficients[ 0 ] = r.coefficients[ 0 ];

   for ( int s = 1; s < maxTerms; s++ )
   {
       if ( r.exponents[ s ] != 0 )
       {
          exponents[ s ] = r.exponents[ s ];
          coefficients[ s ] = r.coefficients[ s ];
       }
       else
       {
          if ( exponents[ s ] == 0 )
             break;

          exponents[ s ] = 0;
          coefficients[ s ] = 0;
      }  // end else
   } // end for

   return *this;
} // end function operator=

Polynomial Polynomial::operator+( const Polynomial &r ) const
{
   Polynomial temp;
   bool exponentExists;
   int s;

   // process element with a zero exponent
   temp.coefficients[ 0 ] = coefficients[ 0 ] + r.coefficients[ 0 ];

   // copy right arrays into temp object; s will be used to keep
   // track of first open coefficient element
   for ( s = 1; ( s < maxTerms ) && ( r.exponents[ s ] != 0 ); s++ )
   {
      temp.coefficients[ s ] = r.coefficients[ s ];
      temp.exponents[ s ] = r.exponents[ s ];
   } // end for

   for ( int x = 1; x < maxTerms; x++ )
   {
      exponentExists = false; // assume exponent will not be found

      for ( int t = 1; ( t < maxTerms ) && ( !exponentExists ); t++ )
         if ( exponents[ x ] == temp.exponents[ t ] )
         {
            temp.coefficients[ t ] += coefficients[ x ];
            exponentExists = true;  // exponent found
         } // end if

      // exponent was not found, insert into temp
      if ( !exponentExists )
      {
         temp.exponents[ s ] = exponents[ x ];
         temp.coefficients[ s ] += coefficients[ x ];
         s++;
      } // end if
   } // end for

   return temp;
} // end function operator+

Polynomial &Polynomial::operator+=( const Polynomial &r )
{
   *this = *this + r;
   return *this;
} // end function operator+=

Polynomial Polynomial::operator-( const Polynomial &r ) const
{
   Polynomial temp;
   bool exponentExists;
   int s;

   // process element with a zero exponent
   temp.coefficients[ 0 ] = coefficients[ 0 ] - r.coefficients[ 0 ];

   // copy left arrays into temp object; s will be used to keep
   // track of first open coefficient element
   for ( s = 1; ( s < maxTerms ) && ( exponents[ s ] != 0 ); s++ )
   {
      temp.coefficients[ s ] = coefficients[ s ];
      temp.exponents[ s ] = exponents[ s ];
   } // end for

   for ( int x = 1; x < maxTerms; x++ )
   {
      exponentExists = false; // assume exponent will not be found

      for ( int t = 1; ( t < maxTerms ) && ( !exponentExists ); t++ )

         if ( r.exponents[ x ] == temp.exponents[ t ] )
         {
            temp.coefficients[ t ] -= r.coefficients[ x ];
            exponentExists = true;  // exponent found
         } // end if

      // exponent was not found, insert into temp
      if ( !exponentExists )
      {
         temp.exponents[ s ] = r.exponents[ x ];
         temp.coefficients[ s ] -= r.coefficients[ x ];
         s++;
      } // end if
   } // end for

   return temp;
} // end function operator-

Polynomial &Polynomial::operator-=( const Polynomial &r )
{
   *this = *this - r;
   return *this;
} // end function operator-=

Polynomial Polynomial::operator*( const Polynomial &r ) const
{
   Polynomial temp;
   int s = 1; // subscript location for temp coefficient and exponent

   for ( int x = 0; ( x < maxTerms ) &&
      ( x == 0  || coefficients[ x ] != 0 ); x++ )

      for ( int y = 0; ( y < maxTerms ) &&
         ( y == 0 || r.coefficients[ y ] != 0 ); y++ )

         if ( coefficients[ x ] * r.coefficients[ y ] )

            if ( ( exponents[ x ] == 0 ) && ( r.exponents[ y ] == 0 ) )
               temp.coefficients[ 0 ] +=
                  coefficients[ x ] * r.coefficients[ y ];
            else
            {
               temp.coefficients[ s ] =
                  coefficients[ x ] * r.coefficients[ y ];
               temp.exponents[ s ] = exponents[ x ] + r.exponents[ y ];
               s++;
            } // end else

   polynomialCombine( temp ); // combine common terms
   return temp;
} // end function operator* 

void Polynomial::polynomialCombine( Polynomial &w )
{
   Polynomial temp = w;

   // zero out elements of w
   for ( int x = 0; x < maxTerms; x++ )
   {
      w.coefficients[ x ] = 0;
      w.exponents[ x ] = 0;
   } // end for

   for ( int x = 1; x < maxTerms; x++ )
   {
      for ( int y = x + 1; y < maxTerms; y++ )
         if ( temp.exponents[ x ] == temp.exponents[ y ] )
         {
            temp.coefficients[ x ] += temp.coefficients[ y ];
            temp.exponents[ y ] = 0;
            temp.coefficients[ y ] = 0;
         } // end if
   } // end outer for

   w = temp;
} // end function polynomialCombine

Polynomial &Polynomial::operator*=( const Polynomial &r )
{
   *this = *this * r;
   return *this;
} // end function operator*=

void Polynomial::enterTerms()
{
   bool found = false; 
   int c, e, term;

   cout << "\nEnter number of polynomial terms: ";
   cin >> numberOfTerms;

   for ( int n = 0; n < maxTerms && n < numberOfTerms; n++ )
   {
      cout << "\nEnter coefficient: ";
      cin >> c;
      cout << "Enter exponent: ";
      cin >> e;

      if ( c != 0 )
      {
         // exponents of zero are forced into first element
         if ( e == 0 )
         {
            coefficients[ 0 ] += c;
            continue;
         } // end if

         for ( term = 1; ( term < maxTerms ) &&
                ( coefficients[ term ] != 0 ); term++ )

            if ( e == exponents[ term ] )
            {
               coefficients[ term ] += c;
               exponents[ term ] = e;
               found = true;  // existing exponent updated
            } // end if

         if ( !found ) // add term
         {
            coefficients[ term ] += c;
            exponents[ term ] = e;
         } // end if
      } // end outer if
   } // end outer for
} // end function endTerms

int Polynomial::getNumberOfTerms() const
{
   return numberOfTerms;
} // end function getNumberOfTerms

int Polynomial::getTermExponent( int term ) const
{
   return exponents[ term ];
} // end function getTermExponent

int Polynomial::getTermCoefficient( int term ) const
{
   return coefficients[ term ];
} // end function getTermsCoefficient

void Polynomial::setCoefficient( int term, int coefficient )
{
   if ( coefficients[ term ] == 0 ) // no term at this location
      cout << "No term at this location, cannot set term." << endl;
   else // otherwise, set term
      coefficients[ term ] = coefficient;
} // end function setTerm

// destructor
Polynomial::~Polynomial()
{
   // empty destructor
} // end destructor



