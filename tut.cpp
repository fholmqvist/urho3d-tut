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

    initScene();
    auto* cam = initCamera();
    auto* cache = GetSubsystem<ResourceCache>();
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

void TutorialApp::initScene()
{
    scene_ = new Scene(context_);
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<PhysicsWorld>();
    auto* cache = GetSubsystem<ResourceCache>();

    Node* floorNode = scene_->CreateChild("Floor");
    floorNode->SetPosition(Vector3(0, -1.0f, 0));
    floorNode->SetScale(Vector3(200, 1.0f, 200));
    auto* object = floorNode->CreateComponent<StaticModel>();
    object->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    object->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));
    auto* floorBody = floorNode->CreateComponent<RigidBody>();
    auto* floorShape = floorNode->CreateComponent<CollisionShape>();
    floorShape->SetBox(Vector3::ONE);

    auto* boxNode = scene_->CreateChild("Model Node");
    boxNode->SetPosition(Vector3(0, 1.0f, 0));
    boxNode->SetScale(2.5f);
    auto* boxObject = boxNode->CreateComponent<StaticModel>();
    boxObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    boxObject->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));
    auto* body = boxNode->CreateComponent<RigidBody>();
    auto* shape = boxNode->CreateComponent<CollisionShape>();
    shape->SetBox(Vector3::ONE);

    auto* lightNode = scene_->CreateChild("Light Node");
    auto* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));
}

Node* TutorialApp::initCamera()
{
    auto camNode = scene_->CreateChild("Camera");
    auto* camera = camNode->CreateComponent<Camera>();
    auto cam = camNode->GetComponent<Camera>();
    cam->SetFarClip(100);
    cam->SetFov(45.0f);
    camNode->Translate(Vector3(0, Player::HEIGHT, -5));
    return camNode;
}

void TutorialApp::initViewport(Node* camNode)
{
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, camNode->GetComponent<Camera>()));
    auto* renderer = GetSubsystem<Renderer>();
    renderer->SetViewport(0, viewport);
}
