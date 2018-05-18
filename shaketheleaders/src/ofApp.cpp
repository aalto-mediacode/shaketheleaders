#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    //Load images
    //image1.load("erdogan.png");
    //image1.load("putin.png");
    image1.load("trump.png");
    image1.resize(150,200);
    
    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.enableIndices();
    mesh.enableColors();
    
    meshCopy.setMode(OF_PRIMITIVE_LINES);
    meshCopy.enableIndices();
    meshCopy.enableColors();
    
    //Optimize the threshold
    float intensityThreshold = 75;
    w = image1.getWidth();
    h = image1.getHeight();
    
    //Go through all pixels, get color of pixels
    //Paint mesh verticies of pixel colors
    for(int x=0;x<w;x++)
    {
        for(int y=0;y<h;y++)
        {
            ofColor c = image1.getColor(x, y);
            
            float intensity = c.getLightness();
            
            if(intensity >= intensityThreshold)
            {
                //For 3D
                //                float saturation=c.getSaturation();
                //                float z=ofMap(saturation, 0, 255, -100, 100);
                ofVec3f pos(x*4,y*4,0);
                mesh.addVertex(pos);
                mesh.addColor(c);
                
                meshCopy.addVertex(pos);
                meshCopy.addColor(c);
                
                offsets.push_back(ofVec3f(ofRandom(0,100000), ofRandom(0,100000), ofRandom(0,100000)));
            }
        }
    }
    
    //How widely verticies move around
    displacementScale = 5;
    
    //Displacement increases or not
    shouldGo = false;
    
    float connectionDistance = 5;
    int numVerts = mesh.getNumVertices();
    
    for (int a=0; a<numVerts; ++a)
    {
        ofVec3f verta = mesh.getVertex(a);
        
        for (int b=a+1; b<numVerts; ++b)
        {
            ofVec3f vertb = mesh.getVertex(b);
            float distance = verta.distance(vertb);
            
            if (distance <= connectionDistance)
            {
                // In OF_PRIMITIVE_LINES, every pair of vertices or indices will be
                // connected to form a line
                mesh.addIndex(a);
                mesh.addIndex(b);
                
                meshCopy.addIndex(a);
                meshCopy.addIndex(b);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    float time;
    float timeScale;
    
    numVerts = mesh.getNumVertices();
    
    for (int i=0; i<numVerts; ++i)
    {
        ofVec3f vert = meshCopy.getVertex(i);
        
        time = ofGetElapsedTimef();
        timeScale = 2.0;
  
        ofVec3f timeOffsets = offsets[i];
        
        vert.x += (ofSignedNoise(time*timeScale+timeOffsets.x)) * displacementScale;
        vert.y += (ofSignedNoise(time*timeScale+timeOffsets.y)) * displacementScale;

        mesh.setVertex(i, vert);
    }
    
    if (shouldGo == true)
    {
        displacementScale += acc;
        
        if (displacementScale < 5)
        {
            shouldGo = false;

        }

    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    ofColor centerColor = ofColor(255,0,0);
    ofColor edgeColor(0,0,0);
    
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    //    ofBackground(255);
    //    easyCam.begin();
    //        ofPushMatrix();
    //            ofTranslate(-ofGetWidth()/2, ofGetHeight()/2);
    mesh.draw();
    //        ofPopMatrix();
    //    easyCam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 't')
    {
        acc = 6;
 
        shouldGo = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == 't')
    {
    acc  = -1;
    
    shouldGo = true;
    }
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
