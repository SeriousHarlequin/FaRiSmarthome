import socket
from flask import Flask, jsonify
from flask_cors import CORS  # Import flask-cors
import threading

# UDP settings
UDP_IP = "0.0.0.0"  # Listen on all interfaces
UDP_PORT = 12345    # Port to listen on

# Global variable to store last sender IP
last_sender_ip = None

# Create a Flask app
app = Flask(__name__)
CORS(app)  # Enable CORS for all routes

@app.route('/get_ip', methods=['GET'])
def get_ip():
    """HTTP GET endpoint to return the last received IP"""
    if last_sender_ip:
        return jsonify({"last_sender_ip": last_sender_ip})
    else:
        return jsonify({"error": "No UDP packets received yet"}), 404

def udp_listener():
    """Function to listen for UDP packets"""
    global last_sender_ip
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))
    print("Listening for UDP broadcasts...")

    while True:
        data, addr = sock.recvfrom(1024)  # Buffer size is 1024 bytes
        last_sender_ip = addr[0]
        print(f"Received message: {data.decode()} from {last_sender_ip}")

# Run UDP listener in a separate thread
udp_thread = threading.Thread(target=udp_listener, daemon=True)
udp_thread.start()

# Run Flask server
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)  # Change port if needed

