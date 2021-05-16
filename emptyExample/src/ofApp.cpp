#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofDisableArbTex();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	default_image.load("C:/pic/bike.jpg");
	shape_count = 0;
	text_count = 0;
	current_grid_size = kDefaultGridSize;
	ofVec3f starting_position = ofVec3f(0, 0, 0);
	SetupUI();
}

//--------------------------------------------------------------
void ofApp::update() {
	current_grid_size = grid_size;
}

//--------------------------------------------------------------
void ofApp::draw(){
	// Creates the shape list based on the shapes currently availible, only updates when a shape is created or deleted
	if (selected_shape != -1 && previous_selected_shape != selected_shape) {	
		shape_list.clear();
		shape_gui.clear();
		shape_list.add(select_shape.setup("selected shape", selected_shape, 0, shape_vector.size() - 1));

		for (int i = 0; i < shape_vector.size(); i++) {
			shape_list.add(shape_vector[i]->label.setup(std::to_string(i) + "-" + shape_vector[i]->name));
		}
		
		// Creates the ui that allows the user to modify the currently selected shape
		SetupShapeUI(selected_shape);

		previous_selected_shape = selected_shape;
	}

	// Creates the text list based on the labels currently availible, only updates wehn a label is created or deleted
	if (selected_text != -1 && previous_selected_text != selected_text) {
		text_list.clear();
		text_gui.clear();
		text_list.add(select_label.setup("selected label", selected_text, 0, text_vector.size() - 1));

		for (int i = 0; i < text_vector.size(); i++) {
			text_list.add(text_vector[i]->text_label.setup(std::to_string(i) + "-" + text_vector[i]->name));
		}

		// Creates the ui that allows the user to modify the currently selected text
		SetupTextUI(selected_text);

		previous_selected_text = selected_text;
	}

	if (shape_vector.size() != 0) {
		selected_shape = select_shape;
	}

	if (text_vector.size() != 0) {
		selected_text = select_label;
	}

	for (shape* shape : shape_vector) {
		if (!shape->hide_shape) {
			DrawShape(shape);
		}
	}

	for (text* label : text_vector) {
		if (!label->hide_text) {
			ofTrueTypeFont font1;
			font1.load("C:/pic/OpenSans-Bold.ttf", label->text_size);
			ofSetColor(label->color);
			font1.drawString(label->text, label->x_position, label->y_position);
			ofSetColor(kDefaultColor);
		}
	}

	if (selected_shape != -1) {
		cout << selected_shape;
		shape_vector[selected_shape]->current_textured = shape_vector[selected_shape]->textured;
		shape_vector[selected_shape]->current_fill = shape_vector[selected_shape]->filled;
		shape_vector[selected_shape]->current_color = shape_vector[selected_shape]->color;
		shape_vector[selected_shape]->current_hide = shape_vector[selected_shape]->hide_shape;
		shape_vector[selected_shape]->current_delete = shape_vector[selected_shape]->delete_shape;
		DrawSelectionTriangle(FindShapeCenter(shape_vector[selected_shape]).x, FindShapeCenter(shape_vector[selected_shape]).y);
	}

	if (selected_text != -1) {
		text_vector[selected_text]->current_color = text_vector[selected_text]->color;
		text_vector[selected_text]->current_size = text_vector[selected_text]->text_size;
		text_vector[selected_text]->current_hide = text_vector[selected_text]->hide_text;
		text_vector[selected_text]->current_delete = text_vector[selected_text]->delete_text;
	}
	
	DrawGrid();
	general_gui.draw();
	shape_gui.draw();
	text_gui.draw();
	shape_list.draw();
	text_list.draw();
	previous_mouse_position = ofVec3f(mouseX, mouseY, 0);

	if (selected_shape != -1) {
		if (shape_vector[selected_shape]->index != selected_shape) {
			MoveShape();
		}
	}

	//if (selected_text != -1) {
		//if (text_vector[selected_text]->index != selected_text) {
			//MoveText();
		//}
	//}
	DeleteShapes();
	DeleteText();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_LEFT_CONTROL) {
		if (selected_shape != -1) {
			ofVec3f shape_center = FindShapeCenter(shape_vector[selected_shape]);

			for (int i = 0; i < shape_vector[selected_shape]->points.size(); i++) {
				ofVec3f point = shape_vector[selected_shape]->points[i];
				float x_difference = point.x - shape_center.x;
				float y_difference = point.y - shape_center.y;
				shape_vector[selected_shape]->points[i] = ofVec3f(mouseX + x_difference, mouseY + y_difference, 0);
			}
		}
	}

	if (key == OF_KEY_RIGHT) {
		if (selected_shape != -1) {
			RotateShape(1, shape_vector[selected_shape]);
		}
	}

	if (key == OF_KEY_LEFT) {
		if (selected_shape != -1) {
			RotateShape(-1, shape_vector[selected_shape]);
		}
	}

	if (key == OF_KEY_SHIFT) {
		if (selected_shape != -1) {
			EnlargeShape(ofVec3f(mouseX, mouseY, 0), shape_vector[selected_shape]);
		}
	}

	if (key == OF_KEY_ALT) {
		if (selected_shape != -1) {
			if (shape_vector[selected_shape]->add_points) {
				shape_vector[selected_shape]->points.push_back(ofVec3f(mouseX, mouseY, 0));
			}
		}
	}

	if (key == OF_KEY_TAB) {
		if (selected_text != -1) {
			text_vector[selected_text]->x_position = mouseX;
			text_vector[selected_text]->y_position = mouseY;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	starting_position = ofVec3f(x, y, 0);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	ofVec3f ending_position = ofVec3f(x, y, 0);

	if (selected_shape != -1) {
		StretchShape(starting_position, ending_position, shape_vector[selected_shape]);
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

// Takes a shape object and renders all its vectors, fill, and texture
void ofApp::DrawShape(shape* to_draw) {
	ofFbo fbo;
	ofImage texture = to_draw->texture;
	texture.resize(ofGetWidth(), ofGetHeight());
	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

	fbo.begin(); {
		ofClear(0, 0, 0, 0);
	}
	fbo.end();

	fbo.begin(); {
		ofClear(0, 0, 0, 0);
		ofSetColor(to_draw->color);
		ofSetLineWidth(to_draw->line_width);

		if (to_draw->filled) {
			ofFill();
		} else {
			ofNoFill();
		}

		ofSetLineWidth(to_draw->line_width);

		ofBeginShape();
		for (ofVec3f point : to_draw->points) {
			ofVertex(point);
		}

		if (to_draw->points.size() != 0 && to_draw->close_shape) {
			ofVertex(to_draw->points[0]);
		}
		ofEndShape();
	}
	fbo.end();

	if (to_draw->current_textured) {
		texture.getTexture().setAlphaMask(fbo.getTexture());
		texture.draw(0, 0);
	} else {
		fbo.draw(0, 0);
	}
}

// Creates a square shape the user can modify
void ofApp::DrawSquareButtonPressed() {
	selected_shape = shape_vector.size();
	shape *square = new shape();
	square->name = "square" + std::to_string(shape_count);
	shape_count++;
	square->points.push_back(ofVec3f(kBasePosition - kBaseRadius, kBasePosition - kBaseRadius, 0));
	square->points.push_back(ofVec3f(kBasePosition + kBaseRadius, kBasePosition - kBaseRadius, 0));
	square->points.push_back(ofVec3f(kBasePosition + kBaseRadius, kBasePosition + kBaseRadius, 0));
	square->points.push_back(ofVec3f(kBasePosition - kBaseRadius, kBasePosition + kBaseRadius, 0));
	square->texture = default_image;
	square->current_textured = false;
	square->current_color = kDefaultColor;
	square->current_width = kDefaultLineWidth;
	square->current_hide = false;
	square->current_delete = false;
	shape_vector.push_back(square);
}

// Creates a circle shape the user can modify
void ofApp::DrawCircleButtonPressed() {
	selected_shape = shape_vector.size();
	shape *circle = new shape();
	circle->name = "circle" + std::to_string(shape_count);
	shape_count++;
	double slice = 2 * M_PI / kCircleResolution;

	for (int i = 0; i < kCircleResolution; i++) {
		double angle = slice * i;
		int newX = (int)(kBasePosition + kBaseRadius * cos(angle));
		int newY = (int)(kBasePosition + kBaseRadius * sin(angle));
		circle->points.push_back(ofVec3f(newX, newY, 0));
	}

	circle->texture = default_image;
	circle->current_textured = false;
	circle->current_color = kDefaultColor;
	circle->current_width = kDefaultLineWidth;
	circle->current_hide = false;
	circle->current_delete = false;
	shape_vector.push_back(circle);
}

// Creates a triangle shape the user can modify
void ofApp::DrawTriangleButtonPressed() {
	selected_shape = shape_vector.size();
	shape *triangle = new shape();
	triangle->name = "triangle" + std::to_string(shape_count);
	shape_count++;
	triangle->points.push_back(ofVec3f(kBasePosition, kBasePosition - kBaseRadius, 0));
	triangle->points.push_back(ofVec3f(kBasePosition + kBaseRadius, kBasePosition + kBaseRadius, 0));
	triangle->points.push_back(ofVec3f(kBasePosition - kBaseRadius, kBasePosition + kBaseRadius, 0));
	triangle->texture = default_image;
	triangle->current_textured = false;
	triangle->current_color = kDefaultColor;
	triangle->current_width = kDefaultLineWidth;
	triangle->current_hide = false;
	triangle->current_delete = false;
	shape_vector.push_back(triangle);
}

// Creates a shape object tha tthe user can add points to by pressing alt, and modify
void ofApp::DrawShapeButtonPressed() {
	selected_shape = shape_vector.size();
	int this_shape = selected_shape;
	shape *new_shape = new shape();
	new_shape->name = "shape" + std::to_string(shape_count);
	shape_count++;
	new_shape->texture = default_image;
	new_shape->current_textured = false;
	new_shape->current_color = kDefaultColor;
	new_shape->current_width = kDefaultLineWidth;
	new_shape->current_hide = false;
	new_shape->current_delete = false;
	shape_vector.push_back(new_shape);
}

// Checks if a file path is valid
inline bool ofApp::CheckFile(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

// Find the center of a shape, used in various functions
ofVec3f ofApp::FindShapeCenter(shape* shape) {
	float x_position = 0;
	float y_position = 0;

	for (ofVec3f point : shape->points) {
		x_position += point.x;
		y_position += point.y;
	}

	return ofVec3f(x_position / shape->points.size(), y_position / shape->points.size(), 0);
}

// Draws a triangle on the center of the currently selected shape to indicate it has been selected
void ofApp::DrawSelectionTriangle(int position_x, int position_y) {
	shape *triangle = new shape();
	triangle->name = "triangle" + std::to_string(shape_count);
	triangle->points.push_back(ofVec3f(position_x, position_y, 0));
	triangle->points.push_back(ofVec3f(position_x + kBaseRadius / 3, position_y + kBaseRadius / 3, 0));
	triangle->points.push_back(ofVec3f(position_x - kBaseRadius / 3, position_y + kBaseRadius / 3, 0));
	triangle->current_textured = false;
	triangle->current_delete = false;
	triangle->current_color = kSelectionColor;
	triangle->current_width = kDefaultLineWidth;
	DrawShape(triangle);
}

void ofApp::SetupUI() {
	selected_shape = -1;
	selected_text = -1;
	previous_selected_shape = -1;
	previous_selected_text = -1;
	general_gui.setup("general");
	shape_gui.setup("modify");
	text_gui.setup("modify text");
	shape_list.setup("shapes");
	text_list.setup("labels");
	general_gui.add(draw_square.setup("square"));
	general_gui.add(draw_circle.setup("circle"));
	general_gui.add(draw_triangle.setup("triangle"));
	general_gui.add(draw_shape.setup("shape"));
	general_gui.add(add_text.setup("text"));
	general_gui.add(gridded.setup("show grid"));
	general_gui.add(grid_size.setup("grid size", current_grid_size, 2, 50));
	general_gui.add(take_screen_shot.setup("screen shot"));
	general_gui.add(screen_shot_x.setup("screen shot x", kBasePosition, 0, ofGetWidth()));
	general_gui.add(screen_shot_y.setup("screen shot y", kBasePosition, 0, ofGetHeight()));
	general_gui.add(screen_shot_width.setup("screen shot width", kBaseRadius, 1, ofGetWidth()));
	general_gui.add(screen_shot_height.setup("screen shot height", kBaseRadius, 1, ofGetHeight()));
	general_gui.add(grid_color.setup("grid color", kDefaultColor, ofColor(0, 0, 0), kDefaultColor));
	draw_square.addListener(this, &ofApp::DrawSquareButtonPressed);
	draw_circle.addListener(this, &ofApp::DrawCircleButtonPressed);
	draw_triangle.addListener(this, &ofApp::DrawTriangleButtonPressed);
	draw_shape.addListener(this, &ofApp::DrawShapeButtonPressed);
	add_text.addListener(this, &ofApp::AddTextButtonPressed);
	take_screen_shot.addListener(this, &ofApp::TakeScreenShotButtonPressed);
}

void ofApp::SetupShapeUI(int selected) {
	if (shape_vector[selected]->name.find("shape") != string::npos) {
		shape_gui.add(shape_vector[selected]->add_points.setup("add points"));
		shape_gui.add(shape_vector[selected]->close_shape.setup("close shape"));
	} else {
		shape_vector[selected]->add_points = false;
	}

	shape_gui.add(shape_vector[selected]->color.setup("color", shape_vector[selected]->current_color, ofColor(0, 0, 0), kDefaultColor));
	shape_gui.add(shape_vector[selected]->index.setup("index", selected, 0, shape_vector.size() - 1));
	shape_gui.add(shape_vector[selected]->filled.setup("fill", shape_vector[selected]->current_fill));
	shape_gui.add(shape_vector[selected]->line_width.setup("line width", shape_vector[selected]->current_width, 1, 5));
	shape_gui.add(shape_vector[selected]->textured.setup("textured", shape_vector[selected]->current_textured));
	shape_gui.add(shape_vector[selected]->hide_shape.setup("hide", shape_vector[selected]->current_hide));
	shape_gui.add(shape_vector[selected]->delete_shape.setup("delete", shape_vector[selected]->current_delete));
	shape_gui.add(shape_vector[selected]->add_texture.setup("add texture"));
	shape_vector[selected]->add_texture.addListener(this, &ofApp::AddTextureButtonPressed);
}

void ofApp::SetupTextUI(int selected) {
	text_gui.add(text_vector[selected]->color.setup("color", text_vector[selected]->current_color, ofColor(0, 0, 0), kDefaultColor));
	text_gui.add(text_vector[selected]->text_size.setup("size", text_vector[selected]->current_size, 1, 20));
	text_gui.add(text_vector[selected]->text_size.setup("index", selected, 0, text_vector.size() - 1));
	text_gui.add(text_vector[selected]->text_button.setup("add label"));
	text_gui.add(text_vector[selected]->hide_text.setup("hide", text_vector[selected]->current_hide));
	text_gui.add(text_vector[selected]->delete_text.setup("delete", text_vector[selected]->current_delete));
	text_vector[selected]->text_button.addListener(this, &ofApp::AddLabelButtonPressed);
}

void ofApp::ClearUI() {
	selected_shape = -1;
	previous_selected_shape = -1;
	general_gui.clear();
	shape_gui.clear();
	shape_list.clear();
}

// Rotates the shape
void ofApp::RotateShape(int direction, shape* to_rotate) {

	for (int i = 0; i < shape_vector[selected_shape]->points.size(); i++) {
		float x = shape_vector[selected_shape]->points[i].x - FindShapeCenter(to_rotate).x; 
		float y = shape_vector[selected_shape]->points[i].y - FindShapeCenter(to_rotate).y;
		float x_change = x * cos(direction * (M_PI / 180)) - y * sin(direction * (M_PI / 180));
		float y_change = x * sin(direction * (M_PI / 180)) + y * cos(direction * (M_PI / 180));
		shape_vector[selected_shape]->points[i] = ofVec3f(x_change + FindShapeCenter(to_rotate).x, y_change + FindShapeCenter(to_rotate).y, 0);
	}
}

// Stretches the shape based on mouse distance
void ofApp::StretchShape(ofVec3f starting_point, ofVec3f ending_point, shape* shape) {
	ofVec3f furthest_distance = FindFurthestDistance(ending_point, shape);
	float distance_change_x = ending_point.x - starting_point.x;
	float distance_change_y = ending_point.y - starting_point.y;

	for (int i = 0; i < shape->points.size(); i++) {
		float new_x = shape->points[i].x + distance_change_x * ((ending_point.x - shape->points[i].x - furthest_distance.x) / furthest_distance.x);
		float new_y = shape->points[i].y + distance_change_y * ((ending_point.y - shape->points[i].y - furthest_distance.y) / furthest_distance.y);
		shape->points[i] = ofVec3f(new_x, new_y, 0);
	}
}

// Scale the size of the shape based on mouse distance
void ofApp::EnlargeShape(ofVec3f point, shape* shape) {
	ofVec3f center = FindShapeCenter(shape);
	float change = abs((point.x - center.x + point.y - center.y) / kScaleFactor);

	for (int i = 0; i < shape->points.size(); i++) {
		float x = (shape->points[i].x - center.x) * change + center.x;
		float y = (shape->points[i].y - center.y) * change + center.y;
		shape->points[i] = ofVec3f(x, y, 0);
	}
}

// Finds the furthest point from a given point, used in drag to determine how much of thed drag distance should be applied
ofVec3f ofApp::FindFurthestDistance(ofVec3f point, shape* selected_shape) {
	float furthest_distance_x = point.x - selected_shape->points[0].x;
	float furthest_distance_y = point.y - selected_shape->points[0].y;

	for (int i = 1; i < selected_shape->points.size(); i++) {
		if (furthest_distance_x < abs(point.x - selected_shape->points[i].x)) {
			furthest_distance_x = point.x - selected_shape->points[i].x;
		}

		if (furthest_distance_y < abs(point.y - selected_shape->points[i].y)) {
			furthest_distance_y = point.y - selected_shape->points[i].y;
		}
	}

	return ofVec3f(furthest_distance_x, furthest_distance_y, 0);
}

void ofApp::AddTextureButtonPressed() {
	std::string file_path;
	file_path = ofSystemTextBoxDialog("input file path", file_path);

	if (CheckFile(file_path)) {
		shape_vector[selected_shape]->texture.load(file_path);
	}
}

// Draws the grid based on user configurations
void ofApp::DrawGrid() {
	if (gridded) {
		ofSetColor(grid_color);
		for (int i = current_grid_size; i < ofGetHeight(); i += current_grid_size) {
			ofDrawLine(ofVec2f(0, current_grid_size * i), ofVec2f(ofGetWidth(), current_grid_size * i));
		}

		for (int i = current_grid_size; i < ofGetWidth(); i += current_grid_size) {
			ofDrawLine(ofVec2f(current_grid_size * i, 0), ofVec2f(current_grid_size * i, ofGetHeight()));
		}
		ofSetColor(kDefaultColor);
	}
}

// Creates a text object that the user can modify
void ofApp::AddTextButtonPressed() {
	selected_text = text_vector.size();
	text *label = new text();
	label->name = "text" + std::to_string(text_count);
	label->current_color = kDefaultColor;
	label->current_size = kDefaultSize;
	label->current_hide = false;
	label->current_delete = false;
	label->x_position = kBasePosition;
	label->y_position = kBasePosition;
	text_count++;

	text_vector.push_back(label);
}

void ofApp::AddLabelButtonPressed() {
	std::string label;
	label = ofSystemTextBoxDialog("input label", label);

	text_vector[selected_text]->text = label;
}

// Deletes shapes objects and functions related to them
void ofApp::DeleteShapes() {
	std::vector<shape*> shapes;
	bool  shape_deleted = false;

	for (int i = 0; i < shape_vector.size(); i++) {
		if (!shape_vector[i]->delete_shape) {
			shapes.push_back(shape_vector[i]);
			continue;
		}

		shape_deleted = true;
	}

	shape_vector = shapes;

	if (shape_deleted) {
		if (shape_vector.size() != 0) {
			selected_shape = 0;
			previous_selected_shape = 0;
		} else {
			selected_shape = -1;
			previous_selected_shape = -1;
		}

		shape_gui.clear();
	}
}

// Deletes text objects and resets related functions and variables
void ofApp::DeleteText() {
	std::vector<text*> labels;
	bool text_deleted = false;

	for (int i = 0; i < text_vector.size(); i++) {
		if (!text_vector[i]->delete_text) {
			labels.push_back(text_vector[i]);
			continue;
		}

		text_deleted = true;
	}

	text_vector = labels;

	if (text_deleted) {
		if (text_vector.size() != 0) {
			selected_text = 0;
			previous_selected_text = 0;
		} else {
			selected_text = -1;
			previous_selected_text = -1;
		}

		text_gui.clear();
	}
}

// Changes the index of a shape to make it draw earlier or later
void ofApp::MoveShape() {
	shape *temp = shape_vector[selected_shape];
	vector<shape*> temp_vector;

	for (int i = 0; i < shape_vector.size(); i++) {
		if (i == shape_vector[selected_shape]->index) {
			temp_vector.push_back(temp);
		}

		if (i != selected_shape) {
			temp_vector.push_back(shape_vector[i]);
		}
	}

	shape_vector = temp_vector;
	selected_shape = temp->index;
}

// Changes the index of a label to make it draw earlier or later
void ofApp::MoveText() {
	text *temp = text_vector[selected_text];
	int index = text_vector[selected_text]->index;
	temp->index = selected_text;
	vector<text*> temp_vector;

	for (int i = 0; i < text_vector.size(); i++) {
		if (i == text_vector[selected_text]->index) {
			temp_vector.push_back(temp);
		}

		if (i != selected_text) {
			temp_vector.push_back(text_vector[i]);
		}
	}

	text_vector = temp_vector;
	selected_text = index;
	cout << selected_text;
}

void ofApp::TakeScreenShotButtonPressed() {
	ofImage screen_shot;
	screen_shot.grabScreen(screen_shot_x, screen_shot_y, screen_shot_width, screen_shot_height);
	screen_shot.save("screenshot.png");
}