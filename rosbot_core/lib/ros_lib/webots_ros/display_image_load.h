#ifndef _ROS_SERVICE_display_image_load_h
#define _ROS_SERVICE_display_image_load_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char DISPLAY_IMAGE_LOAD[] = "webots_ros/display_image_load";

  class display_image_loadRequest : public ros::Msg
  {
    public:
      typedef const char* _filename_type;
      _filename_type filename;

    display_image_loadRequest():
      filename("")
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
     return offset;
    }

    const char * getType(){ return DISPLAY_IMAGE_LOAD; };
    const char * getMD5(){ return "030824f52a0628ead956fb9d67e66ae9"; };

  };

  class display_image_loadResponse : public ros::Msg
  {
    public:
      typedef uint64_t _ir_type;
      _ir_type ir;

    display_image_loadResponse():
      ir(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->ir >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->ir >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->ir >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->ir >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (this->ir >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (this->ir >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (this->ir >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (this->ir >> (8 * 7)) & 0xFF;
      offset += sizeof(this->ir);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->ir =  ((uint64_t) (*(inbuffer + offset)));
      this->ir |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->ir |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->ir |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ir |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      this->ir |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      this->ir |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      this->ir |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      offset += sizeof(this->ir);
     return offset;
    }

    const char * getType(){ return DISPLAY_IMAGE_LOAD; };
    const char * getMD5(){ return "062bd6ec8c99fd70e30cc24256f9226a"; };

  };

  class display_image_load {
    public:
    typedef display_image_loadRequest Request;
    typedef display_image_loadResponse Response;
  };

}
#endif
