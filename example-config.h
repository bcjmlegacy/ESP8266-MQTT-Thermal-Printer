const char* ssid                    = "WIFI-SSID-XX";
const char* password                = "randompassword123";
const char* mqtt_server             = "192.168.1.100";
const char* mqtt_user               = "user";
const char* mqtt_pass               = "password";
const char* my_id                   = "thermal_printer";
const unsigned int mqtt_port        = 1883;
const unsigned int baud             = 9600;

const uint32_t papercheck_milliseconds= 10000L; 

const char* mqtt_listen_topic_text2print     = "printer/thermal_text";
// since Version 2
const char* mqtt_listen_topic_textsize       = "printer/thermal_text_size";
const char* mqtt_listen_topic_textlineheight = "printer/thermal_text_lineheight";
const char* mqtt_listen_topic_textinverse = "printer/thermal_text_textinverse";
const char* mqtt_listen_topic_textjustify = "printer/thermal_text_textjustify";
const char* mqtt_listen_topic_textbold = "printer/thermal_text_textbold";
const char* mqtt_listen_topic_textunderline = "printer/thermal_text_textunderline";
// since Version 2.1
const char* mqtt_listen_topic_barcode = "printer/thermal_barcode"; // print barcode in syntax: <barcodetype>|<barcode_value> e.g. 4|HelloMaster here 4 is barcodetype CODE93
const char* mqtt_listen_topic_papercheck = "printer/thermal_papercheck"; // on this topic, you will recieve every defined 10 seconds the status of the paperload 
//
char mqtt_text_size                  = 'S'; // Letter size - default is S, options are S for Small, M for Medium, L for Large set it via mqtt 
const unsigned int mqtt_row_spacing  = 24; // Spacing between rows - default is 24, values range from minimum of 24 and maximum of 64 set it via mqtt 
