
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

class Polynomial
{
public:
   static const int maxTerms = 100; // maximum number of terms

   Polynomial();
   Polynomial operator+( const Polynomial & ) const; // addition
   Polynomial operator-( const Polynomial & ) const; // subtraction
   Polynomial operator*( const Polynomial & ) const; // multiplication
   Polynomial &operator=( const Polynomial & ); // assignment
   Polynomial &operator+=( const Polynomial & );
   Polynomial &operator-=( const Polynomial & );
   Polynomial &operator*=( const Polynomial & );
   void enterTerms();
   void printPolynomial() const;
   int getNumberOfTerms() const; // user can only retrieve value
   int getTermExponent( int ) const;
   int getTermCoefficient( int ) const;
   void setCoefficient( int, int ); // set coefficient of a specific term
   ~Polynomial(); // destructor
private:
   int numberOfTerms;
   int exponents[ maxTerms ]; // exponent array
   int coefficients[ maxTerms ]; // coefficients array
   static void polynomialCombine( Polynomial & ); // combine common terms
}; 