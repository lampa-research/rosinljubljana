#ifndef _ROS_SERVICE_node_add_force_with_offset_h
#define _ROS_SERVICE_node_add_force_with_offset_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Vector3.h"

namespace webots_ros
{

static const char NODE_ADD_FORCE_WITH_OFFSET[] = "webots_ros/node_add_force_with_offset";

  class node_add_force_with_offsetRequest : public ros::Msg
  {
    public:
      typedef uint64_t _node_type;
      _node_type node;
      typedef geometry_msgs::Vector3 _force_type;
      _force_type force;
      typedef geometry_msgs::Vector3 _offset_type;
      _offset_type offset;
      typedef uint8_t _relative_type;
      _relative_type relative;

    node_add_force_with_offsetRequest():
      node(0),
      force(),
      offset(),
      relative(0)
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
      offset += this->force.serialize(outbuffer + offset);
      offset += this->offset.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->relative >> (8 * 0)) & 0xFF;
      offset += sizeof(this->relative);
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
      offset += this->force.deserialize(inbuffer + offset);
      offset += this->offset.deserialize(inbuffer + offset);
      this->relative =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->relative);
     return offset;
    }

    const char * getType(){ return NODE_ADD_FORCE_WITH_OFFSET; };
    const char * getMD5(){ return "a76c212a713374a1593523ad66a858c4"; };

  };

  class node_add_force_with_offsetResponse : public ros::Msg
  {
    public:
      typedef int32_t _success_type;
      _success_type success;

    node_add_force_with_offsetResponse():
      success(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_success.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_success.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_success.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->success);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_success.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_success.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_success.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->success = u_success.real;
      offset += sizeof(this->success);
     return offset;
    }

    const char * getType(){ return NODE_ADD_FORCE_WITH_OFFSET; };
    const char * getMD5(){ return "3c2bcf2ff0894cb3058b1bf4c8c4175a"; };

  };

  class node_add_force_with_offset {
    public:
    typedef node_add_force_with_offsetRequest Request;
    typedef node_add_force_with_offsetResponse Response;
  };

}
#endif
