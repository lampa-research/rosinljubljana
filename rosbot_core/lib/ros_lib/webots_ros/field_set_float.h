#ifndef _ROS_SERVICE_field_set_float_h
#define _ROS_SERVICE_field_set_float_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char FIELD_SET_FLOAT[] = "webots_ros/field_set_float";

  class field_set_floatRequest : public ros::Msg
  {
    public:
      typedef uint64_t _field_type;
      _field_type field;
      typedef int32_t _index_type;
      _index_type index;
      typedef float _value_type;
      _value_type value;

    field_set_floatRequest():
      field(0),
      index(0),
      value(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->field >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->field >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->field >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->field >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (this->field >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (this->field >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (this->field >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (this->field >> (8 * 7)) & 0xFF;
      offset += sizeof(this->field);
      union {
        int32_t real;
        uint32_t base;
      } u_index;
      u_index.real = this->index;
      *(outbuffer + offset + 0) = (u_index.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_index.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_index.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_index.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->index);
      offset += serializeAvrFloat64(outbuffer + offset, this->value);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->field =  ((uint64_t) (*(inbuffer + offset)));
      this->field |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->field |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->field |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->field |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      this->field |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      this->field |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      this->field |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      offset += sizeof(this->field);
      union {
        int32_t real;
        uint32_t base;
      } u_index;
      u_index.base = 0;
      u_index.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_index.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_index.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_index.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->index = u_index.real;
      offset += sizeof(this->index);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->value));
     return offset;
    }

    const char * getType(){ return FIELD_SET_FLOAT; };
    const char * getMD5(){ return "7bd2d2b340e1cba56d82c440d4c7c9ce"; };

  };

  class field_set_floatResponse : public ros::Msg
  {
    public:
      typedef int32_t _success_type;
      _success_type success;

    field_set_floatResponse():
      success(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_success.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_success.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_success.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->success);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_success.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_success.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_success.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->success = u_success.real;
      offset += sizeof(this->success);
     return offset;
    }

    const char * getType(){ return FIELD_SET_FLOAT; };
    const char * getMD5(){ return "3c2bcf2ff0894cb3058b1bf4c8c4175a"; };

  };

  class field_set_float {
    public:
    typedef field_set_floatRequest Request;
    typedef field_set_floatResponse Response;
  };

}
#endif
