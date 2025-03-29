#!/bin/bash

# Start the Flask server in the background
echo "Starting Flask server..."
python3 IPReciever/Main.py &

# Start the Nuxt.js server
cd WebInterface/FaRiWebUI/
echo "Starting Nuxt.js server..."
npm run dev -- --host &

wait
