#include "World.h"
#include <cmath>



World::World( ModoType modo, float maxVel, unsigned int initBlobCant, unsigned int initFoodCant)
{
	this->texture = Bitmap(WORLD_TEXTURE);
	Blob::loadTextures();
	Food::loadTexture();
	this->velMax = maxVel;//Velocidad maxima definida por el usuario usada en modo 2
	this->modo = modo;//Modo 1 o 2 
	this->initBlobCount = initBlobCant;//Cantidad inicial de blob 
	this->foodCount = initFoodCant;//Cantidad de comida
	this->velPercent = 1.0F;//Velocidad de simualcion 
	this->deathProbGOb = 0.0F;//Probabilidad de muerte de los Good old blob
	this->deathProbGb = 0.0F;//Probabilidad de muerte de los Grown blob
	this->deathProbBb = 0.0F;//Probabilidad de muerte de los Baby blob
	this->smellRadius = 100;//Rango de olfato de los blob
	this->randomJiggleLimit = 360.0F;//Maximo valor de orientacion de un nuevo blob
	

}


int World::birth(float x, float y, float newDir)
{
	int i;
	for (i = 0; i < MAX_BLOB_CANT && arrBlobs[i].isAlive; i++) {}	//Busco un blob muerto
	arrBlobs[i].revive(x, y, newDir);								//Lo revivo en su nueva ubicacion
	switch (this->modo)												//En base al modo le asinamos una velocidad al blob
	{
	case MODO1:
		this->arrBlobs[i].vel = this->velMax;
		break;
	case MODO2:
		this->arrBlobs[i].vel = (rand() % (int)this->velMax) + 1;
		break;
	}

	return i;
}


void World::blobOutScreen(unsigned int blobIndex)
{
	if (this->arrBlobs[blobIndex].pos.x >= this->texture.width)		//Si se pasa por la derecha
	{
		this->arrBlobs[blobIndex].pos.x = -(int)this->arrBlobs[blobIndex].eGroup->texture.width;	//lo llevo al borde izquierdo
	}
	else if (this->arrBlobs[blobIndex].pos.y >= this->texture.height)	//Si se pasa por abajo
	{
		this->arrBlobs[blobIndex].pos.y = -(int)this->arrBlobs[blobIndex].eGroup->texture.height;	//lo llevo al borde superior
	}
	else if (this->arrBlobs[blobIndex].pos.y <= -(int)this->arrBlobs[blobIndex].eGroup->texture.height)	//Si se pasa por arriba
	{
		this->arrBlobs[blobIndex].pos.y = this->texture.height;								//lo llevo al borde inferior
	}
	else if (this->arrBlobs[blobIndex].pos.x <= -(int)this->arrBlobs[blobIndex].eGroup->texture.width)	//Si se pasa por la izquierda
	{
		this->arrBlobs[blobIndex].pos.x = this->texture.width;									//lo llevo al borde derecho
	}
}


void World::Simulation()
{

	int colisionflag = 0;
	static int deathTimer = 0;
	float directionSum = 0.0F, newDirection = 0.0F, speedSum = 0.0F, newSpeed = 0.0f;
	for (int i = 0; i < MAX_BLOB_CANT; i++)//Para cada blob vemos ...
	{
		if (this->arrBlobs[i].isAlive == false)//Si esta muerto el blob
		{
			continue; //Pasamos al siguiente blob 
		}
		//Vemos si el blob muere
		if (deathTimer++ >= FPS)
		{
			deathTimer = 0; 
			switch (this->arrBlobs[i].eGroup->etaGroupID)//Dependiendo el grupo etario tienen distintas probabilidad de muerte
			{
			case BABY_BLOB:
				if (((rand() % 101) / 100.0f) < this->deathProbBb)//Si el numero al azar entre 0 y 1 es menor que la probabilidad de muerte
				{
					this->arrBlobs[i].die();//Lo matamos
					continue; //Pasamos al siguiente blob
				}
				break;
			case GROWN_BLOB:
				if (((rand() % 101) / 100.0f) < this->deathProbGb)
				{
					this->arrBlobs[i].die();//Lo matamos
					continue; //Pasamos al siguiente blob
				}
				break;
			case GOOD_OLD_BLOB:
				if (((rand() % 101) / 100.0f) < this->deathProbGOb)
				{
					this->arrBlobs[i].die();//Lo matamos
					continue; //Pasamos al siguiente blob
				}
				break;
			default:
				break;
			}
		}
		//Vemos las coliciones de los blobs con las comidas
		for(int j=0; j< MAX_FOOD_CANT ; j++)
		{
			if (arrFood[j].isNotEaten)
			{
				if ((((this->arrBlobs[i].pos.x + this->arrBlobs[i].eGroup->texture.width) > (this->arrFood[j].pos.x)) && ((this->arrBlobs[i].pos.x) < (this->arrFood[j].pos.x + this->arrFood[j].texture->width))) && (((this->arrBlobs[i].pos.y + this->arrBlobs[i].eGroup->texture.height) > (this->arrFood[j].pos.y)) && ((this->arrBlobs[i].pos.y) < (this->arrFood[j].pos.y + this->arrFood[j].texture->height))))// Si el blob colisiono con comida
				{
					this->arrBlobs[i].foodCount += 1;//Si se choco con la comida incrementamos su contador de comida
					this->arrFood[j].isNotEaten = false;// Destruimos lo que fue comido

					if (arrBlobs[i].foodCount == arrBlobs[i].eGroup->food2Birth && arrBlobs[MAX_BLOB_CANT-1].isAlive != true)
					{
						arrBlobs[i].sonIndex = this->birth(arrBlobs[i].pos.x, arrBlobs[i].pos.y, abs(arrBlobs[i].pos.direction + (rand() % (int)this->randomJiggleLimit))); // Si ya comio suficiente da a luz
						arrBlobs[arrBlobs[i].sonIndex].dadIndex = i;
						arrBlobs[i].foodCount = 0;																	//Reiniciamos el contador de alimento ingerido
						
					}
				}
			}
		}
		//Vemos las coliciones entre blobs
		colisionflag = 0;
		directionSum = 0.0F;
		speedSum = 0.0F;
		newDirection = 0.0F;
		for (int j = 0; j < MAX_BLOB_CANT && (arrBlobs[i].eGroup->etaGroupID != GOOD_OLD_BLOB) ; j++ )//Aca debemos hacer que el blob ignore compararse consigo mismo
		{
			if (arrBlobs[j].isAlive && (i != j)) {
				if ((((this->arrBlobs[i].pos.x + this->arrBlobs[i].eGroup->texture.width) > (this->arrBlobs[j].pos.x)) && ((this->arrBlobs[i].pos.x) < (this->arrBlobs[j].pos.x + this->arrBlobs[j].eGroup->texture.width))) && (((this->arrBlobs[i].pos.y + this->arrBlobs[i].eGroup->texture.height) > (this->arrBlobs[j].pos.y)) && ((this->arrBlobs[i].pos.y) < (this->arrBlobs[j].pos.y + this->arrBlobs[j].eGroup->texture.height))))
				{
					if (this->arrBlobs[i].eGroup->etaGroupID == this->arrBlobs[j].eGroup->etaGroupID && j != arrBlobs[i].sonIndex && j != arrBlobs[i].dadIndex)//Si son del mismo tamaño
					{
						directionSum += this->arrBlobs[j].pos.direction;//Agrego al promedio la direccion del blob
						speedSum += this->arrBlobs[j].vel;				//Agrego al promedio de la velocidad el blob
						this->arrBlobs[j].die();//Matamos al blob con el que choco
						colisionflag += 1; //Marcamos el flag para saber que el blob va a crecer
					}
				}
				else if (j == arrBlobs[i].sonIndex)								//Si no colisiono con el hijo
				{
					arrBlobs[arrBlobs[i].sonIndex].dadIndex = -1;				//Actualizamos los indices para sacarles la familiaridad
					arrBlobs[i].sonIndex = -1;
				}
				else if (j == arrBlobs[i].dadIndex)								//Si no colisiono con el padre
				{
					arrBlobs[arrBlobs[i].dadIndex].sonIndex = -1;				//Actualizamos los indices para sacarles la familiaridad
					arrBlobs[i].dadIndex = -1;
				}
				
			}
		}
		if (colisionflag > 0)//Si ya revisamos toda la lista y se chocaron dos blobs
		{
			newDirection = (directionSum / colisionflag) + (rand() % (int)this->randomJiggleLimit);
			newSpeed = (speedSum / colisionflag);
			this->arrBlobs[i].grow(newDirection, newSpeed);//Hacemos que el blob crezca 
		}

		//Vemos si hay comida serca del blob 
		this->arrBlobs[i].smell(this->smellRadius, this->arrFood, MAX_FOOD_CANT);//Cambiamos la orientacion de los blobs si hay comida serca

		//Actualizamos las posiciones de los blobs en base a su velocidad
		this->arrBlobs[i].move(this->velPercent);
		this->blobOutScreen(i);
	}

	//Revisamos que tengamos siempre toda la comida
	for (unsigned int i = 0; i < this->foodCount; i++)
	{
		if (this->arrFood[i].isNotEaten == false)//Si esta comida la revivimos en otro lado
		{
			this->arrFood[i].isNotEaten = true;
			this->arrFood[i].pos.x = (rand() % (this->texture.width - this->arrFood[i].texture->width));
			this->arrFood[i].pos.y = (rand() % (this->texture.height - this->arrFood[i].texture->height));
		}
	}

}

bool World::preGame()
{

	bool modeSelected = false;

	ImGui_ImplAllegro5_NewFrame();
	ImGui::NewFrame();
	//antes de empezar la simulacion
	ImGui::SetNextWindowSize(ImVec2(700, 300));			//Posicionamos la ventana de opciones de ImGui
	ImGui::SetNextWindowPos(ImVec2(100, 100));
	ImGui::Begin("Blob World");	//Inicializamos la ventana
	if (ImGui::Button("MODO 1"))								//Si se presiona modo 1 devolvemos true para arrancar a simular
	{
		modo = MODO1;
		modeSelected = true;
	}
	ImGui::SameLine();
	if (ImGui::Button("MODO 2"))								//Si se presiona modo 2 devolvemos true para arrancar a simular
	{
		modo = MODO2;
		modeSelected = true;
	}
	ImGui::SetNextItemWidth(100);
	ImGui::InputInt("Cantidad inicial de blobs", (int*)&initBlobCount);		// Entrada para la cantidad inicial de blobs
	if (initBlobCount < 1 || foodCount > MAX_BLOB_CANT)				//Chequeo por excesos o numeros menores q 1
	{
		initBlobCount = 1;
	}
	ImGui::SetNextItemWidth(100);
	ImGui::InputFloat("Velocidad maxima",&velMax);					//Entrada para la velocidad maxima
	if (velMax < 0 || velMax > MAX_VEL)												//Chequeo de datos validos
	{
		velMax = 0;
	}
	ImGui::InputFloat("Radio de olfato", &smellRadius, 0.5f, 10.0f);				//Entrada del radio de olfateo
	if (smellRadius < 0 || smellRadius > MAX_SMELL_RADIUS)												//Correccion de valor
	{
		smellRadius = 0;
	}
	ImGui::SliderFloat("Probabilidad de muerte para Baby", &deathProbBb, 0.0f, 1.0f, "%.2f");			//Entrada por slider(no necesita chequeo de bordes) para las probabilidades 
	ImGui::SliderFloat("Probabilidad de muerte para Grown", &deathProbGb, 0.0f, 1.0f, "%.2f");			//	de muerte y el rango de angulo aleatorio para la fusion de los blobs 
	ImGui::SliderFloat("Probabilidad de muerte para Good Old", &deathProbGOb, 0.0f, 1.0f, "%.2f");
	ImGui::SliderFloat("Maximo de direccion de fusion", &randomJiggleLimit, 0.0f, 360.0f, "%.1f");
	ImGui::SetNextItemWidth(100);
	ImGui::InputInt("Cantidad de comida", (int*)&foodCount);									//Entrada de datos para el numero de comidas
	if (foodCount < 0 || foodCount > MAX_FOOD_CANT)										//Chequeo de bordes para valores
	{
		foodCount = 0;
	}
	ImGui::End();																//Terminamos y dibujamos
	al_clear_to_color(al_map_rgb(0, 50, 100));
	ImGui::Render();
	ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
	al_flip_display();
	
	return modeSelected;
}

void World::printBlobs()
{
	for (int i = 0; i < MAX_BLOB_CANT; i++)		//Recorremos el arreglo de blobs y dibujamos los que esten vivos
	{
		if (arrBlobs[i].isAlive)
		{
			al_draw_bitmap( arrBlobs[i].eGroup->texture.bitmap, arrBlobs[i].pos.x, arrBlobs[i].pos.y, 0);
		}
	}
}

void World::printFood()
{
	for (int i = 0; i < MAX_FOOD_CANT; i++)				//Recorremos el arreglo de comida y dibujamos las que esten sin comer
	{
		if (arrFood[i].isNotEaten)
		{
			al_draw_bitmap(arrFood[i].texture->bitmap, arrFood[i].pos.x, arrFood[i].pos.y, 0);
		}
	}
}

void World::gamePrint()
{

	ImGui_ImplAllegro5_NewFrame();										//Iniciamos el nuevo frame
	ImGui::NewFrame();
	al_clear_to_color(al_map_rgb(0, 50, 150));
	ImGui::SetNextWindowSize(ImVec2(DISPLAY_WIDTH, DISPLAY_HEIGHT - this->texture.height));	//Armamos el tamanio para la ventana de imgui
	ImGui::SetNextWindowPos(ImVec2(0, 470));
	ImGui::Begin("In Game");																//Iniciamos la ventana de imgui
	ImGui::SliderFloat("Velocidad de simulacion", &velPercent, 0.0f, 1.0f, "%.2f");			//Slider para manejar la velocidad de simulacion
	ImGui::SetNextItemWidth(100);															
	ImGui::InputFloat("Radio de olfato", &smellRadius, 0.5f, 10.0f);						//Entrada para el radio de olfateo
	if (smellRadius < 0)									//Chequeo y correccion de la entrada
	{
		smellRadius = 0;
	}
	ImGui::SliderFloat("Probabilidad de muerte para Baby", &deathProbBb, 0.0f, 1.0f, "%.2f");			//Slider para las probabilidades de muerte y el randomJiggleLimit
	ImGui::SliderFloat("Probabilidad de muerte para Grown", &deathProbGb, 0.0f, 1.0f, "%.2f");
	ImGui::SliderFloat("Probabilidad de muerte para Good Old", &deathProbGOb, 0.0f, 1.0f, "%.2f");
	ImGui::SliderFloat("Maximo de direccion de fusion", &randomJiggleLimit, 0.0f, 360.0f, "%.1f");
	ImGui::SetNextItemWidth(100);
	ImGui::InputInt("Cantidad de comida", (int*)&foodCount);								//Entrada para al cantidad de comida
	if (foodCount < 0 || foodCount > MAX_FOOD_CANT)							//Chequeo maximos y corrijo
	{
		foodCount = 0;
	}
	ImGui::End();														
	al_draw_bitmap(this->texture.bitmap, 0, 0, 0);						//Dibujo el mundo
	printBlobs();														//Dibujo los blobs
	printFood();														//Dibujo las comidas
	ImGui::Render();													//Termino de dibujar y apso a pantalla
	ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
	al_flip_display();
}


void World::initBlobs()
{
	for (unsigned int i = 0; i < this->initBlobCount; i++)
	{
		switch (this->modo)//En base al modo le asinamos una velocidad al blob
		{
		case MODO1:
			this->arrBlobs[i].vel = this->velMax;
			break;
		case MODO2:
			this->arrBlobs[i].vel = (rand() % (int)this->velMax) + 1;
			break;
		}

		this->arrBlobs[i].isAlive = 1;						//Lo inicializamos vivo y con posicion y direccion aleatoria
		this->arrBlobs[i].pos.x = (rand() % (this->texture.width - this->arrBlobs[i].eGroup->texture.width));
		this->arrBlobs[i].pos.y = (rand() % (this->texture.height - this->arrBlobs[i].eGroup->texture.height));
		this->arrBlobs[i].pos.direction = ((rand() % 3600) / 10.0F);

	}
}


void World::initFood()//Inicializador de comida, damos posicion al azar y hacemos que este "viva" 
{
	for (unsigned int i = 0; i < this->foodCount; i++)
	{
		this->arrFood[i].isNotEaten = true;
		this->arrFood[i].pos.x = (rand() % (this->texture.width - this->arrFood[i].texture->width));
		this->arrFood[i].pos.y = (rand() % (this->texture.height - this->arrFood[i].texture->height));
	}
}