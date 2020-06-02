#ifndef _ROS_SERVICE_camera_get_focus_info_h
#define _ROS_SERVICE_camera_get_focus_info_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char CAMERA_GET_FOCUS_INFO[] = "webots_ros/camera_get_focus_info";

  class camera_get_focus_infoRequest : public ros::Msg
  {
    public:
      typedef uint8_t _ask_type;
      _ask_type ask;

    camera_get_focus_infoRequest():
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

    const char * getType(){ return CAMERA_GET_FOCUS_INFO; };
    const char * getMD5(){ return "f9df5232b65af94f73f79fe6d84301bb"; };

  };

  class camera_get_focus_infoResponse : public ros::Msg
  {
    public:
      typedef float _focalLength_type;
      _focalLength_type focalLength;
      typedef float _focalDistance_type;
      _focalDistance_type focalDistance;
      typedef float _maxFocalDistance_type;
      _maxFocalDistance_type maxFocalDistance;
      typedef float _minFocalDistance_type;
      _minFocalDistance_type minFocalDistance;

    camera_get_focus_infoResponse():
      focalLength(0),
      focalDistance(0),
      maxFocalDistance(0),
      minFocalDistance(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->focalLength);
      offset += serializeAvrFloat64(outbuffer + offset, this->focalDistance);
      offset += serializeAvrFloat64(outbuffer + offset, this->maxFocalDistance);
      offset += serializeAvrFloat64(outbuffer + offset, this->minFocalDistance);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->focalLength));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->focalDistance));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->maxFocalDistance));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->minFocalDistance));
     return offset;
    }

    const char * getType(){ return CAMERA_GET_FOCUS_INFO; };
    const char * getMD5(){ return "8cabd8a61992c5b3e4e9d182bb2380ac"; };

  };

  class camera_get_focus_info {
    public:
    typedef camera_get_focus_infoRequest Request;
    typedef camera_get_focus_infoResponse Response;
  };

}
#endif
