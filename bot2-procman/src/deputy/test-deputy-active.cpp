#include <stdio.h>
#include <lcm/lcm-cpp.hpp>
#include "lcmtypes/bot_procman/info2_t.hpp"
#include "lcmtypes/bot_procman/orders2_t.hpp"
#include "lcmtypes/bot_procman/discovery_t.hpp"

class Handler
{
  public:
    ~Handler() {}

    void handleMessage(const lcm::ReceiveBuffer* rbuf,
      const std::string& chan,
      const bot_procman::info2_t* msg){
        printf("Received message on channel \"%s\"\n", chan.c_str());
      }
    void handleMessage2(const lcm::ReceiveBuffer* rbuf,
      const std::string& chan,
      const bot_procman::orders2_t* msg){
        printf("Received message on channel \"%s\"\n", chan.c_str());
      }
    void handleMessage3(const lcm::ReceiveBuffer* rbuf,
      const std::string& chan,
      const bot_procman::discovery_t* msg){
        printf("Received message on channel \"%s\"\n", chan.c_str());
      }

};


int main(int argc, char** argv)
{
  lcm::LCM lcm;
  if(!lcm.good())
    return 1;

  Handler handlerObject;
  lcm.subscribe("PMD_INFO2", &Handler::handleMessage, &handlerObject);
  lcm.subscribe("PMD_ORDERS2", &Handler::handleMessage2, &handlerObject);
  lcm.subscribe("PMD_DISCOVER", &Handler::handleMessage3, &handlerObject);

  while(0 == lcm.handle());

  return 0;
}
