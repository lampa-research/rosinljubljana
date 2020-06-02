#ifndef _ROS_webots_ros_RecognitionObject_h
#define _ROS_webots_ros_RecognitionObject_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"

namespace webots_ros
{

  class RecognitionObject : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef geometry_msgs::Vector3 _position_type;
      _position_type position;
      typedef geometry_msgs::Quaternion _orientation_type;
      _orientation_type orientation;
      typedef geometry_msgs::Vector3 _position_on_image_type;
      _position_on_image_type position_on_image;
      typedef geometry_msgs::Vector3 _size_on_image_type;
      _size_on_image_type size_on_image;
      typedef int32_t _number_of_colors_type;
      _number_of_colors_type number_of_colors;
      uint32_t colors_length;
      typedef geometry_msgs::Vector3 _colors_type;
      _colors_type st_colors;
      _colors_type * colors;
      typedef const char* _model_type;
      _model_type model;

    RecognitionObject():
      header(),
      position(),
      orientation(),
      position_on_image(),
      size_on_image(),
      number_of_colors(0),
      colors_length(0), colors(NULL),
      model("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->position.serialize(outbuffer + offset);
      offset += this->orientation.serialize(outbuffer + offset);
      offset += this->position_on_image.serialize(outbuffer + offset);
      offset += this->size_on_image.serialize(outbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_number_of_colors;
      u_number_of_colors.real = this->number_of_colors;
      *(outbuffer + offset + 0) = (u_number_of_colors.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_number_of_colors.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_number_of_colors.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_number_of_colors.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->number_of_colors);
      *(outbuffer + offset + 0) = (this->colors_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->colors_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->colors_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->colors_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->colors_length);
      for( uint32_t i = 0; i < colors_length; i++){
      offset += this->colors[i].serialize(outbuffer + offset);
      }
      uint32_t length_model = strlen(this->model);
      varToArr(outbuffer + offset, length_model);
      offset += 4;
      memcpy(outbuffer + offset, this->model, length_model);
      offset += length_model;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->position.deserialize(inbuffer + offset);
      offset += this->orientation.deserialize(inbuffer + offset);
      offset += this->position_on_image.deserialize(inbuffer + offset);
      offset += this->size_on_image.deserialize(inbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_number_of_colors;
      u_number_of_colors.base = 0;
      u_number_of_colors.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_number_of_colors.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_number_of_colors.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_number_of_colors.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->number_of_colors = u_number_of_colors.real;
      offset += sizeof(this->number_of_colors);
      uint32_t colors_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      colors_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      colors_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      colors_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->colors_length);
      if(colors_lengthT > colors_length)
        this->colors = (geometry_msgs::Vector3*)realloc(this->colors, colors_lengthT * sizeof(geometry_msgs::Vector3));
      colors_length = colors_lengthT;
      for( uint32_t i = 0; i < colors_length; i++){
      offset += this->st_colors.deserialize(inbuffer + offset);
        memcpy( &(this->colors[i]), &(this->st_colors), sizeof(geometry_msgs::Vector3));
      }
      uint32_t length_model;
      arrToVar(length_model, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_model; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_model-1]=0;
      this->model = (char *)(inbuffer + offset-1);
      offset += length_model;
     return offset;
    }

    const char * getType(){ return "webots_ros/RecognitionObject"; };
    const char * getMD5(){ return "642183f1eab2edbfa9c2ae808be707c2"; };

  };

}
#endif
