Audio demo application {#audio_demo}
======================================================

## Overview

The application demonstrates how various audio data paths can be implemented.

Features:

- The application prints the path configuration of each demo used via UART2,
- The application checks the usage of PDM input to I2S output and I2S input to I2S output paths.
- If it is supported, the application checks the parallel usage of SRC1 and SRC2 using two audio data paths.

There is a number of demos supplied as examples:

1. PDM-SRC1-PCM configuration for voice/audio streaming.
2. PDM-SRC1-MEMORY-> MEMORY-SRC1-PCM configuration for voice recording for duration configured according to build configuration and audio playback.
3. PCM-SRC1-PCM configuration for voice/audio streaming.
4. PCM-SRC1-MEMORY-> MEMORY-SRC1-PCM configuration for voice recording for duration configured according to build configuration and audio playback.
5. Two parallel paths, if it is supported:
  -  PATH_1: PDM-SRC1-MEMORY configuration for voice recording for duration configured according to build configuration.
  -  PATH_2: MEMORY-SRC2-PCM configuration for playback of a tone of 1000 Hz saved in RAM.
6. MEMORY-SRC1-MEMORY configuration that changes the sample rate of a tone in the memory.
7. SDADC-SRC1-PCM configuration for voice/audio streaming.(if it is supported)
8. SDADC-SRC1-MEMORY-> MEMORY-SRC1-PCM configuration for voice recording for duration configured according to build configuration and audio playback.(if it is supported)

  Note:
  - The DA7218 Codec is clocked (MCLK input) by DIVN, mapped through P020. By default it is set to 32MHz.
  - Demos are implemented with the specific configuration (sample rate, bit depth etc.).
  Further configurability is not supported.
  - Demos that include PCM interface can be ran using either DIVN or DIV1(all supported clocks) system clock by setting:

~~~{.c}
        #define SYS_CLK_DIV1                             (1)
~~~
  - Demos that include PCM or MEMORY can have sample rate conversion between two pairs of sample rates:

        1. 16KHz to/from 8KHz by setting:

~~~{.c}
        #define SR1_16_SR2_8                             (1)
        #define SR1_48_SR2_32                            (0)
~~~

         2. 48KHz to/from 32KHz by setting:

~~~{.c}
         #define SR1_16_SR2_8                            (0)
         #define SR1_48_SR2_32                           (1)
~~~
        when PCM is used as output the sample rate is 16/48KHz respectively.

### Folder structure

| Top level folders       | Description
|------------------------ | -------------------------------------------------------
| config/                 | Configuration of demo applications
| sdk/		              | SDK layer
| startup/                | Startup files


| Inlcudes folder contents           | Description
|----------------------------------- | ---------------------------------------------------------------------------------------
| includes/DA7218_driver.h           | Driver for DA7218
| includes/audio_task.h              | Default application configuration (see Suggested configurable parameters)
| includes/periph_setup.h            | Default GPIO pin assignment (see GPIO assignments)
| includes/DA7218_regs.h             | Registers file of Codec DA7218 (should not be modified directly, modify DA7218_driver.h above instead)
| includes/demo_helpers.h	         | Construction of sin and cos tones

###Demos

Using the audio_demo, it is possible to check how Audio framework works.
The features depend on the selected demos which are described below. Only one audio demo should be selected each time.

In general, demos use:
- DA7218_driver.c: functions for Codec DA7218 (apart from DEMO_MEM_TO_MEM)
- audio_task.c :   Demos implementation
- demo_helpers.c:  functions for construction of tones (used only from DEMO_MEM_TO_MEM and DEMO_PDM_MIC_PARALLEL_SRCS)

#### PDM-SRC1-PCM configuration
- **Demonstrated path**: PDM-SRC1-PCM

- **Source file**: audio_task.c

- **Description**:<br>
The demo allows the user to listen from PDM Mic input (such as SPK0838HT4H-B, SPH1668LM4H-1, SPM1423HM4H-B digital microphones),
using a headset, hooked in a DA7218 module jack.

- **Hardware Setup**:
- Dialog DA7218 mikrobus module or embedded Codec DA7218 on motherboard
- SPK0838HT4H-B digital microphone

- **Run steps**:<br>
To enable the demo go to the `includes/audio_task.h` file, the respective macro must be set to (1). If the platform supports it, there are also the options to run the PDM_MIC_PARALLEL_SRCS demo, SDADC_MIC demo and SDADC_RECORD_PLAYBACK demo.

~~~{.c}
#define DEMO_PCM_MIC                    (0)
#define DEMO_PCM_RECORD_PLAYBACK        (0)
#define DEMO_PDM_MIC                    (1)
#define DEMO_PDM_MIC_PARALLEL_SRCS      (0)
#define DEMO_SDADC_MIC                  (0)
#define DEMO_SDADC_RECORD_PLAYBACK      (0)
#define DEMO_PDM_RECORD_PLAYBACK        (0)
#define DEMO_MEM_TO_MEM                 (0)
~~~

####  PDM-SRC1-MEMORY-> MEMORY-SRC1-PCM configuration
- **Demonstrated path**: PDM-SRC1-MEMORY-> MEMORY-SRC1-PCM

- **Source file**: audio_task.c

- **Description**:<br>
The demo allows the user to listen from PDM Mic input (such as SPK0838HT4H-B, SPH1668LM4H-1, SPM1423HM4H-B digital microphones), using a headset hooked in a DA7218 module jack. More specifically:
	- The PDM-SRC1-Memory configuration allows the user to record PDM input to XiP flash (Log partition) by  pressing  K1 button.
	  The recording duration is differentiated according to build configuration with the default sample rate and bit depth.
	- The  Memory-SRC1-PCM configuration allows the user to listen to recorded audio, using a headset hooked in a DA7218 module jack.

- **Hardware Setup**:
- Dialog DA7218 mikrobus module or embedded Codec DA7218 on motherboard
- SPK0838HT4H-B digital microphone

- **Run steps**:<br>
To enable the demo go to the `includes/audio_task.h` file the respective macro must be set to (1). If the platform supports it, there are also the options to run the PDM_MIC_PARALLEL_SRCS demo, SDADC_MIC demo and SDADC_RECORD_PLAYBACK demo.

~~~{.c}
#define DEMO_PCM_MIC                    (0)
#define DEMO_PCM_RECORD_PLAYBACK        (0)
#define DEMO_PDM_MIC                    (0)
#define DEMO_PDM_MIC_PARALLEL_SRCS      (0)
#define DEMO_SDADC_MIC                  (0)
#define DEMO_SDADC_RECORD_PLAYBACK      (0)
#define DEMO_PDM_RECORD_PLAYBACK        (1)
#define DEMO_MEM_TO_MEM                 (0)
~~~

####   PCM-SRC1-PCM configuration
- **Demonstrated path**:  PCM-SRC1-PCM

- **Source file**: audio_task.c

- **Description**:<br>
The demo  allows the user to listen from a PCM Mic input, using a headset hooked in a DA7218 module jack.

- **Hardware Setup**:
- Dialog DA7218 mikrobus module or embedded Codec DA7218 on motherboard

- **Run steps**:<br>
To enable the demo go to the `includes/audio_task.h` file  the respective macro must be set to (1). If the platform supports it, there are also the options to run the PDM_MIC_PARALLEL_SRCS demo, SDADC_MIC demo and SDADC_RECORD_PLAYBACK demo.

~~~{.c}
#define DEMO_PCM_MIC                    (1)
#define DEMO_PCM_RECORD_PLAYBACK        (0)
#define DEMO_PDM_MIC                    (0)
#define DEMO_PDM_MIC_PARALLEL_SRCS      (0)
#define DEMO_SDADC_MIC                  (0)
#define DEMO_SDADC_RECORD_PLAYBACK      (0)
#define DEMO_PDM_RECORD_PLAYBACK        (0)
#define DEMO_MEM_TO_MEM                 (0)
~~~

####  PCM-SRC1-MEMORY-> MEMORY-SRC1-PCM configuration
- **Demonstrated path**:  PCM-SRC1-MEMORY-> MEMORY-SRC1-PCM

- **Source file**: audio_task.c

- **Description**:<br>
- The demo  allows the user to listen from a PCM Mic input, using a headset hooked in a DA7218 module jack. More specifically:
	- The PCM-SRC1-Memory configuration allows the user to record PCM input to XiP flash (Log partition) by  pressing  K1 button.
        The recording duration is differentiated according to build configuration with the default sample rate and bit depth.
	- The Memory-SRC1-PCM configuration allows the user to listen to recorded audio, using a headset hooked in a DA7218 module jack.

- **Hardware Setup**:
- Dialog DA7218 mikrobus module or embedded Codec DA7218 on motherboard

- **Run steps**:<br>
To enable the demo go to the `includes/audio_task.h` file  the respective macro must be set to (1). If the platform supports it, there are also the options to run the PDM_MIC_PARALLEL_SRCS demo, SDADC_MIC demo and SDADC_RECORD_PLAYBACK demo.

~~~{.c}
#define DEMO_PCM_MIC                    (0)
#define DEMO_PCM_RECORD_PLAYBACK        (1)
#define DEMO_PDM_MIC                    (0)
#define DEMO_PDM_MIC_PARALLEL_SRCS      (0)
#define DEMO_SDADC_MIC                  (0)
#define DEMO_SDADC_RECORD_PLAYBACK      (0)
#define DEMO_PDM_RECORD_PLAYBACK        (0)
#define DEMO_MEM_TO_MEM                 (0)
~~~

####  Two parallel paths configuration
- **Demonstrated paths**:
		PATH_1: PDM-SRC1-MEMORY
  		PATH_2: MEMORY-SRC2-PCM

- **Source file**: audio_task.c

- **Description**:<br>
    The demo  allows the user to listen the 1 KHz tone, using a headset hooked in a DA7218 module jack and using debugger to retrieve the data recorded from PDM Mic input. More specifically:
	- The PDM-SRC1-MEMORY configuration allows the  user to record PDM input to RAM for a duration differentiated according to build configuration with the default sample rate and bit depth. Recorded data can be retrieved using debugger's memory browser.
	- The Memory-SRC2-PCM configuration allows the user to listen to recorded tone, using a headset hooked in a DA7218 module jack.

- **Hardware Setup**:
- Dialog DA7218 mikrobus module or embedded Codec DA7218 on motherboard

- **Run steps**:<br>
To enable the demo go to the `includes/audio_task.h` file  the respective macro must be set to (1). If the platform supports it, there are also the options to run the PDM_MIC_PARALLEL_SRCS demo, SDADC_MIC demo and SDADC_RECORD_PLAYBACK demo.

~~~{.c}
#define DEMO_PCM_MIC                    (0)
#define DEMO_PCM_RECORD_PLAYBACK        (0)
#define DEMO_PDM_MIC                    (0)
#define DEMO_PDM_MIC_PARALLEL_SRCS      (1)
#define DEMO_SDADC_MIC                  (0)
#define DEMO_SDADC_RECORD_PLAYBACK      (0)
#define DEMO_PDM_RECORD_PLAYBACK        (0)
#define DEMO_MEM_TO_MEM                 (0)
~~~

#### MEMORY-SRC1-MEMORY configuration
- **Demonstrated path**:  MEMORY-SRC1-MEMORY

- **Source file**: audio_task.c

- **Description**:<br>
- The demo  convert the sample rate of 16 KHz of a tone of 1 KHz in memory to 8 KHz sample rate.
  Using memory browser, the tone in the input memory buffer must be the same with the one in the output memory buffer.

- **Run steps**:<br>
To enable the demo go to the `includes/audio_task.h` file  the respective macro must be set to (1). If the platform supports it, there are also the options to run the PDM_MIC_PARALLEL_SRCS demo, SDADC_MIC demo and SDADC_RECORD_PLAYBACK demo.

~~~{.c}
#define DEMO_PCM_MIC                    (0)
#define DEMO_PCM_RECORD_PLAYBACK        (0)
#define DEMO_PDM_MIC                    (0)
#define DEMO_PDM_MIC_PARALLEL_SRCS      (0)
#define DEMO_SDADC_MIC                  (0)
#define DEMO_SDADC_RECORD_PLAYBACK      (0)
#define DEMO_PDM_RECORD_PLAYBACK        (0)
#define DEMO_MEM_TO_MEM                 (1)
~~~

#### SDADC-SRC1-PCM configuration
- **Demonstrated path**: SDADC-SRC1-PCM

- **Source file**: audio_task.c

- **Description**:<br>
The demo allows the user to listen from SDADC Mic input (CMM-3729AB-38108-TR mems analog microphone), using a headset, hooked in a DA7218 module jack.

- **Hardware Setup**:
- Dialog DA7218 mikrobus module or embedded Codec DA7218 on motherboard
- CMM-3729AB-38108-TR mems analog microphone or embedded CMM-3729AB-38108-TR mems analog microphone on daughter-board

- **Run steps**:<br>
To enable the demo go to the `includes/audio_task.h` file  the respective macro must be set to (1). If the platform supports it, there are also the options to run the PDM_MIC_PARALLEL_SRCS demo, SDADC_MIC demo and SDADC_RECORD_PLAYBACK demo.

~~~{.c}
#define DEMO_PCM_MIC                    (0)
#define DEMO_PCM_RECORD_PLAYBACK        (0)
#define DEMO_PDM_MIC                    (0)
#define DEMO_PDM_MIC_PARALLEL_SRCS      (0)
#define DEMO_SDADC_MIC                  (1)
#define DEMO_SDADC_RECORD_PLAYBACK      (0)
#define DEMO_PDM_RECORD_PLAYBACK        (0)
#define DEMO_MEM_TO_MEM                 (0)
~~~

####  SDADC-SRC1-MEMORY-> MEMORY-SRC1-PCM configuration
- **Demonstrated path**: PDM-SRC1-MEMORY-> MEMORY-SRC1-PCM

- **Source file**: audio_task.c

- **Description**:<br>
The demo allows the user to listen from SDADC Mic input (CMM-3729AB-38108-TR mems analog microphone), using a headset hooked in a DA7218 module jack. More specifically:
	- The SDADC-SRC1-Memory configuration allows the user to record PDM input to RAM by  pressing  K1 button.
	  The recording duration is differentiated according to build configuration with the default sample rate and bit depth.
	- The  Memory-SRC1-PCM configuration allows the user to listen to recorded audio, using a headset hooked in a DA7218 module jack.

- **Hardware Setup**:
- Dialog DA7218 mikrobus module or embedded Codec DA7218 on motherboard
- CMM-3729AB-38108-TR mems analog microphone or embedded CMM-3729AB-38108-TR mems analog microphone on daughter-board

- **Run steps**:<br>
To enable the demo go to the `includes/audio_task.h` file  the respective macro must be set to (1). If the platform supports it, there are also the options to run the PDM_MIC_PARALLEL_SRCS demo, SDADC_MIC demo and SDADC_RECORD_PLAYBACK demo.

~~~{.c}
#define DEMO_PCM_MIC                    (0)
#define DEMO_PCM_RECORD_PLAYBACK        (0)
#define DEMO_PDM_MIC                    (0)
#define DEMO_PDM_MIC_PARALLEL_SRCS      (0)
#define DEMO_SDADC_MIC                  (0)
#define DEMO_SDADC_RECORD_PLAYBACK      (1)
#define DEMO_PDM_RECORD_PLAYBACK        (0)
#define DEMO_MEM_TO_MEM                 (0)
~~~

*Both for DA1469X and D2634:*

-  DA7218 module jack is attached in mikroBUS 1 for the external dev kit of DA1469X.

*For DA1470X:*

- Motherboard 500-05-D (Rev.D) should be used.
- A DA7218 codec is embedded on the motherboard (DA147x DevKit). To deploy it the following configuration is needed:
> J11 pins 1 & 2 must be shorted.(Signals DA7218_BCLK and DA7218_DI are connected to P013 and P012 respectively.)


## Installation procedure

The project is located in the `projects/dk_apps/demos/audio_demo` folder.

To install the project follow the [General Installation and Debugging Procedure](@ref install_and_debug_procedure).

## File structure

The following file structure will be created:

* projects/dk_apps/demos/audio_demo/

    * config
        * custom_config_oqspi.h (only for DA1470X)
        * custom_config_qspi.h
        * custom_config_ram.h
    * includes
        * audio_task.h
        * DA7218_driver.h
        * DA7218_regs.h
        * demo_helpers.h
        * periph_setup.h
    * sdk
    * src
        * audio_task.c
        * config_audio_demo.c
        * DA7218_driver.c
        * demo_helpers.c
        * main.c

## Existing build configurations

The template contains build configurations for executing it from RAM, QSPI or OQSPI.

- `DA1469X-00-Debug_RAM`. The project is built to be run from RAM. The executable is built with debug (-Og) information.
- `DA1469X-00-Debug_QSPI`. The project is built to be run from QSPI. The executable is built with debug (-Og) information.
- `DA1469X-00-Release_RAM`. The project is built to be run from RAM. The executable is built with no debug information and size optimization (-Os).
- `DA1469X-00-Release_QSPI`. The project is built to be run from QSPI. The executable is built with no debug information and size optimization (-Os).
- `DA1470X-00-Debug_RAM`. The project is built to be run from RAM. The executable is built with debug (-Og) information.
- `DA1470X-00-Debug_OQSPI`. The project is built to be run from OQSPI. The executable is built with debug (-Og) information.
- `DA1470X-00-Release_RAM`. The project is built to be run from RAM. The executable is built with no debug information and size optimization (-Os).
- `DA1470X-00-Release_OQSPI`. The project is built to be run from OQSPI. The executable is built with no debug information and size optimization (-Os).
- `D2634-00-Debug_RAM`. The project is built to be run from RAM. The executable is built with debug (-Og) information.
- `D2634-00-Debug_eFLASH`. The project is built to be run from eFLASH. The executable is built with debug (-Og) information.
- `D2798-00-Debug_RAM`. The project is built to be run from RAM. The executable is built with debug (-Og) information.
- `D2798-00-Debug_oQSPI`. The project is built to be run from OQSPI. The executable is built with debug (-Og) information.

