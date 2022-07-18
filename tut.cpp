#include "tut.h"

using namespace Urho3D;

TutorialApp::TutorialApp(Context* context)
    : Application(context)
{
}

void TutorialApp::Setup() {}

void TutorialApp::CreateScene()
{
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

    cameraNode_ = scene_->CreateChild("Camera");
    Camera* camera = cameraNode_->CreateComponent<Camera>();
    auto cam = cameraNode_->GetComponent<Camera>();
    cam->SetFarClip(100.0f);
    cam->SetFov(45.0f);
    cameraNode_->Translate(Vector3(0, 0, -2));

    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    Renderer* renderer = GetSubsystem<Renderer>();
    renderer->SetViewport(0, viewport);
}

void TutorialApp::Start()
{
    CreateScene();
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(TutorialApp, HandleUpdate));
}

void TutorialApp::Stop() {}

void TutorialApp::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    timestep_ = eventData[P_TIMESTEP].GetFloat();
    MoveCamera(eventData);
}

void TutorialApp::MoveCamera(VariantMap& eventData)
{
    const float MOUSE_SENS = 5.0f / 100.0f;
    const float MOVE_SPEED = 25.0f / 100.0f;

    auto* input = GetSubsystem<Input>();

    IntVector2 mouseMove = input->GetMouseMove();
    yaw_ += MOUSE_SENS * mouseMove.x_;
    pitch_ += MOUSE_SENS * mouseMove.y_;
    pitch_ = Clamp(pitch_, -90.0f, 90.0f);

    cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));

    if (input->GetKeyDown(KEY_ESCAPE))
        engine_->Exit();

    Vector3 move;
    if (input->GetKeyDown(KEY_W) || input->GetKeyDown(KEY_UP) || input->GetKeyDown(KEY_I))
        move += Vector3::FORWARD;
    else if (input->GetKeyDown(KEY_S) || input->GetKeyDown(KEY_DOWN) || input->GetKeyDown(KEY_K))
        move += -Vector3::FORWARD;
    if (input->GetKeyDown(KEY_A) || input->GetKeyDown(KEY_LEFT) || input->GetKeyDown(KEY_J))
        move += -Vector3::RIGHT;
    else if (input->GetKeyDown(KEY_D) || input->GetKeyDown(KEY_RIGHT) || input->GetKeyDown(KEY_L))
        move += Vector3::RIGHT;

    move.Normalize();
    vel_ += move * MOVE_SPEED * timestep_;

    auto oldY = cameraNode_->GetPosition().y_;
    cameraNode_->Translate(vel_);
    auto pos = cameraNode_->GetPosition();
    pos.y_ = oldY;
    cameraNode_->SetPosition(pos);

    vel_ *= 0.95f;
}

URHO3D_DEFINE_APPLICATION_MAIN(TutorialApp)
