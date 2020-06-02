#ifndef _ROS_SERVICE_set_bool_h
#define _ROS_SERVICE_set_bool_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char SET_BOOL[] = "webots_ros/set_bool";

  class set_boolRequest : public ros::Msg
  {
    public:
      typedef bool _value_type;
      _value_type value;

    set_boolRequest():
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

    const char * getType(){ return SET_BOOL; };
    const char * getMD5(){ return "e431d687bf4b2c65fbd94b12ae0cb5d9"; };

  };

  class set_boolResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    set_boolResponse():
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

    const char * getType(){ return SET_BOOL; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class set_bool {
    public:
    typedef set_boolRequest Request;
    typedef set_boolResponse Response;
  };

}
#endif
