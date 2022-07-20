#pragma once

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Viewport.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/UI.h>

#include <iostream>
#include <memory>

#include "player.h"

using namespace Urho3D;

class TutorialApp : public Application
{
    URHO3D_OBJECT(TutorialApp, Application)
    Input* input_;
    SharedPtr<Scene> scene_;
    Player* player_;

    float timestep_;

public:
    TutorialApp(Context* context);

    virtual void Setup();
    virtual void Start();
    virtual void Stop();

    void HandleUpdate(StringHash eventType, VariantMap& eventData);

private:
    void initScene();
    Node* initCamera();
    void initPlayer(Node* camNode);
    void initViewport(Node* camNode);
};
