#ifndef _ROS_SERVICE_display_draw_pixel_h
#define _ROS_SERVICE_display_draw_pixel_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char DISPLAY_DRAW_PIXEL[] = "webots_ros/display_draw_pixel";

  class display_draw_pixelRequest : public ros::Msg
  {
    public:
      typedef int32_t _x1_type;
      _x1_type x1;
      typedef int32_t _y1_type;
      _y1_type y1;

    display_draw_pixelRequest():
      x1(0),
      y1(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_x1;
      u_x1.real = this->x1;
      *(outbuffer + offset + 0) = (u_x1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_x1.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_x1.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_x1.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x1);
      union {
        int32_t real;
        uint32_t base;
      } u_y1;
      u_y1.real = this->y1;
      *(outbuffer + offset + 0) = (u_y1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_y1.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_y1.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_y1.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y1);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_x1;
      u_x1.base = 0;
      u_x1.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_x1.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_x1.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_x1.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->x1 = u_x1.real;
      offset += sizeof(this->x1);
      union {
        int32_t real;
        uint32_t base;
      } u_y1;
      u_y1.base = 0;
      u_y1.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_y1.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_y1.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_y1.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->y1 = u_y1.real;
      offset += sizeof(this->y1);
     return offset;
    }

    const char * getType(){ return DISPLAY_DRAW_PIXEL; };
    const char * getMD5(){ return "1a417c344be1a26b28c26afdee67552f"; };

  };

  class display_draw_pixelResponse : public ros::Msg
  {
    public:
      typedef int8_t _success_type;
      _success_type success;

    display_draw_pixelResponse():
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

    const char * getType(){ return DISPLAY_DRAW_PIXEL; };
    const char * getMD5(){ return "0b13460cb14006d3852674b4c614f25f"; };

  };

  class display_draw_pixel {
    public:
    typedef display_draw_pixelRequest Request;
    typedef display_draw_pixelResponse Response;
  };

}
#endif
