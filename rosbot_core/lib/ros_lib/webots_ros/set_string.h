#ifndef _ROS_SERVICE_set_string_h
#define _ROS_SERVICE_set_string_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char SET_STRING[] = "webots_ros/set_string";

  class set_stringRequest : public ros::Msg
  {
    public:
      typedef const char* _value_type;
      _value_type value;

    set_stringRequest():
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

    const char * getType(){ return SET_STRING; };
    const char * getMD5(){ return "64e58419496c7248b4ef25731f88b8c3"; };

  };

  class set_stringResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    set_stringResponse():
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

    const char * getType(){ return SET_STRING; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class set_string {
    public:
    typedef set_stringRequest Request;
    typedef set_stringResponse Response;
  };

}
#endif
