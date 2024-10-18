import cv2
import numpy as np

# Load YOLOv3 model
net = cv2.dnn.readNet("yolov3.weights", "yolov3.cfg")

# Check if the network loaded successfully
if net.empty():
    print("Error: Unable to load YOLOv3 model.")
    exit()

# Load class names
classes = []
with open("coco.names", "r") as f:
    classes = [line.strip() for line in f.readlines()]

# Get layer names
layer_names = net.getLayerNames()

# Specify the output layer indices for YOLOv3
output_layer_names = ['yolo_82', 'yolo_94', 'yolo_106']

# Get the output layers
output_layers = [layer_names.index(layer_name) for layer_name in output_layer_names]

video = cv2.VideoCapture(1)

while True:
    ret, frame = video.read()
    if not ret:
        break

    # Resize frame to improve performance (optional)
    frame = cv2.resize(frame, (640, 480))

    # Detect objects in the frame
    blob = cv2.dnn.blobFromImage(frame, 0.00392, (416, 416), (0, 0, 0), True, crop=False)
    net.setInput(blob)
    outs = net.forward(output_layers)

    # Process detected objects
    for out in outs:
        for detection in out:
            scores = detection[5:]
            class_id = np.argmax(scores)
            confidence = scores[class_id]
            if confidence > 0.5 and class_id == 0:  # Class ID 0 corresponds to a person
                center_x = int(detection[0] * frame.shape[1])
                center_y = int(detection[1] * frame.shape[0])
                w = int(detection[2] * frame.shape[1])
                h = int(detection[3] * frame.shape[0])
                x = int(center_x - w / 2)
                y = int(center_y - h / 2)
                cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

    cv2.imshow('YOLOv3 Human Detection', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

video.release()
cv2.destroyAllWindows()
