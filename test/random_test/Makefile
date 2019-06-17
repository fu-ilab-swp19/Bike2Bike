# name of your application
APPLICATION = random_test

# If no BOARD is found in the environment, use this default:
BOARD ?= airfy-beacon

BOARD_WHITELIST := nrf52dk nrf51dk airfy-beacon

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT

USEMODULE += xtimer
USEMODULE += shell
USEMODULE += crypto
USEMODULE += random

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
include $(RIOTBASE)/dist/testbed-support/Makefile.iotlab
