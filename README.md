# ESP8266 MQTT Thermal Printer for HA (V2.1)
This project is fork from [ESP8266 MQTT Thermal Printer](https://github.com/HutchieV/ESP8266-MQTT-Thermal-Printer) and a I really would like to thatnk original author for it.

Here I'll try to improve it to the best of my abilities for specific use - adding it to [Home Assistant] as printer for anything that wou want to print from it.

in Version 2 we can:
- change the textsize via mqtt
- change the textlineheight via mqtt
- can change to inverse font via mqtt
- can justify the text via mqtt
- can change to print bold via mqtt
- change to underline the text via mqtt
in Version 2.1 we can: 
- print barcodes via mqtt
- receive the paperload status via mqtt


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
Values can be changed via topics configured in the config.h

## Bitmap printing
Maximum size for bitmap printing is 384 pixels width

## Printer has no paper
In Version 2.1 the controller sends in topic *mqtt_listen_topic_papercheck* every defined seconds (*papercheck_milliseconds*) a *yes* or *no* 

## Badcode usage
in Version 2.1
Important: your thermal printer has only 58mm to print the barcode in the example below "Hello!!" the CODE93 barcode the max with of the paper has been reached. :-(
    
   v------ use this number to config <barcodetype> below  
*0* = UPC_A,   < UPC-A barcode system. 11-12 char   
*1* = UPC_E,   < UPC-E barcode system. 11-12 char   
*2* = EAN13,   < EAN13 (JAN13) barcode system. 12-13 char    
*3* = EAN8,    < EAN8 (JAN8) barcode system. 7-8 char    
*4* = CODE39,  < CODE39 barcode system. 1<=num of chars    
*5* = ITF,     < ITF barcode system. 1<=num of chars, must be an even number    
*6* = CODABAR, < CODABAR barcode system. 1<=num<=255    
*7* = CODE93,  < CODE93 barcode system. 1<=num<=255    
*8* = CODE128, < CODE128 barcode system. 2<=num<=255    
  payload for the barcode_ topic (configed below) is    
  **`<barcodetype>|<barcode_value>`**
  e.g. *7|Hello!!*   


## Configuration
In order to compile this project, you need to rename example-config.h to config.h and edit values there:
- *ssid* - change to matche your WiFi SSD
- *password* - needs to match your WiFi password
- *mqtt_server* - IP address of your MQTT server
- *mqtt_user* - if you need user credential to access MQTT, input here username, if not leave empty
- *mqtt_pass* - password to access MQTT server, if needed
- *my_id* - name of the printer (will be visible in MQTT log)
- *mqtt_port* - MQTT server port, default is 1883
- *baud* - baud rate for communication, leave at 9600
- *papercheck_milliseconds* - sends every defined milliseconds the status on topic *mqtt_listen_topic_papercheck* (see below) 
  recommendation: minimum 10000 (= 10sec)
- *mqtt_listen_topic_text2print* - MQTT topic that we will be using ot listen for text to print e.g. *Hello world!*
- *mqtt_listen_topic_textsize* - MQTT topic for the text size aviable parameters are *S* = small, *M* = medium, *L* = large
- *mqtt_listen_topic_textlineheight* - MQTT topic for the textlineheight default ist set in the config.h, minimum *24* and maximum *64*
- *mqtt_listen_topic_textinverse* - MQTT topic for inverse follow the text: *1* = inverse, *0* = not inverse
- *mqtt_listen_topic_textjustify* - MQTT topic for justify follow the text: left = *L*, center = *C*, right = *R*
- *mqtt_listen_topic_textbold* - MQTT topic to bold the follow text: *1* = bold, *0* = not bold
- *mqtt_listen_topic_textunderline* - MQTT topic for inverse the text: *1* = underline, *0* = not underline
- *mqtt_text_size* - MQTT topic for initial size of the text we will print, S for Small, M for Medium, L for Large
- *mqtt_row_spacing* - MQTT topic of initial row spacing with default being 32, minimum 24 and maximum 64
- *mqtt_listen_topic_barcode* - MQTT topic to print barcode in payload should be: `<barcodetype>|<barcode_value>` e.g. `7|HelloMaster` here 4 is barcodetype CODE93
- *mqtt_listen_topic_papercheck* - MQTT topic (readonly!) sends every defined milliseconds *papercheck_milliseconds* the status of the paperload *yes* | *no* 

## MQTT Topics
| mqtt topic\* | payload |
|-|:-|
|*mqtt_listen_topic_text2print*| e.g. "Hello world!" |
|*mqtt_listen_topic_textsize*| *S* = small,<br> *M* = medium,<br> *L* = large |
|*mqtt_listen_topic_textlineheight*| minimum *24* and maximum *64* e.g. 24|
|*mqtt_listen_topic_textinverse*|*1* = inverse,<br> *0* = not inverse|
|*mqtt_listen_topic_textjustify*|left = *L*,<br> center = *C*,<br> right = *R*|
|*mqtt_listen_topic_textbold*|*1* = bold,<br> *0* = not bold|
|*mqtt_listen_topic_textunderline*|*1* = underline,<br> *0* = not underline|
|*mqtt_listen_topic_barcode*| \<barcodetype\>\|\<barcode_value\><br> e.g. 7\|HelloMaster|
|*mqtt_listen_topic_papercheck*| **readonly!**<br> - yes<br>- no |

\*defined in config-file above

# Credits
- [HutchieV](https://github.com/HutchieV) for [ESP8266 MQTT Thermal Printer](https://github.com/HutchieV/ESP8266-MQTT-Thermal-Printer)
