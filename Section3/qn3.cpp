#include <bits/stdc++.h>

using namespace std;

// - For question 3,  implement a basic top-down parser for the given grammar
// using the recursive-descent parsing approach discussed in the class
/*
S -> n B
B -> n B A B | ε
A -> + | ×

Let us model the same grammar by the following transformation: (used for
simplifying the recursion) S -> 0, B -> 1, A -> 2

The updated grammar would be:
0 -> n1
1 -> n121 | epsilon
2 -> + | x
*/

// Global Data Structure: Representing the current grammar:
vector<vector<string>> transition{{"n1"}, {"n121", ""}, {"+", "x"}};
// For reverse translation:
unordered_map<int, string> um;

// Recursive Decent Checker for the strings:
bool isNonTerminal(char x) { return (x >= '0' && x <= '9'); }

string decode(string x) {
  string result;
  for (auto ch : x) {
    if (isNonTerminal(ch))
      result += um[ch - '0'];
    else
      result += ch;
  }
  return result;
}

bool parser(int i, string &s, string &target, int j, vector<string> &sequence,
            int level) {
  if (i == s.length() && j == target.length())
    return true;
  if (i == s.length())
    return false;
  if (!isNonTerminal(s[i])) {
    if (s[i] == target[j])
      return parser(i + 1, s, target, j + 1, sequence, level + 1);
    return false;
  }
  int index = s[i] - '0';
  for (auto x : transition[index]) {
    string temp = s.substr(0, i) + x + s.substr(i + 1, s.length() - i - 1);
    if (parser(i, temp, target, j, sequence, level + 1)) {
      string temp =
          um[index] + "->" + (x.length() == 0 ? "epsilon" : decode(x));
      sequence.push_back(temp);
      return true;
    }
  }
  return false;
}

int main() {
  // These two lines redirects inputs and outputs from/to file:
  ifstream cin("input.txt");
  ofstream cout("output.txt");

  // This is for reverse translation:
  um[0] = "S";
  um[1] = "B";
  um[2] = "A";

  // Getting the input:
  string target, s = "0";
  cin >> target;

  // Storing the seqence of steps:
  vector<string> sequence;
  bool isAccepted = parser(0, s, target, 0, sequence, 0);

  if (isAccepted)
    cout << "Accepted: ";
  else
    cout << "Rejected: ";
  cout << target << endl;

  if (isAccepted) {
    cout << "The leftmost derivation is shown below:" << endl;
    reverse(sequence.begin(), sequence.end());
    for (auto &x : sequence)
      cout << x << endl;
  }

  return 0;
}
