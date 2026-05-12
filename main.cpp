#include "manufactory.h"
#include "parser.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 0;
    }

    Manufactory manufactory;
    if (!Parser::ParseFile(argv[1], manufactory)) {
        return 0;
    }

    manufactory.RunManufactoryWork();
    return 0;
}
