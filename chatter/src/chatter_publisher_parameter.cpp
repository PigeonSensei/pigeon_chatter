#include <ros/ros.h>
#include <std_msgs/String.h>
#include <time.h>

#include <boost/algorithm/string/replace.hpp>

int ReturnChatCommand(std::string cmd)
{
  if(cmd == "/exit")
  {
    std::cout << "exit the chatter_publisher_node" << std::endl;
    return 0;
  }
  if(cmd == "/help")
  {
    std::cout << "/exit : exit the chatter_publisher_node" << std::endl;
    return 1;
  }

  return -1;
}

int main(int argc, char **argv)
{
  std::string my_name;
  std::string chat_message;

  ros::init(argc, argv, "chatter_publisher_parameter_node", ros::init_options::AnonymousName);
  ros::NodeHandle n;

  n.param<std::string>("Name", my_name,"Non");

  ros::Publisher publisher_chatter = n.advertise<std_msgs::String>("chatter", 1000);

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
      msg.data = my_name + " : " + chat_message;

      publisher_chatter.publish(msg);
    }
    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
