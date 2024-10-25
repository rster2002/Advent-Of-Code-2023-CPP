#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <optional>
#include <string_view>

using namespace std;

static const map<string_view, int> numbers {
    { "one", 1 },
    { "two", 2 },
    { "three", 3 },
    { "four", 4 },
    { "five", 5 },
    { "six", 6 },
    { "seven", 7 },
    { "eight", 8 },
    { "nine", 9 },
};

int main() {
    ifstream file("day-1-input.txt");
    string file_contents;

    int total = 0;

    while (getline (file, file_contents)) {
        optional<int> first_value = nullopt;
        optional<int> last_value = nullopt;

        string text_number;

        for (const char& c : file_contents) {
            int value = 0;

            // Either directly convert the char into a number or add it to the current text number.
            if (isdigit(c)) {
                text_number = "";
                value = c - '0';
            } else {
                text_number += c;
                optional<int> found_value = nullopt;

                // Check if the current text number ends with one of the options
                for (const auto& pair : numbers) {
                    if (text_number.ends_with(pair.first)) {
                        found_value = pair.second;
                    }
                }

                // If no match just continue
                if (!found_value.has_value()) {
                    continue;
                }

                value = found_value.value();
            }

            // Set first and last values
            if (!first_value.has_value()) {
                first_value = value;
            }

            last_value = value;
        }

        if (!first_value.has_value() || !last_value.has_value()) {
            cout << "No values" << endl;
            continue;
        }

        cout << first_value.value() << last_value.value() << endl;
        total += first_value.value() * 10 + last_value.value();
    }

    cout << "Total: " << total << endl;

    return 0;
}