#ifndef LAB1_H
#define LAB1_H

#include <iostream>
#include <vector>
#include <algorithm>

/// @brief Пространство имен лабораторной работы
namespace lab1
{
    /// Перечисление возможных форматов поля JSON
    enum jsonType
    {
        jsonString,
        jsonLong,
        jsonDouble,
        jsonBool,
        jsonVoid
    };

    /// brief Основный цикл диалогового меню
    void loop();

    /// @brief Функция определения формата поля JSON
    /// @param str Строка, содержащая поле
    /// @return Элемент перечисления определяющий тип поля JSON
    jsonType getType(std::string &str);

    /// @brief Функция проверки строки, на наличие только цифр и десятичных точек
    /// @param str Проверяемая строка
    /// @return true, если строка состоит только из цифр и точек, false если в ней присутствуют иные символы
    bool isDouble(std::string &str);

    /// @brief Функция перевода JSON-строки в строку-структуру, использующая в качестве аргументов const char*
    /// @param name Название структуры
    /// @param jsonStr JSON-строка
    /// @return Строка-структура const char*
    /// @throws std::runtime_error("bad json input") если ввод не отформатирован под JSON
    const char *parse(const char *name, const char *jsonStr);

    /// @brief Функция перевода JSON-строки в строку-структуру, использующая в качестве аргументов std::string
    /// @param name Название структуры
    /// @param jsonStr JSON-строка
    /// @return Строка-структура std::string
    /// @throws std::runtime_error("bad json input") если ввод не отформатирован под JSON
    std::string parse(const std::string &name, const std::string &jsonStr);
}

#endif // LAB1_H