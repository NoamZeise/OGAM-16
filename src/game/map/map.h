#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "visual.h"
#include "tiled.h"

#include <string>


class Level
{
 public:
  Level() {}
  Level(Render *render, std::string file, Resource::Font mapFont)
  {
    this->tiledMap = tiled::Map(file);
    this->visualMap = Map::Visual(tiledMap, render, mapFont);
  }

  void Update(glm::vec4 camRect, Timer &timer, std::vector<glm::vec4> *activeColliders)
  {
    visualMap.Update(camRect, timer, activeColliders);
  }

  void Draw(Render* render)
  {
    visualMap.Draw(render);
  }

  glm::vec4 getMapRect()
  {
    return glm::vec4(0, 0, tiledMap.width * tiledMap.tileWidth, tiledMap.height * tiledMap.tileHeight);
  }

  void getObjLists(
		   std::vector<glm::vec4> *roomRects,
		   //enemy paths
		   std::vector<glm::vec2> *heroPath
      )
  {
    for(auto& objGroup : tiledMap.objectGroups)
    {
      for(auto& obj: objGroup.objs)
      {
	if(obj.props.room)
	{
	  roomRects->push_back(glm::vec4(obj.x, obj.y, obj.w, obj.h));
        }
      }
      for(auto& obj: objGroup.polys)
      {
	std::vector<glm::vec2> *pointsList = nullptr;
	if(obj.obj.props.hero)
	{
	    pointsList = heroPath;
	}
	  
	if(pointsList != nullptr)
	{
	  for(auto &p: obj.points)
	  {
	    pointsList->push_back(glm::vec2(p.x, p.y));
	  }
	}
      }
    }
  }
  
 private:
  Map::Visual visualMap;
  tiled::Map tiledMap;
};


#endif