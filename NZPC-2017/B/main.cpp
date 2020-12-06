#include <bits/stdc++.h>

using namespace std;

int score1 = 0;
int score2 = 0;
string team1;
string team2;

void print_teams_and_score()
{
    cout << team1 << " " << score1 << " " << team2 << " " << score2 << ". ";
}

int main(int argc, char **argv)
{
    getline(cin, team1); // plays blue n black
    getline(cin, team2); // plays red n yellow
    string n_st; getline(cin, n_st); int n_chars = stoi(n_st);
    string moves; getline(cin, moves);

    for (int i = 0; i < n_chars; i++)
    {
        int p = i % 4;        // which player/team
        char shot = moves.at(i); // which shot happened
        int delta = 0;
        if (shot == 'H')
        {
            delta = 1;
        }
        else if (shot == 'D')
        {
            delta = 2;
        }
        else if (shot == 'O')
        {
            p = (p + 1) % 4; // switch team
            delta = 1;
        }

        if (p == 0 || p == 2)
        { // team1
            score1 += delta;
        }
        else
        {
            score2 += delta;
        } // team 2// team1
        
        // check game state
        if (score1 >= 7)
        {   score1 = 7;
            print_teams_and_score();
            cout << team1 << " has won." << endl;
            exit(0);
        } else if (score2 >= 7) { score2 = 7;
            print_teams_and_score();
            cout << team2 << " has won." << endl;
            exit(0);
        }
    }

    // print game state
    print_teams_and_score();
    if (score1 > score2) {
        cout << team1 << " is winning." << endl;
    } else if (score2 > score1) {
        cout << team2 << " is winning." << endl;
    } else {
        cout << "All square." << endl;
    }

    return 0;
}