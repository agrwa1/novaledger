#include <iostream>
#include <vector>

#include "cmd/all.h"

int main() {
    genesis();
    return 0;
}

/*
    REMAINING REFACTORS:
        - CRYPTO: fix sha256 functions, security risk
        - CRYPTO: streamline functions
        - UTIL: streamline conversion functions, fn overloads
*/