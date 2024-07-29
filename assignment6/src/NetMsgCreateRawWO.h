#pragma once
#include "NetMsg.h"
#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr
{
	class NetMsgCreateRawWO : public NetMsg
	{
	public:
		NetMsgMacroDeclaration(NetMsgCreateRawWO);

		NetMsgCreateRawWO();
		virtual ~NetMsgCreateRawWO();
		virtual bool toStream(NetMessengerStreamBuffer& os) const;
		virtual bool fromStream(NetMessengerStreamBuffer& is);
		virtual void onMessageArrived();
		virtual std::string toString() const;





		unsigned int size;
		float* vertices;



	protected:

	}; 

}//namespace Aftr

#endif

