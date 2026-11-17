#include <cassert>
#include <iostream>

namespace {
    constexpr int MODULES_MIN = 0;
    constexpr int MODULES_MAX = 5;
    constexpr int TEST_MIN = 0;
    constexpr int TEST_MAX = 50;
    constexpr int RECORD_LIMIT = 30;
    constexpr int MIN_MODULES = 2;
    constexpr int SEARCH_THRESHOLD = 60;

    int calculateTotal(int modules, int test) {
        return 10 * modules + test;
    }

    const char* categoryFor(int modules, int m) {
        if (modules < MIN_MODULES) {
            return "недостатньо модулів";
        }
        if (m < SEARCH_THRESHOLD) {
            return "потрібне доопрацювання";
        }
        return "умовний успішний результат";
    }

    bool isSearchMatch(int modules, int m) {
        return modules >= MIN_MODULES && m >= SEARCH_THRESHOLD;
    }

    bool readValidRecord(int recordNumber, int& modules, int& test) {
        while (true) {
            std::cout << "Запис " << recordNumber
                << " (модулі 0..5, тест 0..50): ";

            if (!(std::cin >> modules >> test)) {
                if (std::cin.eof()) {
                    std::cerr << "Неповне введення: досягнуто кінець вводу.\n";
                }
                else {
                    std::cerr << "Помилка формату: введіть два цілі числа. "
                        "Програму завершено без підсумку.\n";
                }
                return false;
            }

            if (modules < MODULES_MIN || modules > MODULES_MAX ||
                test < TEST_MIN || test > TEST_MAX) {
                std::cerr << "Помилка діапазону. Повторіть увесь запис "
                    "(модулі 0..5, тест 0..50).\n";
                continue;
            }
            return true;
        }
    }
}  // namespace

int main() {
    system("chcp 65001 > nul");
    assert(calculateTotal(4, 35) == 75);
    assert(calculateTotal(0, 0) == 0);
    assert(calculateTotal(5, 50) == 100);
    assert(isSearchMatch(2, 60));
    assert(!isSearchMatch(1, 60));
    assert(!isSearchMatch(2, 59));

    int recordCount = 0;
    while (true) {
        std::cout << "Кількість записів N (1..30): ";
        if (!(std::cin >> recordCount)) {
            if (std::cin.eof()) {
                std::cerr << "Неповне введення N. Підсумок не формується.\n";
            }
            else {
                std::cerr << "Помилка формату N. Програму завершено.\n";
            }
            return 1;
        }
        if (recordCount >= 1 && recordCount <= RECORD_LIMIT) {
            break;
        }
        std::cerr << "N має бути в межах 1..30. Введіть N ще раз.\n";
    }

    int sum = 0;
    int minimum = 0;
    int maximum = 0;
    int minimumRecord = 0;
    int maximumRecord = 0;
    int matchCount = 0;
    int firstMatch = 0;

    for (int acceptedRecord = 1; acceptedRecord <= recordCount; ++acceptedRecord) {
        int modules = 0;
        int test = 0;
        if (!readValidRecord(acceptedRecord, modules, test)) {
            return 1;
        }

        const int m = calculateTotal(modules, test);
        const bool matches = isSearchMatch(modules, m);

        if (acceptedRecord == 1) {
            sum = m;
            minimum = m;
            maximum = m;
            minimumRecord = acceptedRecord;
            maximumRecord = acceptedRecord;
        }
        else {
            sum += m;
            if (m < minimum) {
                minimum = m;
                minimumRecord = acceptedRecord;
            }
            if (m > maximum) {
                maximum = m;
                maximumRecord = acceptedRecord;
            }
        }

        if (matches) {
            ++matchCount;
            if (firstMatch == 0) {
                firstMatch = acceptedRecord;
            }
        }

        std::cout << "  m=" << m << " балів; категорія: "
            << categoryFor(modules, m) << "; пошук: "
            << (matches ? "так" : "ні") << '\n';
    }

    const double average = static_cast<double>(sum) / recordCount;
    std::cout << "\nПІДСУМОК ПІСЛЯ " << recordCount << " ПРИЙНЯТИХ ЗАПИСІВ\n"
        << "Сума: " << sum << " балів\n"
        << "Середнє: " << average << " балів\n"
        << "Мінімум: " << minimum << " балів (запис " << minimumRecord << ")\n"
        << "Максимум: " << maximum << " балів (запис " << maximumRecord << ")\n"
        << "Кількість збігів: " << matchCount << '\n'
        << "Перший збіг: ";
    if (firstMatch == 0) {
        std::cout << "немає\n";
    }
    else {
        std::cout << firstMatch << '\n';
    }
    return 0;
}