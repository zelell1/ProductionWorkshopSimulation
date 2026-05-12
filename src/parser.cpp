#include "parser.h"
#include "product.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static constexpr int kMinM = 1;
static constexpr int kMaxM = 100;
static constexpr int kMinN = 1;
static constexpr int kMaxN = 100;
static constexpr int kMaxT = 10000;
static constexpr int kMaxProducts = 100000;

static bool IsBlankLine(const std::string& line) {
    for (char ch : line) {
        if (!std::isspace(static_cast<unsigned char>(ch))) {
            return false;
        }
    }
    return true;
}

static bool ParseInteger(const std::string& token, long long& value) {
    std::size_t parsed_size = 0;

    try {
        value = std::stoll(token, &parsed_size);
    } catch (...) {
        return false;
    }

    return parsed_size == token.size();
}

static bool ParseLine(const std::string& line, std::vector<long long>& values) {
    values.clear();

    std::istringstream input(line);
    std::string token;

    while (input >> token) {
        long long value = 0;
        if (!ParseInteger(token, value)) {
            return false;
        }
        values.push_back(value);
    }

    return true;
}

static bool ReadLine(std::ifstream& input, std::string& line) {
    if (std::getline(input, line)) {
        return true;
    }

    line.clear();
    return false;
}

static void PrintError(const std::string& line) {
    std::cout << line << "\n";
}

static bool CheckRange(long long value, long long left, long long right) {
    return left <= value && value <= right;
}

bool Parser::ParseFile(const std::string& file_path, Manufactory& manufactory) {
    std::ifstream input(file_path);
    if (!input.is_open()) {
        return false;
    }

    std::string line;
    std::vector<long long> values;

    if (!ReadLine(input, line) || !ParseLine(line, values) || values.size() != 2 ||
        !CheckRange(values[0], kMinM, kMaxM) || !CheckRange(values[1], kMinN, kMaxN)) {
        PrintError(line);
        return false;
    }

    int m = static_cast<int>(values[0]);
    int n = static_cast<int>(values[1]);

    manufactory.SetTimeMatrixSize(m, n);

    for (int i = 0; i < m - 1; ++i) {
        if (!ReadLine(input, line) || !ParseLine(line, values) ||
            static_cast<int>(values.size()) != n) {
            PrintError(line);
            return false;
        }

        for (int j = 0; j < n; ++j) {
            if (!CheckRange(values[j], 0, kMaxT)) {
                PrintError(line);
                return false;
            }
            manufactory.SetTimeInMatrix(i, j, values[j]);
        }
    }

    for (int j = 0; j < n; ++j) {
        manufactory.AddMachine();
    }

    int products_count = 0;

    for (int machine_id = 0; machine_id < n; ++machine_id) {
        if (!ReadLine(input, line) || !ParseLine(line, values) || values.empty()) {
            PrintError(line);
            return false;
        }

        long long queue_size = values[0];
        if (queue_size < 0 || queue_size > kMaxProducts - products_count ||
            values.size() != static_cast<std::size_t>(queue_size) + 1) {
            PrintError(line);
            return false;
        }

        for (int position = 0; position < queue_size; ++position) {
            long long product_type = values[position + 1];
            if (!CheckRange(product_type, 0, m - 2)) {
                PrintError(line);
                return false;
            }

            manufactory.AddProduct(
                machine_id,
                Product(products_count, static_cast<int>(product_type), m - 1)
            );
            ++products_count;
        }
    }

    while (std::getline(input, line)) {
        if (!IsBlankLine(line)) {
            PrintError(line);
            return false;
        }
    }

    return true;
}
