import threading
import serial
import socket
import cv2
import picamera
import time 

# Sleep for 3 seconds
time.sleep(1)

# Load the Haar cascade for car detection
car_cascade = cv2.CascadeClassifier('cars.xml')

ser = serial.Serial('/dev/serial0', baudrate=9600)
ser.timeout = None

# Define the server's host and port (RPi1's IP address and port)
server_host = '192.168.137.177'  # Replace with RPi1's IP address
server_port = 12345  # Use the same port you chose on RPi1
# Create a socket object
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#Connect to the server
client_socket.connect((server_host, server_port))
response_ack='0'
errorMessageToSTM='0'
cameraStatus='0'
send_ack='0'
cameraValue ='O'
comRequestMessage ='0'
flag=0

# Function for camera detection using OpenCV and Haar Cascade
def camera_detection_task():
	global flag
	global cameraValue
	global comRequestMessage
	while True :
		if  flag==1 :
			flag = 0
			#open your own camera  
			# Create a PiCamera instance
			camera = picamera.PiCamera()
			camera.resolution = (320, 240)
			camera.framerate = 30
			camera.iso = 800  # Adjust ISO for low light, experiment with different values
			camera.shutter_speed = 6000000  # Set shutter speed for low light, experiment with different values
			camera.awb_mode = 'auto'
			#time.sleep(2)  # Allow camera to adjust to new settings
			# Capture an image
			camera.capture("image2.jpg")
			#print("Image captured successfully")

			# Read the captured image with OpenCV
			image = cv2.imread("image2.jpg")
			
			# Convert the image to grayscale (required for Haar cascades)
			gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
			# Perform car detection
			cars = car_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))
			if len(cars) > 0:
				#print("Car detected!")
				cameraValue='V'
				#ser.write(b'V')
			else:
				#print("No car detected.")
				cameraValue='O'
				#ser.write(b'V')
			# Close the camera when done
			camera.close()

# Function for running the rest of your Python code
def rest_of_code_task():
	global flag
	global cameraValue
	global comRequestMessage
	while True :
		ser.write(b'D')
		print("start COMM")
		response_ack = ser.read()
		response_ack = response_ack.decode()
		#print("read 1 " + response_ack)
		if (response_ack != 'A'):
			#print(response_ack)
			response_ack='0'
			continue
		response_ack='0'
		# Receive Request from main car stm
		comRequestMessage = ser.read()
		comRequestMessage = comRequestMessage.decode()
		print("ReceivedREQ: " + comRequestMessage)
		if comRequestMessage == 'R' : #start wifi communication
			ser.write(b'S') #send ack
			response_ack = ser.read()
			response_ack = response_ack.decode()
			#print("read 2 " + response_ack)
			if (response_ack == ')'): #check if the STM received correctly
				#print(response_ack)
				response_ack='0'
				continue
			response_ack='0'
			# send request to wifi dummy car
			client_socket.send(comRequestMessage.encode())
			# receive data from wifi dummy car
			dummyCarResponse = client_socket.recv(1024).decode()
			print("ReceivedData: " + dummyCarResponse)
			# send data to main car stm
			ser.write(dummyCarResponse.encode())
			response_ack = ser.read()
			response_ack = response_ack.decode()
			#print("read 3 " + response_ack)
			#print(response_ack)
			if (response_ack != 'K'): #check if the STM received correctly
				response_ack='0'
				continue
			response_ack='0'
			print("Communication done ")
			print("==========================")
		elif comRequestMessage == 'C' :
			flag=1
			ser.write(b'S') #send ack
			response_ack = ser.read()
			response_ack = response_ack.decode()
			if (response_ack == '<'): #check if the STM received correctly
				#print(response_ack)
				response_ack='0'
				continue
			response_ack='0'
			#open your own camera  
			cameraStatus = cameraValue
			ser.write(cameraStatus.encode())
			response_ack = ser.read()
			response_ack = response_ack.decode()
			if (response_ack != 'F'): #check if the STM received correctly
				#print("as" + response_ack)
				response_ack='0'
				cameraStatus = '0'
				continue
			response_ack='0'
			cameraStatus = '0' 
		else :
			#print('not R or C')
			ser.write(b'N') #send not ack
	# Close the socket
	client_socket.close()

# Create two threads, one for each task
camera_thread = threading.Thread(target=camera_detection_task)
rest_thread = threading.Thread(target=rest_of_code_task)

# Start both threads
camera_thread.start()
rest_thread.start()

# Wait for both threads to complete
camera_thread.join()
rest_thread.join()





