/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 Metrological
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#pragma once

#include "Module.h"
#include <interfaces/INetworkTools.h>

namespace WPEFramework {
namespace Plugin {

    class NetworkTools : public PluginHost::IPlugin, public PluginHost::IWeb, public Exchange::INetworkTools, public PluginHost::JSONRPC {
    private:
        class Data : public Core::JSON::Container {
        public:
            Data()
                : Core::JSON::Container()
                , Callsign()
                , Enabled()
            {
                Add(_T("callsign"), &Callsign);
                Add(_T("enabled"), &Enabled);
            }
            Data(const Data& copy)
                : Core::JSON::Container()
                , Callsign(copy.Callsign)
                , Enabled(copy.Enabled)
            {
                Add(_T("callsign"), &Callsign);
                Add(_T("enabled"), &Enabled);
            }
            virtual ~Data()
            {
            }

            Data& operator= (const Data& rhs)
            {
                Callsign = rhs.Callsign;
                Enabled = rhs.Enabled;

                return (*this);
            }

        public:
            Core::JSON::String Callsign;
            Core::JSON::Boolean Enabled;
        };

    public:
        NetworkTools(const NetworkTools&) = delete;
        NetworkTools& operator=(const NetworkTools&) = delete;

        NetworkTools()
            : _skipURL(0)
            , _handler(nullptr)
            , _imunityList()
        {
        }

        ~NetworkTools() override = default;

        BEGIN_INTERFACE_MAP(NetworkTools)
            INTERFACE_ENTRY(PluginHost::IPlugin)
            INTERFACE_ENTRY(PluginHost::IWeb)
            INTERFACE_ENTRY(Exchange::INetworkTools)
            INTERFACE_ENTRY(PluginHost::IDispatcher)
        END_INTERFACE_MAP

    public:
        //   IPlugin methods
        // -------------------------------------------------------------------------------------------------------
        const string Initialize(PluginHost::IShell* service) override;
        void Deinitialize(PluginHost::IShell* service) override;
        string Information() const override;

        //   IWeb methods
        // -------------------------------------------------------------------------------------------------------
        void Inbound(Web::Request& request) override;
        Core::ProxyType<Web::Response> Process(const Web::Request& request) override;

        //   INetworkTools methods
        // -------------------------------------------------------------------------------------------------------
        RPC::IStringIterator* Consumers() const override;
        bool Consumer(const string& name) const override;
        uint32_t Consumer(const string& name, const mode value) override;
        uint32_t Select(const string& name) override;

    private:
        uint8_t _skipURL;
    };

} // namespace Plugin
} // namespace WPEFramework
