#include "tut.h"

using namespace Urho3D;

URHO3D_DEFINE_APPLICATION_MAIN(TutorialApp)
TutorialApp::TutorialApp(Context* context)
    : Application(context)
{
}

void TutorialApp::Setup() {}

void TutorialApp::Start()
{
    input_ = GetSubsystem<Input>();
    auto* cache = GetSubsystem<ResourceCache>();

    initScene(cache);
    auto* cam = initCamera();
    player_ = new Player(scene_, cache, cam);
    initViewport(cam);

    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(TutorialApp, HandleUpdate));
}

void TutorialApp::Stop() {}

void TutorialApp::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    if (input_->GetKeyDown(KEY_ESCAPE))
        engine_->Exit();

    timestep_ = eventData[P_TIMESTEP].GetFloat();

    player_->Update(timestep_);
}

void TutorialApp::initScene(ResourceCache* cache)
{
    scene_ = new Scene(context_);
    scene_->CreateComponent<Octree>();
    auto* physics = scene_->CreateComponent<PhysicsWorld>();
    physics->SetGravity(physics->GetGravity() * 80.0f);

    Levels::Load(scene_, cache, Level::Demo);
}

Node* TutorialApp::initCamera()
{
    auto camNode = scene_->CreateChild("Camera");
    auto* cam = camNode->CreateComponent<Camera>();
    cam->SetFarClip(100);
    cam->SetFov(45.0f);
    camNode->Translate(Vector3(0, Player::HEIGHT/2.0f, -5));
    return camNode;
}

void TutorialApp::initViewport(Node* cam)
{
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cam->GetComponent<Camera>()));
    auto* renderer = GetSubsystem<Renderer>();
    renderer->SetViewport(0, viewport);
}
