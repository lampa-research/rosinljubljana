#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_srvs/SetBool.h>
#include <curl/curl.h>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <typeinfo>

using namespace std;
bool sim;
string robot_ip, io_op, io_type, io_idx, io_val;

ros::Publisher f1_pub;
ros::Publisher f2_pub;

static std::vector<std::string> explode(std::string const &s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim);)
    {
        result.push_back(std::move(token));
    }
    std::cout << s << endl;
    std::copy(begin(result), end(result), std::ostream_iterator<string>(std::cout, "\n"));

    return result;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

bool gripper(std_srvs::SetBool::Request &req,
             std_srvs::SetBool::Response &res)
{
    if (sim)
    {
        std_msgs::Float64 msg;
        if (req.data)
        {
            msg.data = 0.006;
            f1_pub.publish(msg);
            f2_pub.publish(msg);
        }
        else
        {
            msg.data = 0.00;
            f1_pub.publish(msg);
            f2_pub.publish(msg);
        }
        res.success = true;
    }
    else
    {
        if (req.data)
            io_val = "1";
        else
            io_val = "0";

        string final_url = "http://" + robot_ip + "io_op=" + io_op + "&io_type=" + io_type + "&io_idx=" + io_idx + "&io_val=" + io_val;
        CURL *curl;
        CURLcode result;
        string readBuffer;

        curl = curl_easy_init();
        if (curl)
        {
            //  curl_easy_setopt(curl, CURLOPT_URL,
            //  "http://192.167.1.122/KAREL/ros_cgio?io_op=write&io_type=9&io_idx=8&io_val=1"); // CLOSE gripper
            curl_easy_setopt(curl, CURLOPT_URL, final_url.c_str()); // open/close operation
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            result = curl_easy_perform(curl);
            // ROS_INFO("Called this url: %s", final_url.c_str());

            // Check for errors
            if (result != CURLE_OK)
            {
                ROS_WARN("call to %s failed\nError: %s\n",
                         final_url.c_str(), curl_easy_strerror(result));

                res.success = false;
                res.message = string("Failed to put the desired input/output values. ") + curl_easy_strerror(result);
                return true;
            }
            auto v = explode(readBuffer, '"');

            if (v[3] == "success")
            {
                res.success = true;
                res.message = "Succeeded to put the desired input/output values.";
            }
            else
            {
                res.success = false;
                res.message = "Failed to put the desired input/output values.";
            }
            curl_easy_cleanup(curl);
        }
    }

    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "schunk_gripper");
    ros::NodeHandle n("~");

    n.param<string>("robot_ip", robot_ip, "192.167.1.122/KAREL/ros_cgio?");
    n.param<string>("io_op", io_op, "write");
    n.param<string>("io_type", io_type, "9");
    n.param<string>("io_idx", io_idx, "8");
    n.param<bool>("sim", sim, false);

    f1_pub = n.advertise<std_msgs::Float64>("finger_joint1_controller/command", 1000);
    f2_pub = n.advertise<std_msgs::Float64>("finger_joint2_controller/command", 1000);
    ros::ServiceServer service = n.advertiseService("gripper_closed", gripper);
    ros::spin();

    return 0;
}
