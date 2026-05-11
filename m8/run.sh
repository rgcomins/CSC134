#!/usr/bin/env bash
# run.sh — start the Flask dev server for Aloha Escapes.
#
# Starts the app on http://127.0.0.1:5000/ in debug mode (edits to
# templates or app.py auto-reload).  Press Ctrl+C to stop.

set -e

# Ensure we're in the m8 directory regardless of where the script
# was invoked from.
cd "$(dirname "$0")"

echo "Starting Aloha Escapes on http://127.0.0.1:5000/"
echo "Press Ctrl+C to stop."
echo

python3 app.py
