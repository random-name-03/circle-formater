#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// string muss als referenz mitgegeben werden!
std::string get_element(std::string &line, char element_separator) {
  int part_end = line.find(element_separator, 0);
  std::string element_part = line.substr(0, part_end);
  line.erase(0, part_end + 1);
  return element_part;
}

int main() {
  std::ifstream file("/home/dev/codium/circle-formater/data/edifact.data");
  if (!file.is_open()) {
    std::cerr << "Could not open file\n";
    return 1;
  }

  std::vector<std::string> lines;
  std::string line;

  while (std::getline(file, line)) {
    lines.push_back(line);
  }

  // char component_separator = lines[0][3]; //:
  char element_separator = lines[0][4]; //+
  // char decimal_point = lines[0][5];       // .
  // char release_indicator = lines[0][6];   // ?
  char segment_terminator = lines[0][8]; //'

  std::map<int, std::map<std::string, std::string>> edifact_data;

  for (size_t i = 1; i < lines.size(); ++i) {

    std::map<std::string, std::string> line_data;

    std::string line = lines[i];
    // TODO: func extension to loop through until segment_terminator
    //      while (!std::find(0, 1, segment_terminator)) {
    line_data.insert({"elements", get_element(line, element_separator)});

    edifact_data.insert({i, line_data});
    std::cout << line << "\n";
  }
}
