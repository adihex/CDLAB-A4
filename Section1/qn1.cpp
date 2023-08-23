#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

typedef vector<list<int>> grammar;

int curr_size = 256;
vector<grammar> globalData(curr_size);
unordered_map<int, string> symbol;

int val(char x) { return (int)x; }

int generateNewSymbol(string x) {
  string newSymbol;
  newSymbol += x;
  newSymbol += "'";
  symbol[curr_size] = newSymbol;
  grammar temp;
  globalData.push_back(temp);
  return curr_size++;
}

bool isNonTerminal(int x) {
  int valA = 'A';
  int valZ = 'Z';
  return (x >= valA && x <= valZ);
}

string getASCIIRep(int val) {
  string temp;
  if (val > 0 && val < 256) {
    char x = char(val);
    temp += x;
  } else
    temp += symbol[val];
  return temp;
}

void parse(string &str) {
  string processedInput;
  for (auto &ch : str) {
    if (ch != ' ')
      processedInput += ch;
  }
  str = processedInput;
  if (!(str[0] >= 'A' && str[0] <= 'Z')) {
    cout << "ERROR: Non terminals must be uppercase english letters!";
    exit(-1);
  }
  int index = val(str[0]);
  if (str[str.length() - 1] != '|')
    str += '|';
  int i = 3;
  if (i >= str.length()) {
    cout << "ERROR: Illegal format";
    return;
  }
  list<int> temp;
  while (i < str.length()) {
    if (str[i] == '|') {
      globalData[index].push_back(temp);
      temp.clear();
    } else {
      temp.push_back(val(str[i]));
    }
    i++;
  }
  return;
}

void printGrammar() {
  for (int i = 0; i < globalData.size(); i++) {
    if (globalData[i].size() == 0)
      continue;
    string res = getASCIIRep(i);
    cout << res << "->";
    for (int j = 0; j < globalData[i].size(); j++) {
      auto &gram = globalData[i][j];
      for (auto &listElem : gram)
        cout << getASCIIRep(listElem);
      if (j != globalData[i].size() - 1)
        cout << "|";
    }
    cout << endl;
  }
}

grammar concatenateOp(list<int> &elem, grammar &currGrammar) {
  grammar result;
  for (auto &lst : currGrammar) {
    list<int> temp;
    for (auto element : lst)
      temp.push_back(element);
    for (auto element : elem)
      temp.push_back(element);
    result.push_back(temp);
  }
  return result;
}

int main(int argc, char *argv[]) {
  ifstream inFile;
  ofstream outFile;
  inFile.open(argv[1]);
  outFile.open(argv[2]);
  string line;
  vector<string> input;
  while (getline(inFile, line)) {
    input.push_back(line);
  }

  for (auto &str : input) {
    parse(str);
  }

  for (int i = 0; i < 256; i++) {
    if (!isNonTerminal(i) || globalData[i].size() == 0)
      continue;
    grammar currGrammar;
    for (auto &elem : globalData[i]) {
      int startSymbol = elem.front();
      if (!isNonTerminal(startSymbol) || startSymbol >= i) {
        currGrammar.push_back(elem);
        continue;
      }
      elem.pop_front();
      grammar tmp = concatenateOp(elem, globalData[startSymbol]);
      for (auto &x : tmp) {
        currGrammar.push_back(x);
      }
    }
    globalData[i] = currGrammar;
    bool isLeftRecursive = false;
    for (auto &elem : globalData[i]) {
      if (isNonTerminal(i) && elem.front() == i) {
        isLeftRecursive = true;
        break;
      }
    }
    if (!isLeftRecursive)
      continue;
    int symbolIndex = generateNewSymbol(getASCIIRep(i));
    grammar newResultantGrammar;
    for (auto elem : globalData[i]) {
      if (isNonTerminal(i) && elem.front() == i) {
        elem.pop_front();
        elem.push_back(symbolIndex);
        globalData[symbolIndex].push_back(elem);
        elem.clear();
        elem.push_back(-1);
        globalData[symbolIndex].push_back(elem);
        elem.clear();
      } else {
        elem.push_back(symbolIndex);
        newResultantGrammar.push_back(elem);
      }
    }
    globalData[i] = newResultantGrammar;
  }
  printGrammar();

  inFile.close();
  outFile.close();
  return 0;
}
