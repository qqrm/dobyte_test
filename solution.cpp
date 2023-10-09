#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <execution>

using namespace std;

const int MAX_DIGIT = 6;
const int MAX_SUM = 6 * 12;
const int BASE = 13;

vector<int> sum_counts(MAX_SUM + 1, 0);

void computePossibleSums() {
    vector<int> current_sum_counts(MAX_SUM + 1, 0);
    vector<int> next_sum_counts(MAX_SUM + 1, 0);

    // Base case
    for (auto val : ranges::iota_view(0, BASE)) {
        current_sum_counts[val] = 1;
    }

    // For each subsequent digit
    for ([[maybe_unused]] auto digit : ranges::iota_view(1, MAX_DIGIT + 1)) {
        ranges::fill(next_sum_counts, 0);

        std::for_each(std::execution::par, ranges::iota_view(0, MAX_SUM + 1).begin(), 
                      ranges::iota_view(0, MAX_SUM + 1).end(), [&](int sum) {
            for (auto val : ranges::iota_view(0, BASE)) {
                if (sum + val <= MAX_SUM) {
                    next_sum_counts[sum + val] += current_sum_counts[sum];
                }
            }
        });

        swap(current_sum_counts, next_sum_counts);
    }

    sum_counts = move(current_sum_counts);
}

int main() {
    computePossibleSums();

    long long count = 0;
    for (auto sum : ranges::iota_view(0, MAX_SUM + 1)) {
        count += (long long) sum_counts[sum] * sum_counts[sum] * BASE;  // Multiply by BASE to account for the middle digit
    }

    cout << count << endl;

    return 0;
}
