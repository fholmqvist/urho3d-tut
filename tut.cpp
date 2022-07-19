#include "tut.h"

using namespace Urho3D;

TutorialApp::TutorialApp(Context* context)
    : Application(context)
{
}

void TutorialApp::Setup() {}

void TutorialApp::Start()
{
    auto* input_ = GetSubsystem<Input>();

    scene_ = new Scene(context_);
    scene_->CreateComponent<Octree>();
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    Node* boxNode = scene_->CreateChild("Model Node");
    StaticModel* boxObject = boxNode->CreateComponent<StaticModel>();
    boxObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    boxObject->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));

    Node* lightNode = scene_->CreateChild("Light Node");
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));

    auto camNode = scene_->CreateChild("Camera");
    Camera* camera = camNode->CreateComponent<Camera>();
    auto cam = camNode->GetComponent<Camera>();
    cam->SetFarClip(100.0f);
    cam->SetFov(45.0f);
    camNode->Translate(Vector3(0, 0, -2));

    player_ = new Player(input_, camNode);

    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, camNode->GetComponent<Camera>()));
    Renderer* renderer = GetSubsystem<Renderer>();
    renderer->SetViewport(0, viewport);

    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(TutorialApp, HandleUpdate));
}

void TutorialApp::Stop() {}

void TutorialApp::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    if (input_->GetKeyDown(KEY_ESCAPE))
        engine_->Exit();

    timestep_ = eventData[P_TIMESTEP].GetFloat();

    player_->Move(timestep_);
}

URHO3D_DEFINE_APPLICATION_MAIN(TutorialApp)
