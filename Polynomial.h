#pragma once

#include <stdexcept>
#include <unordered_map>
#include <string>
#include <iostream>
#include <list>
#include <sstream>
#include "Monom.h"

class Polynomial {
public:
    std::list<Monom> monoms; // список мономов

    // Конструктор по умолчанию
    Polynomial() : monoms({}) {}

    // Метод для добавления монома
    void push(const Monom& monom) {
        for (auto it = monoms.begin(); it != monoms.end(); ++it) {
            if (it->variables == monom.variables) {
                it->coefficient += monom.coefficient;
                if (it->coefficient == 0) {
                    monoms.erase(it);
                }
                return;
            }
        }
        if (monom.coefficient != 0) {
            monoms.push_back(monom);
        }
    }


    // Метод для проверки корректности входной строки
    bool isValidInput(const std::string& str) {
        for (char c : str) {
            if (!std::isdigit(c) && c != '+' && c != '-' && c != '*' && c != '^' && !std::isalpha(c)) {
                return false;
            }
        }
        return true;
    }

    // Оператор сложения
    Polynomial operator+(const Polynomial& other) {
        Polynomial result = *this;
        for (const auto& monom : other.monoms) {
            result.push(monom);
        }
        return result;
    }

    // Оператор вычитания
    Polynomial operator-(const Polynomial& other) {
        Polynomial result = *this;
        for (auto& monom : other.monoms) {
            Monom negative_monom(monom);
            negative_monom.coefficient = -monom.coefficient;
            result.push(negative_monom);
        }
        return result;
    }

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& polynomial) {
        for (std::list<Monom>::const_iterator it = polynomial.monoms.begin(); it != polynomial.monoms.end(); ++it) {
            if (it != polynomial.monoms.begin()) {
                os << " + ";
            }
            os << *it;
        }
        return os;
    }

     // Оператор ввода
    friend std::istream& operator>>(std::istream& is, Polynomial& polynomial) {
        std::string str;
        is >> str;
        if (!polynomial.isValidInput(str)) {
            throw std::invalid_argument("Некорректный ввод");
        }

        std::string monom_str = "";

        if (str[0] == '-') {
            monom_str = "-";
            str = str.substr(1);
        }

        for (char symbol : str) {

            if (symbol == '-') {
                Monom monom;
                std::istringstream monom_iss(monom_str);
                monom_iss >> monom;
                polynomial.push(monom);

                monom_str = "-";
            }

            else if (symbol == '+') {
                Monom monom;
                std::istringstream monom_iss(monom_str);
                monom_iss >> monom;
                polynomial.push(monom);

                monom_str = "";
            }

            else {
                monom_str += symbol;
            }
        }

        Monom monom;
        std::istringstream monom_iss(monom_str);
        monom_iss >> monom;
        polynomial.push(monom);
    }
};
