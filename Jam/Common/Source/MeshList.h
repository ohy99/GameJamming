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
		temp = MeshBuilder::GenerateQuad("RedQuad", Color(1, 0, 0), 1);
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("GreenQuad", Color(0, 1, 0), 1);
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("BlueQuad", Color(0, 0, 1), 1);
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("YellowQuad", Color(1, 0.8f, 0), 1);
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
		
		temp = MeshBuilder::GenerateQuad("PlayerBullet", Color(1, 1, 1, 1.f), 1);
		temp->textureID = LoadTGA("Image\\Protagonist_Bullet.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("PlayerLaser", Color(1, 1, 1, 1.f), 1);
		temp->textureID = LoadTGA("Image\\Protagonist_Laser.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("Bullet1", Color(1, 1, 1, 1.f), 1);
		temp->textureID = LoadTGA("Image\\EnemyBullet_01.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("Bullet2", Color(1, 1, 1, 1.f), 1);
		temp->textureID = LoadTGA("Image\\EnemyBullet_02.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("Bullet3", Color(1, 1, 1, 1.f), 1);
		temp->textureID = LoadTGA("Image\\EnemyBullet_03.tga");
		assignMesh(temp);
	
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

		temp = MeshBuilder::GenerateSpriteAnimation("SheepIdle", 1, 2, 1.f);
		temp->textureID = LoadTGA("Image\\Sheep_idle.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("SheepFire", Color(1, 0, 0), 1.f);
		temp->textureID = LoadTGA("Image\\Sheep_fire.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("HpBack", Color(1,1,1), 1.f);
		temp->textureID = LoadTGA("Image\\ui_health11.tga");
		assignMesh(temp);
		//temp = MeshBuilder::GenerateQuad("HpFront", Color(1, 0, 0), 1.f);
		//temp->textureID = LoadTGA("Image\\ui_health22.tga");
		//assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("HpFront", Color(1, 0, 0), 1.f);
		temp->textureID = LoadTGA("Image\\ui_healthbar1.tga");
		assignMesh(temp);

		temp = MeshBuilder::GenerateSpriteAnimation("reticle", 2, 3, 1.f);
		temp->textureID = LoadTGA("Image\\Recticle.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("sky", 2, 3, 1.f);
		temp->textureID = LoadTGA("Image\\bg_sky.tga");
		assignMesh(temp);

		temp = MeshBuilder::GenerateQuad("Meteor", Color(1, 0, 0), 1.f);
		temp->textureID = LoadTGA("Image\\bg_meteor.tga");
		assignMesh(temp);


		temp = MeshBuilder::GenerateQuad("Enemy", Color(1, 0, 0), 1.f);
		temp->textureID = LoadTGA("Image\\Enemy_Oce_Top.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("EnemySide", Color(1, 0, 0), 1.f);
		temp->textureID = LoadTGA("Image\\Enemy_Oce_Side.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("HarpyBossAttack", Color(1, 0, 0), 1.f);
		temp->textureID = LoadTGA("Image\\enemy_harpyboss_attack.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("HarpyBossIdle", 1, 2, 1.f);
		temp->textureID = LoadTGA("Image\\enemy_harpyboss_idle.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("HarpyBoss2Attack", Color(1, 0, 0), 1.f);
		temp->textureID = LoadTGA("Image\\enemy_harpyboss2_attack.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("HarpyBoss2Idle", 1, 2, 1.f);
		temp->textureID = LoadTGA("Image\\enemy_harpyboss2_idle.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("WolfAttack", 1, 2, 1.f);
		temp->textureID = LoadTGA("Image\\enemy_wolf_attack.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("WolfIdle", 1, 2, 1.f);
		temp->textureID = LoadTGA("Image\\enemy_wolf_idle.tga");
		assignMesh(temp);

		temp = MeshBuilder::GenerateQuad("UiButton", Color(1,1,1), 1.0f);
		temp->textureID = LoadTGA("Image\\ui_button.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("UiButtonStart", Color(1, 1, 1), 1.0f);
		temp->textureID = LoadTGA("Image\\ui_button_start.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("UiButtonExit", Color(1, 1, 1), 1.0f);
		temp->textureID = LoadTGA("Image\\ui_button_exit.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("sky 2", Color(1, 0, 0), 1.f);
		temp->textureID = LoadTGA("Image\\bg_sky2.tga");
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

