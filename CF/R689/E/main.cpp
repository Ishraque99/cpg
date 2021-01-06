#include <bits/stdc++.h>

using namespace std;

bool within_range(int64_t x, int64_t lower, int64_t upper) {
    return (x >= lower and x <= upper);
}

bool valid(int64_t level, int64_t lower_limit, int64_t upper_limit,
           int64_t days, int64_t consumption, int64_t increment, int64_t current_day)
{

    // increment is less than consumption, so we will lose water over time
    if (increment < consumption) {
        // if initial level is high we can't increment on first day,
        // but proceeding days should be in range
        if ((level + increment) > upper_limit) {
            days--;
            level -= consumption;
        }
        // int64_t total_loss = (consumption - increment)*days; // results in overflow
        // int64_t result = level - total_loss;
        int64_t daily_decrement = consumption - increment;
        int64_t days_lasting = (level - lower_limit) / daily_decrement;
        return days_lasting >= days;
    } else {
        // need to simulate problem
        set<int64_t> past_levels;
        for(int64_t i = 0; i < days; i++) {
            // detect cycle
            if (past_levels.find(level%consumption) != past_levels.end()) { break; }
            past_levels.insert(level%consumption);

            // we forward as many days as we can until we have to increment
            int64_t forward_days = (level - lower_limit) / consumption;
            i += forward_days;
            level -= consumption*forward_days;

            if (i >= days) { break; } // we made it

            // otherwise we increment if we can, and consume as normal
            if (within_range(level + increment, lower_limit, upper_limit)) {
                level += increment;
            }
            level -= consumption;
        }
        return within_range(level, lower_limit, upper_limit);
    }
    return false;
}

int main(int argc, char **argv)
{
    int64_t initial_level, lower_limit, upper_limit, days, consumption, increment;
    cin >> initial_level >> lower_limit >> upper_limit >> days >> consumption >> increment;

    bool res = valid(initial_level, lower_limit, upper_limit, days, consumption, increment, 0);
    if (res) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}