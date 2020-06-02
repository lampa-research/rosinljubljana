#ifndef _ROS_SERVICE_speaker_is_sound_playing_h
#define _ROS_SERVICE_speaker_is_sound_playing_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char SPEAKER_IS_SOUND_PLAYING[] = "webots_ros/speaker_is_sound_playing";

  class speaker_is_sound_playingRequest : public ros::Msg
  {
    public:
      typedef const char* _sound_type;
      _sound_type sound;

    speaker_is_sound_playingRequest():
      sound("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_sound = strlen(this->sound);
      varToArr(outbuffer + offset, length_sound);
      offset += 4;
      memcpy(outbuffer + offset, this->sound, length_sound);
      offset += length_sound;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_sound;
      arrToVar(length_sound, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_sound; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_sound-1]=0;
      this->sound = (char *)(inbuffer + offset-1);
      offset += length_sound;
     return offset;
    }

    const char * getType(){ return SPEAKER_IS_SOUND_PLAYING; };
    const char * getMD5(){ return "6f8594d24e685f0ca0a97807507c3483"; };

  };

  class speaker_is_sound_playingResponse : public ros::Msg
  {
    public:
      typedef bool _value_type;
      _value_type value;

    speaker_is_sound_playingResponse():
      value(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_value;
      u_value.real = this->value;
      *(outbuffer + offset + 0) = (u_value.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->value);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_value;
      u_value.base = 0;
      u_value.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->value = u_value.real;
      offset += sizeof(this->value);
     return offset;
    }

    const char * getType(){ return SPEAKER_IS_SOUND_PLAYING; };
    const char * getMD5(){ return "e431d687bf4b2c65fbd94b12ae0cb5d9"; };

  };

  class speaker_is_sound_playing {
    public:
    typedef speaker_is_sound_playingRequest Request;
    typedef speaker_is_sound_playingResponse Response;
  };

}
#endif
