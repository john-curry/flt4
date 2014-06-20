#include "conversions.h"
std::string flt4::team_to_json(std::vector<std::string> team) {
  using namespace Json;
  using namespace std;
  Value root;  
  FastWriter writer;
  for_each(team.begin(), team.end(), [&] (string s) {
    root["team"].append(s);
  });
  return writer.write(root);
}

std::vector<std::string> flt4::json_to_team(std::string json) {
  using namespace Json;
  using namespace std;

  Value root;
  Reader reader;
  vector<string> ret;
  if(!reader.parse(json, root)) {
    throw runtime_error("json_to_team could not parse json"
    ":" + json);
  }

  if (!root["team"].isArray()) {
    throw runtime_error("json_to_team team is not an array");
  }

  auto team = root["team"];

  for_each(team.begin(), team.end(), [&ret] (Value v) {
    ret.push_back(v.asString());
  });
  return ret;
}

std::string flt4::actions_to_json(std::map<std::string, int> act) {
  using namespace Json;
  using namespace std;

  Value root;
  FastWriter writer;

  for_each(act.begin(), act.end(), [&root] (pair<std::string, int>  p) {
    Value actions_node;
    actions_node["name"] = p.first;
    actions_node["damage"] = p.second;
    root["actions"].append(actions_node);
  });
  return writer.write(root);
}


std::map<std::string, int> flt4::json_to_actions(std::string json) {
  using namespace std;
  using namespace Json;
  
  Value root;
  Reader reader; 
  map<string, int> ret; 
  if(!reader.parse(json, root)) {
    throw runtime_error("json_to_actions ould not parse json"
    ":" + json);
  }
  auto actions = root["actions"]; 
  for_each(actions.begin(), actions.end(), [&ret] (Value v) {
   ret.insert(pair<string, int>(v["name"].asString(), v["damage"].asInt()));
  });
  return ret;
}
 
bool flt4::json_to_status(std::string json) {
  Json::Value root;
  Json::Reader reader; 
  if(!reader.parse(json, root)) {
    throw std::runtime_error("json_to_status ould not parse json"
    ":" + json);
  }

  return root["status"].asBool();
}

std::string flt4::status_to_json(bool status) {
  Json::Value root;
  Json::FastWriter writer;
  root["status"] = status;
  return writer.write(root);
}


 
 
 
 
 
 
 
  
