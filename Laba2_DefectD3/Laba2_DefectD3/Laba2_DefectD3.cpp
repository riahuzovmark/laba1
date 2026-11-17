#include <cassert>
#include <iostream>

bool isEligible(int score, int threshold) {
    return score >= threshold;
}

int main() {
    int score = 60;
    int threshold = 60;

    bool result = isEligible(score, threshold);
    std::cout << "score=" << score << ", threshold=" << threshold
        << " -> result=" << result << " (expected 1)\n";

    assert(isEligible(61, 60) == true);
    assert(isEligible(59, 60) == false);
    assert(isEligible(60, 60) == true);

    return 0;
}