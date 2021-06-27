# ESP8266 MQTT Thermal Printer for HA (V2.1)
Many thanks to [BeardedTinker](https://github.com/BeardedTinker) and [lebherz](https://github.com/lebherz) for contributing to this project. BeardedTinker wrote most of this README.

This version supports, since v2:
- Changing the textsize
- Changing the textlineheight
- Toggling inverse text
- Toggling bold text
- Toggling text underline
- Setting text justification

Since v2.1
- print barcodes
- receive the paperload status

# About printer
This [58mm Thermal Printer](https://s.click.aliexpress.com/e/_AZ8OYO) can print by using USB/TTL connection.
In the package you will receive power cable and data cable.
It has preloaded firmware with Latin alphabet (ASCII) but also has capability to print 2D barcode.
Yes, if you know how to convert, printer can also print very simple images.

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
Values can be changed via topics configured in `config.h`

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
