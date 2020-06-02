#ifndef _ROS_SERVICE_lidar_get_layer_point_cloud_h
#define _ROS_SERVICE_lidar_get_layer_point_cloud_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/PointCloud.h"

namespace webots_ros
{

static const char LIDAR_GET_LAYER_POINT_CLOUD[] = "webots_ros/lidar_get_layer_point_cloud";

  class lidar_get_layer_point_cloudRequest : public ros::Msg
  {
    public:
      typedef int32_t _layer_type;
      _layer_type layer;

    lidar_get_layer_point_cloudRequest():
      layer(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_layer;
      u_layer.real = this->layer;
      *(outbuffer + offset + 0) = (u_layer.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_layer.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_layer.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_layer.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->layer);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_layer;
      u_layer.base = 0;
      u_layer.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_layer.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_layer.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_layer.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->layer = u_layer.real;
      offset += sizeof(this->layer);
     return offset;
    }

    const char * getType(){ return LIDAR_GET_LAYER_POINT_CLOUD; };
    const char * getMD5(){ return "0d6c1c0236296850b6361a672e8a61c4"; };

  };

  class lidar_get_layer_point_cloudResponse : public ros::Msg
  {
    public:
      typedef sensor_msgs::PointCloud _pointCloud_type;
      _pointCloud_type pointCloud;

    lidar_get_layer_point_cloudResponse():
      pointCloud()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->pointCloud.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->pointCloud.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return LIDAR_GET_LAYER_POINT_CLOUD; };
    const char * getMD5(){ return "e08e3c13c98d23184c44ac2bd82ce8b4"; };

  };

  class lidar_get_layer_point_cloud {
    public:
    typedef lidar_get_layer_point_cloudRequest Request;
    typedef lidar_get_layer_point_cloudResponse Response;
  };

}
#endif
