/* https://leetcode.com/contest/weekly-contest-252/problems/minimum-garden-perimeter-to-collect-enough-apples/ */
/* In a garden represented as an infinite 2D grid, there is an apple tree planted at every integer coordinate. The apple tree planted at an integer coordinate (i, j) has |i| + |j| apples growing on it. */

/* You will buy an axis-aligned square plot of land that is centered at (0, 0). */

/* Given an integer neededApples, return the minimum perimeter of a plot such that at least neededApples apples are inside or on the perimeter of that plot. */

/* The value of |x| is defined as: */
// you can see what the pattern is by trying to draw out some grids for k = 3 and k = 4
// there is a lot of symmetry, if we choose the top right to be (k, k), then the total perimeter is 8k
// and the total number of follows this patter
// number of apples | coordinates with that many apples
// 2k               | 4
// 2k - 1           | 8 = 4*2
// 2k - 2           | 12 = 4*3
// 2k - 3           | 16 = 4*4
// ...
// k + 1            | 4*k
// ----------------------
// k                | 4*k
// k - 1            | 4*(k-1)
// k - 2            | 4*(k-2)
// ...
// 1                | 4
// notice each row of the lower half is simply 4*j*j so the lower half is
// Sum(4*j*j) for j = 1 to k
// so we can just search for the smallest such k and then return its perimeter
class Solution {
public:
    long long total_apples(long long k) {
        long long total = 0;
        // calculate upper half and lower half simultaneously
        for (long long i = 1; i <= k; ++i) {
            // upper half
            total += (2*k - (i -1)) * 4*i;
            // lower half
            total +=  4*i*i;
        }
        return total;

    }
    long long apples_along_perimeter(long long k) {
        long long total = 0;
        // 2k and k appears 4 times on the perimeter
        total += 4 * (2*k + k);
        // values strictly between k and 2k 
        // appears twice on each side of perimeter which means 8 times in total
        /* for (long long i = k+1; i <= 2*k-1; ++i) { */
        /*     total += 8*i; */
        /* } */
        // inline the for loop
        total += 8 * (2*k + k)*(2*k - 1 - k)/2;

        return total;
    }

    long long minimumPerimeter(long long neededApples) {
        long long k = 0;
        while (neededApples > 0) {
            ++k;
            // try inlining apples_along_perimeter
            neededApples -= 4 * (2 *k + k);
            neededApples -= 8 * (2*k+k)*(2*k-1-k)/2;
        }

        return 8*k;
    }
};
