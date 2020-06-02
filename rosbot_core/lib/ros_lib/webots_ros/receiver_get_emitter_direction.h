#ifndef _ROS_SERVICE_receiver_get_emitter_direction_h
#define _ROS_SERVICE_receiver_get_emitter_direction_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char RECEIVER_GET_EMITTER_DIRECTION[] = "webots_ros/receiver_get_emitter_direction";

  class receiver_get_emitter_directionRequest : public ros::Msg
  {
    public:
      typedef uint8_t _ask_type;
      _ask_type ask;

    receiver_get_emitter_directionRequest():
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

    const char * getType(){ return RECEIVER_GET_EMITTER_DIRECTION; };
    const char * getMD5(){ return "f9df5232b65af94f73f79fe6d84301bb"; };

  };

  class receiver_get_emitter_directionResponse : public ros::Msg
  {
    public:
      uint32_t direction_length;
      typedef float _direction_type;
      _direction_type st_direction;
      _direction_type * direction;

    receiver_get_emitter_directionResponse():
      direction_length(0), direction(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->direction_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->direction_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->direction_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->direction_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->direction_length);
      for( uint32_t i = 0; i < direction_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->direction[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t direction_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      direction_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      direction_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      direction_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->direction_length);
      if(direction_lengthT > direction_length)
        this->direction = (float*)realloc(this->direction, direction_lengthT * sizeof(float));
      direction_length = direction_lengthT;
      for( uint32_t i = 0; i < direction_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_direction));
        memcpy( &(this->direction[i]), &(this->st_direction), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return RECEIVER_GET_EMITTER_DIRECTION; };
    const char * getMD5(){ return "3f61a8da1ee4e83406fd5157b36d50cb"; };

  };

  class receiver_get_emitter_direction {
    public:
    typedef receiver_get_emitter_directionRequest Request;
    typedef receiver_get_emitter_directionResponse Response;
  };

}
#endif
