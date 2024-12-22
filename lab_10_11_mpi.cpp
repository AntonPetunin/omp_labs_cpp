// ЛАБОРАТОРНАЯ РАБОТА № 10-11
// Вариант: 5
// ФИО: Яровой Вадим Дмитриевич
// Группа: 5140904/40102

// Постановка задачи:

// 5. Реализовать рассылку массива значений на n процессов по принципу
// i-ое значение i-му процессу с помощью двухточечных обменов. Эффектив-
// ность реализации сравнить с функцией MPI_Scatter().

// В данном файле приведена реализация из MPI


#include <iostream>
#include <mpi.h>
#include <vector>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<int> values(size);
    int my_value = -1;

    if (rank == 0) {
        values.resize(size);
        for (int i = 0; i < size; ++i) {
            values[i] = i * 10;
        }
    }

    double start_time = MPI_Wtime();

    MPI_Scatter(values.data(), 1, MPI_INT, &my_value, 1, MPI_INT, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    if (rank == 0) {
       std::cout << "Время: " << (end_time - start_time) << " (c)" << std::endl;
    }

    std::cout << "Процесс " << rank << " получил значение " << my_value << std::endl;

    MPI_Finalize();
    return 0;
}

// Эффективность реализации сопоставима с функцией MPI_Scatter().
// Собственная реализация: 3.1177e-05 (с), 2.7546e-05 (с), 3.0324e-05 (с)
// Реализация метода  MPI: 3.0118e-05 (с), 2.7196e-05 (с), 2.9024e-05 (с)