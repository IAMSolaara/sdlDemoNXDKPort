XBE_TITLE = EGP_lorecast
GEN_XISO = $(XBE_TITLE).iso
SRCS =$(CURDIR)/projFunctions.cpp $(CURDIR)/main.cpp 
NXDK_DIR = /opt/nxdk
NXDK_SDL = y
include $(NXDK_DIR)/Makefile

TARGET += $(OUTPUT_DIR)/res/
$(GEN_XISO): $(OUTPUT_DIR)/res/
$(OUTPUT_DIR)/res/: $(CURDIR)/res/ $(OUTPUT_DIR)
	$(VE)cp -r '$<' '$@'
