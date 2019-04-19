#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    panel.setup();
    panel.add(eyeScale.set("eyeScale", 2, 1, 10));
    panel.add(eyeRadius.set("eyeRadius", 20, 10, 100));
    drawEyeShader.load("", "leftEyeShader.frag");
    
    grabber.setup(1280,720);
    tracker.setup();
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    fbo.begin();
    ofClear(255);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    drawEyeShader.load("", "leftEyeShader.frag");
    grabber.update();
    
    // Update tracker when there are new frames
    if(grabber.isFrameNew()){
        tracker.update(grabber);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    grabber.draw(0,0);
    if (tracker.getInstances().size() > 0) {
        ofPolyline left = tracker.getInstances()[0].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::LEFT_EYE);
        ofPoint midLeft;
        for (int i = 0; i < left.size(); i++){
            midLeft += left[i];
        }
        midLeft /= (float)left.size();
        
        ofPolyline right = tracker.getInstances()[0].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::RIGHT_EYE);
        ofPoint midRight;
        for (int i = 0; i < right.size(); i++){
            midRight += right[i];
        }
        midRight /= (float)right.size();
    
        vector<ofPoint> eyePoints = { midLeft, midRight };
        for (ofPoint eyePoint : eyePoints) {
            fbo.begin();
            ofClear(255);
            drawEyeShader.begin();
            drawEyeShader.setUniform1f("height", ofGetHeight());
            drawEyeShader.setUniform1f("radius", eyeRadius);
            drawEyeShader.setUniform1f("scale", eyeScale);
            drawEyeShader.setUniform2f("eyePos", eyePoint.x, eyePoint.y);
            drawEyeShader.setUniformTexture("frame", grabber.getTexture(), 0);
            ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
            drawEyeShader.end();
            fbo.end();
            fbo.draw(0,0);
        }
//        ofSetColor(255);
//        ofFill();
//        ofDrawCircle(midLeft.x, midLeft.y, 30);
    }
    panel.draw();
        //tracker.drawDebug();
    
//    if (tracker.size() > 0){
//        ofPolyline left = tracker.getInstances()[0].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::LEFT_EYE);
//
//        ofPolyline right = tracker.getInstances()[0].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::RIGHT_EYE);
//        //left.draw();
//        ofPoint midLeft;
//        for (int i = 0; i < left.size(); i++){
//            midLeft += left[i];
//        }
//        midLeft /= (float)left.size();
//        ofDrawCircle(midLeft, 10);
//
//        ofPoint midRight;
//        for (int i = 0; i < right.size(); i++){
//            midRight += right[i];
//        }
//        midRight /= (float)right.size();
//        ofDrawCircle(midRight, 10);
//        //ofLine(midRight, midLeft);
//
//        float distance = (midRight-midLeft).length();
//        ofPoint diff = (midRight-midLeft);
//        float angle = atan2(diff.y, diff.x);
//
//        float scale = 200.0 / distance;
//        ofPolyline faceOutline = tracker.getInstances()[0].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::FACE_OUTLINE);
////        faceOutline.draw();
//        grabber.setAnchorPoint(midLeft.x, midLeft.y);
//        ofPushMatrix();
//        ofTranslate(mouseX, mouseY);
//        ofScale(scale, scale);
//        ofRotateZ(-angle*RAD_TO_DEG);
//        grabber.draw(0,0);
//
//        ofPushMatrix();
//        ofTranslate(-midLeft.x, -midLeft.y);
//        faceOutline.draw();
//        ofPopMatrix();
//
//        ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
