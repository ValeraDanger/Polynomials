#include <unordered_map>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>

class Monom {
public:
    double coefficient; // коэффициент монома
    std::unordered_map<char, int> variables; // переменные монома и их степени

    // Конструктор
    Monom(double coefficient, const std::unordered_map<char, int>& variables) : coefficient(coefficient), variables(variables) { }

    // Конструктор по умолчанию
    Monom() : coefficient(0), variables({}) {}

    // Оператор сложения
    Monom operator+(const Monom& other) {
        if (this->variables == other.variables) {
            return Monom(this->coefficient + other.coefficient, this->variables);
        }
        else {
            throw std::invalid_argument("Мономы имеют разные переменные и не могут быть сложены.");
        }
    }

    // Оператор вычитания
    Monom operator-(const Monom& other) {
        if (this->variables == other.variables) {
            return Monom(this->coefficient - other.coefficient, this->variables);
        }
        else {
            throw std::invalid_argument("Мономы имеют разные переменные и не могут быть вычтены.");
        }
    }

    // Оператор умножения мономов
    Monom operator*(const Monom& other) const {
        Monom result = *this; // Начинаем с текущего монома
        result.coefficient *= other.coefficient; // Умножаем коэффициенты

        // Умножаем переменные, суммируя их степени
        for (const auto& var : other.variables) {
            result.variables[var.first] += var.second;
        }

        return result;
    }


    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Monom& monom) {
        os << monom.coefficient;
        for (const auto& var : monom.variables) {
            os << "*" << var.first << "^" << var.second;
        }
        return os;
    }

    // Оператор ввода
    friend std::istream& operator>>(std::istream& is, Monom& monom) {
        std::string str;
        is >> str;
        std::istringstream iss(str);
        std::string part;
        std::getline(iss, part, '*');
        monom.coefficient = std::stod(part);
        while (std::getline(iss, part, '*')) {
            char name = part[0];
            int degree = std::stoi(part.substr(2));
            monom.variables[name] = degree;
        }
        return is;
    }
};
