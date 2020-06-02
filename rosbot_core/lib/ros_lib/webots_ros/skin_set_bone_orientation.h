#ifndef _ROS_SERVICE_skin_set_bone_orientation_h
#define _ROS_SERVICE_skin_set_bone_orientation_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Quaternion.h"

namespace webots_ros
{

static const char SKIN_SET_BONE_ORIENTATION[] = "webots_ros/skin_set_bone_orientation";

  class skin_set_bone_orientationRequest : public ros::Msg
  {
    public:
      typedef int32_t _index_type;
      _index_type index;
      typedef geometry_msgs::Quaternion _orientation_type;
      _orientation_type orientation;
      typedef bool _absolute_type;
      _absolute_type absolute;

    skin_set_bone_orientationRequest():
      index(0),
      orientation(),
      absolute(0)
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
      offset += this->orientation.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_absolute;
      u_absolute.real = this->absolute;
      *(outbuffer + offset + 0) = (u_absolute.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->absolute);
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
      offset += this->orientation.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_absolute;
      u_absolute.base = 0;
      u_absolute.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->absolute = u_absolute.real;
      offset += sizeof(this->absolute);
     return offset;
    }

    const char * getType(){ return SKIN_SET_BONE_ORIENTATION; };
    const char * getMD5(){ return "a6867b70ac9d0b31fe274f3b1674e6a4"; };

  };

  class skin_set_bone_orientationResponse : public ros::Msg
  {
    public:
      typedef int32_t _success_type;
      _success_type success;

    skin_set_bone_orientationResponse():
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

    const char * getType(){ return SKIN_SET_BONE_ORIENTATION; };
    const char * getMD5(){ return "3c2bcf2ff0894cb3058b1bf4c8c4175a"; };

  };

  class skin_set_bone_orientation {
    public:
    typedef skin_set_bone_orientationRequest Request;
    typedef skin_set_bone_orientationResponse Response;
  };

}
#endif
