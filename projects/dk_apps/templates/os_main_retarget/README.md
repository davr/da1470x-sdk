FreeRTOS template demo application using SNC {#os_main_retarget}
======================================================

## Overview

This application is a simple implementation of a FreeRTOS template application which uses SNC.
main.c creates a template task which is notified periodically by SNC and prints
a timestamp and a counter to the output.

## Installation procedure

The project is located in the `projects/dk_apps/templates/os_main_retarget` folder.

To install the project follow the [General Installation and Debugging Procedure](@ref install_and_debug_procedure).

This project depends on another project located in `projects/dk_apps/templates/os_snc_retarget`.
When triggering an `os_main_retarget` build, `os_snc_retarget` is automatically built first.

## File structure

File structure is as follows:

* projects/dk_apps/templates/os_main_retarget
    * config
        * custom_config_oqspi.h
        * custom_config_ram.h
    * interface --> symbolic link to `projects/dk_apps/templates/os_snc_retarget/interface`
    * sdk
    * src
        * main.c
    * startup

## Existing build configurations

The template contains build configurations for execution from RAM or OQSPI.

- `DA1470X-00-Debug_RAM`. The project is built to run from RAM.
  The executable is built with debug (-Og) information.
- `DA1470X-00-Debug_OQSPI`. The project is built to run from OQSPI.
  The executable is built with debug (-Og) information.
- `DA1470X-00-Release_RAM`. The project is built to run from RAM.
  The executable is built with no debug information and size optimization (-Os).
- `DA1470X-00-Release_OQSPI`. The project is built to run from OQSPI.
  The executable is built with no debug information and size optimization (-Os).

## RTT ENABLE

The template gives the user the option to redirect the output either to RTT or
Retarget by defining the CONFIG_RETARGET pre-processor macro.

> Note: The template uses the retarget option by default.
