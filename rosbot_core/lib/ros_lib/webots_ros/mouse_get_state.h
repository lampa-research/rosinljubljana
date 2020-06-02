#ifndef _ROS_SERVICE_mouse_get_state_h
#define _ROS_SERVICE_mouse_get_state_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char MOUSE_GET_STATE[] = "webots_ros/mouse_get_state";

  class mouse_get_stateRequest : public ros::Msg
  {
    public:
      typedef uint8_t _ask_type;
      _ask_type ask;

    mouse_get_stateRequest():
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

    const char * getType(){ return MOUSE_GET_STATE; };
    const char * getMD5(){ return "f9df5232b65af94f73f79fe6d84301bb"; };

  };

  class mouse_get_stateResponse : public ros::Msg
  {
    public:
      typedef uint8_t _left_type;
      _left_type left;
      typedef uint8_t _middle_type;
      _middle_type middle;
      typedef uint8_t _right_type;
      _right_type right;
      typedef float _u_type;
      _u_type u;
      typedef float _v_type;
      _v_type v;
      typedef float _x_type;
      _x_type x;
      typedef float _y_type;
      _y_type y;
      typedef float _z_type;
      _z_type z;

    mouse_get_stateResponse():
      left(0),
      middle(0),
      right(0),
      u(0),
      v(0),
      x(0),
      y(0),
      z(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->left >> (8 * 0)) & 0xFF;
      offset += sizeof(this->left);
      *(outbuffer + offset + 0) = (this->middle >> (8 * 0)) & 0xFF;
      offset += sizeof(this->middle);
      *(outbuffer + offset + 0) = (this->right >> (8 * 0)) & 0xFF;
      offset += sizeof(this->right);
      offset += serializeAvrFloat64(outbuffer + offset, this->u);
      offset += serializeAvrFloat64(outbuffer + offset, this->v);
      offset += serializeAvrFloat64(outbuffer + offset, this->x);
      offset += serializeAvrFloat64(outbuffer + offset, this->y);
      offset += serializeAvrFloat64(outbuffer + offset, this->z);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->left =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->left);
      this->middle =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->middle);
      this->right =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->right);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->u));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->v));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->x));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->y));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->z));
     return offset;
    }

    const char * getType(){ return MOUSE_GET_STATE; };
    const char * getMD5(){ return "17a814b3dc69927476b5cde7968ba299"; };

  };

  class mouse_get_state {
    public:
    typedef mouse_get_stateRequest Request;
    typedef mouse_get_stateResponse Response;
  };

}
#endif
