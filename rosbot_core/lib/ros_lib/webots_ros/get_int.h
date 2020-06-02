#ifndef _ROS_SERVICE_get_int_h
#define _ROS_SERVICE_get_int_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char GET_INT[] = "webots_ros/get_int";

  class get_intRequest : public ros::Msg
  {
    public:
      typedef bool _ask_type;
      _ask_type ask;

    get_intRequest():
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

    const char * getType(){ return GET_INT; };
    const char * getMD5(){ return "fbe9700edfca44c5eefb040d9b60f6d6"; };

  };

  class get_intResponse : public ros::Msg
  {
    public:
      typedef int32_t _value_type;
      _value_type value;

    get_intResponse():
      value(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_value;
      u_value.real = this->value;
      *(outbuffer + offset + 0) = (u_value.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_value.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_value.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_value.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->value);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_value;
      u_value.base = 0;
      u_value.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_value.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_value.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_value.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->value = u_value.real;
      offset += sizeof(this->value);
     return offset;
    }

    const char * getType(){ return GET_INT; };
    const char * getMD5(){ return "b3087778e93fcd34cc8d65bc54e850d1"; };

  };

  class get_int {
    public:
    typedef get_intRequest Request;
    typedef get_intResponse Response;
  };

}
#endif
