#pragma once

#include "manufactory.h"

#include <string>

class Parser {
public:
    static bool ParseFile(const std::string& file_path, Manufactory& manufactory);
};
