#ifndef _ROS_SERVICE_lidar_get_frequency_info_h
#define _ROS_SERVICE_lidar_get_frequency_info_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char LIDAR_GET_FREQUENCY_INFO[] = "webots_ros/lidar_get_frequency_info";

  class lidar_get_frequency_infoRequest : public ros::Msg
  {
    public:
      typedef uint8_t _ask_type;
      _ask_type ask;

    lidar_get_frequency_infoRequest():
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

    const char * getType(){ return LIDAR_GET_FREQUENCY_INFO; };
    const char * getMD5(){ return "f9df5232b65af94f73f79fe6d84301bb"; };

  };

  class lidar_get_frequency_infoResponse : public ros::Msg
  {
    public:
      typedef float _frequency_type;
      _frequency_type frequency;
      typedef float _minFrequency_type;
      _minFrequency_type minFrequency;
      typedef float _maxFrequency_type;
      _maxFrequency_type maxFrequency;

    lidar_get_frequency_infoResponse():
      frequency(0),
      minFrequency(0),
      maxFrequency(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->frequency);
      offset += serializeAvrFloat64(outbuffer + offset, this->minFrequency);
      offset += serializeAvrFloat64(outbuffer + offset, this->maxFrequency);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->frequency));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->minFrequency));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->maxFrequency));
     return offset;
    }

    const char * getType(){ return LIDAR_GET_FREQUENCY_INFO; };
    const char * getMD5(){ return "9814880637e7548b4e9c8076e7471dc3"; };

  };

  class lidar_get_frequency_info {
    public:
    typedef lidar_get_frequency_infoRequest Request;
    typedef lidar_get_frequency_infoResponse Response;
  };

}
#endif
