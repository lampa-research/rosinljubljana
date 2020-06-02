#ifndef _ROS_SERVICE_supervisor_virtual_reality_headset_get_orientation_h
#define _ROS_SERVICE_supervisor_virtual_reality_headset_get_orientation_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Quaternion.h"

namespace webots_ros
{

static const char SUPERVISOR_VIRTUAL_REALITY_HEADSET_GET_ORIENTATION[] = "webots_ros/supervisor_virtual_reality_headset_get_orientation";

  class supervisor_virtual_reality_headset_get_orientationRequest : public ros::Msg
  {
    public:
      typedef uint8_t _ask_type;
      _ask_type ask;

    supervisor_virtual_reality_headset_get_orientationRequest():
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

    const char * getType(){ return SUPERVISOR_VIRTUAL_REALITY_HEADSET_GET_ORIENTATION; };
    const char * getMD5(){ return "f9df5232b65af94f73f79fe6d84301bb"; };

  };

  class supervisor_virtual_reality_headset_get_orientationResponse : public ros::Msg
  {
    public:
      typedef geometry_msgs::Quaternion _orientation_type;
      _orientation_type orientation;

    supervisor_virtual_reality_headset_get_orientationResponse():
      orientation()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->orientation.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->orientation.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return SUPERVISOR_VIRTUAL_REALITY_HEADSET_GET_ORIENTATION; };
    const char * getMD5(){ return "8ed1de3b69473461225107f55ad59b9d"; };

  };

  class supervisor_virtual_reality_headset_get_orientation {
    public:
    typedef supervisor_virtual_reality_headset_get_orientationRequest Request;
    typedef supervisor_virtual_reality_headset_get_orientationResponse Response;
  };

}
#endif
