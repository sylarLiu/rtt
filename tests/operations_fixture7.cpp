/***************************************************************************
  tag: The SourceWorks  Tue Sep 7 00:54:57 CEST 2010  operations_fixture7.cpp

                        operations_fixture7.cpp -  description
                           -------------------
    begin                : Tue September 07 2010
    copyright            : (C) 2010 The SourceWorks
    email                : peter@thesourceworks.com

 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#define BOOST_FUSION_INVOKE_MAX_ARITY 8
#define BOOST_FUSION_UNFUSED_MAX_ARITY 7

#include "operations_fixture.hpp"
#include <iostream>
#include <TaskContext.hpp>
#include <OperationCaller.hpp>
#include <Operation.hpp>
#include <Service.hpp>

using namespace std;
using namespace boost;
using namespace RTT;
using namespace RTT::detail;

void OperationsFixture::createOperationCallerFactories7(TaskContext* target)
{
    Service::shared_ptr to = target->provides("methods");
    // ClientThread
    to->addOperation("m7", &OperationsFixture::m7, this).doc("M7").arg("a", "ad").arg("a", "ad").arg("a", "ad").arg("a", "ad").arg("a", "ad").arg("a", "ad").arg("a", "ad");

    // OwnThread
    to->addOperation("o7", &OperationsFixture::m7, this, OwnThread).doc("M7").arg("a", "ad").arg("a", "ad").arg("a", "ad").arg("a", "ad").arg("a", "ad").arg("a", "ad").arg("a", "ad");
}
