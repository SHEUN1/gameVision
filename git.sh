#!/bin/bash
git init
git add .
git commit -m "make extractor more generic v4"
git remote rm origin
git remote add origin https://github.com/SHEUN1/Cloudbank.git
git push origin DEV_Transistor
