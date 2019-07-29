// Copyright (c) Microsoft Corporation. All rights reserved.
#define LOG_MODULE DBG_API
#include "pal/PAL.hpp"
#include "pal/DeviceInformationImpl.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <locale>
#include <codecvt>

#include "sysinfo_sources.hpp"

#define DEFAULT_DEVICE_ID       "{deadbeef-fade-dead-c0de-cafebabefeed}"

namespace PAL_NS_BEGIN {

    /* TODO: power source is not implemented */
    PowerSource GetCurrentPowerSource()
    {
        return PowerSource_Charging;
    }

    ///// IDeviceInformation API
    DeviceInformationImpl::DeviceInformationImpl() :
                                m_info_helper()
    {
#if defined(ARCH_ARM)
        m_os_architecture = OsArchitectureType_Arm;
#elif defined(ARCH_32BIT)
        m_os_architecture = OsArchitectureType_X86;
#elif defined(ARCH_64BIT)
        m_os_architecture = OsArchitectureType_X64;
#else
        m_os_architecture = OsArchitectureType_Unknown;
#endif

        std::string devId = aria_hwinfo.get("devId");
        m_device_id = (devId.empty()) ? DEFAULT_DEVICE_ID : devId;

        m_manufacturer = aria_hwinfo.get("devMake");

        m_model = aria_hwinfo.get("devModel");

        m_powerSource = GetCurrentPowerSource();

    }

    std::string DeviceInformationImpl::GetDeviceTicket() const
    {
        return m_deviceTicket;
    }

#ifdef ENABLE_LEGACY_CODE
    size_t DeviceInformationImpl::GetMemorySize() const
    {
        return 0;
    }
#endif

    IDeviceInformation* DeviceInformationImpl::Create()
    {
        return new DeviceInformationImpl();
    }

    DeviceInformationImpl::~DeviceInformationImpl() {}

} PAL_NS_END