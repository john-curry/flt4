#include "server.h"
#include "client.h"
#include "conversions.h"
int main() {
  using namespace std;
  using namespace flt4;
  map<string, int> a { { "str" , 43 } ,  { "goddamn" , 32 } };
  //cout << "The jjson is: " << actions_to_json(a) << std::endl;
  //flt4::server game_server;
  //game_server.init();
  //game_server.listen();
  //game_server.accept();
  //std::map<std::string, int> out {
  //  { "string" , 12 },
  //  { "sexy  " , 1  }
  //};
  //game_server.send_turn_end(out);
  flt4::client game_client("192.168.0.11");
  game_client.init();
  game_client.connect();
  game_client.wait_for_round_start();
  game_client.send_round_start(vector<string>{"googog"});
  game_client.get_turn_end();
  game_client.send_turn_end(a);
  game_client.get_round_status();
  game_client.send_round_status(true);
  return 0;
}
