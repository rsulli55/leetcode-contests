/* https://leetcode.com/contest/weekly-contest-253/problems/minimum-number-of-swaps-to-make-the-string-balanced/ */
/* You are given a 0-indexed string s of even length n. The string consists of exactly n / 2 opening brackets '[' and n / 2 closing brackets ']'. */

/* A string is called balanced if and only if: */

/*     It is the empty string, or */
/*     It can be written as AB, where both A and B are balanced strings, or */
/*     It can be written as [C], where C is a balanced string. */

/* You may swap the brackets at any two indices any number of times. */

/* Return the minimum number of swaps to make s balanced. */

// we know the [ and ] each appear n/2 times, so we can just count the number of ]'s that appear before a matching [
// for 1 or 2 we can fix in 1 swap, 3 or 4 we can fix in 2 swaps, 5 or 6 we can fix in 3 swaps, etc
//
//

class Solution {
public:
    int minSwaps(string& s) {
        bool negative_run = false;
        int total_count = 0;
        int count = 0;
        int run = 0;
        for (char c : s) {
            if (c == '[') {
                count++;
                negative_run = false;
                total_count += run;
                run = 0;
            }
            else {
                count--;
            }
            if (count < 0) {
                negative_run = true;
                run++;
            }
        }

        return total_count / 2;

        
    }
};
