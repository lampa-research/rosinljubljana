#ifndef _ROS_SERVICE_display_set_font_h
#define _ROS_SERVICE_display_set_font_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char DISPLAY_SET_FONT[] = "webots_ros/display_set_font";

  class display_set_fontRequest : public ros::Msg
  {
    public:
      typedef const char* _font_type;
      _font_type font;
      typedef int32_t _size_type;
      _size_type size;
      typedef uint8_t _antiAliasing_type;
      _antiAliasing_type antiAliasing;

    display_set_fontRequest():
      font(""),
      size(0),
      antiAliasing(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_font = strlen(this->font);
      varToArr(outbuffer + offset, length_font);
      offset += 4;
      memcpy(outbuffer + offset, this->font, length_font);
      offset += length_font;
      union {
        int32_t real;
        uint32_t base;
      } u_size;
      u_size.real = this->size;
      *(outbuffer + offset + 0) = (u_size.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_size.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_size.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_size.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->size);
      *(outbuffer + offset + 0) = (this->antiAliasing >> (8 * 0)) & 0xFF;
      offset += sizeof(this->antiAliasing);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_font;
      arrToVar(length_font, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_font; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_font-1]=0;
      this->font = (char *)(inbuffer + offset-1);
      offset += length_font;
      union {
        int32_t real;
        uint32_t base;
      } u_size;
      u_size.base = 0;
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->size = u_size.real;
      offset += sizeof(this->size);
      this->antiAliasing =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->antiAliasing);
     return offset;
    }

    const char * getType(){ return DISPLAY_SET_FONT; };
    const char * getMD5(){ return "988e22c5bdd5c0730231987f4e04ae3a"; };

  };

  class display_set_fontResponse : public ros::Msg
  {
    public:
      typedef int8_t _success_type;
      _success_type success;

    display_set_fontResponse():
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

    const char * getType(){ return DISPLAY_SET_FONT; };
    const char * getMD5(){ return "0b13460cb14006d3852674b4c614f25f"; };

  };

  class display_set_font {
    public:
    typedef display_set_fontRequest Request;
    typedef display_set_fontResponse Response;
  };

}
#endif
