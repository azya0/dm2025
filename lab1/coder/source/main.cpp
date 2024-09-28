#include <iostream>

#include "coder/coder.h"


int main() {
    // Инициализация с помощью файла с вероятностями символов
    Coder coder("../../ascii_letter_chance.azya");
    
    // Тестовое кодирование слуайного фрагмента
    coder.code("../../orwell.txt");

    // Для "проверки" достаточно добавить true как второй параметр
    // P.s. Сильно замедляет работу из-за принта в консоль.
    // P.s. Так что отключено по умолчанию
    coder.decode("../../orwell.txt-coded", false);

    // Вывод всех кодов на экран
    coder.print();

    return 0;
}
