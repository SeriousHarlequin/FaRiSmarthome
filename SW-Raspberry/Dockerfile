FROM debian:latest

# Install required packages
RUN apt-get update && \
    apt-get install -y python3 python3-pip nodejs npm python3-flask python3-flask-cors && \
    rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /app

# Copy project files into the container
COPY ./ /app

# Make the script executable
RUN chmod +x /app/start.sh

# If there's a package.json, install Nuxt.js (and other Node) dependencies
RUN if [ -f package.json ]; then npm install; fi

# Expose ports (adjust as needed)
EXPOSE 3000 5000

# Start command (this example starts the Flask server;
# you might need to change it or use a script to run both Flask and Nuxt)
ENTRYPOINT ["/app/start.sh"]
