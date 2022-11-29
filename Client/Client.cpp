#include "Subscriber.h"
#include <iostream>

int main()
{
    std::string server{ "127.0.0.1:8000" };

    Subscriber subscriber(server);
    
    subscriber.run();
}
