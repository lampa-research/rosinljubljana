#ifndef _ROS_SERVICE_node_get_orientation_h
#define _ROS_SERVICE_node_get_orientation_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Quaternion.h"

namespace webots_ros
{

static const char NODE_GET_ORIENTATION[] = "webots_ros/node_get_orientation";

  class node_get_orientationRequest : public ros::Msg
  {
    public:
      typedef uint64_t _node_type;
      _node_type node;

    node_get_orientationRequest():
      node(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->node >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->node >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->node >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->node >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (this->node >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (this->node >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (this->node >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (this->node >> (8 * 7)) & 0xFF;
      offset += sizeof(this->node);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->node =  ((uint64_t) (*(inbuffer + offset)));
      this->node |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->node |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->node |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->node |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      this->node |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      this->node |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      this->node |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      offset += sizeof(this->node);
     return offset;
    }

    const char * getType(){ return NODE_GET_ORIENTATION; };
    const char * getMD5(){ return "364f76d0680a5475664d98abd705f036"; };

  };

  class node_get_orientationResponse : public ros::Msg
  {
    public:
      typedef geometry_msgs::Quaternion _orientation_type;
      _orientation_type orientation;

    node_get_orientationResponse():
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

    const char * getType(){ return NODE_GET_ORIENTATION; };
    const char * getMD5(){ return "8ed1de3b69473461225107f55ad59b9d"; };

  };

  class node_get_orientation {
    public:
    typedef node_get_orientationRequest Request;
    typedef node_get_orientationResponse Response;
  };

}
#endif
