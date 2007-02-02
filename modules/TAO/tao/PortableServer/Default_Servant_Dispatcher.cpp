// $Id$

#include "tao/PortableServer/Default_Servant_Dispatcher.h"
#include "tao/PortableServer/Root_POA.h"

ACE_RCSID(PortableServer,
          Default_Servant_Dispatcher,
          "$Id$")

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

TAO_Default_Servant_Dispatcher::~TAO_Default_Servant_Dispatcher (void)
{
}

TAO_Root_POA *
TAO_Default_Servant_Dispatcher::create_Root_POA (const ACE_CString &name,
                                                 PortableServer::POAManager_ptr poa_manager,
                                                 const TAO_POA_Policy_Set &policies,
                                                 ACE_Lock &lock,
                                                 TAO_SYNCH_MUTEX &thread_lock,
                                                 TAO_ORB_Core &orb_core,
                                                 TAO_Object_Adapter *object_adapter)
{
  TAO_Root_POA *poa = 0;

  ACE_NEW_THROW_EX (poa,
                    TAO_Root_POA (name,
                                  poa_manager,
                                  policies,
                                  0,
                                  lock,
                                  thread_lock,
                                  orb_core,
                                  object_adapter),
                    CORBA::NO_MEMORY ());

  return poa;
}

void
TAO_Default_Servant_Dispatcher::pre_invoke_remote_request (
  TAO_Root_POA &poa,
  CORBA::Short servant_priority,
  TAO_ServerRequest &req,
  TAO::Portable_Server::Servant_Upcall::Pre_Invoke_State &pre_invoke_state)
{
  TAO_Service_Context &request_service_context =
    req.request_service_context ();

  CORBA::Long dscp_codepoint;
  TAO_Connection_Handler *connection_handler =
    req.transport ()->connection_handler ();

  TAO_Network_Priority_Protocols_Hooks *nph =
   poa.orb_core ().get_network_priority_protocols_hooks ();

  TAO::Portable_Server::Cached_Policies::NetworkPriorityModel npm =
    poa.cached_policies ().network_priority_model ();

  if (npm == TAO::Portable_Server::Cached_Policies::
             CLIENT_PROPAGATED_NETWORK_PRIORITY)
    {
      dscp_codepoint = nph->get_dscp_codepoint (request_service_context, poa); 
      connection_handler->set_dscp_codepoint (dscp_codepoint);
    }
  else if (npm == TAO::Portable_Server::Cached_Policies::
                  SERVER_DECLARED_NETWORK_PRIORITY)
    {
      dscp_codepoint = poa.cached_policies ().reply_diffserv_codepoint ();
    }
  else
    {
      // no server side network priority policy defined.
    }
}

void
TAO_Default_Servant_Dispatcher::pre_invoke_collocated_request (
  TAO_Root_POA &,
  CORBA::Short,
  TAO::Portable_Server::Servant_Upcall::Pre_Invoke_State &)
{
}

void
TAO_Default_Servant_Dispatcher::post_invoke (
  TAO_Root_POA &,
  TAO::Portable_Server::Servant_Upcall::Pre_Invoke_State &)
{
}

TAO_END_VERSIONED_NAMESPACE_DECL
