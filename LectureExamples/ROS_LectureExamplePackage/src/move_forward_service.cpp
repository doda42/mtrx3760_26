#include "rclcpp/rclcpp.hpp"
#include "mtrx3760/srv/move_forward.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"

using MoveForward = mtrx3760::srv::MoveForward;
using TwistStamped = geometry_msgs::msg::TwistStamped;

class MoveForwardServer : public rclcpp::Node
{
    public:
        MoveForwardServer()
            : Node("move_forward_server"), speed(0.1)
        {
            RCLCPP_INFO(get_logger(), "Server to move turtlebot");
            publisher = create_publisher<TwistStamped>("/cmd_vel", 10);
            server = create_service<MoveForward>("move_forward",
                        std::bind(&MoveForwardServer::callback, this,
                        std::placeholders::_1, std::placeholders::_2));
        }

    private:

        // Note that this currently always returns True. Missing error handling
        void callback(const MoveForward::Request::SharedPtr request,
                      const MoveForward::Response::SharedPtr response)
        {
            TwistStamped msg;
            msg.header.stamp = get_clock()->now();
            msg.twist.linear.x = speed;

            // Calculate time taken to move requested distance at fixed speed
            double timeToMove = request->distance / msg.twist.linear.x;
            rclcpp::Rate rate(30);

            auto start_time = now();
            while ((now() - start_time).seconds() < timeToMove)
            {
                publisher->publish(msg);
                rate.sleep();
            }

            // Stop the robot
            msg.twist.linear.x = 0.0;
            publisher->publish(msg);

            response->success = true;
            response->message = "Moved forward " + std::to_string(request->distance) + " m";
            RCLCPP_INFO(get_logger(), "%s", response->message.c_str());
        }

        float speed;
        rclcpp::Publisher<TwistStamped>::SharedPtr publisher;
        rclcpp::Service<MoveForward>::SharedPtr server;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MoveForwardServer>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}