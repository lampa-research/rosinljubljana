#ifndef _ROS_SERVICE_speaker_play_sound_h
#define _ROS_SERVICE_speaker_play_sound_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char SPEAKER_PLAY_SOUND[] = "webots_ros/speaker_play_sound";

  class speaker_play_soundRequest : public ros::Msg
  {
    public:
      typedef const char* _sound_type;
      _sound_type sound;
      typedef float _volume_type;
      _volume_type volume;
      typedef float _pitch_type;
      _pitch_type pitch;
      typedef float _balance_type;
      _balance_type balance;
      typedef int8_t _loop_type;
      _loop_type loop;

    speaker_play_soundRequest():
      sound(""),
      volume(0),
      pitch(0),
      balance(0),
      loop(0)
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
      offset += serializeAvrFloat64(outbuffer + offset, this->volume);
      offset += serializeAvrFloat64(outbuffer + offset, this->pitch);
      offset += serializeAvrFloat64(outbuffer + offset, this->balance);
      union {
        int8_t real;
        uint8_t base;
      } u_loop;
      u_loop.real = this->loop;
      *(outbuffer + offset + 0) = (u_loop.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->loop);
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
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->volume));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->pitch));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->balance));
      union {
        int8_t real;
        uint8_t base;
      } u_loop;
      u_loop.base = 0;
      u_loop.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->loop = u_loop.real;
      offset += sizeof(this->loop);
     return offset;
    }

    const char * getType(){ return SPEAKER_PLAY_SOUND; };
    const char * getMD5(){ return "6dbd4a93693dce0672c3d423cfbc9b11"; };

  };

  class speaker_play_soundResponse : public ros::Msg
  {
    public:
      typedef int8_t _success_type;
      _success_type success;

    speaker_play_soundResponse():
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

    const char * getType(){ return SPEAKER_PLAY_SOUND; };
    const char * getMD5(){ return "0b13460cb14006d3852674b4c614f25f"; };

  };

  class speaker_play_sound {
    public:
    typedef speaker_play_soundRequest Request;
    typedef speaker_play_soundResponse Response;
  };

}
#endif
