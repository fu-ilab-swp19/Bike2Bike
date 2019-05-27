# name of your application
APPLICATION = listening

# If no BOARD is found in the environment, use this default:
BOARD ?= nrf52dk

# So far, NimBLE only works on nRF52 based platforms
BOARD_WHITELIST := nrf52dk nrf52840dk airfy-beacon

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT

# We use the xtimer and the shell in this example
USEMODULE += xtimer
USEMODULE += shell
USEMODULE += nimble_scanner
USEMODULE += nimble_scanlist
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
