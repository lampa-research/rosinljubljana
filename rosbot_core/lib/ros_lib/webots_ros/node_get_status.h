#ifndef _ROS_SERVICE_node_get_status_h
#define _ROS_SERVICE_node_get_status_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char NODE_GET_STATUS[] = "webots_ros/node_get_status";

  class node_get_statusRequest : public ros::Msg
  {
    public:
      typedef uint8_t _ask_type;
      _ask_type ask;

    node_get_statusRequest():
      ask(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->ask >> (8 * 0)) & 0xFF;
      offset += sizeof(this->ask);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->ask =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->ask);
     return offset;
    }

    const char * getType(){ return NODE_GET_STATUS; };
    const char * getMD5(){ return "f9df5232b65af94f73f79fe6d84301bb"; };

  };

  class node_get_statusResponse : public ros::Msg
  {
    public:
      typedef uint8_t _status_type;
      _status_type status;

    node_get_statusResponse():
      status(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->status >> (8 * 0)) & 0xFF;
      offset += sizeof(this->status);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->status =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->status);
     return offset;
    }

    const char * getType(){ return NODE_GET_STATUS; };
    const char * getMD5(){ return "284aa12dd9e9e760802ac9f38036ea5e"; };

  };

  class node_get_status {
    public:
    typedef node_get_statusRequest Request;
    typedef node_get_statusResponse Response;
  };

}
#endif
