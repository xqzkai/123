#include <memory>  
#include <chrono>  
#include "rclcpp/rclcpp.hpp"  
#include "geometry_msgs/msg/twist.hpp"  
  
class SquareDrawer : public rclcpp::Node {  
public:  
    SquareDrawer() : Node("square_drawer") {  
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);  
        timer_ = this->create_wall_timer(  
            500ms, std::bind(&SquareDrawer::timer_callback, this));  
  
        // 设置边长和旋转速度（可能需要调整）  
        side_length_ = 2.0;  // 海龟每次移动的距离（米）  
        turn_duration_ = 1.0; // 旋转90度所需的时间（秒，可能需要调整）  
    }  
  
private:  
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;  
    rclcpp::TimerBase::SharedPtr timer_;  
    double side_length_;  
    double turn_duration_;  
    size_t count_ = 0;  
  
    void timer_callback() {  
        if (count_ < 4) {  
            geometry_msgs::msg::Twist vel_msg;  
  
            // 向前移动  
            vel_msg.linear.x = 1.0;  // 线速度  
            vel_msg.angular.z = 0.0;  // 角速度  
            publisher_->publish(vel_msg);  
  
            // 等待足够的时间让海龟移动  
            std::this_thread::sleep_for(std::chrono::seconds(side_length_ / 1.0)); // 假设线速度约为1米/秒  
  
            // 停止移动  
            vel_msg.linear.x = 0.0;  
            publisher_->publish(vel_msg);  
  
            // 旋转90度  
            vel_msg.angular.z = 2.0;  // 旋转速度，可能需要调整以达到90度  
            publisher_->publish(vel_msg);  
  
            // 等待旋转完成  
            std::this_thread::sleep_for(turn_duration_);  
  
            // 重置角速度  
            vel_msg.angular.z = 0.0;  
            publisher_->publish(vel_msg);  
  
            count_++;  
        } else {  
            timer_->cancel();  
        }  
    }  
};  
  
int main(int argc, char **argv) {  
    rclcpp::init(argc, argv);  
    rclcpp::spin(std::make_shared<SquareDrawer>());  
    rclcpp::shutdown();  
    return 0;  
}
