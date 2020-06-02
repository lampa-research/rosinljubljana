#ifndef _ROS_SERVICE_skin_get_bone_name_h
#define _ROS_SERVICE_skin_get_bone_name_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char SKIN_GET_BONE_NAME[] = "webots_ros/skin_get_bone_name";

  class skin_get_bone_nameRequest : public ros::Msg
  {
    public:
      typedef int32_t _index_type;
      _index_type index;

    skin_get_bone_nameRequest():
      index(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_index;
      u_index.real = this->index;
      *(outbuffer + offset + 0) = (u_index.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_index.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_index.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_index.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->index);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_index;
      u_index.base = 0;
      u_index.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_index.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_index.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_index.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->index = u_index.real;
      offset += sizeof(this->index);
     return offset;
    }

    const char * getType(){ return SKIN_GET_BONE_NAME; };
    const char * getMD5(){ return "483eea06cdc3e559421ee31116d0f3b9"; };

  };

  class skin_get_bone_nameResponse : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;

    skin_get_bone_nameResponse():
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

    const char * getType(){ return SKIN_GET_BONE_NAME; };
    const char * getMD5(){ return "c1f3d28f1b044c871e6eff2e9fc3c667"; };

  };

  class skin_get_bone_name {
    public:
    typedef skin_get_bone_nameRequest Request;
    typedef skin_get_bone_nameResponse Response;
  };

}
#endif
