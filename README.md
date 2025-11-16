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

	idf.py -p COM6 flash
	idf.py -p COM6 monitor
	//或者下载加监控串口一起
	idf.py -p COM6 flash monitor
	
## esp32s3 flash tool download

	https://docs.espressif.com/projects/esp-test-tools/en/latest/esp32s3/production_stage/tools/flash_download_tool.html