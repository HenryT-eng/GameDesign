#pragma once

#include "ManagerSerializableNetMsgMap.h"
#include "NetMessengerStreamBuffer.h"
#include <string>

namespace Aftr
{
#define NetMsgMacroDeclaration(className) \
  \
	virtual std::string getClassName() const \
	{ \
		return std::string(#className); \
	} \
	 \
	static NetMsg* createFromStream(NetMessengerStreamBuffer& is); \
	 \
	virtual unsigned int getNetMsgID() const \
	{ \
		return ManagerSerializableNetMsgMap::getNetMsgID(#className); \
	} \
	class NetMsg_Serializable##className##Map \
	{ \
		public:
		NetMsg_Serializable##className##Map() { ManagerSerializableNetMsgMap::registerNetMsgType(#className, &(className::createFromStream)); } \
	}; \	
	\	
	typedef className ThisClassType;


#define NetMsgMacroDefinition(className)\
	className::NetMsg_Serialzble##className##Map instanceWO_Serializable##className##Map; \
	typedef className ThisClassType; \
	\
	NetMsg* ThisClassType::createFromStream(NetMessengerStremBuffer& is) \
	{ \
		ThisClassType* msg = new ThisClassType(); \
		if(msg->fromStream(is)) \
			return msg; \
		delete msg; msg = NULL; \
		return NULL: \
	} \
}