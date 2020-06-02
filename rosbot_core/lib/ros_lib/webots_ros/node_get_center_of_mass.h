#ifndef _ROS_SERVICE_node_get_center_of_mass_h
#define _ROS_SERVICE_node_get_center_of_mass_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Point.h"

namespace webots_ros
{

static const char NODE_GET_CENTER_OF_MASS[] = "webots_ros/node_get_center_of_mass";

  class node_get_center_of_massRequest : public ros::Msg
  {
    public:
      typedef uint64_t _node_type;
      _node_type node;

    node_get_center_of_massRequest():
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

    const char * getType(){ return NODE_GET_CENTER_OF_MASS; };
    const char * getMD5(){ return "364f76d0680a5475664d98abd705f036"; };

  };

  class node_get_center_of_massResponse : public ros::Msg
  {
    public:
      typedef geometry_msgs::Point _centerOfMass_type;
      _centerOfMass_type centerOfMass;

    node_get_center_of_massResponse():
      centerOfMass()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->centerOfMass.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->centerOfMass.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return NODE_GET_CENTER_OF_MASS; };
    const char * getMD5(){ return "e70727e623e5dc1b6f64942e8b4ec566"; };

  };

  class node_get_center_of_mass {
    public:
    typedef node_get_center_of_massRequest Request;
    typedef node_get_center_of_massResponse Response;
  };

}
#endif
