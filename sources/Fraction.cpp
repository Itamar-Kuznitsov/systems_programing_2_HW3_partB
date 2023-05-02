#include "Fraction.hpp"
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;




/**
 * @about: Fraction class implementation, Task 3 - Systems programing N.2 course.
 *         This task goal was to overload operators for fraction class.
 * @author Itamar Kuznitsov.
 * @since May. 2023
*/




namespace ariel{

// default constructor
Fraction:: Fraction(int numer, int denom)
    : numerator(numer), denominator(denom){
        if(denom == 0)
            throw std::invalid_argument("invalid denominator");
        else{
            update_sign(*this);
            this->reduce_fraction(); 
        }
}

// copy constructor
Fraction:: Fraction(const Fraction& f)
    :numerator(f.numerator), denominator(f.denominator){}

// float constructor
Fraction:: Fraction(const float &flo)
    :numerator(flo*1000), denominator(1000){
        this->reduce_fraction(); 
}

// empty constructor
Fraction:: Fraction()
    : numerator(0), denominator(1) {}

// destructor
Fraction:: ~Fraction(){}


// move constructor:
Fraction::Fraction(Fraction&& other) noexcept 
    : numerator(other.numerator), denominator(other.denominator){  
        other.numerator = 0;
        other.denominator = 1;
}

// fraction move assignment 
Fraction& Fraction::operator=(Fraction&& other) noexcept{
    if (this != &other) {
        numerator = other.numerator;
        denominator = other.denominator;
        other.numerator = 0;
        other.denominator = 1;
    }
    return *this;
}

// fraction copy assignment
Fraction& Fraction:: operator=(const Fraction& fra){
    if(this != &fra){
        this->numerator = fra.numerator;
        this->denominator = fra.denominator;
    }
    return *this;
}




// getters ///
int  Fraction:: getNumerator() const{
    return this->numerator;
}
int Fraction:: getDenominator() const{
    return this->denominator;
}



// assistance functions ///

// updete the sign of the fraction to be in form: +-/+.
void Fraction:: update_sign(Fraction& fra){
    // update sign of the fraction.
    if(fra.denominator < 0){
        fra.numerator *= -1;
        fra.denominator *= -1;
    }
}


// return fraction in a reduced form
void Fraction:: reduce_fraction(){
    int gcd_ = __gcd(abs(this->numerator), this->denominator);
    this->numerator /= gcd_;
    this->denominator /= gcd_;
}

// return given fraction as a float - three digits after the decimal point.
float Fraction:: fraction_to_float(Fraction fra){
    float float_num = (float)fra.numerator/(float)fra.denominator;
    return std::round(float_num* 1000.0f)/ 1000.0f;
}



// 2 fractions case: ////
Fraction operator+ (const Fraction& fra1, const Fraction& fra2){
    // compute product of numerators and denominators, convert the operands to long long, to avoid overflow when computing the product of two integers.
    long long new_numer = static_cast<long long>(fra1.getNumerator()) * static_cast<long long>(fra2.getDenominator()) + static_cast<long long>(fra2.getNumerator()) * static_cast<long long>(fra1.getDenominator());
    long long new_denom = static_cast<long long>(fra1.getDenominator()) * static_cast<long long>(fra2.getDenominator());

    // check int overflow
    if (new_numer > std::numeric_limits<int>::max() || new_numer < std::numeric_limits<int>::min() ||
        new_denom > std::numeric_limits<int>::max() || new_denom < std::numeric_limits<int>::min()) {
        throw std::overflow_error("Fraction multiplication overflow");
    }    
    Fraction tmp (new_numer, new_denom);
    tmp.reduce_fraction();
    return tmp;
}

Fraction operator- (const Fraction& fra1, const Fraction& fra2){
    // compute product of numerators and denominators, convert the operands to long long, to avoid overflow when computing the product of two integers.
    long long new_numer = static_cast<long long>(fra1.getNumerator()) * static_cast<long long>(fra2.getDenominator()) - static_cast<long long>(fra2.getNumerator()) * static_cast<long long>(fra1.getDenominator());
    long long new_denom = static_cast<long long>(fra1.getDenominator()) * static_cast<long long>(fra2.getDenominator());

    // check int overflow
    if (new_numer > std::numeric_limits<int>::max() || new_numer < std::numeric_limits<int>::min() ||
        new_denom > std::numeric_limits<int>::max() || new_denom < std::numeric_limits<int>::min()) {
        throw std::overflow_error("Fraction multiplication overflow");
    }  
    Fraction tmp (new_numer, new_denom);
    tmp.reduce_fraction();
    return tmp;
}

Fraction operator* (const Fraction& fra1, const Fraction& fra2){
    // compute product of numerators and denominators, convert the operands to long long, to avoid overflow when computing the product of two integers.
    long long num = static_cast<long long>(fra1.getNumerator()) * static_cast<long long>(fra2.getNumerator());
    long long den = static_cast<long long>(fra1.getDenominator()) * static_cast<long long>(fra2.getDenominator());

    // check int overflow
    if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min() ||
        den > std::numeric_limits<int>::max() || den < std::numeric_limits<int>::min()) {
        throw std::overflow_error("Fraction multiplication overflow");
    }
    Fraction tmp (num, den);
    tmp.reduce_fraction();
    return tmp;
}

Fraction operator/(const Fraction& fra1, const Fraction& fra2){
    // check dividing by zero
    if(fra2.numerator  == 0)
        throw std::runtime_error("divide by zero");
    
    // compute product of numerators and denominators, convert the operands to long long, to avoid overflow when computing the product of two integers.
    long long num = static_cast<long long>(fra1.getNumerator()) * static_cast<long long>(fra2.getDenominator());
    long long den = static_cast<long long>(fra1.getDenominator()) * static_cast<long long>(fra2.getNumerator());

    // check int overflow
    if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min() ||
        den > std::numeric_limits<int>::max() || den < std::numeric_limits<int>::min()) {
        throw std::overflow_error("Fraction multiplication overflow");
    }
    Fraction tmp (num, den);
    tmp.reduce_fraction();
    return tmp;
}

bool operator==(const Fraction& fra1, const Fraction& fra2){
    return (Fraction::fraction_to_float(fra1) == Fraction::fraction_to_float(fra2));
}

bool operator>(const Fraction& fra1, const Fraction& fra2){
    return(fra1.numerator*fra2.denominator > fra2.numerator*fra1.denominator);
}

bool operator<(const Fraction& fra1, const Fraction& fra2){
    return(fra1.numerator*fra2.denominator < fra2.numerator*fra1.denominator);
}

bool operator>=(const Fraction& fra1, const Fraction& fra2){
    // one fraction is negative
    if (fra1.numerator * fra2.numerator < 0) {
        return fra1.numerator > 0;
    }
    // Fractions have same sign, compare them normally
    return (fra1.numerator * fra2.denominator >= fra2.numerator * fra1.denominator);
}

bool operator<=(const Fraction& fra1, const Fraction& fra2){
    return (fra1.numerator * fra2.denominator <= fra2.numerator * fra1.denominator);
}



// 1 fraction 1 float case: ////
Fraction operator+ (const Fraction& fra, const float &flo){
    return (fra+Fraction(flo));   
}

Fraction operator- (const Fraction& fra, const float &flo){
    return  (fra-Fraction(flo));    
}

Fraction operator* (const Fraction& fra, const float &flo){
    return  (fra*Fraction(flo));    
}    
    
Fraction operator/(const Fraction& fra, const float &flo){
    return  (fra/Fraction(flo));    
}

bool operator==(const Fraction& fra, const float &flo){
    return ((fra) == Fraction(flo));
}

bool operator>(const Fraction& fra, const float &flo){
    return (fra > Fraction(flo));
}

bool operator<(const Fraction& fra, const float &flo){
    return (fra < Fraction(flo));
}

bool operator>=(const Fraction& fra, const float &flo){
    return (fra >= Fraction(flo));
}

bool operator<=(const Fraction& fra, const float &flo){
    return (fra <= Fraction(flo));
}




// 1 float 1 fraction case: ////
Fraction operator+ (const float &flo, const Fraction& fra){
    return (Fraction(flo)+fra); 
}

Fraction operator- (const float &flo, const Fraction& fra){
    return (Fraction(flo)-fra); 
}

Fraction operator* (const float &flo, const Fraction& fra){
    return (Fraction(flo)*fra); 
} 

Fraction operator/(const float &flo, const Fraction& fra){
    return (Fraction(flo)/fra); 
}

bool operator==(const float &flo, const Fraction& fra){
    return ((fra) == Fraction(flo));
}

bool operator>(const float &flo, const Fraction& fra){
    return (Fraction(flo) > fra);
}

bool operator<(const float &flo, const Fraction& fra){
    return (Fraction(flo) < fra);
}

bool operator>=(const float &flo, const Fraction& fra){
    return (Fraction(flo) >= fra);
}

bool operator<=(const float &flo, const Fraction& fra){
    return (Fraction(flo) <= fra);
}



// output overloading
ostream& operator<< (ostream& output, const Fraction& fra){
    // output form: "numerator/ denominator"
    output << fra.numerator << "/" << fra.denominator;
    return output;
}

// input overloading - receive inputs form: "numerator,denominator" or "numerator denominator".
istream& operator>> (istream& input, Fraction& fra){
    // get the numerator
    if (input >> fra.numerator){
        char separator = input.peek();
        if (separator == ',' || separator == ' ') {
            input.ignore();
        }
        // the input is not a fraction 
        else {
            input.setstate(ios::failbit);
            throw std::runtime_error("Invalid input: expected comma or space separator");
        }

        // get the denominator
        if (input >> fra.denominator) {
            // the denominator is zero
            if (fra.denominator == 0) {
                input.setstate(ios::failbit);
                throw std::runtime_error("Invalid input: denominator cannot be zero");
            }
            // update sign of the fraction.
            else if(fra.denominator < 0){
                fra.numerator *= -1;
                fra.denominator *= -1;
            }
        }
        // the input is not a fraction 
        else {
            input.setstate(ios::failbit);
            throw std::runtime_error("Invalid input: no denominator was given");
        }
    }
    // the input is not a fraction  
    else {
        input.setstate(ios::failbit);
        throw std::runtime_error("Invalid input: no numerator was given");
    }
    return input;
}
}

// end of program.