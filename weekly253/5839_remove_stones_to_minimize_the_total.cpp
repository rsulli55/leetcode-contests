/* https://leetcode.com/contest/weekly-contest-253/problems/remove-stones-to-minimize-the-total/ */
/* You are given a 0-indexed integer array piles, where piles[i] represents the number of stones in the ith pile, and an integer k. You should apply the following operation exactly k times: */

/*     Choose any piles[i] and remove floor(piles[i] / 2) stones from it. */

/* Notice that you can apply the operation on the same pile more than once. */

/* Return the minimum possible total number of stones remaining after applying the k operations. */

/* floor(x) is the greatest integer that is smaller than or equal to x (i.e., rounds x down). */

// the greedy solution of always taking from the maximum size pile works (taking the from the maximum can not be worse than taking
// from any other pile)
//
#include <functional>
#include <algorithm>
#include <numeric>
#include <map>
using namespace std;
class Solution {
public:
    int minStoneSum(vector<int>& piles, int k) {
        int total_stones = std::reduce(std::cbegin(piles), std::cend(piles));
        map<int, int, std::greater<int>> piles_map;

        for (int i = 0; i < piles.size(); ++i) {
            piles_map[piles[i]]++;
        }

        int stones_removed = 0;
        for (int i = 0; i < k; ++i) {
            // grab top element
            auto top = piles_map.begin();
            std::pair<int, int> replacement = *top;
            bool replace = replacement.second > 1;
            replacement.second--;
            int to_remove = top->first / 2;
            stones_removed += to_remove;
            auto new_pile = top->first - to_remove;
            piles_map.erase(top);
            if (replace) {piles_map.insert(replacement);}
            piles_map[new_pile]++;
        }

        return total_stones - stones_removed;
        
    }
};
