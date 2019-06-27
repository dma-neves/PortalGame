INC_DIRECOTRY=src -I src/Util -I src/AssetManagers -I src/Entities -I src/Entities/Types -I src/Level -I src/Events 
INC_DIRECOTRY+=-I src/Events/EntityEvents
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

CPPC=g++ -std=c++11 -g

OBJECT_FILES=obj/main.o obj/Game.o obj/Vector2D.o obj/Rect.o obj/Entity.o obj/TextureManager.o obj/EntityRenderer.o
OBJECT_FILES+=obj/Player.o obj/LevelLoader.o obj/DynamicEntity.o obj/EntityManager.o obj/PortalProjectile.o obj/DisplaceableEntity.o
OBJECT_FILES+=obj/Lever.o

PortalGame: $(OBJECT_FILES)
	$(CPPC) $(OBJECT_FILES) -o bin/PortalGame $(LIBS)

obj/main.o: main.cpp
	$(CPPC) -c main.cpp -I $(INC_DIRECOTRY) -o obj/main.o

obj/Game.o: src/Game.cpp src/Game.h
	$(CPPC) -c src/Game.cpp -I $(INC_DIRECOTRY) -o obj/Game.o

obj/Vector2D.o: src/Util/Vector2D.cpp src/Util/Vector2D.h
	$(CPPC) -c src/Util/Vector2D.cpp -I $(INC_DIRECOTRY) -o obj/Vector2D.o

obj/Rect.o: src/Util/Rect.cpp src/Util/Rect.h
	$(CPPC) -c src/Util/Rect.cpp -I $(INC_DIRECOTRY) -o obj/Rect.o

obj/Entity.o: src/Entities/Entity.cpp src/Entities/Entity.h
	$(CPPC) -c src/Entities/Entity.cpp -I $(INC_DIRECOTRY) -o obj/Entity.o

obj/TextureManager.o: src/AssetManagers/TextureManager.cpp src/AssetManagers/TextureManager.h
	$(CPPC) -c src/AssetManagers/TextureManager.cpp -I $(INC_DIRECOTRY) -o obj/TextureManager.o

obj/EntityRenderer.o: src/Entities/EntityRenderer.cpp src/Entities/EntityRenderer.h
	$(CPPC) -c src/Entities/EntityRenderer.cpp -I $(INC_DIRECOTRY) -o obj/EntityRenderer.o

obj/Player.o: src/Entities/Types/Player.cpp src/Entities/Types/Player.h
	$(CPPC) -c src/Entities/Types/Player.cpp -I $(INC_DIRECOTRY) -o obj/Player.o

obj/LevelLoader.o: src/Level/LevelLoader.cpp src/Level/LevelLoader.h
	$(CPPC) -c src/Level/LevelLoader.cpp -I $(INC_DIRECOTRY) -o obj/LevelLoader.o

obj/DynamicEntity.o: src/Entities/Types/DynamicEntity.cpp src/Entities/Types/DynamicEntity.h
	$(CPPC) -c src/Entities/Types/DynamicEntity.cpp -I $(INC_DIRECOTRY) -o obj/DynamicEntity.o

obj/EntityManager.o: src/Entities/EntityManager.cpp src/Entities/EntityManager.h
	$(CPPC) -c src/Entities/EntityManager.cpp -I $(INC_DIRECOTRY) -o obj/EntityManager.o

obj/PortalProjectile.o: src/Entities/Types/PortalProjectile.cpp src/Entities/Types/PortalProjectile.h
	$(CPPC) -c src/Entities/Types/PortalProjectile.cpp -I $(INC_DIRECOTRY) -o obj/PortalProjectile.o

obj/DisplaceableEntity.o: src/Entities/Types/DisplaceableEntity.cpp src/Entities/Types/DisplaceableEntity.h
	$(CPPC) -c src/Entities/Types/DisplaceableEntity.cpp -I $(INC_DIRECOTRY) -o obj/DisplaceableEntity.o

obj/Lever.o: src/Entities/Types/Lever.cpp src/Entities/Types/Lever.h
	$(CPPC) -c src/Entities/Types/Lever.cpp -I $(INC_DIRECOTRY) -o obj/Lever.o

clean:
	rm obj/*.o bin/PortalGame
