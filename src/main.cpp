#include <iostream>
#include <vector>

#include "cmd/all.h"

int main() {
    genesis(1, 10'000'000'000);
    return 0;
}

/*
    REMAINING REFACTORS:
        - CRYPTO: fix sha256 functions, security risk
        - CRYPTO: streamline functions
        - UTIL: streamline conversion functions, fn overloads
        - MAJOR GLOBAL: error codes and error handling
*/