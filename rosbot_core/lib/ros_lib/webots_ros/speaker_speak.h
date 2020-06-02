#ifndef _ROS_SERVICE_speaker_speak_h
#define _ROS_SERVICE_speaker_speak_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char SPEAKER_SPEAK[] = "webots_ros/speaker_speak";

  class speaker_speakRequest : public ros::Msg
  {
    public:
      typedef const char* _text_type;
      _text_type text;
      typedef float _volume_type;
      _volume_type volume;

    speaker_speakRequest():
      text(""),
      volume(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_text = strlen(this->text);
      varToArr(outbuffer + offset, length_text);
      offset += 4;
      memcpy(outbuffer + offset, this->text, length_text);
      offset += length_text;
      offset += serializeAvrFloat64(outbuffer + offset, this->volume);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_text;
      arrToVar(length_text, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_text; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_text-1]=0;
      this->text = (char *)(inbuffer + offset-1);
      offset += length_text;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->volume));
     return offset;
    }

    const char * getType(){ return SPEAKER_SPEAK; };
    const char * getMD5(){ return "bb1ebe440a2b05139ec89adc2289c3ea"; };

  };

  class speaker_speakResponse : public ros::Msg
  {
    public:
      typedef int8_t _success_type;
      _success_type success;

    speaker_speakResponse():
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

    const char * getType(){ return SPEAKER_SPEAK; };
    const char * getMD5(){ return "0b13460cb14006d3852674b4c614f25f"; };

  };

  class speaker_speak {
    public:
    typedef speaker_speakRequest Request;
    typedef speaker_speakResponse Response;
  };

}
#endif
