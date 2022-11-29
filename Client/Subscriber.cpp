#include "Subscriber.h"

#include <iostream>

Subscriber::Subscriber(const std::string& pEndpoint)
    : mContext(),
    mSocket(mContext, zmq::socket_type::sub),
    mServer(pEndpoint)
{
}

Subscriber::~Subscriber()
{
    mSocket.close();
}

void Subscriber::run()
{
    const std::string localEndpoint{ "127.0.0.1:65001" };
    std::string publisher = "tcp://" + localEndpoint + ";" + mServer;
    mSocket.connect(publisher);
    subscribe(""); // subscribe to all channels

    int counter = 0;

    mIsRunning = true;
    
    while (true)
    {
        std::string topic;
        std::string message;
        try {
            receive(topic, message);
            std::cout << "Incoming message: " << topic << " - " << message << std::endl;
        }
        catch (std::exception& e)
        {
            std::cerr << "Unable to process incoming message from publisher, details: " 
                << e.what() << std::endl;
        }
    }
    
    mIsRunning = false;
}

void Subscriber::subscribe(const std::string& topic)
{
    mSocket.set(zmq::sockopt::subscribe, topic);
}

void Subscriber::unsubscribe(const std::string& topic)
{
    mSocket.set(zmq::sockopt::unsubscribe, topic);
}

void Subscriber::receive(std::string& pTopic, std::string& pMessage)
{
    std::vector<zmq::message_t> recv_msgs;
    zmq::recv_result_t result =
        zmq::recv_multipart(mSocket, std::back_inserter(recv_msgs));

    if (!result.has_value())
    {
        throw std::runtime_error("No message received from ZMQ publisher!");
    }
    else if (recv_msgs.size() <= 1)
    {
        for (auto& i : recv_msgs)
        {
            std::cerr << "Error: Invalid message: " << i << std::endl;
        }
        throw std::runtime_error("Message received from ZMQ publisher is invalid!");
    }

    pTopic = recv_msgs[0].to_string();
    pMessage = recv_msgs[1].to_string();
}
