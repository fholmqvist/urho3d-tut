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
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/UI.h>

#include <iostream>
#include <memory>

#include "player.h"

class TutorialApp : public Urho3D::Application
{
    URHO3D_OBJECT(TutorialApp, Application)
    Urho3D::Input* input_;
    Urho3D::SharedPtr<Urho3D::Scene> scene_;
    Player* player_;

    float timestep_;

public:
    TutorialApp(Urho3D::Context* context);

    virtual void Setup();
    virtual void Start();
    virtual void Stop();

    void HandleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData);

private:
    void initScene();
    Urho3D::Node* initCamera();
    void initViewport(Urho3D::Node* cam);
};
