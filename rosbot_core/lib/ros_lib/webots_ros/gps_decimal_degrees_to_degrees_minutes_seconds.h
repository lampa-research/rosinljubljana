#ifndef _ROS_SERVICE_gps_decimal_degrees_to_degrees_minutes_seconds_h
#define _ROS_SERVICE_gps_decimal_degrees_to_degrees_minutes_seconds_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char GPS_DECIMAL_DEGREES_TO_DEGREES_MINUTES_SECONDS[] = "webots_ros/gps_decimal_degrees_to_degrees_minutes_seconds";

  class gps_decimal_degrees_to_degrees_minutes_secondsRequest : public ros::Msg
  {
    public:
      typedef float _decimalDegrees_type;
      _decimalDegrees_type decimalDegrees;

    gps_decimal_degrees_to_degrees_minutes_secondsRequest():
      decimalDegrees(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_decimalDegrees;
      u_decimalDegrees.real = this->decimalDegrees;
      *(outbuffer + offset + 0) = (u_decimalDegrees.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_decimalDegrees.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_decimalDegrees.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_decimalDegrees.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->decimalDegrees);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_decimalDegrees;
      u_decimalDegrees.base = 0;
      u_decimalDegrees.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_decimalDegrees.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_decimalDegrees.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_decimalDegrees.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->decimalDegrees = u_decimalDegrees.real;
      offset += sizeof(this->decimalDegrees);
     return offset;
    }

    const char * getType(){ return GPS_DECIMAL_DEGREES_TO_DEGREES_MINUTES_SECONDS; };
    const char * getMD5(){ return "f8f7a12c44f9c148c60202aa01cea424"; };

  };

  class gps_decimal_degrees_to_degrees_minutes_secondsResponse : public ros::Msg
  {
    public:
      typedef const char* _degreesMinutesSeconds_type;
      _degreesMinutesSeconds_type degreesMinutesSeconds;

    gps_decimal_degrees_to_degrees_minutes_secondsResponse():
      degreesMinutesSeconds("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_degreesMinutesSeconds = strlen(this->degreesMinutesSeconds);
      varToArr(outbuffer + offset, length_degreesMinutesSeconds);
      offset += 4;
      memcpy(outbuffer + offset, this->degreesMinutesSeconds, length_degreesMinutesSeconds);
      offset += length_degreesMinutesSeconds;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_degreesMinutesSeconds;
      arrToVar(length_degreesMinutesSeconds, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_degreesMinutesSeconds; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_degreesMinutesSeconds-1]=0;
      this->degreesMinutesSeconds = (char *)(inbuffer + offset-1);
      offset += length_degreesMinutesSeconds;
     return offset;
    }

    const char * getType(){ return GPS_DECIMAL_DEGREES_TO_DEGREES_MINUTES_SECONDS; };
    const char * getMD5(){ return "1dd167c46cb823612e4149b12fa41046"; };

  };

  class gps_decimal_degrees_to_degrees_minutes_seconds {
    public:
    typedef gps_decimal_degrees_to_degrees_minutes_secondsRequest Request;
    typedef gps_decimal_degrees_to_degrees_minutes_secondsResponse Response;
  };

}
#endif
