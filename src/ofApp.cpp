#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    ofSetFrameRate(24);
    ofSetVerticalSync(true);
    ofSetWindowPosition(ofGetScreenWidth() / 18., ofGetScreenHeight() / 18.);
    ofSetWindowShape(ofGetScreenWidth() / 18. * 16, ofGetScreenHeight() / 18. * 16);
    ofBackground(0);
    
    //setup client
    client.setup();
    directory.setup();
    
    //setup warp
    warp.setup();
    warp.setTargetRect(ofRectangle(ofGetWidth() / 3., ofGetHeight() / 3., ofGetWidth() / 3., ofGetHeight() / 3.));
    warp.load("warpSaveData.xml");
    sourceRect = ofRectangle(0, 0, 1080, 1080);
    warp.setSourceRect(sourceRect);
    
    //load windowRect
    tool.loadWindowRect();
}

//--------------------------------------------------------------
void ofApp::update() {

    ofSetWindowTitle("mapper | " + ofToString(round(ofGetFrameRate())) + " | " + ofToString(client.getWidth()) + " * " + ofToString(client.getHeight()) + " | " + client.getServerName());
    
    //search server
    if (client.getServerName() == "" && directory.size() > 0) {
        if (index >= directory.size()) index = 0;
        client.set(directory.getServerList()[index]);
    }
    
    //update warp
    if ((sourceRect.width != client.getWidth() || sourceRect.height != client.getHeight()) && client.getWidth() > 0 && client.getHeight() > 0) {
        sourceRect = ofRectangle(0, 0, client.getWidth(), client.getHeight());
        warp.setSourceRect(sourceRect);
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
        
    //draw client
    ofPushMatrix();
    ofMultMatrix(warp.getMatrix());
    if (client.getServerName() == "") {
        ofSetColor(255, 0, 0);
        ofDrawRectangle(sourceRect);
    } else {
        ofSetColor(255);
        client.draw(0, 0);
    }
    ofPopMatrix();
    
    //draw warp
    ofSetColor(255);
    warp.draw();
}

//--------------------------------------------------------------
void ofApp::exit() {
    
    //save warp
    warp.save("warpSaveData.xml");
    
    //save windowRect
    tool.saveWindowRect();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

    //warp
    if (key == 'r' || key == 'R') warp.setTargetRect(ofRectangle(ofGetWidth() / 3., ofGetHeight() / 3., ofGetWidth() / 3., ofGetHeight() / 3.));
    if (key == 'w' || key == 'W') warp.toggleShow();
    if (key == 's' || key == 'S') warp.save("warpSaveData.xml");
    if (key == 'l' || key == 'L') warp.load("warpSaveData.xml");
    
    //switch server
    if (key == ' ' && directory.size() > 0) {
        index++;
        if (index >= directory.size()) index = 0;
        client.set(directory.getServerList()[index]);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

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
