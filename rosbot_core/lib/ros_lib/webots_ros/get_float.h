#ifndef _ROS_SERVICE_get_float_h
#define _ROS_SERVICE_get_float_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char GET_FLOAT[] = "webots_ros/get_float";

  class get_floatRequest : public ros::Msg
  {
    public:
      typedef bool _ask_type;
      _ask_type ask;

    get_floatRequest():
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

    const char * getType(){ return GET_FLOAT; };
    const char * getMD5(){ return "fbe9700edfca44c5eefb040d9b60f6d6"; };

  };

  class get_floatResponse : public ros::Msg
  {
    public:
      typedef float _value_type;
      _value_type value;

    get_floatResponse():
      value(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->value);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->value));
     return offset;
    }

    const char * getType(){ return GET_FLOAT; };
    const char * getMD5(){ return "1b1594d2b74931ef8fe7be8e2d594455"; };

  };

  class get_float {
    public:
    typedef get_floatRequest Request;
    typedef get_floatResponse Response;
  };

}
#endif
