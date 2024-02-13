#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();

	auto deg_span = 1.5;
	auto radius_span = 10;
	for (auto deg = 0; deg < 360; deg += 3) {

		for (auto radius = 60; radius <= 1024; radius += radius_span) {

			auto noise_location = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
			auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));

			auto left = glm::vec2(radius * cos((deg + deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD));
			auto right = glm::vec2(radius * cos((deg - deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD));
			auto next_left = glm::vec2((radius + radius_span) * cos((deg + deg_span * 0.5) * DEG_TO_RAD), (radius + radius_span) * sin((deg + deg_span * 0.5) * DEG_TO_RAD));
			auto next_right = glm::vec2((radius + radius_span) * cos((deg - deg_span * 0.5) * DEG_TO_RAD), (radius + radius_span) * sin((deg - deg_span * 0.5) * DEG_TO_RAD));

			auto noise_value = ofNoise(glm::vec3(noise_location * 10, radius * 0.01 - ofGetFrameNum() * 0.05));
			auto threshold = 0.6;
			if (noise_value < threshold) {

				this->face.addVertex(glm::vec3(left, 0));
				this->face.addVertex(glm::vec3(next_left, 0));
				this->face.addVertex(glm::vec3(next_right, 0));
				this->face.addVertex(glm::vec3(right, 0));

				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 2); this->face.addIndex(this->face.getNumVertices() - 3);
				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 3); this->face.addIndex(this->face.getNumVertices() - 4);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofSetColor(39);
	this->face.draw();

	/*
	int start = 300;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}