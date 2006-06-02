/***************************************************************************
  tag: Peter Soetens  Mon May 10 19:10:37 CEST 2004  Types.cxx 

                        Types.cxx -  description
                           -------------------
    begin                : Mon May 10 2004
    copyright            : (C) 2004 Peter Soetens
    email                : peter.soetens@mech.kuleuven.ac.be
 
 ***************************************************************************
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place,                                    *
 *   Suite 330, Boston, MA  02111-1307  USA                                *
 *                                                                         *
 ***************************************************************************/
#include "corelib/Types.hpp"

#include <pkgconf/system.h>
#include <pkgconf/corelib.h>

#include <corelib/MultiVector.hpp>
#include <corelib/Logger.hpp>
#include "corelib/Attribute.hpp"
#include "corelib/DataSourceAdaptor.hpp"
#include "corelib/TemplateTypeInfo.hpp"
#include <corelib/TypeStream.hpp>
#include <corelib/mystd.hpp>

#ifdef OROCFG_CORELIB_REALTIME_TOOLKIT_IMPORT
#include <corelib/RealTimeToolkit.hpp>
#endif

#include <functional>
#include <sstream>

using namespace std;
using namespace ORO_CoreLib::detail;

#ifdef OROCFG_CORELIB_REALTIME_TOOLKIT_IMPORT
#include <os/StartStopManager.hpp>
namespace ORO_CoreLib {
    namespace {

        /**
         * This struct has the sole purpose of invoking
         * the Import function.
         */
        int loadRTT()
        {
            Toolkit::Import( RealTimeToolkit );
            return true;
        }

        ORO_OS::InitFunction RTTLoader( &loadRTT );
    }
}
#endif


namespace ORO_CoreLib
{
    AttributeBase* TypeInfo::buildVariable( int ) const {
        return this->buildVariable();
    }

    AttributeBase* TypeInfo::buildConstant(DataSourceBase::shared_ptr dsb, int ) const {
        return this->buildConstant( dsb );
    }


    TypeInfo::~TypeInfo()
    {
    }

    string TypeInfo::toString( DataSourceBase::shared_ptr in ) const
    {
        stringstream result;
        this->write( result, in );
        return result.str();
    }

    namespace {
        boost::shared_ptr<TypeInfoRepository> typerepos;
    }

    TypeInfoRepository::TypeInfoRepository()
    {
    }

    boost::shared_ptr<TypeInfoRepository> TypeInfoRepository::Instance()
    {
        if ( typerepos ) 
            return typerepos;
        typerepos.reset( new TypeInfoRepository() );

        return typerepos;
    }

    TypeInfo* TypeInfoRepository::type( const std::string& name ) const
    {
        map_t::const_iterator i = data.find( name );
        if ( i == data.end() )
            return 0;
        else return i->second;
    }

    TypeInfoRepository::~TypeInfoRepository()
    {
        map_t::const_iterator i = data.begin();
        for( ; i != data.end(); ++i )
            delete i->second;
    }


    bool TypeInfoRepository::addType(TypeInfo* t)
    {
        if ( data.count( t->getTypeName() ) != 0 ) {
            Logger::log() << Logger::Warning << "Attempt to register Type '"<<t->getTypeName() <<"' twice to the Orocos Type System."<<Logger::endl;
        }
        data[ t->getTypeName() ] = t;
        Logger::log() << Logger::Debug << "Registered Type '"<<t->getTypeName() <<"' to the Orocos Type System."<<Logger::endl;
        return true;
    }

    std::vector<std::string> TypeInfoRepository::getTypes() const
    {
        return ORO_std::keys( data );
    }

}
