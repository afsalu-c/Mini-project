import smbus
import time
import os
import glob

# Raspberry Pi configuration
bus = smbus.SMBus(1)  # Raspberry Pi uses I2C bus 1

# Arduino address
SLAVE_ADDRESS = 0x04

def measure_distance():
    # Request distance from Arduino
    bus.write_byte(SLAVE_ADDRESS, 0)
    time.sleep(0.1)
    distance = bus.read_byte(SLAVE_ADDRESS)
    return distance

def detect_object():
    os.system("python3 detect.py --source photo.jpg")

def get_latest_detected_image():
    # Get the latest detected image file path
    files = glob.glob("runs/detect/exp*/photo.jpg")
    if files:
        return max(files, key=os.path.getctime)
    else:
        return None

def main():
    try:
        while True:
            distance = measure_distance()
            print("Distance:", distance, "cm")
            if distance <= 20:
                detect_object()
                print("Object detected! Object detection completed.")
                # Get the path of the latest detected image
                detected_image_path = get_latest_detected_image()
                if detected_image_path:
                    # Display detected image using default image viewer
                    os.system(f"xdg-open {detected_image_path}")
                else:
                    print("No detected image found.")
                # Sleep to avoid continuously detecting objects for a single object
                time.sleep(5)
    except KeyboardInterrupt:
        pass

if _name_ == "_main_":
    main()
