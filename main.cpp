#include <math.h>
#include <fstream>
#include <iostream>

#define PI 3.14159265

#define txm_FILE "test"

#define READ_CTOI(Char, Int) tSource.read(&Char, 1); Int = Char
#define COUT_VAL(val) std::cout << val << std::endl;

char testFunc(char input) {
	return 2 * input;
}

#define RAY (rayPart + ray * 30) / 10 * 5
#define MAX_RAY (30 + 9 * 30) / 10 * 5

#define Z_AS_COS cos((RAY / 2 - MAX_RAY / 4) / 180 * PI) * depthPerRay / 15
#define Z_AS_LINEAR depthPerRay / 10

int main(void) {
	std::ofstream rmcDraw = std::ofstream("rmc_draw.mcfunction", std::ios::out | std::ios::trunc);
	std::ofstream rmcDrawDebug = std::ofstream("rmc_drawDEBUG.mcfunction", std::ios::out | std::ios::trunc);
	std::ofstream rmcCls = std::ofstream("rmc_cls.mcfunction", std::ios::out | std::ios::trunc);

	int screenPos[3] = { 10, 10, 0 };

	rmcCls << "fill " << screenPos[0] << " " << screenPos[1] << " " << screenPos[2] << " " << screenPos[0] + 80 << " " << screenPos[1] + 50 << " " << screenPos[2] << " concrete 15\n" << std::endl;

	for (float ray = 0; ray <= 80; ray++) {
		for (float depthPerRay = 1; depthPerRay <= 10; depthPerRay++) {
			float rmc_dh = (ray / 2 - 20) * depthPerRay * 0.1;

			int tileData = 0;
			if (depthPerRay >= 7) {
				tileData = 7;
			}
			else if (depthPerRay >= 4) {
				tileData = 8;
			}

			//tp entity to proper position
			rmcDraw << "tp @e[type=rmc:void] ^" << -sin((ray / 2 - 20) * 4.2 / 180 * PI) * depthPerRay << "^^" << cos((ray / 2 - 20) * 4.2 / 180 * PI) * depthPerRay << "\n";

			//draw pixel(s)
			int pixelPos[3] = { screenPos[0] + ray, screenPos[1] + depthPerRay * 4, screenPos[2] };
			rmcDraw << "execute @e[type=rmc:void] ~~~ detect ~~~ concrete 0 execute @s " << pixelPos[0] << " " << pixelPos[1] << " " << pixelPos[2];
			rmcDraw << " fill ~~~ ~~50~ concrete " << tileData << " replace concrete 15";
			//proper flush
			rmcDraw << std::endl;
		}
	}

	for (float ray = 0; ray <= 80; ray++) {
		for (float depthPerRay = 1; depthPerRay <= 10; depthPerRay++) {
			float rmc_dh = (ray / 2 - 20) * depthPerRay * 0.1;

			int tileData = 0;
			if (depthPerRay >= 7) {
				tileData = 7;
			}
			else if (depthPerRay >= 4) {
				tileData = 8;
			}

			//tp entity to proper position
			rmcDrawDebug << "tp @e[type=rmc:void] ^" << -sin((ray / 2 - 20) * 4.2 / 180 * PI) * depthPerRay << "^^" << cos((ray / 2 - 20) * 4.2 / 180 * PI) * depthPerRay << "\n";
			rmcDrawDebug << "execute @e[type=rmc:void] ~~~ particle minecraft:basic_smoke_particle ~~~\n";

			//draw pixel(s)
			int pixelPos[3] = { screenPos[0] + ray, screenPos[1] + depthPerRay * 4, screenPos[2] };
			rmcDrawDebug << "execute @e[type=rmc:void] ~~~ detect ~~~ concrete 0 execute @s " << pixelPos[0] << " " << pixelPos[1] << " " << pixelPos[2];
			rmcDrawDebug << " fill ~~~ ~~50~ concrete " << tileData << " replace concrete 15";
			//proper flush
			rmcDrawDebug << std::endl;
		}
	}

	rmcDraw.close();
	rmcDrawDebug.close();
	rmcCls.close();

	return 0;
}