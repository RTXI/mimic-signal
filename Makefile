PLUGIN_NAME = mimic-signal

HEADERS = mimic-signal.h

SOURCES = mimic-signal.cpp\
	moc_mimic-signal.cpp

LIBS = 

### Do not edit below this line ###

include $(shell rtxi_plugin_config --pkgdata-dir)/Makefile.plugin_compile
