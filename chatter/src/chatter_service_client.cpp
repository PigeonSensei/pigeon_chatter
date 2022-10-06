#include <ros/ros.h>
#include <std_msgs/String.h>
#include <time.h>

#include <boost/algorithm/string/replace.hpp>

#include "chatter/ChattMsg.h"

int ReturnChatCommand(std::string cmd)
{
  if(cmd == "/exit")
  {
    std::cout << "exit the chatter_service_client_node" << std::endl;
    return 0;
  }
  if(cmd == "/help")
  {
    std::cout << "/exit : exit the chatter_service_client_node" << std::endl;
    return 1;
  }

  return -1;
}

int main(int argc, char **argv)
{
  time_t time_now;
  time_now = time(NULL);

  std::string my_name;
  std::string chat_message;

  std::cout << "Input your name : ";

  getline(std::cin, my_name);
  boost::replace_all(my_name, " ", "_");

  std::string time_stamp = std::to_string(time_now);
  std::string node_name = "chatter_service_client_node_" + my_name + "_" + time_stamp;

  ros::init(argc, argv, node_name);
  ros::NodeHandle n;

  ros::ServiceClient service_client_chatt_msg = n.serviceClient<chatter::ChattMsg>("chatt_msg");
  chatter::ChattMsg chatt_msg;

  ros::Rate loop_rate(10);

  boost::replace_all(my_name, "_", " ");

  while(ros::ok())
  {
    std_msgs::String msg;

    std::cout << "send message : ";

    getline(std::cin, chat_message);

    std::cout << std::endl;

    int command = ReturnChatCommand(chat_message);


    if(command == 0) break;
    else if(command == 1);
    else
    {
      chatt_msg.request.name = my_name;
      chatt_msg.request.message = chat_message;
      service_client_chatt_msg.call((chatt_msg));
    }
    ros::spinOnce();

    loop_rate.sleep();
   }

  return 0;
}
