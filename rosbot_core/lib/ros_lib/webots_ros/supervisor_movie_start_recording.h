#ifndef _ROS_SERVICE_supervisor_movie_start_recording_h
#define _ROS_SERVICE_supervisor_movie_start_recording_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char SUPERVISOR_MOVIE_START_RECORDING[] = "webots_ros/supervisor_movie_start_recording";

  class supervisor_movie_start_recordingRequest : public ros::Msg
  {
    public:
      typedef const char* _filename_type;
      _filename_type filename;
      typedef int32_t _width_type;
      _width_type width;
      typedef int32_t _height_type;
      _height_type height;
      typedef int32_t _codec_type;
      _codec_type codec;
      typedef int32_t _quality_type;
      _quality_type quality;
      typedef int32_t _acceleration_type;
      _acceleration_type acceleration;
      typedef uint8_t _caption_type;
      _caption_type caption;

    supervisor_movie_start_recordingRequest():
      filename(""),
      width(0),
      height(0),
      codec(0),
      quality(0),
      acceleration(0),
      caption(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_filename = strlen(this->filename);
      varToArr(outbuffer + offset, length_filename);
      offset += 4;
      memcpy(outbuffer + offset, this->filename, length_filename);
      offset += length_filename;
      union {
        int32_t real;
        uint32_t base;
      } u_width;
      u_width.real = this->width;
      *(outbuffer + offset + 0) = (u_width.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_width.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_width.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_width.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->width);
      union {
        int32_t real;
        uint32_t base;
      } u_height;
      u_height.real = this->height;
      *(outbuffer + offset + 0) = (u_height.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_height.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_height.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_height.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->height);
      union {
        int32_t real;
        uint32_t base;
      } u_codec;
      u_codec.real = this->codec;
      *(outbuffer + offset + 0) = (u_codec.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_codec.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_codec.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_codec.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->codec);
      union {
        int32_t real;
        uint32_t base;
      } u_quality;
      u_quality.real = this->quality;
      *(outbuffer + offset + 0) = (u_quality.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_quality.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_quality.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_quality.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->quality);
      union {
        int32_t real;
        uint32_t base;
      } u_acceleration;
      u_acceleration.real = this->acceleration;
      *(outbuffer + offset + 0) = (u_acceleration.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_acceleration.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_acceleration.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_acceleration.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->acceleration);
      *(outbuffer + offset + 0) = (this->caption >> (8 * 0)) & 0xFF;
      offset += sizeof(this->caption);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_filename;
      arrToVar(length_filename, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_filename; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_filename-1]=0;
      this->filename = (char *)(inbuffer + offset-1);
      offset += length_filename;
      union {
        int32_t real;
        uint32_t base;
      } u_width;
      u_width.base = 0;
      u_width.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_width.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_width.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_width.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->width = u_width.real;
      offset += sizeof(this->width);
      union {
        int32_t real;
        uint32_t base;
      } u_height;
      u_height.base = 0;
      u_height.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_height.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_height.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_height.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->height = u_height.real;
      offset += sizeof(this->height);
      union {
        int32_t real;
        uint32_t base;
      } u_codec;
      u_codec.base = 0;
      u_codec.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_codec.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_codec.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_codec.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->codec = u_codec.real;
      offset += sizeof(this->codec);
      union {
        int32_t real;
        uint32_t base;
      } u_quality;
      u_quality.base = 0;
      u_quality.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_quality.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_quality.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_quality.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->quality = u_quality.real;
      offset += sizeof(this->quality);
      union {
        int32_t real;
        uint32_t base;
      } u_acceleration;
      u_acceleration.base = 0;
      u_acceleration.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_acceleration.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_acceleration.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_acceleration.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->acceleration = u_acceleration.real;
      offset += sizeof(this->acceleration);
      this->caption =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->caption);
     return offset;
    }

    const char * getType(){ return SUPERVISOR_MOVIE_START_RECORDING; };
    const char * getMD5(){ return "6002a2a6b3b34251dd3d092b3750f050"; };

  };

  class supervisor_movie_start_recordingResponse : public ros::Msg
  {
    public:
      typedef int8_t _success_type;
      _success_type success;

    supervisor_movie_start_recordingResponse():
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

    const char * getType(){ return SUPERVISOR_MOVIE_START_RECORDING; };
    const char * getMD5(){ return "0b13460cb14006d3852674b4c614f25f"; };

  };

  class supervisor_movie_start_recording {
    public:
    typedef supervisor_movie_start_recordingRequest Request;
    typedef supervisor_movie_start_recordingResponse Response;
  };

}
#endif
