
//******************************************************************************
// RCF - Remote Call Framework
//
// Copyright (c) 2005 - 2012, Delta V Software. All rights reserved.
// http://www.deltavsoft.com
//
// RCF is distributed under dual licenses - closed source or GPL.
// Consult your particular license for conditions of use.
//
// If you have not purchased a commercial license, you are using RCF 
// under GPL terms.
//
// Version: 2.0
// Contact: support <at> deltavsoft.com 
//
//******************************************************************************

#ifndef INCLUDE_RCF_UNIXLOCALENDPOINT_HPP
#define INCLUDE_RCF_UNIXLOCALENDPOINT_HPP

#include <RCF/Endpoint.hpp>
#include <RCF/Export.hpp>
#include <RCF/ClientTransport.hpp>
#include <RCF/ServerTransport.hpp>

#include <SF/SerializeParent.hpp>

#if defined(BOOST_WINDOWS)
#error Unix domain sockets not supported on Windows.
#endif

namespace RCF {

    class RCF_EXPORT UnixLocalEndpoint : public I_Endpoint
    {
    public:

        UnixLocalEndpoint();

        UnixLocalEndpoint(const std::string & pipeName);

        ServerTransportAutoPtr createServerTransport() const;
        ClientTransportAutoPtr createClientTransport() const;
        EndpointPtr clone() const;

        std::string asString() const;

#ifdef RCF_USE_SF_SERIALIZATION

        void serialize(SF::Archive &ar);

#endif

        std::string getPipeName() const
        {
            return mPipeName;
        }

    private:

        std::string mPipeName;
    };

} // namespace RCF

#endif // ! INCLUDE_RCF_UNIXLOCALENDPOINT_HPP
