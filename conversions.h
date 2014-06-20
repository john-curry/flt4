#ifndef CONVERSION_H
#define CONVERSION_H

#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <json/reader.h>
#include <json/writer.h>
namespace flt4 {
  std::string team_to_json(std::vector<std::string> team);
  std::vector<std::string> json_to_team(std::string json);
  std::string actions_to_json(std::map<std::string, int> act);
  std::map<std::string, int> json_to_actions(std::string json);
  bool json_to_status(std::string json); // status is either game going or game over
  std::string status_to_json(bool);
}
#endif
