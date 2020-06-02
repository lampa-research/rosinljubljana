#ifndef _ROS_SERVICE_motor_set_control_pid_h
#define _ROS_SERVICE_motor_set_control_pid_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char MOTOR_SET_CONTROL_PID[] = "webots_ros/motor_set_control_pid";

  class motor_set_control_pidRequest : public ros::Msg
  {
    public:
      typedef float _controlp_type;
      _controlp_type controlp;
      typedef float _controli_type;
      _controli_type controli;
      typedef float _controld_type;
      _controld_type controld;

    motor_set_control_pidRequest():
      controlp(0),
      controli(0),
      controld(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->controlp);
      offset += serializeAvrFloat64(outbuffer + offset, this->controli);
      offset += serializeAvrFloat64(outbuffer + offset, this->controld);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->controlp));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->controli));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->controld));
     return offset;
    }

    const char * getType(){ return MOTOR_SET_CONTROL_PID; };
    const char * getMD5(){ return "1ebf8f7154a3c8eec118cec294f2c32c"; };

  };

  class motor_set_control_pidResponse : public ros::Msg
  {
    public:
      typedef int8_t _success_type;
      _success_type success;

    motor_set_control_pidResponse():
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

    const char * getType(){ return MOTOR_SET_CONTROL_PID; };
    const char * getMD5(){ return "0b13460cb14006d3852674b4c614f25f"; };

  };

  class motor_set_control_pid {
    public:
    typedef motor_set_control_pidRequest Request;
    typedef motor_set_control_pidResponse Response;
  };

}
#endif
