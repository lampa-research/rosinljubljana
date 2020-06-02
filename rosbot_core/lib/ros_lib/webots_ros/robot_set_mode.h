#ifndef _ROS_SERVICE_robot_set_mode_h
#define _ROS_SERVICE_robot_set_mode_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char ROBOT_SET_MODE[] = "webots_ros/robot_set_mode";

  class robot_set_modeRequest : public ros::Msg
  {
    public:
      uint32_t arg_length;
      typedef uint8_t _arg_type;
      _arg_type st_arg;
      _arg_type * arg;
      typedef int32_t _mode_type;
      _mode_type mode;

    robot_set_modeRequest():
      arg_length(0), arg(NULL),
      mode(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->arg_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->arg_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->arg_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->arg_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->arg_length);
      for( uint32_t i = 0; i < arg_length; i++){
      *(outbuffer + offset + 0) = (this->arg[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->arg[i]);
      }
      union {
        int32_t real;
        uint32_t base;
      } u_mode;
      u_mode.real = this->mode;
      *(outbuffer + offset + 0) = (u_mode.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mode.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_mode.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_mode.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->mode);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t arg_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      arg_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      arg_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      arg_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->arg_length);
      if(arg_lengthT > arg_length)
        this->arg = (uint8_t*)realloc(this->arg, arg_lengthT * sizeof(uint8_t));
      arg_length = arg_lengthT;
      for( uint32_t i = 0; i < arg_length; i++){
      this->st_arg =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->st_arg);
        memcpy( &(this->arg[i]), &(this->st_arg), sizeof(uint8_t));
      }
      union {
        int32_t real;
        uint32_t base;
      } u_mode;
      u_mode.base = 0;
      u_mode.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mode.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_mode.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_mode.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->mode = u_mode.real;
      offset += sizeof(this->mode);
     return offset;
    }

    const char * getType(){ return ROBOT_SET_MODE; };
    const char * getMD5(){ return "352bd896b9891f9831590c1a8d916605"; };

  };

  class robot_set_modeResponse : public ros::Msg
  {
    public:
      typedef int8_t _success_type;
      _success_type success;

    robot_set_modeResponse():
      success(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
     return offset;
    }

    const char * getType(){ return ROBOT_SET_MODE; };
    const char * getMD5(){ return "0b13460cb14006d3852674b4c614f25f"; };

  };

  class robot_set_mode {
    public:
    typedef robot_set_modeRequest Request;
    typedef robot_set_modeResponse Response;
  };

}
#endif
