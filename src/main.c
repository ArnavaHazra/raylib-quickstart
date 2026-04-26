#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define WIDTH 	900
#define HEIGHT	600
#define G		1000	 	//Gravitational acc 
#define L1 		250			//Length of Upper mass 
#define L2 		150 		//Length of Lower mass 
#define M1		10 			//Mass of Upper mass 
#define M2 		10 			//Mass of Lower mass 
#define R1 		15			//Radius of Upper mass 
#define R2 		15 			//Radius of Lower mass 


//Global vars
float phi1, phi2, phi1_d, phi2_d, phi1_dd, phi2_dd;


//To get end pos coordinates
Vector2 get_end_pos(Vector2 start, float L,float phi) {
	Vector2 end= (Vector2) { 
		start.x + L * sinf(phi),  
		start.y + L * cosf(phi)
	};
	return end;
}


//To draw the line
void draw_line(Vector2 start, Vector2 end) {
	DrawLineEx(start, end, 2, WHITE);
}


//To draw the mass
void draw_mass(Vector2 end, float R) {
	DrawCircle(end.x, end.y, R, YELLOW);
}


//Double pendulam call
void double_pend(Vector2 start) {
	Vector2 start_pos_L1 = start;
	Vector2 end_pos_L1 = get_end_pos(start_pos_L1, L1, phi1);

	Vector2 start_pos_L2 = end_pos_L1;
	Vector2 end_pos_L2 = get_end_pos(start_pos_L2, L2, phi2);


	draw_line(start_pos_L1, end_pos_L1);
	draw_line(start_pos_L2, end_pos_L2);

	draw_mass(end_pos_L1, R1);
	draw_mass(end_pos_L2, R2);
}

//system parameters
void step(float dt) {

	//angular acc
	 phi1_dd = ( (-G*(2*M1+M2)*sinf(phi1)) - (M2*G*sinf(phi1-2*phi2)) - (2*sinf(phi1-phi2)*M2*(phi2_d*phi2_d*L2 + phi1_d*phi1_d*L1*cosf(phi1-phi2))) )/(L1*(2*M1 + M2 - (M2*cosf(2*phi1 - 2*phi2)) ));
	 phi2_dd = ( (2*sinf(phi1-phi2))*( (phi1_d*phi1_d*L1*(M1+M2)) + (G*(M1+M2)*cosf(phi1)) + (phi2_d*phi2_d*L2*M2*cosf(phi1-phi2)) ) )/( L2*(2*M1 + M2 - (M2*cosf(2*phi1 - 2*phi2))) );

	//angular vel
	 phi1_d += phi1_dd * dt;
	 phi2_d += phi2_dd * dt; 

	//angle 
	 phi1 += phi1_d * dt;
	 phi2 += phi2_d * dt;

}


//Initializing the system
void init_pend() {
	phi1 = GetRandomValue(-90, 90)*DEG2RAD;
	phi2 = GetRandomValue(-90, 90)*DEG2RAD;

	phi1_d = 0;
	phi2_d = 0;
}


int main(int argc, char *argv[]) {
	
	InitWindow(WIDTH, HEIGHT, "Double pendulum");
	SetTargetFPS(60);

	Vector2 start_pos_L1 = (Vector2){WIDTH/2, 0};
	init_pend();
	while(!WindowShouldClose()) {

		step(GetFrameTime());
		if(IsKeyPressed(KEY_SPACE))
			init_pend();
		BeginDrawing();
		ClearBackground(BLACK);
		double_pend(start_pos_L1);
		EndDrawing();
	}
	return 0;
}