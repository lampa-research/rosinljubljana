#ifndef _ROS_SERVICE_node_get_field_h
#define _ROS_SERVICE_node_get_field_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char NODE_GET_FIELD[] = "webots_ros/node_get_field";

  class node_get_fieldRequest : public ros::Msg
  {
    public:
      typedef uint64_t _node_type;
      _node_type node;
      typedef const char* _fieldName_type;
      _fieldName_type fieldName;

    node_get_fieldRequest():
      node(0),
      fieldName("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->node >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->node >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->node >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->node >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (this->node >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (this->node >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (this->node >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (this->node >> (8 * 7)) & 0xFF;
      offset += sizeof(this->node);
      uint32_t length_fieldName = strlen(this->fieldName);
      varToArr(outbuffer + offset, length_fieldName);
      offset += 4;
      memcpy(outbuffer + offset, this->fieldName, length_fieldName);
      offset += length_fieldName;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->node =  ((uint64_t) (*(inbuffer + offset)));
      this->node |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->node |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->node |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->node |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      this->node |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      this->node |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      this->node |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      offset += sizeof(this->node);
      uint32_t length_fieldName;
      arrToVar(length_fieldName, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_fieldName; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_fieldName-1]=0;
      this->fieldName = (char *)(inbuffer + offset-1);
      offset += length_fieldName;
     return offset;
    }

    const char * getType(){ return NODE_GET_FIELD; };
    const char * getMD5(){ return "2d4687ce20fc4847078a8ce0c31e1e6b"; };

  };

  class node_get_fieldResponse : public ros::Msg
  {
    public:
      typedef uint64_t _field_type;
      _field_type field;

    node_get_fieldResponse():
      field(0)
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
     return offset;
    }

    const char * getType(){ return NODE_GET_FIELD; };
    const char * getMD5(){ return "6e05f2ccbc5e22655a0890e2557862bd"; };

  };

  class node_get_field {
    public:
    typedef node_get_fieldRequest Request;
    typedef node_get_fieldResponse Response;
  };

}
#endif
