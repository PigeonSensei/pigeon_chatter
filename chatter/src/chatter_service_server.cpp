#include <ros/ros.h>
#include <std_msgs/String.h>
#include <time.h>
#include <pwd.h>

#include "chatter/ChattMsg.h"

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
  ros::init(argc, argv, "chatter_service_server_node", ros::init_options::AnonymousName);
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
