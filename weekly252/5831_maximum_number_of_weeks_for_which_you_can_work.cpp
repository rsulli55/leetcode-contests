/* https://leetcode.com/contest/weekly-contest-252/problems/maximum-number-of-weeks-for-which-you-can-work/ */

/* There are n projects numbered from 0 to n - 1. You are given an integer array milestones where each milestones[i] denotes the number of milestones the ith project has. */

/* You can work on the projects following these two rules: */

/*     Every week, you will finish exactly one milestone of one project. You must work every week. */
/*     You cannot work on two milestones from the same project for two consecutive weeks. */

/* Once all the milestones of all the projects are finished, or if the only milestones that you can work on will cause you to violate the above rules, you will stop working. Note that you may not be able to finish every project's milestones due to these constraints. */

/* Return the maximum number of weeks you would be able to work on the projects without violating the rules mentioned above. */

// it seems like a greedy solution should work
// here the greedy choice is to always work on the project with the highest number of 
// remaining milestones
// if we have a current partial schedule of (w_1, ...., w_n) which is a prefix of  an
// optimal soutions (w_1, ..., w_n, w_n+1*, ..., w_m*) then for the greedy choice
// we may make a schedule such that w_n+1 =/= w_n+1*, but we can just swap these two projects
// in the end tail of the schedule and still obtain an optimal sequence
//
// in a perfect case, the amount of weeks would just be the sum of all milestones
// this case can fail if there are "gaps" between the two maximal number of milestone projects and the rest.
// (as long as there are two projects with equal number of milestones, we can "ping-pong" between them so exhaust
// all milestones)
// if we stored the sorted milestones in `sorted` then the total number of weeks would be
// then we can exhaust all milestones in the range (1:end).
// For the project with the maximal number of milestones, we can exhaust either all of them,
// or 2*sum(sorted(1:end)) +1 of them (we could interleave the maximal project in every other week).
// In other words, the total number of weeks is
// total = sum(milestones) 
// or
// total = 2 * (sum(milestones) - max) +1
// dependeing on the difference between max and sum(sorted(1:end))
// 

#include <algorithm>
#include <functional>
#include <map>
#include<queue>
class Solution {
public:
    long long numberOfWeeks(vector<int>& milestones) {
        long long max = *std::max_element(std::cbegin(milestones), std::cend(milestones));
        long long sum = std::reduce(std::cbegin(milestones), std::cend(milestones), 0ll);
        // we can fully exhaust max if sum(sorted(1:n)) + 1 >= max and sum(sorted(1:n)) = sum - max
        if (sum+1 >= 2* max) { return sum;}
        // otherwise we cannot fully exhaust max
        return 2*(sum - max) + 1;
    }

};
/* class Solution { */
/* public: */
/*     long long numberOfWeeks(vector<int>& milestones) { */
/*         // sort it */
/*         std::sort(std::begin(milestones), std::end(milestones), std::greater<int>()); */

/*         bool can_proceed = true; */
/*         long long num_weeks = 0; */
/*         // project from the last week */
/*         long last_proj = -1; */
/*         long pointer = 0; */
        

/*         while (can_proceed) { */
/*             // if pointer and pointer+1 have the same value, move pointer all the way to the right */
/*             // which still has that value */
/*             while (pointer+1 < milestones.size() && milestones[pointer+1] == milestones[pointer]) { */
/*                     pointer++; */
/*             } */
/*             // everything to the left of pointer if equal */
/*             if (pointer != last_proj && milestones[pointer] > 0) { */
/*             // then we can use pointer as this weeks project */
/*                 /1* std::cout << "Using project: " << pointer << " with milestones: " << milestones[pointer] << '\n'; *1/ */
/*                 milestones[pointer]--; */
/*                 last_proj = pointer; */
/*                 pointer = std::max(pointer -1, 0l); */
/*                 num_weeks++; */
/*             } */
/*             // check if there are non zero values to the right */
/*             else if (pointer+1 < milestones.size() && milestones[pointer+1] > 0) { */
/*                 pointer++; */
/*             // continue all the way to the right again */
/*                 while (pointer+1 < milestones.size() && milestones[pointer+1] == milestones[pointer]) { */
/*                         pointer++; */
/*                 } */
/*             // we didn't use the leftmost pointer, so we should reset pointer all the way to the left */
/*                 /1* std::cout << "Using project: " << pointer << " with milestones: " << milestones[pointer] << '\n'; *1/ */
/*                 milestones[pointer]--; */
/*                 last_proj = pointer; */
/*                 num_weeks++; */
/*                 pointer = 0; */
/*             } */
/*             // otherwise there was nothing valid to take */
/*             else { */
/*                 can_proceed = false; */
/*             } */
/*         } */

/*         return num_weeks; */

        
/*     } */
/* }; */
// this solution was too slow
/* class Solution { */
/* public: */
/*     long long numberOfWeeks(vector<int>& milestones) { */
/*         // put it in std::map to sort it */
/*         // val has the form (project, milestone) */
/*         using val = std::pair<int, int>; */
/*         // we only want to sort by milestone */
/*         auto compare = [](const val& v1, const val& v2) { */
/*             return v1.second < v2.second; */
/*         }; */
/*         std::priority_queue<val, std::vector<val>, decltype(compare)> projects_queue{compare}; */
/*         // would be better to use heapify */
/*         for (int i = 0; i < milestones.size(); ++i) { */
/*             projects_queue.push(std::make_pair(i, milestones[i])); */
/*         } */

/*         bool can_proceed = true; */
/*         long long num_weeks = 0; */
/*         // project from the last week */
/*         int last_proj = -1; */
/*         while (can_proceed && projects_queue.size() > 0) { */
/*             auto to_pick = projects_queue.top(); */
/*             projects_queue.pop(); */
/*             auto add_back = to_pick; */
/*             bool extra_add = false; */
/*             // cant use to_pick if same as last week */
/*             if (to_pick.first == last_proj) { */
/*                 if (projects_queue.size() == 0) { */
/*                     // nothing valid to pick */
/*                     can_proceed = false; */
/*                     break; */
/*                 } */
/*                 // otherwise get next valid project */
/*                 to_pick = projects_queue.top(); */
/*                 projects_queue.pop(); */
/*                 extra_add = true; */
/*             } */
/*             // we can use to_pick for this week */
/*             if (to_pick.second > 1) { */
/*                 // need to add back to_pick with one milestone removed */
/*                 auto to_add = to_pick; */
/*                 to_add.second--; */
/*                 projects_queue.push(to_add); */
                
/*             } */
/*             // otherwise don't add it back and */ 
/*             num_weeks++; */
/*             last_proj = to_pick.first; */
/*             /1* push add_back if necessary *1/ */
/*             if (extra_add) { projects_queue.push(add_back);} */
/*         } */

/*         return num_weeks; */

        
/*     } */
/* }; */
