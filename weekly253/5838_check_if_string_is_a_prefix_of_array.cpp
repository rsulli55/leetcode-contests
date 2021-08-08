/* https://leetcode.com/contest/weekly-contest-253/problems/check-if-string-is-a-prefix-of-array/ */
/* Given a string s and an array of strings words, determine whether s is a prefix string of words. */

/* A string s is a prefix string of words if s can be made by concatenating the first k strings in words for some positive k no larger than words.length. */

/* Return true if s is a prefix string of words, or false otherwise. */
#include <string>
using namespace std;
class Solution {
public:
    bool isPrefixString(string s, vector<string>& words) {
        string joined;
        const auto expected_length = s.size();
        int joined_length = 0;
        for (const auto& str : words) {
            joined_length += str.size();
            joined += str;
            if (joined_length > expected_length) { return false;}
            else if (joined_length == expected_length) { break; }
        }

        if (joined.compare(s) == 0) {
            return true;
        }

        return false;

    }
};
