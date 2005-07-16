#include "orbsvcs/Log/BasicLogFactory_i.h"

ACE_RCSID (Log,
           BasicLogFactory_i,
           "$Id$")

TAO_BasicLogFactory_i::TAO_BasicLogFactory_i (void)
{
}

TAO_BasicLogFactory_i::~TAO_BasicLogFactory_i (void)
{
}

DsLogAdmin::BasicLogFactory_ptr
TAO_BasicLogFactory_i::activate (CORBA::ORB_ptr orb,
                                 PortableServer::POA_ptr poa
                                 ACE_ENV_ARG_DECL)
{
  TAO_LogMgr_i::init (orb, poa ACE_ENV_ARG_PARAMETER);
  ACE_CHECK_RETURN (DsLogAdmin::BasicLogFactory::_nil ());
  

  PortableServer::ObjectId_var oid =
    this->factory_poa_->activate_object (this
					 ACE_ENV_ARG_PARAMETER);
  ACE_CHECK_RETURN (DsLogAdmin::BasicLogFactory::_nil ());

  CORBA::Object_var obj =
    this->factory_poa_->id_to_reference (oid.in ()
					 ACE_ENV_ARG_PARAMETER);
  ACE_CHECK_RETURN (DsLogAdmin::BasicLogFactory::_nil ());

  // narrow and store the result..
  this->log_mgr_ =
    DsLogAdmin::LogMgr::_narrow (obj.in ()
                                 ACE_ENV_ARG_PARAMETER);
  ACE_CHECK_RETURN (DsLogAdmin::BasicLogFactory::_nil ());

  DsLogAdmin::BasicLogFactory_var v_return =
    DsLogAdmin::BasicLogFactory::_narrow (obj.in ()
					  ACE_ENV_ARG_PARAMETER);
  ACE_CHECK_RETURN (DsLogAdmin::BasicLogFactory::_nil ());

  return v_return._retn ();
}

DsLogAdmin::BasicLog_ptr
TAO_BasicLogFactory_i::create (DsLogAdmin::LogFullActionType full_action,
                               CORBA::ULongLong max_size,
                               DsLogAdmin::LogId_out id_out
                               ACE_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   DsLogAdmin::InvalidLogFullAction
                   ))
{
ACE_DEBUG((LM_DEBUG, "TAO_BasicLogFactory_i::create\n"));
  this->create_i (full_action,
		  max_size,
		  0,
		  id_out
		  ACE_ENV_ARG_PARAMETER);
  ACE_CHECK_RETURN (DsLogAdmin::BasicLog::_nil ());
  DsLogAdmin::LogId id = id_out;
  
  DsLogAdmin::Log_var log =
    this->create_log_object (id);

  // narrow to BasicLog
  DsLogAdmin::BasicLog_var basic_log =
    DsLogAdmin::BasicLog::_narrow (log);

  return basic_log._retn ();
}

DsLogAdmin::BasicLog_ptr
TAO_BasicLogFactory_i::create_with_id (DsLogAdmin::LogId id,
                                       DsLogAdmin::LogFullActionType full_action,
                                       CORBA::ULongLong max_size
                                       ACE_ENV_ARG_DECL)
  ACE_THROW_SPEC ((
                   CORBA::SystemException,
                   DsLogAdmin::LogIdAlreadyExists,
                   DsLogAdmin::InvalidLogFullAction
                   ))
{
ACE_DEBUG((LM_DEBUG, "TAO_BasicLogFactory_i::create_with_id\n"));
  this->create_with_id_i (id,
			  full_action,
			  max_size,
			  0
			  ACE_ENV_ARG_PARAMETER);
  ACE_CHECK_RETURN (DsLogAdmin::BasicLog::_nil ());

  DsLogAdmin::Log_var log =
    this->create_log_object (id);

  // narrow to BasicLog
  DsLogAdmin::BasicLog_var basic_log =
    DsLogAdmin::BasicLog::_narrow (log);

  return basic_log._retn ();
}

PortableServer::ObjectId*
TAO_BasicLogFactory_i::create_objectid (DsLogAdmin::LogId id)
{
  char buf[32]; 
  ACE_OS::sprintf(buf, "%lu", static_cast<unsigned long>(id)); 
 
  PortableServer::ObjectId_var oid = 
        PortableServer::string_to_ObjectId(buf);

  return oid._retn ();
}

DsLogAdmin::Log_ptr
TAO_BasicLogFactory_i::create_log_reference (DsLogAdmin::LogId id
					     ACE_ENV_ARG_DECL)
{
  PortableServer::ObjectId_var oid =
    this->create_objectid (id);
  const char *intf = 
	"IDL:omg.org/DsLogAdmin:BasicLog:1.0";
  
  CORBA::Object_var obj =
    this->log_poa_->create_reference_with_id (oid.in (),
					      intf
					      ACE_ENV_ARG_PARAMETER);
  ACE_CHECK_RETURN (DsLogAdmin::Log::_nil ());
  
  DsLogAdmin::BasicLog_var basic_log =
    DsLogAdmin::BasicLog::_narrow (obj.in ()
				   ACE_ENV_ARG_PARAMETER);
  ACE_CHECK_RETURN (DsLogAdmin::Log::_nil ());
  
  return basic_log._retn();
}


DsLogAdmin::Log_ptr
TAO_BasicLogFactory_i::create_log_object (DsLogAdmin::LogId id
				          ACE_ENV_ARG_DECL)
{
  TAO_BasicLog_i* basic_log_i;

  ACE_NEW_THROW_EX (basic_log_i,
                    TAO_BasicLog_i (this->orb_.in (),
				    this->log_poa_.in (),
                                    *this,
                                    this->log_mgr_.in (),
                                    id),
                    CORBA::NO_MEMORY ());
  ACE_CHECK_RETURN (DsLogAdmin::BasicLog::_nil ());

  basic_log_i->init (ACE_ENV_SINGLE_ARG_PARAMETER);
  ACE_CHECK_RETURN (DsLogAdmin::BasicLog::_nil ());

  PortableServer::ServantBase_var safe_basic_log_i = basic_log_i;
  // Transfer ownership to the POA.

  // Obtain ObjectId
  PortableServer::ObjectId_var oid = this->create_objectid (id);
  
  // Register with the poa
  this->log_poa_->activate_object_with_id (oid.in (),
					   basic_log_i
					   ACE_ENV_ARG_PARAMETER);
  ACE_CHECK_RETURN (DsLogAdmin::BasicLog::_nil ());

  return create_log_reference (id ACE_ENV_ARG_PARAMETER);
}
