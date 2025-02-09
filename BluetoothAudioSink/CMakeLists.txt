# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2021 Metrological
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

project(BluetoothAudioSink)

cmake_minimum_required(VERSION 3.3)

find_package(WPEFramework)

project_version(1.0.0)

set(MODULE_NAME ${NAMESPACE}${PROJECT_NAME})

message("Setup ${MODULE_NAME} v${PROJECT_VERSION}")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(PLUGIN_BLUETOOTHSDPSERVER_AUTOSTART true CACHE STRING "Autostart")
set(PLUGIN_BLUETOOTHSDPSERVER_CONTROLLER "BluetoothControl" CACHE STRING "Bluetooth controller callsign")
set(PLUGIN_BLUETOOTHSDPSERVER_LATENCY 0 CACHE STRING "Device audio latency adjustment (in ms)")
set(PLUGIN_BLUETOOTHAUDIOSINK_CODECSBC_PRESET "HQ" CACHE STRING "SBC codec quality preset")

find_package(${NAMESPACE}Bluetooth REQUIRED)
find_package(${NAMESPACE}Plugins REQUIRED)
find_package(${NAMESPACE}Definitions REQUIRED)
find_package(CompileSettingsDebug CONFIG REQUIRED)
find_package(SBC REQUIRED)

set(PLUGIN_BLUETOOTHAUDIOSINK_AUTOSTART true CACHE STRING true)

add_library(${MODULE_NAME} SHARED
    BluetoothAudioSink.cpp
    AudioCodecSBC.cpp
    AudioEndpoint.cpp
    ServiceDiscovery.cpp
    Module.cpp)

set_target_properties(${MODULE_NAME} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES)

target_link_libraries(${MODULE_NAME}
    PRIVATE
        CompileSettingsDebug::CompileSettingsDebug
        ${NAMESPACE}Plugins::${NAMESPACE}Plugins
        ${NAMESPACE}Definitions::${NAMESPACE}Definitions
        ${NAMESPACE}Bluetooth::${NAMESPACE}Bluetooth
        ${SBC_LIBRARIES})

install(TARGETS ${MODULE_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${STORAGE_DIRECTORY}/plugins)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")

write_config()
