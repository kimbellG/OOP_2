#ifndef MENU_FUNC_HPP
#define MENU_FUNC_HPP

#include <iostream>
#include <string>

#include "get_fromkb.hpp"
#include "eqinterface.h"

bool isCurrentAnswer(std::string rightAnswer, std::string userAnswer);

template<typename T> inline T getFromKeyBoard() {
    T valueFromKeyboard;
    std::cin >> valueFromKeyboard;
    return valueFromKeyboard;
}

inline void inputAndAnswerQ() {
    const std::string question = "Как сделать собственную обработку необработанного исключения?";
    const std::string correctAnswer = "Необходимо использовать создать собственную функция без аргументов и возвращающего значения. Далее вызовом функции set_unexcept(void (*userFunc)()) переназначить предыдущую функцию";
    std::string Answer;

    std::cout << question << std::endl;
    std::cout << "Answer que: ";
    Answer = getFromKeyBoard<std::string>();

    if (!isCurrentAnswer(correctAnswer, Answer)) {
        std::cout << "Ответ неправильный!" << std::endl;
        std::cout << "Правильный ответ: " << correctAnswer;
    } else {
        std::cout << "Ответ правильный!";
    }
}

inline bool isCurrentAnswer(std::string rightAnswer, std::string userAnswer) {
    return rightAnswer == userAnswer;
}

std::string get_filename()
{
    gym::input_interface::clear_window();
    std::cout << "Input name of file for work: ";
    std::string filename = get_from_keyboard<std::string>();
    return filename;
}

#endif // MENU_FUNC_HPP
