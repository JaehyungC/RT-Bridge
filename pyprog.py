# Python program
# Publisher sends the messages to the 5557 socket
# Subscriber reads from the 5556 socket and prints out the messages

import pwrap
import zmq

# Socket to talk to server
context = zmq.Context()
subsocket = pwrap.connectsub(context, "tcp://localhost:5556")

# Set up Python publisher
#pubsocket = pwrap.connectpub(context, "tcp://*:5557")

print("Waiting for C Publisher...")

# Set up filter
pwrap.setup(subsocket)

# Open the CSV file for receiving
csv_r = pwrap.setupcsv("python_recv.csv")

# Open the CSV file for sending
#csv_s = pwrap.setupcsv("python_sent.csv")

#pwrap.startmsg(subsocket, pubsocket, csv_r[0], csv_s[0], csv_r[1], csv_s[1])
pwrap.headerdemo(subsocket, csv_r[0], csv_r[1])