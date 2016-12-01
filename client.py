import socket
import sys
from compiler.ast import While

HOST, PORT = "localhost", 50000
data = " ".join(sys.argv[1:])
data = 1

# Create a socket (SOCK_STREAM means a TCP socket)
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # Connect to server and send data
    sock.connect((HOST, PORT))
    while data != 10:
        sock.sendall(str(data) + "\n")

        # Receive data from the server and shut down
        received = sock.recv(1024)
        print received
        data = int(received) + 1
except:
    print "Unexpected error:", sys.exc_info()[0]
    raise

finally:
    sock.close()

print "Sent:     {}".format(data)
print "Received: {}".format(received)