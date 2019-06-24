# name of your application
APPLICATION = bike2bike

# If no BOARD is found in the environment, use this default:
BOARD ?= airfy-beacon

BOARD_WHITELIST := nrf52dk airfy-beacon

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT

USEPKG += nimble

USEMODULE += xtimer
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += bluetil_ad
USEMODULE += nimble_scanner
USEMODULE += crypto
USEMODULE += periph_gpio_irq

BLE_RESERVED_PACKAGE_SIZE = 70
CFLAGS += -DMYNEWT_VAL_MSYS_1_BLOCK_SIZE=$(BLE_RESERVED_PACKAGE_SIZE)
CFLAGS += -DCRYPTO_AES

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
#DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
include $(RIOTBASE)/dist/testbed-support/Makefile.iotlab
