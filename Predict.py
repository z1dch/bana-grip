from ultralytics import YOLO
import cv2
import cvzone
import threading
import serial
import time

# 🎯 Step 1: Initialize Serial Communication
try:
    arduino = serial.Serial(port='COM8', baudrate=9600, timeout=1)
    print("✅ Arduino connected successfully.")
    time.sleep(2)  # Allow Arduino to reset
except serial.SerialException as e:
    print(f"⚠️ Serial Error: {e}")
    exit()

# 🎯 Step 2: Set up Camera
camera_url = "http://172.20.10.3:4747/video"
cap = cv2.VideoCapture(camera_url)

# 🎯 Step 3: Load YOLO Model
model = YOLO("yolov11x_custom.pt").to("cuda")
print("🟢 Model is running on:", model.device)

# Class Labels
classNames = ["bad", "good"]

# 🎯 Step 4: Threading Variables
frame = None
lock = threading.Lock()
stop_thread = False
latest_prediction = None
latest_predictions = {}

# 🎯 Step 5: Define Region Mappings
def get_region(cx_cm, cy_cm):
    if 27 <= cx_cm <= 33 and 5 <= cy_cm <= 20:
        return "A"
    elif 21 <= cx_cm <= 26 and 5 <= cy_cm <= 20:
        return "B"
    elif 5 <= cx_cm <= 20 and 3 <= cy_cm <= 9:
        return "C"
    elif 5 <= cx_cm <= 20 and 11 <= cy_cm <= 17:
        return "D"
    return "Outside"

# 🎯 Step 6: Capture Video Frames
def read_frames():
    global frame, stop_thread
    while not stop_thread:
        ret, new_frame = cap.read()
        if ret:
            with lock:
                frame = new_frame
        else:
            print("❌ Error: Frame not received.")
            stop_thread = True

# 🎯 Step 7: Process Frames & Await Arduino Request
def process_frames():
    global frame, stop_thread, latest_prediction, latest_predictions

    while not stop_thread:
        if frame is None:
            time.sleep(0.01)
            continue

        with lock:
            process_frame = frame.copy()

        results = model(process_frame, stream=True)
        latest_predictions.clear()

        for r in results:
            for box in r.boxes:
                x1, y1, x2, y2 = map(int, box.xyxy[0])
                w, h = x2 - x1, y2 - y1
                cx, cy = x1 + w // 2, y1 + h // 2
                cx_cm, cy_cm = cx * 0.0635, cy * 0.0635
                box_label = get_region(cx_cm, cy_cm)

                cls = int(box.cls[0])
                class_name = classNames[cls]

                if box_label != "Outside":
                    latest_predictions[box_label] = (class_name, (x1, y1, w, h))
                    latest_prediction = f"{box_label} {cls}"
                    print(f"📌 Latest detection: {latest_prediction}")
                    return  # Stop processing after one object is detected

# 🎯 Step 8: Start Threads
read_thread = threading.Thread(target=read_frames)
read_thread.start()

cv2.namedWindow('Object Detection', cv2.WINDOW_NORMAL)

try:
    while True:
        if frame is not None:
            with lock:
                display_frame = frame.copy()

            # Draw bounding boxes
            for box_label, (class_name, (x1, y1, w, h)) in latest_predictions.items():
                cvzone.cornerRect(display_frame, (x1, y1, w, h), l=10)
                cvzone.putTextRect(display_frame, f'{box_label} {class_name}',
                                   (max(0, x1), max(35, y1)), scale=0.6, thickness=1, offset=3)

            if latest_prediction:
                arduino.write(f"{latest_prediction}\n".encode())
                print(f"📤 Sent to Arduino: {latest_prediction}")
                latest_prediction = None  # Clear after sending

            cv2.imshow('Object Detection', display_frame)

        if arduino.in_waiting > 0:
            request = arduino.readline().decode().strip()
            if request == "REQUEST":
                process_frames()  # Detect only when Arduino requests

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

finally:
    print("🔄 Stopping Threads...")
    stop_thread = True
    read_thread.join()
    cap.release()
    cv2.destroyAllWindows()
    arduino.close()
    print("🔴 Arduino Disconnected.")