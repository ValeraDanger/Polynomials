#include "Polynomial.h"
using namespace std;

int main() {
    std::unordered_map<char, int> a1 = {
        {'x', 5},
        {'y', 1},
        {'z', 3}
    };

    std::unordered_map<char, int> a2 = {
        {'y', 1},
        {'x', 5},
        {'z', 3}
    };

    Monom m1(3.5, a1);
    Monom m2(7, a2);

    Polynomial p1;   //5*x^2*y^4+7*y^4*x^2+5*x^1*y^4+6*z^2+10
    Polynomial p2;   //-12*x^2*y^4-4*x^1*y^4+10*z^2+4

    cin >> p1;
    cin >> p2;

    //cout << m1 << '\n' << m2 << '\n' << endl;
    Polynomial sum = p1 + p2;
    Polynomial dif = p1 - p2;
    Polynomial mul = p1 * p2;
    Polynomial const_mul = p1 * 5;

    cout << sum << endl;
    cout << dif << endl;
    cout << mul << endl;
    cout << const_mul << endl;
}





//#include "List.h"
//#include <iostream>
//
//int main() {
//	List<int> a;
//
//	a.push_back(1);
//	a.push_back(2);
//	a.push_back(3);
//	a.push_back(4);
//	a.push_back(5);
//
//	auto it = a.begin();
//	++it;
//	a.erase(it);
//
//	//for (auto it = a.begin(); it != a.end(); ++it) {
//	//	std::cout << *it << std::endl;
//	//}
//
//	for (auto el : a) {
//		std::cout << el << std::endl;
//	}
//}

