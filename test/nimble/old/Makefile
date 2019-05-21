
# name of your application
APPLICATION = Bike2Bike

# If no BOARD is found in the environment, use this default:
BOARD ?= airfy-beacon

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/RIOT

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
CFLAGS += -DDEVELHELP

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

# Modules to include:
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += xtimer
USEMODULE += nrfble

# USEPKG += nordic_softdevice_ble

include $(RIOTBASE)/Makefile.include