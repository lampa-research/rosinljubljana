#ifndef _ROS_webots_ros_RadarTarget_h
#define _ROS_webots_ros_RadarTarget_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace webots_ros
{

  class RadarTarget : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef float _distance_type;
      _distance_type distance;
      typedef float _receivedPower_type;
      _receivedPower_type receivedPower;
      typedef float _speed_type;
      _speed_type speed;
      typedef float _azimuth_type;
      _azimuth_type azimuth;

    RadarTarget():
      header(),
      distance(0),
      receivedPower(0),
      speed(0),
      azimuth(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->distance);
      offset += serializeAvrFloat64(outbuffer + offset, this->receivedPower);
      offset += serializeAvrFloat64(outbuffer + offset, this->speed);
      offset += serializeAvrFloat64(outbuffer + offset, this->azimuth);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->distance));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->receivedPower));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->speed));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->azimuth));
     return offset;
    }

    const char * getType(){ return "webots_ros/RadarTarget"; };
    const char * getMD5(){ return "39dda2b01810c27987f6a767b1a78c1c"; };

  };

}
#endif
