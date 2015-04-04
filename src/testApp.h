#pragma once

#include "ofMain.h"
#include "ofxCv.h"
using namespace ofxCv;
using namespace cv;

#include "ofxFaceTrackerThreaded.h"

class testApp : public ofBaseApp {
public:
	void setup();
    void exit();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofVideoGrabber cam;
    //test original is tracker
	ofxFaceTrackerThreaded tracker;
	ofVec2f position;
	float scale;
	ofVec3f orientation;
	ofMatrix4x4 rotationMatrix;
	
	Mat translation, rotation;
	ofMatrix4x4 pose;
	
	ofEasyCam easyCam;
    
    ofImage parrot;
    ofImage eyepatch;
    
    //other ideas
    
    

};
