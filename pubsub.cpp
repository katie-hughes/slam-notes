#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

// Matt's one exception to not liking using namespace
// This lets you make suffixes for literal types
using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */


void func1(int a, int b){
    return a+b;
}

auto func2 = std::bind(func1,5);

// func2 is then (generally)
func2(int b){
    return func1(5, b);
}


class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    // This is liek an initialization list
    : Node("minimal_publisher"), count_(0)
    // could also do 
    // publisher_{create_publisher<std_msgs::msg::String>("topic", 10)}
    // timer_create_wall_timer
    //   500ms, std::bind(&MinimalPublisher::timer_callback, this))
    {
      publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
      // this here is completely unnecessarry. Could just be create_wall_timer
      timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
      // ms is something that comes from chrono_literals!!!!
      // what is bind?
      // timer_callback is member of class and so can access member vars
      // it's calling timer_callback on this object.
      // 2 nodes: 2 different objects
    }

        // void tcallback(){
        //     this.timer_callback()
        // }

        // could put lambda func. Then every time timer ticks hello is printed to screen
        // [this]() {cout << "hello"}

  private:
    void timer_callback()
    {
      auto message = std_msgs::msg::String();
      message.data = "Hello, world! " + std::to_string(count_++);
      // unneccessaary this again.
      // get logger in python
      // RCLCPP_INFO_STREAM(get_logger(), "Publishing: '" << message.data << "'")
      // capital letters are macros
      RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};


// there are other ways besides init and shutdown that matt thinks are better
int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}