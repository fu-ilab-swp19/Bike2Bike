# name of your application
APPLICATION = button_interrupts

# If no BOARD is found in the environment, use this default:
BOARD ?= nrf52dk

# Only written for nrf52dk!
BOARD_WHITELIST := nrf52dk

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT

# We use the xtimer and the shell in this example
USEMODULE += periph_gpio_irq
USEMODULE += xtimer
USEMODULE += shell

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
#DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
