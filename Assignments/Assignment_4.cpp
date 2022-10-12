// Object-Oriented Programming in C++
// Assignment 4 - a class for complex numbers
// Timothe Rhein - 12/3/2022

#include <iostream>
#include <cmath>
#include <string>


// Numerical constants
const double pi{std::atan(1) * 4};


class ComplexNumber
	// Class to manipulate complex numbers of the form "x + iy" or "x - iy".
{
public:
	// Constructors and destructor.
	ComplexNumber() = default;
	ComplexNumber(const double& real_part, const double& imaginary_part) : real{real_part}, imaginary{imaginary_part} {}

	~ComplexNumber() {}

	// Member functions.
	double get_real() const { return real; }
	double get_imaginary() const { return imaginary; }
	double get_modulus() const { return std::sqrt( std::pow(real, 2) + std::pow(imaginary, 2)); }
	double get_argument() const;

	ComplexNumber get_conjugate() const 
	{
		ComplexNumber temp{real, -imaginary};
		return temp;
	}

	// Overloaded functions.
	ComplexNumber operator+(const ComplexNumber& complex_number) const 
	{
		ComplexNumber temp{real + complex_number.real, imaginary + complex_number.imaginary};
		return temp;
	}
	ComplexNumber operator-(const ComplexNumber& complex_number) const 
	{
		ComplexNumber temp{real - complex_number.real, imaginary - complex_number.imaginary};
		return temp;
	}
	ComplexNumber operator*(const ComplexNumber& complex_number) const 
	{
		double real_part{real * complex_number.real - imaginary * complex_number.imaginary};
		double imaginary_part{real*complex_number.imaginary + imaginary*complex_number.real};
		ComplexNumber temp{real_part, imaginary_part};
		return temp;
	}
	ComplexNumber operator/(const ComplexNumber& complex_number) const 
	{
		double real_part{(real*complex_number.real + imaginary*complex_number.imaginary)/ std::pow(complex_number.get_modulus(), 2)};
		double imaginary_part{(-real*complex_number.imaginary + imaginary*complex_number.real)/ std::pow(complex_number.get_modulus(), 2)};
		ComplexNumber temp{real_part, imaginary_part};
		return temp;
	}

	// Overloaded friend functions.
	friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& complex_number);
	friend std::istream& operator>>(std::istream& is, ComplexNumber& complex_number);


private:
	double real{0};
	double imaginary{0};

};

// ComplexNumber class and friend functions
double ComplexNumber::get_argument() const 
{
	double reference_angle{std::atan(imaginary / real)};
	if (real < 0) {
		reference_angle += pi;
	}
	if (reference_angle > pi) {
		reference_angle -= 2 * pi;
	}
	return reference_angle;
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber& complex_number)
{
	if (complex_number.imaginary < 0) {
		os << complex_number.real << " - i" << -complex_number.imaginary;
	} else {
		os << complex_number.real << " + i" << complex_number.imaginary;
	}
	return os;
}

std::istream& operator>>(std::istream& is, ComplexNumber& complex_number)
// Read complex number from istream of the form 'x + iy' or 'x - iy'. Space sensitive.
{
	double real_part;
	double imaginary_part;
	std::string sign;

	is >> real_part;
	is.ignore();
	sign = is.peek();
	if (sign == "+") {
		is >> sign;
		is >> std::ws;
		is.ignore();
		is >> imaginary_part;
	} else if (sign == "-") {
		is >> sign;
		is >> std::ws;
		is.ignore();
		is >> imaginary_part;
		imaginary_part *= -1;
	} else {
		imaginary_part = 0;
	}
	complex_number.real = real_part;
	complex_number.imaginary = imaginary_part;
	return is;
}


int main()
{
	// Trial complex numbers a = 3 + i4; b = 1 - i2
	ComplexNumber a{3,4};
	ComplexNumber b{1,-2};

	std::cout << "The complex number a is " << a << ".\n";
	std::cout << "The complex number b is " << b << ".\n";

	// Arithmetic functions
	ComplexNumber c{a + b};
	ComplexNumber d{a - b};
	ComplexNumber e{a * b};
	ComplexNumber f{a / b};

	std::cout << "a + b = " << c << std::endl;
	std::cout << "a - b = " << d << std::endl;
	std::cout << "a * b = " << e << std::endl;
	std::cout << "a / b = " << f << std::endl;

	// Method functions
	std::cout << "The modulus of a is " << a.get_modulus() << ".\n";
	std::cout << "The argument of a is " << a.get_argument() << " radians.\n";
	std::cout << "The real part of a is " << a.get_real() << ".\n";
	std::cout << "The imaginary part of a is " << a.get_imaginary() << ".\n";
	std::cout << "The complex conjugate of a is " << a.get_conjugate() << ".\n";

	
	// istream complex number input test
	ComplexNumber input_number;

	std::cout << "\nInput test.\n";
	std::cout << "Please enter a complex number in the form 'x + iy' or 'x - iy': ";
	std::cin >> input_number;

	std::cout << "Your complex number is " << input_number << ".\n";

	return 0;
}