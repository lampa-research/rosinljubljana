#ifndef _ROS_SERVICE_camera_get_info_h
#define _ROS_SERVICE_camera_get_info_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char CAMERA_GET_INFO[] = "webots_ros/camera_get_info";

  class camera_get_infoRequest : public ros::Msg
  {
    public:
      typedef uint8_t _ask_type;
      _ask_type ask;

    camera_get_infoRequest():
      ask(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->ask >> (8 * 0)) & 0xFF;
      offset += sizeof(this->ask);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->ask =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->ask);
     return offset;
    }

    const char * getType(){ return CAMERA_GET_INFO; };
    const char * getMD5(){ return "f9df5232b65af94f73f79fe6d84301bb"; };

  };

  class camera_get_infoResponse : public ros::Msg
  {
    public:
      typedef uint32_t _width_type;
      _width_type width;
      typedef uint32_t _height_type;
      _height_type height;
      typedef float _Fov_type;
      _Fov_type Fov;
      typedef float _nearRange_type;
      _nearRange_type nearRange;

    camera_get_infoResponse():
      width(0),
      height(0),
      Fov(0),
      nearRange(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->width >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->width >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->width >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->width >> (8 * 3)) & 0xFF;
      offset += sizeof(this->width);
      *(outbuffer + offset + 0) = (this->height >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->height >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->height >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->height >> (8 * 3)) & 0xFF;
      offset += sizeof(this->height);
      offset += serializeAvrFloat64(outbuffer + offset, this->Fov);
      offset += serializeAvrFloat64(outbuffer + offset, this->nearRange);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->width =  ((uint32_t) (*(inbuffer + offset)));
      this->width |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->width |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->width |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->width);
      this->height =  ((uint32_t) (*(inbuffer + offset)));
      this->height |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->height |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->height |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->height);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->Fov));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->nearRange));
     return offset;
    }

    const char * getType(){ return CAMERA_GET_INFO; };
    const char * getMD5(){ return "d6d9c6a6d765e066fb12d59d0c7dee0f"; };

  };

  class camera_get_info {
    public:
    typedef camera_get_infoRequest Request;
    typedef camera_get_infoResponse Response;
  };

}
#endif
