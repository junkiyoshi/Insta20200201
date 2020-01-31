#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
	ofEnableDepthTest();

	ofTrueTypeFont font;
	font.loadFont("fonts/Kazesawa-Bold.ttf", 28, true, true, true);

	string word = "PCDTOKYO2020PCDTOKYO2020";
	for (int i = 0; i < (int)word.size(); i++) {

		this->path_list.push_back(font.getCharacterAsPoints(word[i], true, false));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofFill();
	ofSetColor(39);
	ofDrawSphere(glm::vec3(), 180);

	int y = 0;
	for (auto radius = 200; radius < 250; radius += 5) {

		ofRotateX(ofMap(ofNoise(ofRandom(10000), ofGetFrameNum() * 0.001), 0, 1, 0, 360));
		ofRotateZ(ofMap(ofNoise(ofRandom(10000), ofGetFrameNum() * 0.001), 0, 1, 0, 360));
		for (int deg = 0; deg < 360; deg += 5) {

			auto location = glm::vec3(0, y, -radius);
			auto rotation_y = glm::rotate(glm::mat4(), (float)(deg * DEG_TO_RAD), glm::vec3(0, 1, 0));
			location = glm::vec4(location, 0) * rotation_y;

			ofPushMatrix();
			ofTranslate(location);
			ofRotateY(180 - deg);
			ofRotateX(180);

			int noise_index = ofMap(ofNoise(location.x * 0.008, location.y * 0.008, location.z * 0.008, ofGetFrameNum() * 0.005), 0, 1, 0, path_list.size());
			int tmp_size = (2 * radius * PI) / 72;
			auto outline = path_list[noise_index].getOutline();

			ofSetColor(239);
			ofFill();
			ofBeginShape();
			for (int line_index = 0; line_index < outline.size(); line_index++) {

				if (line_index != 0) { ofNextContour(true); }

				auto vertices = outline[line_index].getVertices();
				for (int i = 0; i < vertices.size(); i++) {

					ofVertex((vertices[i] / 28 * tmp_size) + glm::vec2(tmp_size * -0.5, tmp_size * 0.5));
				}
			}
			ofEndShape(true);

			ofSetColor(39);
			ofNoFill();
			ofBeginShape();
			for (int line_index = 0; line_index < outline.size(); line_index++) {

				if (line_index != 0) { ofNextContour(true); }

				auto vertices = outline[line_index].getVertices();
				for (int i = 0; i < vertices.size(); i++) {

					ofVertex((vertices[i] / 28 * tmp_size) + glm::vec2(tmp_size * -0.5, tmp_size * 0.5));
				}
			}
			ofEndShape(true);

			ofPopMatrix();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}