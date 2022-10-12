// Object-Oriented Programming in C++
// Assignment 5 - a class for matrices
// Timothe Rhein - 27/3/2022

#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

class Matrix
	// Class to store matrix of size m x n, where m is rows and n colunms.
{
public:
	Matrix() = default;
	Matrix(const size_t m, const size_t n);
	Matrix(const Matrix& copied_matrix);
	Matrix(Matrix&& moved_matrix) noexcept;
	~Matrix();

	// Overloaded operators
	Matrix& operator=(const Matrix& copied_matrix);
	Matrix& operator=(Matrix&& moved_matrix) noexcept;
	double operator()(const size_t row, const size_t column) const;
	double& operator()(const size_t row, const size_t column);
	Matrix operator+(const Matrix& matrix) const;
	Matrix operator-(const Matrix& matrix) const;
	Matrix operator*(const Matrix& matrix) const;

	// Overloaded friend functions
	friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
	friend std::istream& operator>>(std::istream& is, Matrix& matrix);

	// Member functions
	Matrix remove_row_column(const size_t row, const size_t column) const;
	double calculate_determinant() const;

private:
	size_t number_of_rows{};
	size_t number_of_columns{};
	size_t size{number_of_rows * number_of_columns};
	double* data{nullptr};
};


// Constructors and destructor
Matrix::Matrix(const size_t m, const size_t n)
{
	if (m * n == 0) {
		std::cout << "Error. Cannot create matrix of size 0.\n";
	}
	number_of_rows = m;
	number_of_columns = n;
	size = m * n;
	data = new double[size];

	for (size_t i{0}; i < size; i++) {
		data[i] = 0;
	}
}

Matrix::Matrix(const Matrix& copied_matrix)
{
	number_of_rows = copied_matrix.number_of_rows;
	number_of_columns = copied_matrix.number_of_columns;
	size = copied_matrix.size;

	if (size != 0) {
		data = new double[size];
		for (size_t i{0}; i < size; i++) {
			data[i] = copied_matrix.data[i];
		}
	}
}

Matrix::Matrix(Matrix&& moved_matrix) noexcept
{
	number_of_rows = moved_matrix.number_of_rows;
	number_of_columns = moved_matrix.number_of_columns;
	size = moved_matrix.size;
	data = moved_matrix.data;

	moved_matrix.number_of_rows = 0;
	moved_matrix.number_of_columns = 0;	
	moved_matrix.size = 0;
	moved_matrix.data = nullptr;
}

Matrix::~Matrix()
{
	delete data;
}


// Overloaded operators
Matrix& Matrix::operator=(const Matrix& copied_matrix)
{
	if (this != &copied_matrix) {

		delete[] data;

		// Copy data
		number_of_rows = copied_matrix.number_of_rows;
		number_of_columns = copied_matrix.number_of_columns;
		size = copied_matrix.size;
		data = nullptr;

		if (size != 0) {
			data = new double[size];
			for (size_t i{0}; i < size; i++) {
				data[i] = copied_matrix.data[i];
			}
		}
	}
	return *this;
}

Matrix& Matrix::operator=(Matrix&& moved_matrix) noexcept
{
	if (this != &moved_matrix) {
		delete[] data;

		number_of_rows = moved_matrix.number_of_rows;
		number_of_columns = moved_matrix.number_of_columns;
		size = moved_matrix.size;
		data = moved_matrix.data;

		moved_matrix.number_of_rows = 0;
		moved_matrix.number_of_columns = 0;
		moved_matrix.size = 0;
		moved_matrix.data = nullptr;
	}
	return *this;
}

double Matrix::operator()(const size_t row, const size_t column) const
{
	return data[(column-1) + (row-1)*number_of_columns];
}

double& Matrix::operator()(const size_t row, const size_t column)
{
	return data[(column - 1) + (row - 1) * number_of_columns];
}

Matrix Matrix::operator+(const Matrix& matrix) const
{
	if (number_of_rows != matrix.number_of_rows || number_of_columns != matrix.number_of_columns) {
		std::cout << "Error: added matrices must have the same dimensions.\n";
		return Matrix();
	}

	Matrix temp{number_of_rows, number_of_columns};
	for (size_t i{0}; i < temp.size; i++) {
		temp.data[i] = data[i] + matrix.data[i];
	}
	return temp;
}

Matrix Matrix::operator-(const Matrix& matrix) const
{
	if (number_of_rows != matrix.number_of_rows || number_of_columns != matrix.number_of_columns) {
		std::cout << "Error: subtracted matrices must have the same dimensions.\n";
		return Matrix();
	}

	Matrix temp{number_of_rows, number_of_columns};
	for (size_t i{0}; i < temp.size; i++) {
		temp.data[i] = data[i] - matrix.data[i];
	}
	return temp;
}

Matrix Matrix::operator*(const Matrix& matrix) const
{
	if (number_of_columns != matrix.number_of_rows) {
		std::cout << "Error: multiplied matrices must be of dimensions (mxn) x (nxp).\n";
		return Matrix();
	}

	Matrix temp{number_of_rows, matrix.number_of_columns};
	for (size_t i{1}; i <= temp.number_of_rows; i++) {
		for (size_t j{1}; j <= temp.number_of_columns; j++) {

			double product_entry{0};
			for (size_t k{1}; k <= number_of_columns; k++) {
				product_entry += this->operator()(i, k) * matrix(k, j);
			}
			temp.data[(j-1) + (i-1)*temp.number_of_columns] = product_entry;
		}
	}
	return temp;
}


// Overloaded friend functions
std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
	os << "[";
	for (size_t i{1}; i <= matrix.number_of_rows; i++) {
		os << "[";
		for (size_t j{1}; j < matrix.number_of_columns; j++) {
			os << matrix(i, j) << ", ";
		}
		os << matrix(i, matrix.number_of_columns) << "]";
		if (i != matrix.number_of_rows) {
			os << ",\n";
		}
	}
	os << "]";
	
	return os;
}

std::istream& operator>>(std::istream& is, Matrix& matrix)
	// Matrix insertion operator. Format: entries are split by spaces, rows are split using '/' and the end of the matrix is denoted by '//'. 
	// For example: "1 0/0 1//" is the identity matrix I_2.
{
	size_t row_count{0}, column_count{0};
	double matrix_entry;
	std::vector<double> matrix_data;

	while (row_count < 100) {
		row_count++;
		is >> std::ws;

		while (is.peek() != '/') {
			is >> matrix_entry;
			is >> std::ws;
			matrix_data.push_back(matrix_entry);
			if (row_count == 1) {
				column_count++;
			}
		}
		is.ignore(); // skip first '/'.
		if (is.peek() == '/') { break; } // end reading loop if two forward slashes follow each other ie. "//".
	}

	// Assign Matrix elements
	Matrix temp{row_count, column_count};

	if (temp.size != matrix_data.size()) {
		std::cout << "Error: matrix was not read in correctly. Please check the format.\n";

	} else {
		for (size_t i{0}; i < temp.size; i++) {
			temp.data[i] = matrix_data[i];
		}
		matrix = temp;
	}
	return is;
}


// Member functions
Matrix Matrix::remove_row_column(const size_t row, const size_t column) const
{
	Matrix temp{number_of_rows - 1, number_of_columns - 1};

	for (size_t i{1}; i <= number_of_rows; i++) {
		for (size_t j{1}; j <= number_of_columns; j++) {
			if (i != row && j != column) {
				size_t new_i{i}, new_j{j};
				if (i > row) { new_i--; }
				if (j > column) { new_j--; }

				temp(new_i, new_j) = this->operator()(i, j);
			}
		}
	}
	return temp;
}

double Matrix::calculate_determinant() const
{
	if (number_of_rows != number_of_columns) {
		std::cout << "Error: matrix must be square to calculate determinant.\n";
		return std::nan("");
	}

	if (number_of_rows == 0) {
		std::cout << "Error: matrix must be of size greater than zero to calculate determinant.\n";
		return std::nan("");

	} else if (number_of_rows == 1) {
		return this->operator()(1, 1);

	} else if (number_of_rows == 2) {
		return this->operator()(1, 1) * this->operator()(2, 2) - this->operator()(1, 2) * this->operator()(2, 1);

	} else {
		double determinant{0};

		for (size_t j{1}; j <= number_of_rows; j++) {
			determinant += std::pow(-1, 1 + j) * this->operator()(1, j) * this->remove_row_column(1, j).calculate_determinant();
		}
		return determinant;
	}
}


int main()
{
	// Create matrices and assign values
	Matrix a;
	std::stringstream a_input;
	a_input << "1 2 3 / 9 8 7 / 4 2 6 //";
	a_input >> a;

	Matrix b;
	std::stringstream b_input;
	b_input << "5 5 4/1 2 3/6 9 8//";
	b_input >> b;

	Matrix c;
	std::stringstream c_input;
	c_input << "3 4 1/2 5 6//";
	c_input >> c;

	// Test operations
	std::cout << "A+B = \n" << a + b << "\n\n";
	std::cout << "A-B = \n" << a - b << "\n\n";
	std::cout << "A*B = \n" << a * b << "\n\n";
	std::cout << "C*B = \n" << c * b << "\n\n";
	std::cout << "B*C = \n" << b * c << "\n\n";

	// Determinants
	std::cout << "The determinant of A is " << a.calculate_determinant() << ".\n";
	std::cout << "The determinant of B is " << b.calculate_determinant() << ".\n\n";

	// Copy constructor
	Matrix a_copy{a};

	a_input.str("");
	a_input << "1/2/3//";
	a_input >> a;

	std::cout << "The copy of A is \n" << a_copy << "\n\n";
	std::cout << "A after being changed is \n" << a << "\n\n";

	// Move constructor
	Matrix a_moved{std::move(a)};
	std::cout << "The value of a_moved constructed by moving A is \n" << a_moved << "\n\n";
	std::cout << "A after being moved is \n" << a << "\n\n";

	return 0;
}