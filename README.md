# ESP8266 MQTT Thermal Printer for HA
This project is fork from [ESP8266 MQTT Thermal Printer](https://github.com/HutchieV/ESP8266-MQTT-Thermal-Printer) and a I really would like to thatnk original author for it.

Here I'll try to improve it to the best of my abilities for specific use - adding it to [Home Assistant] as printer for anything that wou want to print from it.

Although COMPLETELY unnecessary, this printer is really fun addtion to it allowing you to expand your system output options and it would be great to have it in future as part of the notification platform. BUT that is out of my (I'l just a sales guy tinkering) programming capabilities.

# About printer

This [58mm Thermal Printer](https://s.click.aliexpress.com/e/_AZ8OYO) can print by using USB/TTL connection.
In the package you will receive power cable and data cable.
It has preloaded firmware with Latin alphabet (ASCII) but also has capability to print Bar Code (something I still havent test) and 2D Bar code.
Yes, if you know how to convert, pritner can also print very simple images.

Paper needs to be 57.5mm (58 is ok) and there are even [sticker version](https://www.aliexpress.com/item/1005001877510938.html), which opens up some more capabilites.

# Parts required
- [thermal printer](https://s.click.aliexpress.com/e/_AZ8OYO)
- [ESP8266](https://www.aliexpress.com/item/32633763949.html)
- some wires - for testing I used dupont cables m/f type
- power supply - for testing I used 2A mobile phone charger

# Adafruit Thermal Printer library
For printing, we are using Adafruit Thermal Library. At this point, I tried to improve on original code, by adding 2 options in static configuration file. 
- Text size (options are S, M and L with S being default)
- Line spacing (minimum value is 24, default 32 and maximum 64)
It would be great if anyone could contribute so we can have internal default values, but also ability to override them my using MQTT topic.

But there are some more options in Arduino library, that cuold be used in future:
- inverseOn() - uset to inverse print and print white-on-black
- doubleHeight() - used to make text double the height
- justify() - to select if you want text to be justified left, center or right
- boldOn() - to print BOLD text
- underlineOn() - for underlined text

## Bitmap printing
Maximum size for bitmap printing is 384 pixels width

## Other options
Library contains option to check status of the paper - printer.has_paper should return True is there is paper and False if no paper is present.

# Configuration
In order to compile this project, you need to rename example-config.h to config.h and edit values there:
- *ssid* - change to matche your WiFi SSD
- *password* - needs to match your WiFi password
- *mqtt_server* - IP address of your MQTT server
- *mqtt_user* - if you need user credential to access MQTT, input here username, if not leave empty
- *mqtt_pass* - password to access MQTT server, if needed
- *my_id* - name of the printer (will be visible in MQTT log)
- *mqtt_port* - MQTT server port, default is 1883
- *baud* - baud rate for communication, leave at 9600
- *mqtt_listen_topic* - MQTT topic that we will be using ot listen for text to print
- *mqtt_text_size* - size of the text we will print, S for Small, M for Medium, L for Large*
- *mqtt_row_spacing* - row spacing with default being 32, minimum 24 and maximum 64

# Credits
- [HutchieV](https://github.com/HutchieV) for [ESP8266 MQTT Thermal Printer](https://github.com/HutchieV/ESP8266-MQTT-Thermal-Printer)