#include <iostream>
#include <windows.h>


int main() {
	int modules{0};
	int test{0};

	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	std::cout << "введіть модулі (0-5) та тест (0-50): ";

	if (!(std::cin >> modules >> test)) {
		std::cout << "Неправильне введення" << std::endl;
		return 1;
	};
	if (modules < 0 || modules > 5 || test < 0 || test > 50) {
		std::cerr << "Помилка: Значення виходять за допустимі межі.\n";
		return 1;
	};
		
		const int modulePoints = modules * 10;
		const int total = modules * 10 + test;

		std::cout << "Бали за модулі = " << modulePoints << std::endl;
		std::cout << "Загальна сума = " << total << std::endl;
	

	if (modules < 2) {std::cout << "недостатньо завершених модулів" << std::endl;}
	else if (total < 60) { std::cout << "потрібне доопрацювання" << std::endl; }
	else { std::cout << "умовний успішний результат" << std::endl; 
	}
	

	return 0;
}