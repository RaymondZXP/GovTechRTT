# GovTech CAG Autonomous Trolley Collector RTT Indoor Trqacking with NRF52833
This project is pulled and modified from https://github.com/martinaalien/rangingRTT.git, see this repo for the original code.
The algorithm calculates the clock cycles the packets use between the boards. 

# Use Guide

Use guide for linux ubuntu system

1. Install GNU make 
    - sudo apt-get install build-essential checkinstall
2. Install GNU toolchain for ARM Cortex-M
    - GNU toolchain including compiler and GDB debugger can be downloaded using this link:
    https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads.
    - Download and install the latest version. Then make sure to add the path to your toolchain to your OS PATH environment variable:
    <path to install directory>/GNU Tools ARM Embedded/4.9 2015q3/bin
    - For ubuntu, you can add the path by:
    sudo nano ~/.bashrc
    go to the last line and add this line:
    export PATH=$PATH: <path to install directory>/gcc-arm-none-eabi-9-2020-q2-update/bin

    - Verify the installation of the toolchain:
    arm-none-eabi-gcc --version

3. Set the toolchain path for the project
    - after cloning the repo, go to lib_sdk/components/toolchain/gcc
    - Modify the content of Makefule.posix:
    GNU_INSTALL_ROOT ?= <path to install directory>/gcc-arm-none-eabi-9-2020-q2-update/bin/  
    (p.s. depends on the version of the toolchain you have installed, please modify the path accordingly)

4. Build the project and flash the DK
    - Navigate to /radio_A/product/nrf52840
    - Type 'make' in the terminal, GNU make should start buidling using Makefile.
    - Connect one of your NRF52833 DKs
    - type 'make flash' to programme the DK
    - Repeat the same procedure with radio_B folder with another DK, you might be asked which board to flash when you type 'make flash' if you have two boards connected. Check the serial code on the board to identify which board you are flashing.

5. View the output
    - The log from the DK will be communicated through UART, you can view the log with PuTTY
    - Install PuTTY with:
    sudo apt-get install -y putty
    - Open PuTTY by keying in 'putty' in the terminal
    - In the configuration window, click 'Serial' ('SSH' by default), change the speed to '115200' (baud rate defined for the project) and change the serial line to the serial line of your DK flashed with radio_A
    - To find out the serial line, type 'ls /dev/tty*', connect the DK and identify its serial line (usually ttyACM*)
    - Click open on the putty configuration window
    - Turn on both DK, flashed with radio_A and radio_B respectively, you should see some output from the putty window


# Current Progress 

## What is modified from the original repo
The original repo displays the output on the externally connected OED, it is now changed to log on the putty window through UART.

## Issues
1. Distance calculation parameter tunning
    For the calculation of the distance from the time difference measured at radio_A, there are a few parameters we need to tune:
        - The process time at radio_B between it receives the package and sends the response. Possible ways to measure:
            1. Place two boards close to each other and just note down the minimum time measured (sort of like a universal magic number)
            2. Start a clock at radio_B, in the package send back to radio_A, send the process time measured here

2. Change the project configuration to 52833
    - The original project is built on NRF52840, although somehow now it can be flashed on the NRF52833 board, we need to change the configuration later.
    - I have tried to change some parameters in the MakeFile, (board target and PCA and also the source paths), but I am running into some build errors when I change it. I am still figuring out how to change the configs
3. Trilateration implementation
    - Receiving packages from multiple slaves. How does the master receive packages from multiple salves to calculate different RTT (channel hopping?)
    - Better way of labelling the anchors for trilateration. The NRF devZone says there is no way to identify the board with serial ID etc with the firmware and the current measure is to mannually label the anchors, is there better way to label them?




# References

Setting up the environment: https://devzone.nordicsemi.com/nordic/nordic-blog/b/blog/posts/development-with-gcc-and-eclipse
Some paper: http://ethesisarchive.library.tu.ac.th/thesis/2016/TU_2016_5722040531_7217_4921.pdf












