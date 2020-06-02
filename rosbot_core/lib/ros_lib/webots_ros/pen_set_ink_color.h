#ifndef _ROS_SERVICE_pen_set_ink_color_h
#define _ROS_SERVICE_pen_set_ink_color_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char PEN_SET_INK_COLOR[] = "webots_ros/pen_set_ink_color";

  class pen_set_ink_colorRequest : public ros::Msg
  {
    public:
      typedef int32_t _color_type;
      _color_type color;
      typedef float _density_type;
      _density_type density;

    pen_set_ink_colorRequest():
      color(0),
      density(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_color;
      u_color.real = this->color;
      *(outbuffer + offset + 0) = (u_color.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_color.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_color.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_color.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->color);
      offset += serializeAvrFloat64(outbuffer + offset, this->density);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_color;
      u_color.base = 0;
      u_color.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_color.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_color.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_color.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->color = u_color.real;
      offset += sizeof(this->color);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->density));
     return offset;
    }

    const char * getType(){ return PEN_SET_INK_COLOR; };
    const char * getMD5(){ return "156d8b74482921c561726aaf09907de8"; };

  };

  class pen_set_ink_colorResponse : public ros::Msg
  {
    public:
      typedef int8_t _success_type;
      _success_type success;

    pen_set_ink_colorResponse():
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

    const char * getType(){ return PEN_SET_INK_COLOR; };
    const char * getMD5(){ return "0b13460cb14006d3852674b4c614f25f"; };

  };

  class pen_set_ink_color {
    public:
    typedef pen_set_ink_colorRequest Request;
    typedef pen_set_ink_colorResponse Response;
  };

}
#endif
