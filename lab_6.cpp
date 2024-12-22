// ЛАБОРАТОРНАЯ РАБОТА № 6
// Вариант: 4
// ФИО: Петунин Антон Александрович
// Группа: 5140904/40102

// Задание:

// Дана последовательность символов С = {с0…сn–1} и символ b. 
// Создать OpenMP-приложение для определения количество вхождений символа b
// в строку C. Количество символов и потоков являются входными параметрами 
// программы, количество символов в строке может быть не кратно количеству потоков. 

#include <iostream>
#include <cstring>
#include <vector>
#include <omp.h>

int main(int argc, char* argv[]) {
    // Обработка ошибки неверного числа аргументов
    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " <num_threads> <searchChar> <sourceCharArray>" << std::endl;
        return 1; 
    }
    
    // Количество потоков первым аргументом
    size_t num_threads = std::stoi(argv[1]);
    // Искомый символ вторым аргументов
    char * searchChar = argv[2];

    // Проверка, что вторым параметром пришёл валидный символ
    if (searchChar && std::strlen(searchChar) > 1 || !searchChar) {
        std::cout << "Error: searchChar isn't char because of it's size." << std::endl;
        return 1;
    }
    
    // Исходная строка для поиска третьим аргументом
    char * sourceCharArray = argv[3];
    // Поиск длины исходной строки
    size_t charArrSize = std::strlen(sourceCharArray);
    // Размер чанка для прагмы omp
    size_t schedule_chunk_size = charArrSize / num_threads + 1;

    // Результирующее число вхождений искомого символа в строке
    int searchCharCount = 0;
    // Номер итерации
    size_t i = 0;

    // Параллельный цикл с использованием прагмы
#pragma omp parallel for schedule(static, schedule_backet_size) private(i) reduction(+:searchCharCount)
    for (i = 0; i < charArrSize; i++) {
        // Проверка совпадения символа в строке
        if (sourceCharArray[i] == *searchChar) {
            // Инкрементация счетчика
            searchCharCount++;
            // Вывод номера потока выполнения
            std::cout << "Active thread num on increase: " << omp_get_thread_num() << std::endl;
        }
    }

    // Вывод количества вхождений искомого символа в строке
    std::cout << "Number of occurrences is " << searchCharCount << std::endl;
    return 0;
}

// clang -fopenmp -o bin/lab_6 lab_6.cpp -lstdc++ && ./bin/lab_6 4 a djfhk_jhalkjhkajhkjhdakjha_kj\
dhfkjhakjfhakjaa_jadjufhdkjfhkjah_dkfjaaadfgsaddfsd
