#ifndef _ROS_SERVICE_robot_wait_for_user_input_event_h
#define _ROS_SERVICE_robot_wait_for_user_input_event_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char ROBOT_WAIT_FOR_USER_INPUT_EVENT[] = "webots_ros/robot_wait_for_user_input_event";

  class robot_wait_for_user_input_eventRequest : public ros::Msg
  {
    public:
      typedef int32_t _eventType_type;
      _eventType_type eventType;
      typedef int32_t _timeout_type;
      _timeout_type timeout;

    robot_wait_for_user_input_eventRequest():
      eventType(0),
      timeout(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_eventType;
      u_eventType.real = this->eventType;
      *(outbuffer + offset + 0) = (u_eventType.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_eventType.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_eventType.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_eventType.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->eventType);
      union {
        int32_t real;
        uint32_t base;
      } u_timeout;
      u_timeout.real = this->timeout;
      *(outbuffer + offset + 0) = (u_timeout.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_timeout.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_timeout.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_timeout.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->timeout);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_eventType;
      u_eventType.base = 0;
      u_eventType.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_eventType.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_eventType.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_eventType.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->eventType = u_eventType.real;
      offset += sizeof(this->eventType);
      union {
        int32_t real;
        uint32_t base;
      } u_timeout;
      u_timeout.base = 0;
      u_timeout.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_timeout.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_timeout.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_timeout.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->timeout = u_timeout.real;
      offset += sizeof(this->timeout);
     return offset;
    }

    const char * getType(){ return ROBOT_WAIT_FOR_USER_INPUT_EVENT; };
    const char * getMD5(){ return "3e70b4ac6cfb42776e6d4bc21b66e815"; };

  };

  class robot_wait_for_user_input_eventResponse : public ros::Msg
  {
    public:
      typedef int32_t _event_type;
      _event_type event;

    robot_wait_for_user_input_eventResponse():
      event(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_event;
      u_event.real = this->event;
      *(outbuffer + offset + 0) = (u_event.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_event.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_event.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_event.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->event);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_event;
      u_event.base = 0;
      u_event.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_event.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_event.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_event.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->event = u_event.real;
      offset += sizeof(this->event);
     return offset;
    }

    const char * getType(){ return ROBOT_WAIT_FOR_USER_INPUT_EVENT; };
    const char * getMD5(){ return "b2a9c605bb7a420089b02c6063322298"; };

  };

  class robot_wait_for_user_input_event {
    public:
    typedef robot_wait_for_user_input_eventRequest Request;
    typedef robot_wait_for_user_input_eventResponse Response;
  };

}
#endif
