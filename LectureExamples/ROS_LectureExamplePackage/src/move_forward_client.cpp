
#include "rclcpp/rclcpp.hpp"
#include "mtrx3760/srv/move_forward.hpp"

using MoveForward = mtrx3760::srv::MoveForward;

class MoveForwardClient : public rclcpp::Node
{
    public:
        MoveForwardClient()
            : Node("move_forward_client")
        {
            RCLCPP_INFO(get_logger(), "Client to move turtlebot started");
            client = create_client<MoveForward>("move_forward");
            while (!client->wait_for_service(std::chrono::seconds(1)));
            sendRequest(0.1);
        }
        
    private:
        void handleResponse(rclcpp::Client<MoveForward>::SharedFuture future)
        {
            try
            {
                auto response = future.get();
                RCLCPP_INFO(get_logger(), "Result of calling move service: %d", response->success);
            }
            catch (const std::exception &e)
            {
                RCLCPP_ERROR(get_logger(), "Service call failed: %s", e.what());
            }
        }

        void sendRequest(double distance)
        {
            auto request = std::make_shared<MoveForward::Request>();
            request->distance = distance;
            client->async_send_request(request, std::bind(&MoveForwardClient::handleResponse, this, 
                    std::placeholders::_1));
        }
        rclcpp::Client<MoveForward>::SharedPtr client;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MoveForwardClient>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}


