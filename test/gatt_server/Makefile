# name of your application
APPLICATION = nimble_gatt

# If no BOARD is found in the environment, use this default:
BOARD ?= airfy-beacon

# So far, NimBLE only works on nRF52 based platforms
BOARD_WHITELIST := nrf52dk nrf52840dk nrf52832-mdk airfy-beacon

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT

# Include NimBLE
USEPKG += nimble
USEMODULE += shell

#USEMODULE += nimble_svc_gap
#USEMODULE += nimble_svc_gatt
#USEMODULE += nimble_scanlist

# We also use the AD part of the BLE helper module
USEMODULE += bluetil_ad

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
