#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;

int val(char x) { return (int)x; }

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
    }
  }
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

  inFile.close();
  outFile.close();
  return 0;
}
