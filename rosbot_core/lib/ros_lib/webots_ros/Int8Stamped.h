#ifndef _ROS_webots_ros_Int8Stamped_h
#define _ROS_webots_ros_Int8Stamped_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace webots_ros
{

  class Int8Stamped : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef int8_t _data_type;
      _data_type data;

    Int8Stamped():
      header(),
      data(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int8_t real;
        uint8_t base;
      } u_data;
      u_data.real = this->data;
      *(outbuffer + offset + 0) = (u_data.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->data);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int8_t real;
        uint8_t base;
      } u_data;
      u_data.base = 0;
      u_data.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->data = u_data.real;
      offset += sizeof(this->data);
     return offset;
    }

    const char * getType(){ return "webots_ros/Int8Stamped"; };
    const char * getMD5(){ return "09ed9a93cacbec0f13a0fad6e1719649"; };

  };

}
#endif
