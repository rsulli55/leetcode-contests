/* https://leetcode.com/contest/weekly-contest-252/problems/three-divisors/ */
/* 5830. Three Divisors */

/* Given an integer n, return true if n has exactly three positive divisors. Otherwise, return false. */

/* An integer m is a divisor of n if there exists an integer k such that n = k * m. */

#include <cmath>

bool is_prime(int n) {
    if (n == 2 || n == 3 || n == 5 || n == 7 || n == 11 || n == 13 || n == 17 || n == 19) {
        return true;
    }

    for (int i =  2; i < std::sqrt(n) + 1; ++i ) {
        if (n % i == 0) 
            return false;
    }
    return true;
}
 

class Solution {
public:
    bool isThree(int n) {
        // d1 = 1 is always a postitive divisor and d3 = n is as well
        int d2;
        // really this is equivalent to asking if n is a the square of a prime

        for (int i = 2; i < sqrt(n) + 1; ++i) {
            if (is_prime(i) && i * i == n) {
                return true;
            }
        }
        
    }
};
