#ifndef _MeshList_
#define _MeshList_

#define AXIS 0

#include <vector>
#include <map>
#include <string>

#include "MeshNotFound.h"
#include "Vertex.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "SingletonTemplate.h"

class MeshList : public Singleton <MeshList>
{
	friend Singleton;
	std::map<std::string, Mesh*>Entities;

	MeshList(){

		Mesh* temp;

		//Base Meshes
		temp = MeshBuilder::GenerateAxes("Axis", 1000, 1000, 1000);
		assignMesh(temp);
		temp = MeshBuilder::GenerateSphere("Sphere", Color(1, 1, 1), 10, 10, 1);
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("Quad", Color(1, 1, 1), 1);
		assignMesh(temp);

		temp = MeshBuilder::GenerateCone("Cone", Color(1, 1, 1), 10, 1, 1);
		assignMesh(temp);
		temp = MeshBuilder::GenerateCube("Cube", Color(1, 1, 1), 1);
		assignMesh(temp);
		temp = MeshBuilder::GenerateRing("Ring", Color(1, 1, 1), 10, 1.0f, 0.5f);
		assignMesh(temp);

		temp = MeshBuilder::GenerateText("CALIBRI", 16, 16);
		temp->textureID = LoadTGA("Image//calibri.tga");
		assignMesh(temp);

		temp = MeshBuilder::GenerateLine("REDLINE", Color(1,0,0), 1);
		assignMesh(temp);
		temp = MeshBuilder::GenerateLine("GREENLINE", Color(0, 1, 0), 1);
		assignMesh(temp);
		temp = MeshBuilder::GenerateLine("BLUELINE", Color(0, 0, 1), 1);
		assignMesh(temp);

		
		temp = MeshBuilder::GenerateQuad("REDHPBAR", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image//redhpbar.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("GREENHPBAR", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image//greenhpbar.tga");
		assignMesh(temp);

		temp = MeshBuilder::GenerateText("CHILLER", 16, 16);
		temp->textureID = LoadTGA("Image//chiller.tga");
		assignMesh(temp);
		
		//temp = MeshBuilder::GenerateSpriteAnimation("BLACKDRAGON", 1, 6, 1.f);
		//temp->textureID = LoadTGA("Image//blackdragon.tga");
		//assignMesh(temp);
		//temp = MeshBuilder::GenerateSpriteAnimation("BLACKATTACK", 1, 6, 1.f);
		//temp->textureID = LoadTGA("Image//blackattack.tga");
		//assignMesh(temp);

	
		temp = MeshBuilder::GenerateQuad("chargeborder", Color(1, 1, 1, 0.2f), 1);
		temp->textureID = LoadTGA("Image\\chargeborder.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("charge", Color(1, 1, 1, 0.2f), 1);
		temp->textureID = LoadTGA("Image\\charge.tga");
		assignMesh(temp);

		temp = MeshBuilder::GenerateQuad("node", Color(1, 1, 1, 1.f), 1);
		temp->textureID = LoadTGA("Image\\node.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("node_highlight", Color(1, 1, 1, 1.f), 1);
		temp->textureID = LoadTGA("Image\\node_highlight.tga");
		assignMesh(temp);
	}

	void assignMesh(Mesh* a) {
		Entities[a->name] = a;
	}

public:

	Mesh* getMesh(std::string a)
	{
		Mesh* ret = Entities[a];
		if (ret == NULL)
			throw MeshNotFound(a);
		return ret;
	}


	~MeshList() {
		for (auto it : Entities)
		{
			if (it.second != NULL)
			{
				delete it.second;
				it.second = nullptr;
			}
		}
	}
};



#endif

