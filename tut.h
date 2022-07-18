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
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/UI.h>

#include <iostream>
#include <memory>

using namespace Urho3D;

class TutorialApp : public Application
{

    URHO3D_OBJECT(TutorialApp, Application)
    SharedPtr<Scene> scene_;
    Node* cameraNode_;

    Vector3 vel_;
    float timestep_;
    float yaw_;
    float pitch_;

public:
    TutorialApp(Context* context);

    virtual void Setup();
    virtual void Start();
    virtual void Stop();

    void HandleUpdate(StringHash eventType, VariantMap& eventData);

private:
    void CreateScene();
    void MoveCamera(VariantMap& eventData);
};
