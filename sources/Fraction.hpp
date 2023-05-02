#pragma once

#include <iostream>
using namespace std;


/**
 * @about: Fraction header file for Fraction class, Task 3 - Systems programing N.2 course.
 * @author Itamar Kuznitsov.
 * @since May. 2023
*/



namespace ariel{
    class Fraction
    {
    private:
        int numerator;
        int denominator;

    public:
        // constructor
        Fraction(int, int);
        Fraction(const Fraction &);
        Fraction(const float &flo);
        Fraction();

        // destructor
        ~Fraction();

        // move constructor
        Fraction(Fraction&& other) noexcept;

        // move assignment operator
        Fraction& operator=(Fraction&& other) noexcept;
        Fraction& operator=(const Fraction &fra);

        // assistance functions
        void reduce_fraction();
        static float fraction_to_float(Fraction fra);
        int getNumerator() const;
        int getDenominator() const;
        void update_sign(Fraction& fra);

        // 2 fractions case:
        friend Fraction operator+(const Fraction &fra1, const Fraction &fra2);
        friend Fraction operator-(const Fraction &fra1, const Fraction &fra2);
        friend Fraction operator*(const Fraction &fra1, const Fraction &fra2);
        friend Fraction operator/(const Fraction &fra1, const Fraction &fra2);
        friend bool operator==(const Fraction &fra1, const Fraction &fra2);
        friend bool operator>(const Fraction &fra1, const Fraction &fra2);
        friend bool operator<(const Fraction &fra1, const Fraction &fra2);
        friend bool operator>=(const Fraction &fra1, const Fraction &fra2);
        friend bool operator<=(const Fraction &fra1, const Fraction &fra2);

        // 1 fraction 1 float case:
        friend Fraction operator+(const Fraction &fra, const float &flo);
        friend Fraction operator-(const Fraction &fra, const float &flo);
        friend Fraction operator*(const Fraction &fra, const float &flo);
        friend Fraction operator/(const Fraction &fra, const float &flo);
        friend bool operator==(const Fraction &fra, const float &flo);
        friend bool operator>(const Fraction &fra, const float &flo);
        friend bool operator<(const Fraction &fra, const float &flo);
        friend bool operator>=(const Fraction &fra, const float &flo);
        friend bool operator<=(const Fraction &fra, const float &flo);

        // 1 float 1 fraction case:
        friend Fraction operator+(const float &flo, const Fraction &fra);
        friend Fraction operator-(const float &flo, const Fraction &fra);
        friend Fraction operator*(const float &flo, const Fraction &fra);
        friend Fraction operator/(const float &flo, const Fraction &fra);
        friend bool operator==(const float &flo, const Fraction &fra);
        friend bool operator>(const float &flo, const Fraction &fra);
        friend bool operator<(const float &flo, const Fraction &fra);
        friend bool operator>=(const float &flo, const Fraction &fra);
        friend bool operator<=(const float &flo, const Fraction &fra);

        // stdin & stdout: 
        friend std::ostream &operator<<(std::ostream &output, const Fraction &fra);
        friend std::istream &operator>>(std::istream &input, Fraction &fra);

        // prefix increment:
        Fraction &operator++()
        {
            this->numerator += this->denominator;
            this->reduce_fraction();
            return *this;
        }

        // postfix increment: int indicates postfix increment
        Fraction operator++(int)
        {
            // save the currunt fraction, update the original and return the first one.
            Fraction tmp_fraction(*this);

            this->numerator += this->denominator;
            this->reduce_fraction();
            return tmp_fraction;
        }

        // prefix increment:
        Fraction &operator--()
        {
            this->numerator -= this->denominator;
            this->reduce_fraction();
            return *this;
        }

        // postfix increment: int indicates postfix increment
        Fraction operator--(int)
        {
            // save the currunt fraction, update the original and return the first one.
            Fraction tmp_fraction(*this);

            this->numerator -= this->denominator;
            this->reduce_fraction();
            return tmp_fraction;
        }
    };
}

// end of header file.