# E Water Level

<https://codeforces.com/contest/1461/problem/E>

In recent years John has very successfully settled at his new job at the office. But John doesn't like to idly sit around while his code is compiling, so he immediately found himself an interesting distraction. The point of his distraction was to maintain a water level in the water cooler used by other zebras.

Originally the cooler contained exactly k liters of water. John decided that the amount of water must always be at least l liters of water but no more than r liters. John will stay at the office for exactly t days. He knows that each day exactly x liters of water will be used by his colleagues. At the beginning of each day he can add exactly y liters of water to the cooler, but at any point in time the amount of water in the cooler must be in the range [l,r].

Now John wants to find out whether he will be able to maintain the water level at the necessary level for t days. Help him answer this question!

## Input

The first line of the input contains six integers k, l, r, t, x and y (1 ≤ l ≤ k ≤ r ≤ 10^18; 1 ≤ t ≤ 10^18; 1 ≤ x ≤ 10^6; 1 ≤ y ≤ 10^18 ) — initial water level, the required range, the number of days, daily water usage and the exact amount of water that can be added, respectively.

## Output

Print "Yes" if John can maintain the water level for t days and "No" otherwise.