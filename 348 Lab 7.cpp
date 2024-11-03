/*
Name: Jaydee Brown
Lab: Wed 1pm
KUID: 3140576
Desc: Matrix input, output and operations*/




#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
//prototypes
class Matrix;
Matrix add_matrices(const Matrix& matrix_1, const Matrix& matrix_2);
Matrix multiply_matrices(const Matrix& matrix_1, const Matrix& matrix_2);

class Matrix {
public:
    int matrix_size;
    double** matrix_data;
    
    //initialize matrix data memory size
    Matrix(int size = 0) : matrix_size(size) {
        matrix_data = new double* [matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size];
        }
    }
    //overload equals
    Matrix& operator=(const Matrix& other) {
        if (this == &other) {
            return *this;
        }

        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;

        matrix_size = other.matrix_size;

        matrix_data = new double* [matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size];
            for (int j = 0; j < matrix_size; ++j) {
                matrix_data[i][j] = other.matrix_data[i][j];
            }
        }

        return *this;
    }

    //overload addition
    Matrix operator+(const Matrix& other) {
        return add_matrices(*this,other);
    }
    //overload multiplication
    Matrix operator*(const Matrix& other) {
        return multiply_matrices(*this, other);
    }

    ~Matrix() {
        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;
    }
};

//splits strings into a double array
void split(const string& str, char del,double*& array) {
    std::stringstream ss(str);
    string val;
    int i = 0;
    while(getline(ss,val,del)){
        array[i] = stod(val);
        i++;
    };
}

void read_matrix_from_file(const string& file_name, Matrix& matrix_1, Matrix& matrix_2) {
    string temp_string;
    int matrix_size;

    //read file
    ifstream ReadFile("matrix.txt");

    //get matrix size
    getline(ReadFile, temp_string);
    matrix_size = std::stoi(temp_string);

    //initialize matrices
    matrix_1 = Matrix(matrix_size);
    matrix_2 = Matrix(matrix_size);


    //convert matrix 1 to array
    for (int i = 0; i < matrix_size; i++) {
        string tmp;
        getline(ReadFile, tmp);
        split(tmp, ' ',matrix_1.matrix_data[i]);
    }
    //convert matrix 2 to array
    for (int i = 0; i < matrix_size; i++) {
        string tmp;
        getline(ReadFile, tmp);
        split(tmp, ' ', matrix_2.matrix_data[i]);
    }
}

void print_matrix(const Matrix& matrix) {
    for (int i=0; i < matrix.matrix_size; i++) {
        for (int j=0; j < matrix.matrix_size; j++) {
            std::cout << matrix.matrix_data[i][j] << " ";
        }
        std::cout << endl;
    }
    std::cout << endl;
}

void print_matrix(const Matrix& matrix_1, const Matrix& matrix_2) {
    std::cout << "Matrix 1:" << endl;
    print_matrix(matrix_1);
    std::cout << "Matrix 2:" << endl;
    print_matrix(matrix_2);

}

Matrix add_matrices(const Matrix& matrix_1, const Matrix& matrix_2) {
    //initialize matrix
    Matrix output_matrix = Matrix(matrix_1.matrix_size); //since both matrices are the same size, I can initilized based off one matrix size
    //populate values
    for (int i = 0; i < output_matrix.matrix_size; i++) {
        for (int j = 0; j < output_matrix.matrix_size; j++) {
            output_matrix.matrix_data[i][j] = matrix_1.matrix_data[i][j] + matrix_2.matrix_data[i][j];
        }
    }
    return output_matrix;
}

Matrix multiply_matrices(const Matrix& matrix_1, const Matrix& matrix_2) {
    //initialize output matrix
    int matrix_size = matrix_1.matrix_size; //both are same size so don't need to calculate new values
    Matrix output_matrix = Matrix(matrix_size);

    //matrix multiplication
    for (int i = 0; i < matrix_size; i++) {
        for (int n = 0; n < matrix_size; n++) {
            for (int j = 0; j < matrix_size; j++) { //multiplies row of m1 with column of m2
                output_matrix.matrix_data[i][n] = matrix_1.matrix_data[i][j] * matrix_2.matrix_data[j][n];
            }
        }
    }
    return output_matrix;
}


void get_diagonal_sum(const Matrix& matrix) {
    int matrix_size = matrix.matrix_size;
    int prim_dag = 0;
    int sec_dag = 0;
    //primary diag
    for (int i = 0; i < matrix_size; i++) {
        prim_dag += matrix.matrix_data[i][i];
    }
    //secondary dag diag
    for (int i = 0; i < matrix_size; i++) {
        sec_dag += matrix.matrix_data[i][matrix_size-i];
    }
    //print
    cout << "Sum of Primary Diagonal: " << prim_dag << endl;
    cout << "Sum of Secondary Diagonal: " << sec_dag << endl;
}

void swap_matrix_row(Matrix& matrix, int row1, int row2) {
    int matrix_size = matrix.matrix_size;
    //check indices
    if (!(0 <= row1 < matrix_size || 0 <= row2 < matrix_size)) {
        cout << "Invalid Row Indices!";
        return;
    }
    //swap rows
    for (int i = 0; i < matrix_size; i++) {
        double tmp = matrix.matrix_data[row1][i];
        matrix.matrix_data[row1][i] = matrix.matrix_data[row2][i];
        matrix.matrix_data[row2][i] = tmp;
    }
    print_matrix(matrix);
}

int main(int argc, char* argv[]) {
    Matrix matrix_1, matrix_2;
    read_matrix_from_file("matrix.txt", matrix_1, matrix_2);

    cout << "print_matrix" << endl;
    print_matrix(matrix_1, matrix_2);
    cout << endl;

    cout << "add_matrices result:" << endl;
    Matrix add_result_1 = add_matrices(matrix_1, matrix_2);
    Matrix add_result_2 = matrix_1 + matrix_2;
    print_matrix(add_result_1);
    print_matrix(add_result_2);
    
    cout << "multiply_matrices result:" << endl;
    Matrix multiply_result_1 = multiply_matrices(matrix_1, matrix_2);
    Matrix multiply_result_2 = matrix_1 * matrix_2;
    print_matrix(multiply_result_1);
    print_matrix(multiply_result_2);
    
    cout << "get matrix diagonal sum" << endl;
    get_diagonal_sum(matrix_1);
    cout << endl;

    cout << "swap matrix rows" << endl;
    swap_matrix_row(matrix_1, 0, 1);

    return 0;
}