#ifndef _ROS_SERVICE_display_draw_oval_h
#define _ROS_SERVICE_display_draw_oval_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char DISPLAY_DRAW_OVAL[] = "webots_ros/display_draw_oval";

  class display_draw_ovalRequest : public ros::Msg
  {
    public:
      typedef int32_t _cx_type;
      _cx_type cx;
      typedef int32_t _cy_type;
      _cy_type cy;
      typedef int32_t _a_type;
      _a_type a;
      typedef int32_t _b_type;
      _b_type b;

    display_draw_ovalRequest():
      cx(0),
      cy(0),
      a(0),
      b(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_cx;
      u_cx.real = this->cx;
      *(outbuffer + offset + 0) = (u_cx.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_cx.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_cx.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_cx.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->cx);
      union {
        int32_t real;
        uint32_t base;
      } u_cy;
      u_cy.real = this->cy;
      *(outbuffer + offset + 0) = (u_cy.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_cy.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_cy.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_cy.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->cy);
      union {
        int32_t real;
        uint32_t base;
      } u_a;
      u_a.real = this->a;
      *(outbuffer + offset + 0) = (u_a.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_a.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_a.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_a.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->a);
      union {
        int32_t real;
        uint32_t base;
      } u_b;
      u_b.real = this->b;
      *(outbuffer + offset + 0) = (u_b.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_b.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_b.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_b.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->b);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_cx;
      u_cx.base = 0;
      u_cx.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_cx.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_cx.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_cx.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->cx = u_cx.real;
      offset += sizeof(this->cx);
      union {
        int32_t real;
        uint32_t base;
      } u_cy;
      u_cy.base = 0;
      u_cy.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_cy.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_cy.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_cy.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->cy = u_cy.real;
      offset += sizeof(this->cy);
      union {
        int32_t real;
        uint32_t base;
      } u_a;
      u_a.base = 0;
      u_a.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_a.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_a.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_a.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->a = u_a.real;
      offset += sizeof(this->a);
      union {
        int32_t real;
        uint32_t base;
      } u_b;
      u_b.base = 0;
      u_b.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_b.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_b.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_b.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->b = u_b.real;
      offset += sizeof(this->b);
     return offset;
    }

    const char * getType(){ return DISPLAY_DRAW_OVAL; };
    const char * getMD5(){ return "78363f0f1b453e74fe20a86614ff165b"; };

  };

  class display_draw_ovalResponse : public ros::Msg
  {
    public:
      typedef int8_t _success_type;
      _success_type success;

    display_draw_ovalResponse():
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

    const char * getType(){ return DISPLAY_DRAW_OVAL; };
    const char * getMD5(){ return "0b13460cb14006d3852674b4c614f25f"; };

  };

  class display_draw_oval {
    public:
    typedef display_draw_ovalRequest Request;
    typedef display_draw_ovalResponse Response;
  };

}
#endif
