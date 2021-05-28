const char* ssid                    = "WIFI-SSID-XX";
const char* password                = "randompassword123";
const char* mqtt_server             = "192.168.1.100";
const char* mqtt_user               = "user";
const char* mqtt_pass               = "password";
const char* my_id                   = "thermal_printer";
const unsigned int mqtt_port        = 1883;
const unsigned int baud             = 9600;
const char* mqtt_listen_topic_text2print     = "printer/thermal_text";
// new in Version 2
const char* mqtt_listen_topic_textsize       = "printer/thermal_text_size";
const char* mqtt_listen_topic_textlineheight = "printer/thermal_text_lineheight";
const char* mqtt_listen_topic_textinverse = "printer/thermal_text_textinverse";
const char* mqtt_listen_topic_textjustify = "printer/thermal_text_textjustify";
const char* mqtt_listen_topic_textbold = "printer/thermal_text_textbold";
const char* mqtt_listen_topic_textunderline = "printer/thermal_text_textunderline";
//
char mqtt_text_size                  = 'S'; // Letter size - default is S, options are S for Small, M for Medium, L for Large set it via mqtt 
const unsigned int mqtt_row_spacing  = 24; // Spacing between rows - default is 24, values range from minimum of 24 and maximum of 64 set it via mqtt 
