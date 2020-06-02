#ifndef _ROS_SERVICE_node_get_static_balance_h
#define _ROS_SERVICE_node_get_static_balance_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char NODE_GET_STATIC_BALANCE[] = "webots_ros/node_get_static_balance";

  class node_get_static_balanceRequest : public ros::Msg
  {
    public:
      typedef uint64_t _node_type;
      _node_type node;

    node_get_static_balanceRequest():
      node(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->node >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->node >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->node >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->node >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (this->node >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (this->node >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (this->node >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (this->node >> (8 * 7)) & 0xFF;
      offset += sizeof(this->node);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->node =  ((uint64_t) (*(inbuffer + offset)));
      this->node |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->node |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->node |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->node |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      this->node |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      this->node |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      this->node |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      offset += sizeof(this->node);
     return offset;
    }

    const char * getType(){ return NODE_GET_STATIC_BALANCE; };
    const char * getMD5(){ return "364f76d0680a5475664d98abd705f036"; };

  };

  class node_get_static_balanceResponse : public ros::Msg
  {
    public:
      typedef uint8_t _balance_type;
      _balance_type balance;

    node_get_static_balanceResponse():
      balance(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->balance >> (8 * 0)) & 0xFF;
      offset += sizeof(this->balance);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->balance =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->balance);
     return offset;
    }

    const char * getType(){ return NODE_GET_STATIC_BALANCE; };
    const char * getMD5(){ return "f560e1499c2583506afd83461a0e3fd6"; };

  };

  class node_get_static_balance {
    public:
    typedef node_get_static_balanceRequest Request;
    typedef node_get_static_balanceResponse Response;
  };

}
#endif
