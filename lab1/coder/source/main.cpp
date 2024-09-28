#include <iostream>

#include "coder/coder.h"


int main() {
    // Инициализация с помощью файла с вероятностями символов
    Coder coder("../../ascii_letter_chance.azya");
    
    // Тестовое кодирование слуайного фрагмента
    coder.code("../../orwell.txt");

    // Декодирование исходного фрагмента
    coder.decode("../../orwell.txt-coded");

    return 0;
}
