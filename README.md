android-screenrecord-helper
===========================
Helper tool to create a screen capture video for Android device.

## Usage
```
# cleaning up previous data files
rm data/*
adb shell rm /sdcard/fb/*

# start helper tool
adb shell /data/local/tmp/screenrecord /sdcard/fb 

# pull captured images
adb pull /sdcard/fb ./data/ 

# create a video from captured images
./mkvideo.py
```
