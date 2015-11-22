#! /bin/bash
find . -type d | xargs -t -i touch {}/__init__.py
