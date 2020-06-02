#ifndef _ROS_SERVICE_display_draw_line_h
#define _ROS_SERVICE_display_draw_line_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char DISPLAY_DRAW_LINE[] = "webots_ros/display_draw_line";

  class display_draw_lineRequest : public ros::Msg
  {
    public:
      typedef int32_t _x1_type;
      _x1_type x1;
      typedef int32_t _y1_type;
      _y1_type y1;
      typedef int32_t _x2_type;
      _x2_type x2;
      typedef int32_t _y2_type;
      _y2_type y2;

    display_draw_lineRequest():
      x1(0),
      y1(0),
      x2(0),
      y2(0)
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
      union {
        int32_t real;
        uint32_t base;
      } u_x2;
      u_x2.real = this->x2;
      *(outbuffer + offset + 0) = (u_x2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_x2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_x2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_x2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x2);
      union {
        int32_t real;
        uint32_t base;
      } u_y2;
      u_y2.real = this->y2;
      *(outbuffer + offset + 0) = (u_y2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_y2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_y2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_y2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y2);
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
      union {
        int32_t real;
        uint32_t base;
      } u_x2;
      u_x2.base = 0;
      u_x2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_x2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_x2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_x2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->x2 = u_x2.real;
      offset += sizeof(this->x2);
      union {
        int32_t real;
        uint32_t base;
      } u_y2;
      u_y2.base = 0;
      u_y2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_y2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_y2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_y2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->y2 = u_y2.real;
      offset += sizeof(this->y2);
     return offset;
    }

    const char * getType(){ return DISPLAY_DRAW_LINE; };
    const char * getMD5(){ return "01b404007f6687249fa0f27eea3c1daf"; };

  };

  class display_draw_lineResponse : public ros::Msg
  {
    public:
      typedef int8_t _success_type;
      _success_type success;

    display_draw_lineResponse():
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

    const char * getType(){ return DISPLAY_DRAW_LINE; };
    const char * getMD5(){ return "0b13460cb14006d3852674b4c614f25f"; };

  };

  class display_draw_line {
    public:
    typedef display_draw_lineRequest Request;
    typedef display_draw_lineResponse Response;
  };

}
#endif
