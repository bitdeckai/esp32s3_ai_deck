# esp32s3 ai deck

	esp32s3 ai deck support crazyflie platform based on Bitcraze

## windows install tool for compile

	esp-idf-tools all
	https://dl.espressif.cn/dl/esp-idf/?idf=4.4
	
	esp-idf-tools-setup-offline-5.2.exe
	https://github.com/espressif/idf-installer/releases/download/offline-5.2/esp-idf-tools-setup-offline-5.2.exe
	
	esp-idf-tools-setup-offline-5.5.exe
	https://github.com/espressif/idf-installer/releases/download/offline-5.5/esp-idf-tools-setup-offline-5.5.exe
	

## esp32s3 compile and download

	idf.py fullclean
	idf.py set-target esp32s3
	idf.py menuconfig
	idf.py build

	//flash
	idf.py -p COM6 flash
	
	//COM monitor 115200
	idf.py -p COM6 monitor
	
	//flash and COM monitor
	idf.py -p COM6 flash monitor
	
## esp32s3 flash tool download

	https://docs.espressif.com/projects/esp-test-tools/en/latest/esp32s3/production_stage/tools/flash_download_tool.html


## code

### esp32s3_ai_deck_allinone

- support ov2640 camera stream to Web HTTP Server
- support sample micphone data then play speaker

### esp32s3_camera_ov2640_stream

- support ov2640 camera stream to Web HTTP Server
  
### esp32s3_audio_i2s_es8311

- support audio play music
- support sample micphone data then play speaker 
  
        