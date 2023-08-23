#include <bits/stdc++.h>

using namespace std;

/* Global Data Structures: */
vector<string> adj[256];
/* (Helps to generate new symbol as required)
0 - 25 => A' -> Z'
26 - 51 -> A'' -> Z''
*/
int currSymbol = 0;

string getSymbol() {
  int base = 'A';
  int pos = currSymbol % 26;
  int dashes = currSymbol / 26 + 1;
  currSymbol++;
  string resultant;
  resultant += char(base + pos);
  while (dashes--)
    resultant += "'";
  return resultant;
}

/** Using Trie Data Structure to do the left refactoring:
 * -----------------------------------------------------------------*/
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
        if (i != res.size() - 1)
          output += "|";
      }
      finalResult.push_back(output);
      return symbol;
    }
    return "";
  }

  /** Inserts a word into the trie. */
  void insert(string word) {
    TrieNode *temp = head;
    for (auto x : word) {
      int pos = x;
      if (!temp->child[pos]) {
        TrieNode *created = new TrieNode();
        temp->child[pos] = created;
      }
      temp = temp->child[pos];
    }
    temp->isEnd = true;
  }

  void printTheResultantGrammar(int i) {
    vector<string> finalResult;
    string temp;
    temp += char(i);
    temp += "->";
    temp += printHelper(head, finalResult);
    finalResult.push_back(temp);
    reverse(finalResult.begin(), finalResult.end());
    for (auto &x : finalResult)
      cout << x << endl;
  }
};

/**--------Helper
 * Functions-------------------------------------------------------------------------------------------------*/

void printLeftFactoredGrammar(vector<string> s, int i) {
  Trie *obj = new Trie();
  for (auto &word : s)
    obj->insert(word);
  obj->printTheResultantGrammar(i);
}

void parseAndInsert(string &str) {
  string removedSpacesFromInput;
  for (auto &ch : str)
    if (ch != ' ')
      removedSpacesFromInput += ch;
  str = removedSpacesFromInput;
  if (!(str[0] >= 'A' && str[0] <= 'Z')) {
    cout << "ERROR: Non terminals must be uppercase english letters";
    exit(-1);
  }
  int index = str[0];
  int arrowPos = str.find("->");
  if (arrowPos == string::npos) {
    cout << "ERROR: Arrow (->) missing in grammar rule";
    exit(-1);
  }
  string production = str.substr(arrowPos + 2);
  stringstream ss(production);
  string rule;
  while (getline(ss, rule, '|')) {
    adj[index].push_back(rule);
  }
}

int main() {

  // These two lines redirects inputs and outputs from/to file:
  ifstream cin("input.txt");
  // ofstream cout("output.txt")

  // Get the input grammar and store it in the global data structure;
  string inputLine;
  while (true) {
    getline(cin, inputLine);
    if (inputLine.length() == 0)
      break;
    parseAndInsert(inputLine);
  }

  cout << "Left Factored Grammar:" << endl;
  for (int i = 0; i < 256; i++) {
    if (adj[i].size() == 0)
      continue;
    printLeftFactoredGrammar(adj[i], i);
    cout << endl;
  }
  return 0;
}
