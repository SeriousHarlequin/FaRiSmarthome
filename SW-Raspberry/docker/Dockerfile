# Use the official Debian base image
FROM debian:latest

# Set environment variables to avoid interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update package lists and install necessary packages
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        python3-venv \
        python3-pip \
        python3-dev \
        build-essential && \
    rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /app

# Create a virtual environment
RUN python3 -m venv /opt/venv

# Ensure pip is up-to-date
RUN /opt/venv/bin/pip install --upgrade pip

# Copy the requirements file
#COPY requirements.txt .

# Install Python dependencies within the virtual environment
#RUN /opt/venv/bin/pip install --no-cache-dir -r requirements.txt

#copy webserver
COPY ../ /app/

# Set environment variables to use the virtual environment
ENV PATH="/opt/venv/bin:$PATH"

# Expose the ports that the Flask app and Node.js server run on
EXPOSE 5000
EXPOSE 3000

# Define the command to run the application
#CMD ["python3", "/app/FaRiSmarthome/SW-Raspberry/IPReciever/Main.py"]
