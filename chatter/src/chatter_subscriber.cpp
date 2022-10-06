#include <ros/ros.h>
#include <std_msgs/String.h>
#include <time.h>
#include <pwd.h>

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

void ChatterCallback(const std_msgs::String::ConstPtr& msg)
{
  std::cout << "[" << GetTimeNow() << "] " << msg->data.c_str() << std::endl;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "chatter_subscriber_node", ros::init_options::AnonymousName);
  ros::NodeHandle n;

  ros::Subscriber subscriber_chatter = n.subscribe("chatter", 1000, ChatterCallback);

  ros::spin();

  return 0;
}
