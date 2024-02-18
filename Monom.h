#include <unordered_map>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>

class Monom {
public:
    double coefficient; // ����������� ������
    std::unordered_map<char, int> variables; // ���������� ������ � �� �������

    // �����������
    Monom(double coefficient, const std::unordered_map<char, int>& variables) : coefficient(coefficient), variables(variables) { }

    // ����������� �� ���������
    Monom() : coefficient(0), variables({}) {}

    // �������� ��������
    Monom operator+(const Monom& other) {
        if (this->variables == other.variables) {
            return Monom(this->coefficient + other.coefficient, this->variables);
        }
        else {
            throw std::invalid_argument("������ ����� ������ ���������� � �� ����� ���� �������.");
        }
    }

    // �������� ���������
    Monom operator-(const Monom& other) {
        if (this->variables == other.variables) {
            return Monom(this->coefficient - other.coefficient, this->variables);
        }
        else {
            throw std::invalid_argument("������ ����� ������ ���������� � �� ����� ���� �������.");
        }
    }

    // �������� ������
    friend std::ostream& operator<<(std::ostream& os, const Monom& monom) {
        os << monom.coefficient;
        for (const auto& var : monom.variables) {
            os << "*" << var.first << "^" << var.second;
        }
        return os;
    }

    // �������� �����
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
