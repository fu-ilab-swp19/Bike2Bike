# name of your application
APPLICATION = timer_bug

# If no BOARD is found in the environment, use this default:
BOARD ?= airfy-beacon

# So far, NimBLE only works on nRF52 based platforms
BOARD_WHITELIST := nrf52dk nrf52840dk airfy-beacon nrf51dk

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT

USEMODULE += xtimer
USEMODULE += shell

# configure and use Nimble
USEPKG += nimble

BLE_RESERVED_PACKAGE_SIZE = 150
CFLAGS += -DMYNEWT_VAL_MSYS_1_BLOCK_SIZE=$(BLE_RESERVED_PACKAGE_SIZE)
# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
#DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
