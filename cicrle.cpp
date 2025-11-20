#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

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

  std::map<std::string, char> descriptors;
  descriptors.insert({"component_separator", lines[0][3]});
  descriptors.insert({"element_separator", lines[0][4]});
  descriptors.insert({"decimal_point", lines[0][5]});
  descriptors.insert({"release_indicator", lines[0][6]});
  descriptors.insert({"space", lines[0][7]});
  descriptors.insert({"segment_terminator", lines[0][8]});

  std::map<std::string, std::vector<std::string>> edifact_data;

  for (size_t i = 1; i < lines.size(); ++i) {
    std::string line = lines[i];
    std::vector<std::string> line_data;

    while (line.length() > 1) {
      int part_end = line.find(descriptors["element_separator"], 0);
      if (part_end < 0) {
        part_end = line.length() - 1;
      }
      std::string element_part = line.substr(0, part_end);
      line.erase(0, part_end + 1);
      line_data.push_back(element_part);
    }

    edifact_data.insert({line_data[0], line_data});
  }

  for (const auto &[key, vec] : edifact_data) { 
    std::cout << key << ": ";
    for (const auto &value : vec) {
      std::cout << value << " ";
    }
    std::cout << "\n";
  }
}
