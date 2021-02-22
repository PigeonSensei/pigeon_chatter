# pigeon_chatter
ROS  chatting Program

### Yotube Video
   https://youtu.be/xBQHQTsNyHA

### Package composition

- #### chatter
  
  - chatter_publisher_node
  
    This is the node for entering the message.
    
  - chatter_subscriber_node
  
    This is a node that shows the chat content.
  
### Run

Set ROS_MASTER_URI and ROS_HOSTNAME before use

Reference http://wiki.ros.org/ROS/NetworkSetup

- Run chatter_publisher_node

  ```bash
  rosrun chatter chatter_publisher_node
  ```

- Run chatter_subscriber_node
  ```bash
  rosrun chatter chatter_subscriber_node
  ```
