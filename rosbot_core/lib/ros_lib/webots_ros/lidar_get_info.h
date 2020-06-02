#ifndef _ROS_SERVICE_lidar_get_info_h
#define _ROS_SERVICE_lidar_get_info_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char LIDAR_GET_INFO[] = "webots_ros/lidar_get_info";

  class lidar_get_infoRequest : public ros::Msg
  {
    public:
      typedef uint8_t _ask_type;
      _ask_type ask;

    lidar_get_infoRequest():
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

    const char * getType(){ return LIDAR_GET_INFO; };
    const char * getMD5(){ return "f9df5232b65af94f73f79fe6d84301bb"; };

  };

  class lidar_get_infoResponse : public ros::Msg
  {
    public:
      typedef uint32_t _horizontalResolution_type;
      _horizontalResolution_type horizontalResolution;
      typedef uint32_t _numberOfLayers_type;
      _numberOfLayers_type numberOfLayers;
      typedef float _fov_type;
      _fov_type fov;
      typedef float _verticalFov_type;
      _verticalFov_type verticalFov;
      typedef float _minRange_type;
      _minRange_type minRange;
      typedef float _maxRange_type;
      _maxRange_type maxRange;

    lidar_get_infoResponse():
      horizontalResolution(0),
      numberOfLayers(0),
      fov(0),
      verticalFov(0),
      minRange(0),
      maxRange(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->horizontalResolution >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->horizontalResolution >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->horizontalResolution >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->horizontalResolution >> (8 * 3)) & 0xFF;
      offset += sizeof(this->horizontalResolution);
      *(outbuffer + offset + 0) = (this->numberOfLayers >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->numberOfLayers >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->numberOfLayers >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->numberOfLayers >> (8 * 3)) & 0xFF;
      offset += sizeof(this->numberOfLayers);
      offset += serializeAvrFloat64(outbuffer + offset, this->fov);
      offset += serializeAvrFloat64(outbuffer + offset, this->verticalFov);
      offset += serializeAvrFloat64(outbuffer + offset, this->minRange);
      offset += serializeAvrFloat64(outbuffer + offset, this->maxRange);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->horizontalResolution =  ((uint32_t) (*(inbuffer + offset)));
      this->horizontalResolution |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->horizontalResolution |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->horizontalResolution |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->horizontalResolution);
      this->numberOfLayers =  ((uint32_t) (*(inbuffer + offset)));
      this->numberOfLayers |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->numberOfLayers |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->numberOfLayers |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->numberOfLayers);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->fov));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->verticalFov));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->minRange));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->maxRange));
     return offset;
    }

    const char * getType(){ return LIDAR_GET_INFO; };
    const char * getMD5(){ return "e3ce26475d0d5fee0e59e3479a798bf0"; };

  };

  class lidar_get_info {
    public:
    typedef lidar_get_infoRequest Request;
    typedef lidar_get_infoResponse Response;
  };

}
#endif
