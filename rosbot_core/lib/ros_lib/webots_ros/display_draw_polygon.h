#ifndef _ROS_SERVICE_display_draw_polygon_h
#define _ROS_SERVICE_display_draw_polygon_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char DISPLAY_DRAW_POLYGON[] = "webots_ros/display_draw_polygon";

  class display_draw_polygonRequest : public ros::Msg
  {
    public:
      uint32_t x_length;
      typedef int32_t _x_type;
      _x_type st_x;
      _x_type * x;
      uint32_t y_length;
      typedef int32_t _y_type;
      _y_type st_y;
      _y_type * y;
      typedef int32_t _size_type;
      _size_type size;

    display_draw_polygonRequest():
      x_length(0), x(NULL),
      y_length(0), y(NULL),
      size(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->x_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->x_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->x_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->x_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x_length);
      for( uint32_t i = 0; i < x_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_xi;
      u_xi.real = this->x[i];
      *(outbuffer + offset + 0) = (u_xi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_xi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_xi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_xi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x[i]);
      }
      *(outbuffer + offset + 0) = (this->y_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->y_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->y_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->y_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y_length);
      for( uint32_t i = 0; i < y_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_yi;
      u_yi.real = this->y[i];
      *(outbuffer + offset + 0) = (u_yi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_yi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_yi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_yi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y[i]);
      }
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
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t x_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      x_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      x_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      x_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->x_length);
      if(x_lengthT > x_length)
        this->x = (int32_t*)realloc(this->x, x_lengthT * sizeof(int32_t));
      x_length = x_lengthT;
      for( uint32_t i = 0; i < x_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_x;
      u_st_x.base = 0;
      u_st_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_x = u_st_x.real;
      offset += sizeof(this->st_x);
        memcpy( &(this->x[i]), &(this->st_x), sizeof(int32_t));
      }
      uint32_t y_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      y_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      y_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      y_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->y_length);
      if(y_lengthT > y_length)
        this->y = (int32_t*)realloc(this->y, y_lengthT * sizeof(int32_t));
      y_length = y_lengthT;
      for( uint32_t i = 0; i < y_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_y;
      u_st_y.base = 0;
      u_st_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_y = u_st_y.real;
      offset += sizeof(this->st_y);
        memcpy( &(this->y[i]), &(this->st_y), sizeof(int32_t));
      }
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
     return offset;
    }

    const char * getType(){ return DISPLAY_DRAW_POLYGON; };
    const char * getMD5(){ return "45140bfdfc5d8a44cc51b5a3d292b11c"; };

  };

  class display_draw_polygonResponse : public ros::Msg
  {
    public:
      typedef int8_t _success_type;
      _success_type success;

    display_draw_polygonResponse():
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

    const char * getType(){ return DISPLAY_DRAW_POLYGON; };
    const char * getMD5(){ return "0b13460cb14006d3852674b4c614f25f"; };

  };

  class display_draw_polygon {
    public:
    typedef display_draw_polygonRequest Request;
    typedef display_draw_polygonResponse Response;
  };

}
#endif
