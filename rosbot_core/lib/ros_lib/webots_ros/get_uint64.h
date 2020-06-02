#ifndef _ROS_SERVICE_get_uint64_h
#define _ROS_SERVICE_get_uint64_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char GET_UINT64[] = "webots_ros/get_uint64";

  class get_uint64Request : public ros::Msg
  {
    public:
      typedef bool _ask_type;
      _ask_type ask;

    get_uint64Request():
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

    const char * getType(){ return GET_UINT64; };
    const char * getMD5(){ return "fbe9700edfca44c5eefb040d9b60f6d6"; };

  };

  class get_uint64Response : public ros::Msg
  {
    public:
      typedef uint64_t _value_type;
      _value_type value;

    get_uint64Response():
      value(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->value >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->value >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->value >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->value >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (this->value >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (this->value >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (this->value >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (this->value >> (8 * 7)) & 0xFF;
      offset += sizeof(this->value);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->value =  ((uint64_t) (*(inbuffer + offset)));
      this->value |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->value |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->value |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->value |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      this->value |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      this->value |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      this->value |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      offset += sizeof(this->value);
     return offset;
    }

    const char * getType(){ return GET_UINT64; };
    const char * getMD5(){ return "a2c9fb44e48f75feda2746b01055cfa1"; };

  };

  class get_uint64 {
    public:
    typedef get_uint64Request Request;
    typedef get_uint64Response Response;
  };

}
#endif
