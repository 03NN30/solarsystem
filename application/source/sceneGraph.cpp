#include "sceneGraph.hpp"

#include <iostream>
#include <string>

Node solarSystem;

SceneGraph::SceneGraph() {
    setRoot(&solarSystem);            
}

Node* &SceneGraph::getRoot() {
    return root;
}

void SceneGraph::setRoot(Node* node) {
    root = node;
}
