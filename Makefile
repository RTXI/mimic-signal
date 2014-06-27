PLUGIN_NAME = mimic_signal

HEADERS = mimic.h

SOURCES = mimic.cpp\
	moc_mimic.cpp

LIBS = 

### Do not edit below this line ###

include $(shell rtxi_plugin_config --pkgdata-dir)/Makefile.plugin_compile
