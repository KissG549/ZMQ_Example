#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <zmq_addon.hpp>

/**
    //http://api.zeromq.org/4-1:zmq-tcp
    // Connecting using an IP address
    rc = zmq_connect(socket, "tcp://192.168.1.1:5555");
    assert (rc == 0);
    // Connecting using a DNS name
    rc = zmq_connect(socket, "tcp://server1:5555");
    assert (rc == 0);
    // Connecting using a DNS name and bind to eth1
    rc = zmq_connect(socket, "tcp://eth1:0;server1:5555");
    assert (rc == 0);
    // Connecting using a IP address and bind to an IP address
    rc = zmq_connect(socket, "tcp://192.168.1.17:5555;192.168.1.1:5555"); assert (rc == 0);
*/

/**
    Implements a zeroMQ subscriber
    This class is to be intended to handle the subscription to a publisher
    and receive the messages from it.

    Depends on libzmq-mt-4_3_4.lib installed with vcpkg
*/


class Subscriber
{
public:
    Subscriber(const std::string& pEndpoint);
    ~Subscriber();
    
    /**
    * Starts the subscriber
    * Connect to the publisher and read the published messages
    */
    void run();
    bool isRunning() { return mIsRunning; }

private:

    /**
        Subscribes to the publisher
        @param topic The topic to subscribe to
    */
    void subscribe(const std::string& topic);

    /**
        Unsubscribes from the publisher
        @param topic The topic to unsubscribe from
    */
    void unsubscribe(const std::string& topic);

    /**
        Receives a message from the publisher
        @param topic The topic of the message
        @param message The message
        @return A pair of topic and message
    */
    void receive(std::string& pTopic, std::string& pMessage);

    zmq::context_t  mContext;
    zmq::socket_t   mSocket;
    /// <summary>
    ///   The endpoint of the publisher
    ///   @mServer Server addr or name with the port number
    /// e.g.: 127.0.0.1:65000
    /// </summary>
    std::string             mServer;
    bool                    mIsRunning{};
};

#endif
