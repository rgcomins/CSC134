#!/usr/bin/env bash
# setup.sh — one-time setup for the Aloha Escapes booking site.
#
# Installs the only Python dependency we need (Flask).  Run this once
# after cloning the repo, then use ./run.sh to start the dev server.

set -e

echo "Installing Flask..."
pip install flask

echo
echo "Setup complete. Run ./run.sh to start the dev server."
