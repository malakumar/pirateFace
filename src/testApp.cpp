#include "testApp.h"

#define parrot_scaling_factor .175
#define patch_scaling_factor .008

using namespace ofxCv;

void testApp::setup() {
	ofSetVerticalSync(true);
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
	cam.initGrabber(640, 480);
    parrot.loadImage("images/parrot.png");
    eyepatch.loadImage("images/patch.png");
    //move parrot up
    parrot.setAnchorPercent(1.3, 0.05);
    //increase size of eyepatch, move eyepatch up
    eyepatch.setAnchorPercent(0.5, 1.05);
	tracker.setup();
}

void testApp::exit() {
    tracker.waitForThread();
}

void testApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		tracker.update(toCv(cam));
		position = tracker.getPosition();
		scale = tracker.getScale();
		orientation = tracker.getOrientation();
		rotationMatrix = tracker.getRotationMatrix();
	}
}

void testApp::draw() {
	ofSetColor(255);
	cam.draw(0, 0);
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
    ofPolyline rightEye = tracker.getImageFeature(tracker.RIGHT_EYE);
    ofRectangle boundingBox = rightEye.getBoundingBox();

	
	if(tracker.getFound()) {
        //wireframe face
//		ofSetLineWidth(1);
//		tracker.draw();
        
        //eyepatch
        ofPushMatrix();
        ofTranslate(position.x, position.y);
        ofScale(scale*boundingBox.width*patch_scaling_factor, scale*boundingBox.width*patch_scaling_factor);
        applyMatrix(rotationMatrix);
        eyepatch.draw(0,0);
        ofPopMatrix();
        
        //parrot
        ofPushMatrix();
        ofTranslate(position.x, position.y);
        ofScale(scale*parrot_scaling_factor, scale*parrot_scaling_factor);
        applyMatrix(rotationMatrix);
        parrot.draw(0,0);
        ofPopMatrix();
        
        
		//easyCam.begin();
//		ofSetupScreenOrtho(640, 480, -1000, 1000);
//		ofTranslate(640 / 2, 480 / 2);
//		applyMatrix(rotationMatrix);
//		ofScale(5,5,5);
//		ofDrawAxis(scale);
//		tracker.getObjectMesh().drawWireframe();
		//easyCam.end();
	}
}

void testApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
	}
    
    if(key == 'q') {
        tracker.reset();
    
    }
}