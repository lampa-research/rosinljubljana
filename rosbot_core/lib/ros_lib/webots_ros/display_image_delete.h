#ifndef _ROS_SERVICE_display_image_delete_h
#define _ROS_SERVICE_display_image_delete_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char DISPLAY_IMAGE_DELETE[] = "webots_ros/display_image_delete";

  class display_image_deleteRequest : public ros::Msg
  {
    public:
      typedef uint64_t _ir_type;
      _ir_type ir;

    display_image_deleteRequest():
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

    const char * getType(){ return DISPLAY_IMAGE_DELETE; };
    const char * getMD5(){ return "062bd6ec8c99fd70e30cc24256f9226a"; };

  };

  class display_image_deleteResponse : public ros::Msg
  {
    public:
      typedef int8_t _success_type;
      _success_type success;

    display_image_deleteResponse():
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

    const char * getType(){ return DISPLAY_IMAGE_DELETE; };
    const char * getMD5(){ return "0b13460cb14006d3852674b4c614f25f"; };

  };

  class display_image_delete {
    public:
    typedef display_image_deleteRequest Request;
    typedef display_image_deleteResponse Response;
  };

}
#endif
