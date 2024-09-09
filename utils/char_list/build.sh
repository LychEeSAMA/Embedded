#!/bin/bash

export TARGET=chr_list

# 定义颜色
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[1;34m'
NC='\033[0m' # No Color
 
function echo_color()
{
    if [[ $1 == "red" ]];then
        echo -e "${RED}$2${NC}"
    elif [[ $1 == "green" ]];then
        echo -e "${GREEN}$2${NC}"
    elif [[ $1 == "yellow" ]];then
        echo -e "${YELLOW}$2${NC}"
    elif [[ $1 == "blue" ]];then
        echo -e "${BLUE}$2${NC}"
    fi
}
 
function prepare_toolchain()
{
    export ARCH=arm
    export PATH=/develop/toolchain_t113_musl/bin/:$PATH
    echo_color yellow "Prepare toolchain for [$PLATFORM_NAME] complete."
}

function build_project()
{
    local cpu_cores=$(grep -c '^processor' /proc/cpuinfo)
    make clean
    make all -j $cpu_cores 

    if [ ! $? -eq 0 ];then
        echo_color red "Build [$TARGET] failed!"
    fi
}

function read_user_choice()
{
    echo_color blue "Please choose platform:"
    echo_color blue "1. x86"
    echo_color blue "2. T113"

    # 使用read命令读取用户输入
    read choice

    # 根据用户的输入执行相应的操作
    case $choice in
        1)
            echo_color blue "Current platform is x86."
            ;;
        2)
            echo_color blue "Current platform is T113."
            prepare_toolchain
            ;;
        *)
            echo_color red "Invaild choice, must be 1 or 2"
            read_user_choice
            ;;
    esac
}

function main()
{
    build_project
}

main