#ifndef _ROS_SERVICE_node_get_name_h
#define _ROS_SERVICE_node_get_name_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char NODE_GET_NAME[] = "webots_ros/node_get_name";

  class node_get_nameRequest : public ros::Msg
  {
    public:
      typedef uint64_t _node_type;
      _node_type node;

    node_get_nameRequest():
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

    const char * getType(){ return NODE_GET_NAME; };
    const char * getMD5(){ return "364f76d0680a5475664d98abd705f036"; };

  };

  class node_get_nameResponse : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;

    node_get_nameResponse():
      name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
     return offset;
    }

    const char * getType(){ return NODE_GET_NAME; };
    const char * getMD5(){ return "c1f3d28f1b044c871e6eff2e9fc3c667"; };

  };

  class node_get_name {
    public:
    typedef node_get_nameRequest Request;
    typedef node_get_nameResponse Response;
  };

}
#endif
