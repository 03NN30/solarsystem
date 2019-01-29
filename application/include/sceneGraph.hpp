#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP

#include "glewInc.hpp"

#include "node.hpp"

class SceneGraph {
public:
    static SceneGraph& get() {
        static SceneGraph instance;
        return instance;
    }

    Node* &getRoot();
    
private:
    Node* root;
    void setRoot(Node* node);
    
    SceneGraph();
};

#endif