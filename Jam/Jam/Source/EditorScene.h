
#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include "GameObject.h"
#include <vector>
#include "Scene.h"
#include "Camera.h"
#include "AudioPlayer.h"
class Mesh;
#include "Collision.h"
#include <list>
class EditorScene : public Scene
{
public:
	EditorScene();
	~EditorScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	Camera camera;
	double fps;
	//AudioPlayer audioPlayer;
	Mesh* axis;

	//Mesh* background;
	float worldHeight;
	float worldWidth;

	enum ACTION
	{
		CREATE_NEW_PAT,
		VIEW_PAT
	} current_action;

	typedef std::list< Collision > upattern;
	typedef upattern::iterator upattern_iter;
	std::list <upattern> unsaved_pattern;//on world
	int current_path;

	typedef std::vector < Vector3 > lpat_path;//one path
	typedef std::vector < lpat_path > lpat_pattern;//all paths in one pattern
	std::vector < lpat_pattern > loaded_pattern;//all the patterns
	int current_pattern;

	Mesh* node;
	Mesh* highlight;
	Vector3 node_scale;
	const std::string start_of_pattern;
	const std::string end_of_pattern;

	void update_create_new_pattern();
	void render_create_new_pattern();
	void update_view_patterns();
	void render_view_patterns();

	void clear_unsaved_pattern();
	void clear_loaded_pattern();
	void save_pattern(char* file_path = "Image//enemy_spawn_pattern.txt");
	void load_pattern(char* file_path = "Image//enemy_spawn_pattern.txt");

	void load_this_pattern(std::ifstream& fileStream, char * buf);
	void load_this_path(std::ifstream& fileStream, char * buf);

	void delete_pattern(unsigned int index, char* file_path = "Image//enemy_spawn_pattern.txt");
};

#endif