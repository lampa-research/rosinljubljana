#ifndef _ROS_SERVICE_get_string_h
#define _ROS_SERVICE_get_string_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char GET_STRING[] = "webots_ros/get_string";

  class get_stringRequest : public ros::Msg
  {
    public:
      typedef bool _ask_type;
      _ask_type ask;

    get_stringRequest():
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

    const char * getType(){ return GET_STRING; };
    const char * getMD5(){ return "fbe9700edfca44c5eefb040d9b60f6d6"; };

  };

  class get_stringResponse : public ros::Msg
  {
    public:
      typedef const char* _value_type;
      _value_type value;

    get_stringResponse():
      value("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_value = strlen(this->value);
      varToArr(outbuffer + offset, length_value);
      offset += 4;
      memcpy(outbuffer + offset, this->value, length_value);
      offset += length_value;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_value;
      arrToVar(length_value, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_value; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_value-1]=0;
      this->value = (char *)(inbuffer + offset-1);
      offset += length_value;
     return offset;
    }

    const char * getType(){ return GET_STRING; };
    const char * getMD5(){ return "64e58419496c7248b4ef25731f88b8c3"; };

  };

  class get_string {
    public:
    typedef get_stringRequest Request;
    typedef get_stringResponse Response;
  };

}
#endif
