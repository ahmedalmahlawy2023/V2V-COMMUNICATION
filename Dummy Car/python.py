import serial
import socket
ser = serial.Serial('/dev/serial0', baudrate=9600)  # Adjust the baud rate as needed
ser.timeout = None
#Define the host and port for the server
host = '0.0.0.0'  # Leave it empty to accept connections from any IP address
port = 12345  # You can choose any available port

#Create a socket object
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#Bind the socket to the host and port
server_socket.bind((host, port))

#Listen for incoming connections
server_socket.listen(1)

#Accept a connection and get the client socket
client_socket, client_address = server_socket.accept()
response_ack='0'
while True :
	# Receive request from main car WIFI
	comRequestMessage = client_socket.recv(1024).decode()
	#print("1 " + comRequestMessage)
	if comRequestMessage == 'R' :
		#Send request to dummy car stm
		ser.write(comRequestMessage.encode())
		# Receive data from dummy car stm
		dummyCarResponse = ser.read()
		dummyCarResponse = dummyCarResponse.decode()
		#print("2 " + dummyCarResponse)
		# Send dummy data to main car WIFI
		client_socket.send(dummyCarResponse.encode())
#Close the sockets
client_socket.close()
server_socket.close()
