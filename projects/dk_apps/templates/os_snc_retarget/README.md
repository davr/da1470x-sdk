Dialog CoRoutines template demo application for SNC {#os_snc_retarget}
======================================================

## Overview

This application is a simple implementation of a Dialog CoRoutines template application.
main.c creates a template task which sends periodically notifications to M33.

## Installation procedure

The project is located in the `projects/dk_apps/templates/os_snc_retarget` folder.
This project is not standalone. The produced SNC binary shall be used with an M33 project,
i.e. `os_main_retarget`, located in `projects/dk_apps/templates/os_main_retarget`.

## File structure

File structure is as follows:

* projects/dk_apps/templates/os_snc_retarget
    * config
        * custom_config_snc.h
    * interface
        * snc_shared_space.h
        * snc_shared_space.c
    * sdk
    * src
        * main.c
    * startup

## Existing build configurations

The template contains build configurations for execution from RAM on SNC.

- `DA1470X-00-SNC-Debug`. The project is built to run from RAM on SNC.
  The executable is built with debug (-Og) information.
- `DA1470X-00-SNC-Release`. The project is built to run from RAM on SNC.
  The executable is built with no debug information and size optimization (-Os).
