#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <dynamic_reconfigure/server.h>
#include <camera_exercise/GreenConfig.h>

using namespace cv;
using namespace std;

class ImageConverter
{
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;
    int low = 40;
    int high = 100;
    dynamic_reconfigure::Server<camera_exercise::GreenConfig> server;

public:
    ImageConverter() : it_(nh_)
    {
        // Subscrive to input video feed and publish output video feed
        image_sub_ = it_.subscribe("/camera/image_raw", 1,
                                   &ImageConverter::imageCb, this);
        image_pub_ = it_.advertise("/camera/output_video", 1);

        dynamic_reconfigure::Server<camera_exercise::GreenConfig>::CallbackType f;

        f = boost::bind(&ImageConverter::callback, this, _1, _2);
        server.setCallback(f);
    }

    void callback(camera_exercise::GreenConfig &config, uint32_t level)
    {
        this->low = (int)config.low;
        this->high = (int)config.high;
        ROS_INFO("Reconfigure Request: %d %d",
                 this->low, this->high);
    }

    void imageCb(const sensor_msgs::ImageConstPtr &msg)
    {
        cv_bridge::CvImagePtr cv_ptr;
        try
        {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception &e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }

        // Convert the image to HSV color space, filter, convert back to BGR
        GaussianBlur(cv_ptr->image, cv_ptr->image, Size(5, 5), 0, 0);
        cvtColor(cv_ptr->image, cv_ptr->image, CV_BGR2HSV);

        ROS_INFO_STREAM("Low: " << this->low << " high: " << this->high);

        inRange(cv_ptr->image, Scalar(this->low, 0, 0), Scalar(this->high, 255, 255), cv_ptr->image);

        // Find contours and mark them in red
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(cv_ptr->image, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
        cvtColor(cv_ptr->image, cv_ptr->image, CV_GRAY2BGR);
        for (int i = 0; i < contours.size(); i++)
        {
            Scalar color = Scalar(0, 0, 255);
            drawContours(cv_ptr->image, contours, i, color, 2, 8, hierarchy, 0, Point());
        }

        // Output modified video stream
        image_pub_.publish(cv_ptr->toImageMsg());
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_converter");
    ImageConverter ic;

    ros::spin();
    return 0;
}