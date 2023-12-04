#include <iostream>
#include <cstdlib>
#include <ctime>


void InitMatrix(int **matrix, int n) {
    int value = 1;
    int startrow = n / 2, startcol = n / 2;
    int steps = 1;

    matrix[startrow][startcol] = value++;

    while (steps < n) {
        // Move right
        for (int i = 0; i < steps; i++) {
            matrix[startrow][++startcol] = value++;
        }
        // Move up
        for (int i = 0; i < steps; i++) {
            matrix[--startrow][startcol] = value++;
        }
        steps++;

        // Move left
        for (int i = 0; i < steps; i++) {
            matrix[startrow][--startcol] = value++;
        }
        // Move down
        for (int i = 0; i < steps; i++) {
            matrix[++startrow][startcol] = value++;
        }
        steps++;
    }

    for (int i = 0; i < steps - 1; i++) {
        matrix[startrow][++startcol] = value++;
    }
}


void ClearMatrix(int ***matrix, int n) // We SHOULD clear our matrix array (bcs it has a lot of shit in ded. memory)
{
    int **clearMatrix = *matrix;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            clearMatrix[i][j] = 0;
        }
    }
}

void TransposeMatrix(int **matrix, int n) {
    int **result = new int *[n];
    for (int i = 0; i < n; i++) {
        result[i] = new int[n];
    }

    // Transpose the matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = matrix[j][i];
        }
    }

    // Copy the transposed matrix back to the original matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = result[i][j];
        }
    }

    // Deallocate memory for the temporary matrix
    for (int i = 0; i < n; i++) {
        delete[] result[i];
    }
    delete[] result;
}

void GenerateRandomMatrix(int **matrix, int n) {
    // Stackoverflow <3
    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 11;
        }
    }
}

void ComputeMatrixFromMatrix(int **inputMatrix, int **resultMatrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            resultMatrix[i][j] -= inputMatrix[i][j];
        }
    }
}


void PrintMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << '\n';
}

int main() {
    int n;
    std::cout << "Matrix size (it must be in range [4; 20] and even)\n";
    std::cin >> n;
    if (n < 4 || n > 20 || not(n % 2)) {
        std::cout << "Incorrect size";
        return -1;
    }

    int **matrix = new int *[n];
    for (int i = 0; i < n; i++) {
        int *col = new int[n];
        matrix[i] = col;
    }
    ClearMatrix(&matrix, n);
    InitMatrix(matrix, n);
    std::cout << "Init Matrix:" << "\n";
    PrintMatrix(matrix, n);


    std::cout << "Done. First part of code finished process with code 0." << "\n" << "\n" << "Making Additional task:";
    std::cout << "Transpose Matrix:" << "\n";
    TransposeMatrix(matrix, n);
    PrintMatrix(matrix, n);
    int **rand_matrix = new int *[n];
    for (int i = 0; i < n; i++) {
        rand_matrix[i] = new int[n];
    }
    InitMatrix(rand_matrix, n);
    GenerateRandomMatrix(rand_matrix, n);
    std::cout << "Creating Rand Matrix" << "\n";
    PrintMatrix(rand_matrix, n);

    std::cout << "Transpose Matrix - Rand Matrix :" << "\n";

    ComputeMatrixFromMatrix(rand_matrix, matrix, n);
    PrintMatrix(matrix, n);

    //    clearing sh... things for our program
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
        delete[] rand_matrix[i];
    }
    delete[] matrix;
    delete[] rand_matrix;

    return 0;
}
