#pragma once

#include <stdexcept>
#include <unordered_map>
#include <string>
#include <iostream>
//#include <list>
#include "List.h"
#include <sstream>
#include "Monom.h"

class Polynomial {
public:
    //std::list<Monom> monoms; // список мономов
    List<Monom> monoms;

    // Конструктор по умолчанию
    Polynomial() {}

    // Метод для добавления монома
    void push(const Monom& monom) {
        bool added = false;
        for (auto it = monoms.begin(); it != monoms.end(); ++it) {
            if (it->variables == monom.variables) {
                it->coefficient += monom.coefficient;
                if (it->coefficient == 0) {
                    monoms.erase(it);
                }
                added = true;
                break;
            }
        }
        if (!added && monom.coefficient != 0) {
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

    // Оператор сложения (для наглядности без изменений)
    Polynomial operator+(Polynomial& other) {
        Polynomial result = *this;
        for (auto it = other.monoms.begin(); it != other.monoms.end(); ++it) {
            result.push(*it);
        }
        return result;
    }

    // Оператор вычитания (для наглядности без изменений)
    Polynomial operator-(Polynomial& other) {
        Polynomial result = *this;
        for (auto it = other.monoms.begin(); it != other.monoms.end(); ++it) {
            Monom negative_monom = *it;
            negative_monom.coefficient = -negative_monom.coefficient;
            result.push(negative_monom);
        }
        return result;
    }

    // Оператор умножения полиномов
    Polynomial operator*(Polynomial& other) {
        Polynomial result;
        for (auto it = monoms.begin(); it != monoms.end(); ++it) {
            for (auto jt = other.monoms.begin(); jt != other.monoms.end(); ++jt) {
                Monom product = *it * *jt; // Умножаем каждый моном первого полинома на каждый моном второго
                result.push(product); // Добавляем результат в полином результата
            }
        }
        return result;
    }
    
    // Оператор умножения полинома на константу
    Polynomial operator*(const double constant) {
        Polynomial result;
        for (auto it = monoms.begin(); it != monoms.end(); ++it) {
            Monom temp = *it;
            temp.coefficient *= constant; // Умножаем коэффициент каждого монома на константу
            result.push(temp); // Добавляем измененный моном в результат
        }
        return result;
    }


    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, Polynomial& polynomial) {
        auto it = polynomial.monoms.begin();
        if (it != polynomial.monoms.end()) {
            os << *it;
            ++it;
        }
        while (it != polynomial.monoms.end()) {
            os << " + " << *it;
            ++it;
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
