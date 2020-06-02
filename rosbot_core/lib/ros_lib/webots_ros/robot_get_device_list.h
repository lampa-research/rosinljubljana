#ifndef _ROS_SERVICE_robot_get_device_list_h
#define _ROS_SERVICE_robot_get_device_list_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace webots_ros
{

static const char ROBOT_GET_DEVICE_LIST[] = "webots_ros/robot_get_device_list";

  class robot_get_device_listRequest : public ros::Msg
  {
    public:
      typedef uint8_t _ask_type;
      _ask_type ask;

    robot_get_device_listRequest():
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

    const char * getType(){ return ROBOT_GET_DEVICE_LIST; };
    const char * getMD5(){ return "f9df5232b65af94f73f79fe6d84301bb"; };

  };

  class robot_get_device_listResponse : public ros::Msg
  {
    public:
      uint32_t list_length;
      typedef char* _list_type;
      _list_type st_list;
      _list_type * list;

    robot_get_device_listResponse():
      list_length(0), list(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->list_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->list_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->list_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->list_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->list_length);
      for( uint32_t i = 0; i < list_length; i++){
      uint32_t length_listi = strlen(this->list[i]);
      varToArr(outbuffer + offset, length_listi);
      offset += 4;
      memcpy(outbuffer + offset, this->list[i], length_listi);
      offset += length_listi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t list_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      list_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      list_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      list_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->list_length);
      if(list_lengthT > list_length)
        this->list = (char**)realloc(this->list, list_lengthT * sizeof(char*));
      list_length = list_lengthT;
      for( uint32_t i = 0; i < list_length; i++){
      uint32_t length_st_list;
      arrToVar(length_st_list, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_list; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_list-1]=0;
      this->st_list = (char *)(inbuffer + offset-1);
      offset += length_st_list;
        memcpy( &(this->list[i]), &(this->st_list), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return ROBOT_GET_DEVICE_LIST; };
    const char * getMD5(){ return "8e09fa9aad51508cfdcab3b64f048ce0"; };

  };

  class robot_get_device_list {
    public:
    typedef robot_get_device_listRequest Request;
    typedef robot_get_device_listResponse Response;
  };

}
#endif
