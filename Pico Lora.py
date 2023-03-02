import time
import board
import busio
import digitalio
import adafruit_rfm9x

# Define pins 
CS = digitalio.DigitalInOut(board.GP17)
RESET = digitalio.DigitalInOut(board.GP0)

# Define frequency and baudrate
RADIO_FREQ_MHZ = 915.0
BAUDRATE = 9600

# Initialize SPI bus
spi = busio.SPI(board.GP18, MOSI=board.GP19, MISO=board.GP16)

# Initialize LoRa radio
rfm9x = adafruit_rfm9x.RFM9x(spi, CS, RESET, RADIO_FREQ_MHZ)

# Set the node ID
NODE_ID = 0x01

while True:
    # Wait for a message to be received
    packet = rfm9x.receive(timeout=5.0)

    # If a message was received, print the contents
    if packet is not None:
        print("Received: ", str(packet, "utf-8"))

    # Read a message from the console and send it over LoRa
    if input():
        message = str(input("Enter message: "))
        packet = bytes(message, "utf-8")
        rfm9x.send(packet, NODE_ID)
        print("Sent: ", message)
    time.sleep(0.1)
