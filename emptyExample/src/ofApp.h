#pragma once
#define _USE_MATH_DEFINES

#include "ofMain.h"
#include "ofxGui.h"
#include <vector>
#include <math.h> 
#include <cmath>

class ofApp : public ofBaseApp{
	ofImage default_image;
	ofxButton draw_square;
	ofxButton draw_circle;
	ofxButton draw_triangle;
	ofxButton draw_shape;
	ofxButton add_text;
	ofxButton take_screen_shot;
	ofxIntSlider select_shape;
	ofxIntSlider select_label;
	ofxIntSlider grid_size;
	ofxIntSlider screen_shot_x;
	ofxIntSlider screen_shot_y;
	ofxIntSlider screen_shot_width;
	ofxIntSlider screen_shot_height;
	ofxColorSlider grid_color;
	ofxToggle gridded;
	ofxPanel general_gui;
	ofxPanel shape_gui;
	ofxPanel text_gui;
	ofxPanel shape_list;
	ofxPanel text_list;
	int selected_shape;
	int selected_text;
	int previous_selected_shape;
	int previous_selected_text;
	int shape_count;
	int text_count;
	int current_grid_size;
	ofVec3f starting_position;

	const int kCircleResolution = 80;
	const int kDefaultSize = 12;
	const int kBaseRadius = 50;
	const int kBasePosition = 100;
	const int kScaleFactor = 200;
	const int kDefaultGridSize = 25;
	const float kDefaultLineWidth = 2;
	const ofColor kDefaultColor = ofColor(255, 255, 255);
	const ofColor kSelectionColor = ofColor(0, 0, 0);

	struct text {
		string name;
		ofxToggle hide_text;
		ofxToggle delete_text;
		bool current_hide;
		bool current_delete;
		ofxButton text_button;
		ofxLabel text_label;
		ofxIntSlider text_size;
		int current_size;
		int current_index;
		float x_position;
		float y_position;
		string text;
		ofColor current_color;
		ofxColorSlider color;
		ofxIntSlider index;
	};

	struct shape {
		std::vector<ofVec3f> points;
		std::string name;
		ofImage texture;
		ofxToggle textured;
		ofxToggle add_points;
		ofxToggle close_shape;
		ofxFloatSlider line_width;
		ofxIntSlider index;
		ofxLabel label;
		ofxToggle delete_shape;
		ofxToggle hide_shape;
		ofxButton add_texture;
		float current_width;
		ofxColorSlider color;
		ofColor current_color;
		ofxToggle filled;
		bool current_fill;
		bool current_textured;
		bool current_hide;
		bool current_delete;
		int current_index;
	};

	std::vector<shape*> shape_vector;
	std::vector<text*> text_vector;
	ofVec3f previous_mouse_position;

	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void DrawSquareButtonPressed();
		void DrawCircleButtonPressed();
		void DrawTriangleButtonPressed();
		void DrawShapeButtonPressed();
		void DrawShape(shape* to_draw);
		inline bool CheckFile(const std::string& name);
		void DrawSelectionTriangle(int position_x, int position_y);
		void SetupUI();
		void SetupShapeUI(int selected);
		void SetupTextUI(int selected);
		void ClearUI();
		void RotateShape(int direction, shape* to_rotate);
		ofVec3f FindShapeCenter(shape* shape);
		void StretchShape(ofVec3f starting_point, ofVec3f ending_point, shape* shape);
		ofVec3f FindFurthestDistance(ofVec3f point, shape* selected_shape);
		void EnlargeShape(ofVec3f point, shape* shape);
		void AddTextureButtonPressed();
		void DrawGrid();
		void AddTextButtonPressed();
		void AddLabelButtonPressed();
		void DeleteShapes();
		void DeleteText();
		void MoveShape();
		void MoveText();
		void TakeScreenShotButtonPressed();
};
