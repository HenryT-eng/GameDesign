#include "NetMsgCreateRawWO.h"
#include "NetMsg.h"
#include "WO.h"
#include "ManagerGLView.h"
#include "GLView.h"
#include "WorldContainer.h"


namespace Aftr
{
	NetMsgMacroDefinition(NetMsgCreateRawWO);

	NetMsgCreateRawWO::NetMsgCreateRawWO()
	{

	}

	NetMsgCreateRawWO::~NetMsgCreateRawWO()
	{

	}

	bool NetMsgCreateRawWO::toStream(NetMessengerStreamBuffer& os) const
	{
		os << this->size;
		for (size_t i = 0; i < size; i++)
		{
			os << this->vertices[i];
		}
		return true;
	}

	bool NetMsgCreateRawWO::fromStream(NetMessengerStreamBuffer& is)
	{
		is >> this->size;
		this->vertices = new float[size];
		for (size_t i = 0; i < size; i++)
		{
			is >> this->vertices[i];
		}
		return true;
	}

	void NetMsgCreateRawWO::onMessageArrived()
	{
		/*WO* wo = WORawQuads::New(vertices, (size / 3) / 4);
		ManagerGLView::getGLView()->getWorldContainer()->push_back(wo);
		wo->setPosition(0, 0, 100);
		std::cout << this->toString() << std::endl;*/
		std::string grass(ManagerEnvironmentConfiguration::getSMM() + "/models/grassFloor400x400_pp.wrl");
		WO* wo = WO::New(grass, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
		wo->setPosition(Vector(0, 0, 0));
		wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
		wo->setLabel("Grass");
		ManagerGLView::getGLView()->getWorldContainer()->push_back(wo);
	}

	std::string NetMsgCreateRawWO::toString() const
	{
		std::stringstream ss;

		ss << NetMsg::toString();
		ss << "		Payload: " << this->size << ".../n";
		//for(size_t i = 0; i < size / 3; i++)
		//{
		//	std::cout << vertices[i*3+0] << " " << vertices[i*3+1] << " " << vertices[i*3+2] << std::endl; 
		//{
		return ss.str();
	}
}//NAMESPACE AFTR