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
  uid_t user_id;
  struct passwd *user_pw;

  user_id = getuid();
  user_pw = getpwuid(user_id);

  std::string my_name = user_pw->pw_name;

  time_t time_now;
  time_now = time(NULL);

  std::string time_stamp = std::to_string(time_now);
  std::string node_name = "chatter_subscriber_node_" + my_name + "_" + time_stamp; 

  ros::init(argc, argv, node_name);
  ros::NodeHandle n;

  ros::Subscriber subscriber_chatter = n.subscribe("chatter", 1000, ChatterCallback);

  ros::spin();

  return 0;
}
