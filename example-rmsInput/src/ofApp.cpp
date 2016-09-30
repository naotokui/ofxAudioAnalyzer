#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    
    int sampleRate = 44100;
    int bufferSize = 2048;
    int outChannels = 0;
    int inChannels = 2;
    int ticksPerBuffer = bufferSize/64;
    
    buffer_1 =  new float[bufferSize];
    buffer_2 =  new float[bufferSize];
    for(int i = 0; i < bufferSize; i++) { buffer_1[i]=buffer_2[i]= 0;}
    audioAnalyzer1.setup(bufferSize, sampleRate);
    audioAnalyzer2.setup(bufferSize, sampleRate);
    
    audioAnalyzer1.setOnsetTreshold(0.50);
    audioAnalyzer1.setOnsetAlpha(3.0);
    
    ofSoundStreamSettings settings;
    settings.setInListener(this);
    settings.numOutputChannels = outChannels;
    settings.numInputChannels = inChannels;
    settings.sampleRate = sampleRate;
    settings.bufferSize = bufferSize;
    settings.numBuffers = ticksPerBuffer;
    
//    auto devices = soundStream.getMatchingDevices("default");
//    if(!devices.empty()){
//        settings.setInDevice(devices[0]);
//    }
    soundStream.setup(settings);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
//    if (audioAnalyzer1.getIsOnset()) cout << "onset!"  <<endl;
    ofSetColor(ofColor::seaGreen);
    
    float radius = 10 + 100*audioAnalyzer1.getRms();
    float xpos = ofGetWidth() *.5;
    float ypos = ofGetHeight()*.5;
    ypos -= ofGetHeight()*.5 * audioAnalyzer2.getRms();
    ofCircle(xpos, ypos, radius);
}
//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input){
    
    int bufferSize = input.getNumFrames();
    int nChannels = input.getNumChannels();
    vector<float>  buffer = input.getBuffer();
    for (int i = 0; i < input.getNumFrames(); i++){
        buffer_1[i]	= buffer[i*nChannels];
        buffer_2[i]	= buffer[i*nChannels+1];
    }
    audioAnalyzer1.analyze(buffer_1, bufferSize);
    audioAnalyzer2.analyze(buffer_2, bufferSize);
    
}
//--------------------------------------------------------------
void ofApp::exit(){
    soundStream.stop();
    soundStream.close();
    
    audioAnalyzer1.exit();
    audioAnalyzer2.exit();

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
