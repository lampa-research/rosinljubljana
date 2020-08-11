#include <ros/ros.h>
#include <std_srvs/SetBool.h>
#include <curl/curl.h>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <typeinfo>


using namespace std;
string robot_ip, final_url, io_op, io_type, io_idx, io_val;


static std::vector<std::string> explode(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }
    std::cout << s <<endl;
    std::copy(begin(result), end(result), std::ostream_iterator<string>(std::cout, "\n"));

    return result;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool set_io_service(std_srvs::SetBool::Request  &req, 
                    std_srvs::SetBool::Response &res)
{
  if(req.data)
    io_val = "1";
    else
    io_val = "0";

  final_url = "http://" + robot_ip + "io_op=" + io_op + "&io_type=" + io_type + "&io_idx=" + io_idx + "&io_val=" + io_val;
  CURL *curl;
  CURLcode result;
  string readBuffer;

  curl = curl_easy_init();
  if(curl) 
  {
    //  curl_easy_setopt(curl, CURLOPT_URL, 
    //  "http://192.167.1.105/KAREL/ros_cgio?io_op=write&io_type=9&io_idx=8&io_val=1"); // CLOSE gripper
    curl_easy_setopt(curl, CURLOPT_URL, final_url.c_str()); // open/close operation
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    result = curl_easy_perform(curl);
    ROS_INFO("Called this url: %s", final_url.c_str());
    
    // Check for errors 
    if(result != CURLE_OK)
    {
        ROS_WARN("call to %s failed\nError: %s\n",
                  final_url.c_str(), curl_easy_strerror(result));

        res.success = false;
        res.message = string("Failed to put the desired input/output values. ")
                      + curl_easy_strerror(result);
        return true;
    }
    auto v = explode(readBuffer, '"');

    if (v[3] == "success")
    {
        res.success = true;
        res.message = "Succeeded to put the desired input/output values.";
    } else {
        res.success = false;
        res.message = "Failed to put the desired input/output values.";
    }
    // always cleanup 
    curl_easy_cleanup(curl);
  }
  
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "gripper_controller_node");
  ros::NodeHandle n;
  // nastavitev parametrov
  io_op = "write"; // read/write
  io_type = "9";   // type
  io_idx = "8";    // port

  // nastavi ip ce je podan sicer uporabi tega
  n.param<std::string>("robot_ip", robot_ip, "192.167.1.105/KAREL/ros_cgio?");
  
  ros::ServiceServer service = n.advertiseService("gripper_srv", set_io_service);

  ROS_INFO("Ready! url:");
  ROS_INFO_STREAM("http://" + robot_ip + "io_op=" + io_op + 
                  "&io_type=" + io_type + "&io_idx=" + io_idx + "&io_val=<0/1>");
  
  ros::spin();
}