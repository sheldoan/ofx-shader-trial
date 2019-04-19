#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    panel.setup();
    panel.add(eyeScale.set("eyeScale", 2, 1, 10));
    panel.add(radiusScaleFactor.set("radiusScaleFactor", 0.3, 0, 5));
    panel.add(useMask.set("useMask", false, false, true));
    
    drawEyeShader.load("", "leftEyeShader.frag");
    
    //grabber.setup(1280,720);
    tracker.setup();
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    fbo.begin();
    ofClear(255);
    fbo.end();
    
    videoFrameFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    videoFrameFbo.begin();
    ofClear(255);
    videoFrameFbo.end();
    
    
    videoPlayer.load("joan of arc.mp4");
    videoPlayer.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    videoPlayer.update();
    drawEyeShader.load("", "leftEyeShader.frag");
    //grabber.update();
    
    // Update tracker when there are new frames
    if(videoPlayer.isFrameNew()){
        tracker.update(videoPlayer);
    }
}

void ofApp::distortEyes() {
    
    for (ofxFaceTracker2Instance instance : tracker.getInstances()) {
        ofPolyline left = instance.getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::LEFT_EYE);
        ofPoint midLeft;
        for (int i = 0; i < left.size(); i++){
            midLeft += left[i];
        }
        midLeft /= (float)left.size();
        
        ofPolyline right = instance.getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::RIGHT_EYE);
        ofPoint midRight;
        for (int i = 0; i < right.size(); i++){
            midRight += right[i];
        }
        midRight /= (float)right.size();
        vector<ofPoint> eyePoints = { midLeft, midRight };
        float distance = (midRight-midLeft).length();
        for (ofPoint eyePoint : eyePoints) {
            fbo.begin();
            ofClear(255);
            drawEyeShader.begin();
            drawEyeShader.setUniform1f("height", ofGetHeight());
            drawEyeShader.setUniform1f("radius", distance * radiusScaleFactor);
            drawEyeShader.setUniform1f("scale", eyeScale);
            drawEyeShader.setUniform2f("eyePos", eyePoint.x, eyePoint.y);
            drawEyeShader.setUniformTexture("frame", videoPlayer.getTexture(), 0);
            ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
            drawEyeShader.end();
            fbo.end();
            fbo.draw(0,0);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(0);
    fbo.begin();
    ofClear(255);
    fbo.end();
    
    if (tracker.getInstances().size() > 0) {
        vector<ofPath> facePaths;
        for (ofxFaceTracker2Instance instance : tracker.getInstances()) {
            ofPolyline face = instance.getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::FACE_OUTLINE);
            ofPath facePath;
            facePath.moveTo(face[0]);
            for (int i = 1; i < face.size(); i++) {
                facePath.lineTo(face[i]);
            }
            facePath.setFilled(true);
            facePaths.push_back(facePath);
        }
        
        fbo.begin();
        ofClear(255);
        for (ofPath facePath : facePaths) {
            facePath.draw();
        }
        fbo.end();
    }
    if (useMask) {
        videoPlayer.getTexture().setAlphaMask(fbo.getTexture());
    } else {
        videoPlayer.getTexture().disableAlphaMask();
    }
    videoPlayer.draw(0,0);
    distortEyes();
    //tracker.drawDebug();
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
