#ifndef _ROS_SERVICE_display_image_copy_h
#define _ROS_SERVICE_display_image_copy_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char DISPLAY_IMAGE_COPY[] = "webots_ros/display_image_copy";

  class display_image_copyRequest : public ros::Msg
  {
    public:
      typedef int32_t _x_type;
      _x_type x;
      typedef int32_t _y_type;
      _y_type y;
      typedef int32_t _width_type;
      _width_type width;
      typedef int32_t _height_type;
      _height_type height;

    display_image_copyRequest():
      x(0),
      y(0),
      width(0),
      height(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_x;
      u_x.real = this->x;
      *(outbuffer + offset + 0) = (u_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x);
      union {
        int32_t real;
        uint32_t base;
      } u_y;
      u_y.real = this->y;
      *(outbuffer + offset + 0) = (u_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y);
      union {
        int32_t real;
        uint32_t base;
      } u_width;
      u_width.real = this->width;
      *(outbuffer + offset + 0) = (u_width.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_width.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_width.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_width.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->width);
      union {
        int32_t real;
        uint32_t base;
      } u_height;
      u_height.real = this->height;
      *(outbuffer + offset + 0) = (u_height.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_height.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_height.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_height.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->height);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_x;
      u_x.base = 0;
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->x = u_x.real;
      offset += sizeof(this->x);
      union {
        int32_t real;
        uint32_t base;
      } u_y;
      u_y.base = 0;
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->y = u_y.real;
      offset += sizeof(this->y);
      union {
        int32_t real;
        uint32_t base;
      } u_width;
      u_width.base = 0;
      u_width.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_width.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_width.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_width.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->width = u_width.real;
      offset += sizeof(this->width);
      union {
        int32_t real;
        uint32_t base;
      } u_height;
      u_height.base = 0;
      u_height.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_height.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_height.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_height.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->height = u_height.real;
      offset += sizeof(this->height);
     return offset;
    }

    const char * getType(){ return DISPLAY_IMAGE_COPY; };
    const char * getMD5(){ return "4425f1067abc7ec2e487d28194eccff4"; };

  };

  class display_image_copyResponse : public ros::Msg
  {
    public:
      typedef uint64_t _ir_type;
      _ir_type ir;

    display_image_copyResponse():
      ir(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->ir >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->ir >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->ir >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->ir >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (this->ir >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (this->ir >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (this->ir >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (this->ir >> (8 * 7)) & 0xFF;
      offset += sizeof(this->ir);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->ir =  ((uint64_t) (*(inbuffer + offset)));
      this->ir |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->ir |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->ir |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ir |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      this->ir |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      this->ir |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      this->ir |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      offset += sizeof(this->ir);
     return offset;
    }

    const char * getType(){ return DISPLAY_IMAGE_COPY; };
    const char * getMD5(){ return "062bd6ec8c99fd70e30cc24256f9226a"; };

  };

  class display_image_copy {
    public:
    typedef display_image_copyRequest Request;
    typedef display_image_copyResponse Response;
  };

}
#endif
