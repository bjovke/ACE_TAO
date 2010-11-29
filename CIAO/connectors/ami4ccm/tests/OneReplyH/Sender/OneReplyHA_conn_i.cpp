// -*- C++ -*-
// $Id$

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v1.8.3
 * TAO and the TAO IDL Compiler have been developed by:
 *       Center for Distributed Object Computing
 *       Washington University
 *       St. Louis, MO
 *       USA
 *       http://www.cs.wustl.edu/~schmidt/doc-center.html
 * and
 *       Distributed Object Computing Laboratory
 *       University of California at Irvine
 *       Irvine, CA
 *       USA
 * and
 *       Institute for Software Integrated Systems
 *       Vanderbilt University
 *       Nashville, TN
 *       USA
 *       http://www.isis.vanderbilt.edu/
 *
 * Information about TAO is available at:
 *     http://www.cs.wustl.edu/~schmidt/TAO.html
 **/

// TAO_IDL - Generated from
// be/be_codegen.cpp:1661

#include "OneReplyHA_conn_i.h"
#include "OneReplyH_Sender_exec.h"

namespace CIAO_OneReplyH_Sender_Impl
{
  AMI4CCM_MyFooReplyHandler_i::AMI4CCM_MyFooReplyHandler_i (
      Atomic_UShort &nr_of_received)
   : nr_of_received_ (nr_of_received)
  {
  }

  AMI4CCM_MyFooReplyHandler_i::~AMI4CCM_MyFooReplyHandler_i (void)
  {
  }

  void
  AMI4CCM_MyFooReplyHandler_i::foo (::CORBA::Long ami_return_val,
                                         const char * /* answer */)
  {
    if ( ami_return_val == OneReplyH::cmd_asynch_foo_ok)
     {
       ++this->nr_of_received_;
     }
  }

  void
  AMI4CCM_MyFooReplyHandler_i::foo_excep (
      ::CCM_AMI::ExceptionHolder_ptr excep_holder)
  {
    try
       {
         excep_holder->raise_exception ();
       }
     catch (const OneReplyH::InternalError& ex)
       {
         CIAO_OneReplyH_Sender_Impl::HandleException (ex.id,
                               OneReplyH::cmd_asynch_foo_nok,
                               ex.error_string.in(), "asynch foo");
       }
     catch (const CORBA::Exception& ex)
       {
         ex._tao_print_exception ("ERROR: Caught unexpected exception:");
       }
  }

  void
  AMI4CCM_MyFooReplyHandler_i::bar (const char * /* answer */,
      ::CORBA::Long l_cmd)
  {
    if ( l_cmd == OneReplyH::cmd_asynch_bar_ok )
       {
         ++this->nr_of_received_;
       }
  }

  void
  AMI4CCM_MyFooReplyHandler_i::bar_excep (
      ::CCM_AMI::ExceptionHolder_ptr excep_holder)
  {
    try
    {
       excep_holder->raise_exception ();
     }
   catch (const OneReplyH::InternalError& ex)
     {
       CIAO_OneReplyH_Sender_Impl::HandleException (ex.id, OneReplyH::cmd_asynch_bar_nok,
                        ex.error_string.in(), "asynch bar");
     }
   catch (const CORBA::Exception& ex)
     {
       ex._tao_print_exception ("ERROR: Caught unexpected exception:");
     }
  }
}