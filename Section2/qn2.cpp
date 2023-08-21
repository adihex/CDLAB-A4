#include <bits/stdc++.h>
#include <fstream>
using namespace std;

vector<string> adj[256];

class Trie {
public:
  typedef struct TrieNode {
    TrieNode *child[256];
    bool isEnd;
  } TrieNode;

  TrieNode *head;

  Trie() { head = new TrieNode(); }

  string printHelper(TrieNode *header, vector<string> &finalResult) {
    vector<string> res;
    for (int i = 0; i < 256; i++) {
      if (header->child[i]) {
        string temp = char(i) + printHelper(header->child[i], finalResult);
        res.push_back(temp);
      }
    }
    if (res.size() == 1)
      return res[0];
    if (res.size() > 1) {
      string symbol = getSymbol();
      string output;
      output += symbol + "->";
      for (int i = 0; i < res.size(); i++) {
        output += res[i];
        if (i != res.size() = 1)
          output += "|";
      }
    }
  }
};

void parseAndInsert(string &str) {
  string removedSpacesFromInput;
  for (auto &ch : str)
    if (ch != ' ')
      removedSpacesFromInput += ch;
  str = removedSpacesFromInput;
  if (!(str[0] >= 'A' && str[0] <= 'Z')) {
    cout << "Error: Non terminals must be uppercase english letters\n";
    exit(-1);
  }
  int index = str[0];
  if (str[str.length() - 1] != '|')
    str += '|';
  int i = 3;
  if (i >= str.length()) {
    cout << "ERROR: Illegal format";
    return;
  }
  string curr;
  while (i < str.length()) {
    if (str[i] == '|') {
      adj[index].push_back(curr);
      curr = "";
    } else
      curr += str[i];
    i++;
  }
  return;
}

int main(void) {
  ifstream cin("input.txt");
  string inputLine;
  while (true) {
    getline(cin, inputLine);
    if (inputLine.length() == 0)
      break;
    parseAndInsert(inputLine);
  }

  cout << "Left factored grammar:" << endl;
  return 0;
}
