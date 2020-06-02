#ifndef _ROS_SERVICE_camera_get_zoom_info_h
#define _ROS_SERVICE_camera_get_zoom_info_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char CAMERA_GET_ZOOM_INFO[] = "webots_ros/camera_get_zoom_info";

  class camera_get_zoom_infoRequest : public ros::Msg
  {
    public:
      typedef uint8_t _ask_type;
      _ask_type ask;

    camera_get_zoom_infoRequest():
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

    const char * getType(){ return CAMERA_GET_ZOOM_INFO; };
    const char * getMD5(){ return "f9df5232b65af94f73f79fe6d84301bb"; };

  };

  class camera_get_zoom_infoResponse : public ros::Msg
  {
    public:
      typedef float _minFov_type;
      _minFov_type minFov;
      typedef float _maxFov_type;
      _maxFov_type maxFov;

    camera_get_zoom_infoResponse():
      minFov(0),
      maxFov(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->minFov);
      offset += serializeAvrFloat64(outbuffer + offset, this->maxFov);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->minFov));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->maxFov));
     return offset;
    }

    const char * getType(){ return CAMERA_GET_ZOOM_INFO; };
    const char * getMD5(){ return "09ec32bcace1e2e7e22f392cd9bb4659"; };

  };

  class camera_get_zoom_info {
    public:
    typedef camera_get_zoom_infoRequest Request;
    typedef camera_get_zoom_infoResponse Response;
  };

}
#endif
