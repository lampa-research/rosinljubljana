#ifndef _ROS_SERVICE_set_float_array_h
#define _ROS_SERVICE_set_float_array_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char SET_FLOAT_ARRAY[] = "webots_ros/set_float_array";

  class set_float_arrayRequest : public ros::Msg
  {
    public:
      uint32_t values_length;
      typedef float _values_type;
      _values_type st_values;
      _values_type * values;

    set_float_arrayRequest():
      values_length(0), values(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->values_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->values_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->values_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->values_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->values_length);
      for( uint32_t i = 0; i < values_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->values[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t values_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      values_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      values_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      values_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->values_length);
      if(values_lengthT > values_length)
        this->values = (float*)realloc(this->values, values_lengthT * sizeof(float));
      values_length = values_lengthT;
      for( uint32_t i = 0; i < values_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_values));
        memcpy( &(this->values[i]), &(this->st_values), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return SET_FLOAT_ARRAY; };
    const char * getMD5(){ return "b9163d7c678dcd669317e43e46b63d96"; };

  };

  class set_float_arrayResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    set_float_arrayResponse():
      success(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
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
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
     return offset;
    }

    const char * getType(){ return SET_FLOAT_ARRAY; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class set_float_array {
    public:
    typedef set_float_arrayRequest Request;
    typedef set_float_arrayResponse Response;
  };

}
#endif
