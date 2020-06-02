#ifndef _ROS_SERVICE_supervisor_set_label_h
#define _ROS_SERVICE_supervisor_set_label_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char SUPERVISOR_SET_LABEL[] = "webots_ros/supervisor_set_label";

  class supervisor_set_labelRequest : public ros::Msg
  {
    public:
      typedef int32_t _id_type;
      _id_type id;
      typedef const char* _label_type;
      _label_type label;
      typedef float _xpos_type;
      _xpos_type xpos;
      typedef float _ypos_type;
      _ypos_type ypos;
      typedef float _size_type;
      _size_type size;
      typedef int32_t _color_type;
      _color_type color;
      typedef float _transparency_type;
      _transparency_type transparency;
      typedef const char* _font_type;
      _font_type font;

    supervisor_set_labelRequest():
      id(0),
      label(""),
      xpos(0),
      ypos(0),
      size(0),
      color(0),
      transparency(0),
      font("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_id;
      u_id.real = this->id;
      *(outbuffer + offset + 0) = (u_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_id.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_id.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_id.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->id);
      uint32_t length_label = strlen(this->label);
      varToArr(outbuffer + offset, length_label);
      offset += 4;
      memcpy(outbuffer + offset, this->label, length_label);
      offset += length_label;
      offset += serializeAvrFloat64(outbuffer + offset, this->xpos);
      offset += serializeAvrFloat64(outbuffer + offset, this->ypos);
      offset += serializeAvrFloat64(outbuffer + offset, this->size);
      union {
        int32_t real;
        uint32_t base;
      } u_color;
      u_color.real = this->color;
      *(outbuffer + offset + 0) = (u_color.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_color.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_color.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_color.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->color);
      offset += serializeAvrFloat64(outbuffer + offset, this->transparency);
      uint32_t length_font = strlen(this->font);
      varToArr(outbuffer + offset, length_font);
      offset += 4;
      memcpy(outbuffer + offset, this->font, length_font);
      offset += length_font;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_id;
      u_id.base = 0;
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->id = u_id.real;
      offset += sizeof(this->id);
      uint32_t length_label;
      arrToVar(length_label, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_label; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_label-1]=0;
      this->label = (char *)(inbuffer + offset-1);
      offset += length_label;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->xpos));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->ypos));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->size));
      union {
        int32_t real;
        uint32_t base;
      } u_color;
      u_color.base = 0;
      u_color.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_color.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_color.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_color.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->color = u_color.real;
      offset += sizeof(this->color);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->transparency));
      uint32_t length_font;
      arrToVar(length_font, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_font; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_font-1]=0;
      this->font = (char *)(inbuffer + offset-1);
      offset += length_font;
     return offset;
    }

    const char * getType(){ return SUPERVISOR_SET_LABEL; };
    const char * getMD5(){ return "383d62b53c2b62c441c9996504515955"; };

  };

  class supervisor_set_labelResponse : public ros::Msg
  {
    public:
      typedef int8_t _success_type;
      _success_type success;

    supervisor_set_labelResponse():
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

    const char * getType(){ return SUPERVISOR_SET_LABEL; };
    const char * getMD5(){ return "0b13460cb14006d3852674b4c614f25f"; };

  };

  class supervisor_set_label {
    public:
    typedef supervisor_set_labelRequest Request;
    typedef supervisor_set_labelResponse Response;
  };

}
#endif
