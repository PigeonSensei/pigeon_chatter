#include <ros/ros.h>
#include <std_msgs/String.h>
#include <time.h>
#include <pwd.h>

#include "chatter/ChattMsg.h"1

std::string GetTimeNow()
{
  time_t rawtime;
  struct tm  *tm;
  time(&rawtime);
  tm = localtime(&rawtime);
  std::string hour = std::to_string(tm->tm_hour);
  std::string min = std::to_string(tm->tm_min);
  std::string sec = std::to_string(tm->tm_sec);

  std::string now_time = hour + ":" + min + ":" + sec;

  return now_time;
}

bool ChattMsgServiceCallback(chatter::ChattMsg::Request &req,
                                    chatter::ChattMsg::Response &res)
{
  std::cout << "[" << GetTimeNow() << "] " << req.name << " : " << req.message << std::endl;
  res.result = "true";
  res.message = "Send Message!";
  return true;
}


int main(int argc, char **argv)
{
  uid_t user_id;
  struct passwd *user_pw;

  user_id = getuid();
  user_pw = getpwuid(user_id);

  std::string my_name = user_pw->pw_name;

  time_t time_now;
  time_now = time(NULL);

  std::string time_stamp = std::to_string(time_now);
  std::string node_name = "chatter_service_server_node_" + my_name + "_" + time_stamp; 

  ros::init(argc, argv, node_name);
  ros::NodeHandle n;

  ros::Rate loop_rate(10);

  ros::ServiceServer service_server_chatt_msg = n.advertiseService("chatt_msg", ChattMsgServiceCallback);

  while(ros::ok())
  {
    ros::spinOnce();

    loop_rate.sleep();
  }
  return 0;
}
