import zmq
import time

# Create ZMQ context and associate the publisher socket with it
zmq_publisher_context = zmq.Context()
publisher_socket = zmq_publisher_context.socket(zmq.PUB)
publisher_socket.bind(f'tcp://127.0.0.1:8500')


def send( channel: str, msg: str ):
    publisher_socket.send_multipart([bytes(channel, 'utf-8'), bytes(msg, 'utf-8')])

if __name__ == "__main__":
   counter = 0
   
   while True:
       # Send a message to the channel 'channel1'
       send('channel1', f'Hello World: #{counter} updated')
       counter += 1
       time.sleep(1)
       
