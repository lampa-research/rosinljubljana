#!/usr/bin/env python

import functools
import rospy

from nav_msgs.msg import Odometry

rospy.init_node("delay")

pub = rospy.Publisher("odom_delayed", Odometry, queue_size=4)

def delayed_callback(msg, event):
    msg.header.frame_id="odom_delayed"
    msg.child_frame_id="odom_delayed"
    pub.publish(msg)

def callback(msg):
    timer = rospy.Timer(rospy.Duration(2.5),
                        functools.partial(delayed_callback, msg),
                        oneshot=True)

sub = rospy.Subscriber("odom", Odometry, callback, queue_size=4)

rospy.spin()