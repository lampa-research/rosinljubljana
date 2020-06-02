#ifndef _ROS_SERVICE_supervisor_virtual_reality_headset_get_position_h
#define _ROS_SERVICE_supervisor_virtual_reality_headset_get_position_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Point.h"

namespace webots_ros
{

static const char SUPERVISOR_VIRTUAL_REALITY_HEADSET_GET_POSITION[] = "webots_ros/supervisor_virtual_reality_headset_get_position";

  class supervisor_virtual_reality_headset_get_positionRequest : public ros::Msg
  {
    public:
      typedef uint8_t _ask_type;
      _ask_type ask;

    supervisor_virtual_reality_headset_get_positionRequest():
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

    const char * getType(){ return SUPERVISOR_VIRTUAL_REALITY_HEADSET_GET_POSITION; };
    const char * getMD5(){ return "f9df5232b65af94f73f79fe6d84301bb"; };

  };

  class supervisor_virtual_reality_headset_get_positionResponse : public ros::Msg
  {
    public:
      typedef geometry_msgs::Point _position_type;
      _position_type position;

    supervisor_virtual_reality_headset_get_positionResponse():
      position()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->position.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->position.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return SUPERVISOR_VIRTUAL_REALITY_HEADSET_GET_POSITION; };
    const char * getMD5(){ return "e7bb0ef028c744b081acdc57743b11d8"; };

  };

  class supervisor_virtual_reality_headset_get_position {
    public:
    typedef supervisor_virtual_reality_headset_get_positionRequest Request;
    typedef supervisor_virtual_reality_headset_get_positionResponse Response;
  };

}
#endif
