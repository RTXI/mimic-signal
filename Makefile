PLUGIN_NAME = mimic

HEADERS = mimic.h

SOURCES = mimic.cpp \
          moc_mimic.cpp\

### Do not edit below this line ###

include $(shell rtxi_plugin_config --pkgdata-dir)/Makefile.plugin_compile
