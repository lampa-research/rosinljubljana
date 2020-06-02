#ifndef _ROS_SERVICE_node_reset_functions_h
#define _ROS_SERVICE_node_reset_functions_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char NODE_RESET_FUNCTIONS[] = "webots_ros/node_reset_functions";

  class node_reset_functionsRequest : public ros::Msg
  {
    public:
      typedef uint64_t _node_type;
      _node_type node;

    node_reset_functionsRequest():
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

    const char * getType(){ return NODE_RESET_FUNCTIONS; };
    const char * getMD5(){ return "364f76d0680a5475664d98abd705f036"; };

  };

  class node_reset_functionsResponse : public ros::Msg
  {
    public:
      typedef int8_t _success_type;
      _success_type success;

    node_reset_functionsResponse():
      success(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
     return offset;
    }

    const char * getType(){ return NODE_RESET_FUNCTIONS; };
    const char * getMD5(){ return "0b13460cb14006d3852674b4c614f25f"; };

  };

  class node_reset_functions {
    public:
    typedef node_reset_functionsRequest Request;
    typedef node_reset_functionsResponse Response;
  };

}
#endif
