#ifndef _ROS_SERVICE_set_float_h
#define _ROS_SERVICE_set_float_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char SET_FLOAT[] = "webots_ros/set_float";

  class set_floatRequest : public ros::Msg
  {
    public:
      typedef float _value_type;
      _value_type value;

    set_floatRequest():
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

    const char * getType(){ return SET_FLOAT; };
    const char * getMD5(){ return "1b1594d2b74931ef8fe7be8e2d594455"; };

  };

  class set_floatResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    set_floatResponse():
      success(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
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
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
     return offset;
    }

    const char * getType(){ return SET_FLOAT; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class set_float {
    public:
    typedef set_floatRequest Request;
    typedef set_floatResponse Response;
  };

}
#endif
