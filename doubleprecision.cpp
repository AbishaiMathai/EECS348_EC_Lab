#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <iomanip>
using namespace std;

double extractNumeric(const string &str) {
    string whole = "";
    string decimal = "";
    bool isDecimalPart = false;

    // Validate and separate whole and decimal parts
    for (size_t i = 0; i < str.size(); i++) {
        if (i == 0 && (str[i] == '-' || str[i] == '+')) {
            // Append sign to the whole part
            whole += str[i];
        } else if (isdigit(str[i])) {
            // Append to whole or decimal based on the flag
            if (isDecimalPart) {
                decimal += str[i];
            } else {
                whole += str[i];
            }
        } else if (str[i] == '.') {
            // Switch to decimal part
            if (!isDecimalPart) {
                isDecimalPart = true;
            } else {
                // Multiple decimal points are invalid
                return -999999.99;
            }
        } else {
            // Invalid character encountered
            return -999999.99;
        }
    }

    // Convert whole part to numeric value iteratively
    double number = 0.0;
    bool isNegative = false;
    size_t startIndex = 0;

    if (!whole.empty() && (whole[0] == '-' || whole[0] == '+')) {
        isNegative = (whole[0] == '-');
        startIndex = 1; // Skip the sign for number calculation
    }

    for (size_t i = startIndex; i < whole.size(); i++) {
        int digit = whole[i] - '0';
        number = number * 10 + digit;
    }

    if (isNegative) {
        number = -number;
    }

    // Convert decimal part using a divisor
    double decimalValue = 0.0;
    double divisor = 10.0;

    for (char c : decimal) {
        int digit = c - '0';
        decimalValue += digit / divisor; // Divide each digit by the current divisor
        divisor *= 10.0; // Increase divisor for the next place
    }

    // Combine the whole and decimal parts
    number += decimalValue;

    return number;
}

int main() {
    string input;
    while (true) {
        cout << "Enter a string (or \"END\" to quit): ";
        cin >> input;

        if (input == "END") {
            break;
        }

        double number = extractNumeric(input);

        if (number != -999999.99) {
            cout << "The input is: " << fixed << setprecision(4) << number << endl;
        } else {
            cout << "The input is invalid." << endl;
        }
    }
    return 0;
}
