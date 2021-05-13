# kitty-count
This app displays real time litter box usage when equipped with an Arduino connected to a PIR sensor.  The app is built with Flask and provides an API for the Arduino to post litter box visits with a timestamp.

# Preview
Note this is just test data.
![alt text](https://github.com/diepholz/kitty-count/blob/main/kitty-count/demo.PNG?raw=true)


# Installation
```
pip install -r requirements.txt
set FLASK_APP=kittycount
set FLASK_ENV=development
flask run
```
