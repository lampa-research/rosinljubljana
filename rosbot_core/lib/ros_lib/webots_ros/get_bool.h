#ifndef _ROS_SERVICE_get_bool_h
#define _ROS_SERVICE_get_bool_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char GET_BOOL[] = "webots_ros/get_bool";

  class get_boolRequest : public ros::Msg
  {
    public:
      typedef bool _ask_type;
      _ask_type ask;

    get_boolRequest():
      ask(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_ask;
      u_ask.real = this->ask;
      *(outbuffer + offset + 0) = (u_ask.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->ask);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_ask;
      u_ask.base = 0;
      u_ask.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->ask = u_ask.real;
      offset += sizeof(this->ask);
     return offset;
    }

    const char * getType(){ return GET_BOOL; };
    const char * getMD5(){ return "fbe9700edfca44c5eefb040d9b60f6d6"; };

  };

  class get_boolResponse : public ros::Msg
  {
    public:
      typedef bool _value_type;
      _value_type value;

    get_boolResponse():
      value(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_value;
      u_value.real = this->value;
      *(outbuffer + offset + 0) = (u_value.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->value);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_value;
      u_value.base = 0;
      u_value.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->value = u_value.real;
      offset += sizeof(this->value);
     return offset;
    }

    const char * getType(){ return GET_BOOL; };
    const char * getMD5(){ return "e431d687bf4b2c65fbd94b12ae0cb5d9"; };

  };

  class get_bool {
    public:
    typedef get_boolRequest Request;
    typedef get_boolResponse Response;
  };

}
#endif
