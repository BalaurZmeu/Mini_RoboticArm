# Automatica Sud

AutomaticaSud is a robotics and automation company. This website serves as a 'proof of concept' for a robot controlled remotely by an operator via the internet.

---

work in progress

## PLAN:

To implement a Django-powered website that allows users to control a mini robotic arm and view its live movements via video, you'll need to integrate several technologies: Django for the web interface, Arduino for controlling the robotic arm, and a live streaming solution for video. Here's a step-by-step high-level approach:

### 1. **Setup the Arduino and Robotic Arm**
   - **Arduino Control**: You’ll need to develop code on the Arduino that listens for commands sent from the Django server (via a serial or wireless interface) and translates those into movements for the robotic arm.
   - **Communication with the Server**: Depending on your setup, you can connect the Arduino to the Django server via:
     - **Serial Communication**: Direct USB connection where the Django server sends movement commands via a Python serial library like `pySerial`.
     - **Wi-Fi or Bluetooth Module**: If you want to make it wireless, you could use a Wi-Fi module (like ESP8266) or a Bluetooth module to interface between the server and the Arduino.
   - **Control Logic**: The Arduino sketch will listen for incoming commands (such as "move left," "move right") and control the robotic arm motors accordingly.

### 2. **Web Interface using Django**
   - **Frontend for Control**:
     - Create a Django view that serves a webpage containing buttons to control the robotic arm.
     - Use a form or AJAX requests to send user commands (e.g., move left, right, up, down) to the backend.
   
   - **Command Handling in Django**:
     - Django views can handle the POST requests triggered by button presses.
     - The view will send the movement commands to the Arduino through the communication interface (e.g., using `pySerial` if using a wired connection or an HTTP endpoint if Arduino is using Wi-Fi).

   Example (simplified):
   ```python
   # views.py
   import serial

   def control_robotic_arm(request):
       if request.method == "POST":
           action = request.POST.get("action")  # e.g., 'move_left'
           # Send command to Arduino via serial
           with serial.Serial('/dev/ttyUSB0', 9600) as ser:
               ser.write(action.encode())  # Send the action to Arduino
       return render(request, 'control.html')  # Return the control page

   # control.html (example)
   <form method="POST">
       {% csrf_token %}
       <button name="action" value="move_left">Move Left</button>
       <button name="action" value="move_right">Move Right</button>
       <button name="action" value="move_up">Move Up</button>
       <button name="action" value="move_down">Move Down</button>
   </form>
   ```

### 3. **Live Video Streaming**
   To show live video of the robotic arm's movement on the website, you need to stream video from the robotic arm's environment to the user’s browser.

   - **Camera Setup**: You’ll need a camera (e.g., a USB webcam or Raspberry Pi camera module) positioned to capture the robotic arm’s movement.
   - **Streaming Options**:
     - **RTSP Stream**: You can use a camera that supports RTSP streaming (e.g., some USB webcams or an IP camera) and stream the feed directly to the website.
     - **Raspberry Pi + Camera Module**: If using a Raspberry Pi, you can use `MJPEG-streamer` or similar software to stream video from the camera over HTTP, and embed it on the website using an `<img>` tag with the stream's URL.

     Example of embedding a video stream in Django:
     ```html
     <!-- control.html -->
     <div>
         <h3>Live Video Feed:</h3>
         <img src="http://<raspberry-pi-ip>:8080/?action=stream" alt="Live Feed" />
     </div>
     ```

### 4. **Combining Control and Live Video**
   Your Django page will have buttons for controlling the robotic arm and a live video feed to display the arm's movements. When the user presses a button to move the arm, the command is sent to the server, forwarded to the Arduino, and the live video feed updates in real-time, allowing the user to see the effect of their command.

### 5. **Asynchronous Control and Updates**
   - Use **AJAX** for sending control commands asynchronously, so the page doesn't need to reload each time the user sends a command.
   - Consider using **WebSockets** or **Django Channels** if you want to handle bidirectional communication for real-time updates or feedback from the robotic arm, such as its current position.

### 6. **Example Tech Stack and Components**:
   - **Django**: For building the web interface, handling user input, and managing backend logic.
   - **Arduino (or ESP8266)**: To control the robotic arm based on commands from the server.
   - **pySerial (or HTTP requests)**: For communication between Django and Arduino (depending on wired or wireless setup).
   - **Live Streaming**: Use MJPEG-streamer for live video from a camera.
   - **AJAX**: For sending movement commands without reloading the page.
   - **WebSockets/Django Channels**: For real-time updates from the robotic arm if needed.

### 7. **Security Considerations**:
   - **Authentication**: Ensure that only authorized users can control the robotic arm.
   - **Rate Limiting**: Add rate-limiting to prevent users from sending commands too rapidly or spamming the controls.
   - **Network Latency**: Monitor network delays to ensure smooth control and streaming experience.

### 8. **Testing and Debugging**:
   - Test the connection between Django and Arduino by sending commands directly via the Django admin or command-line interface.
   - Verify that the camera feed streams correctly in the browser before integrating it into the control page.

This approach combines Django for web control, Arduino for hardware control, and a video streaming solution to provide a live feed, ensuring a smooth interaction between the web interface and the physical robotic arm.
