#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

// Реализуйте здесь
// * класс Matrix
// * оператор ввода для класса Matrix из потока istream
// * оператор вывода класса Matrix в поток ostream
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix
class Matrix
{
public:
	Matrix()
	{
		rows = 0;
		cols = 0;
	}
	Matrix(int num_rows, int num_cols)
	{
		Reset(num_rows, num_cols);
	}

	int GetNumRows() const
	{
		return rows;
	}

	int GetNumColumns() const
	{
		return cols;
	}

	int At(int row, int col) const
	{
		if (row < 0 || row > rows - 1 || col < 0 || col > cols - 1)
		{
			throw out_of_range("rows or columns are out of range");
		}
		return matrix[row][col];
	}

	int& At(int row, int col)
	{
		if (row < 0 || row > rows - 1 || col < 0 || col > cols - 1)
		{
			throw out_of_range("rows or columns are out of range");
		}
		return matrix[row][col];
	}

	void Reset(int new_rows, int new_cols)
	{
		if (new_rows < 0 || new_cols < 0)
		{
			throw out_of_range("rows or columns can't be negative");
		}
		rows = new_rows;
		cols = new_cols;
		matrix.assign(new_rows, vector<int>(new_cols, 0));
	}

	bool isEmpty() const
	{
		return (rows == 0 || cols == 0);
	}

	friend bool operator==(const Matrix& lhs, const Matrix& rhs);
private:
	vector<vector<int>> matrix;
	int rows;
	int cols;
};

ostream& operator<<(ostream& stream, const Matrix& mt)
{
	int rows = mt.GetNumRows();
	int cols = mt.GetNumColumns();
	stream << rows << ' ' << cols << endl;
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
			stream << mt.At(i, j) << ' ';
		//if (i != rows - 1)
		//{
			stream << endl;
		//}
	}
	return stream;
}

istream& operator>>(istream& stream, Matrix& mt)
{
	int rows;
	int cols;
	stream >> rows >> cols;
	mt.Reset(rows, cols);
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
			stream >> mt.At(i, j);
	}
	return stream;
}

bool operator==(const Matrix& lhs, const Matrix& rhs)
{
	if (lhs.isEmpty() && rhs.isEmpty())
	{
		return true;
	}
	return lhs.matrix == rhs.matrix;
}


Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
	if (lhs.isEmpty() && rhs.isEmpty())
	{
		return Matrix();
	}
	if ((lhs.GetNumRows() != rhs.GetNumRows()) || (lhs.GetNumColumns() != rhs.GetNumColumns()))
	{
		throw invalid_argument("Matrixes have different sizes");
	}
	Matrix result(lhs.GetNumRows(), lhs.GetNumColumns());
	for (int i = 0; i < lhs.GetNumRows(); ++i)
	{
		for (int j = 0; j < lhs.GetNumColumns(); ++j)
		{
			result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
		}
	}
	return result;
}

int main() {
	try
	{
	/*	Matrix one;
		Matrix two;

		ifstream file("input.txt");
		file >> one >> two;
		cout << (one + two) << endl;*/
		
		Matrix one(1, 0);
		Matrix two(0, 0);
		std::cout << (one == two) << std::endl;
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}
