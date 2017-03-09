#include "CommandLine.h"
int main() {
  CommandLine c = CommandLine(std::cin);
  char* cmd = c.getCommand();
  int size = c.getArgCount();
  char** myarr = c.getArgVector();
  cout << cmd << endl;
  cout << size << endl;

  for (int i = 0; i < size; i++) {
    cout << myarr[i] << ' ';
  }
  cout << endl;

  char* second_command = c.getArgVector(1);
  cout << second_command << endl;

  bool amp = c.noAmpersand();
  cout << amp << endl;
}