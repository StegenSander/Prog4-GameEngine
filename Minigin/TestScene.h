#pragma once
#include "Scene.h"

class TestScene :
    public dae::Scene
{
public:
    TestScene();

    void Initialise() override;
private:

    std::shared_ptr<dae::GameObject> CreatePlayer(int index);

    std::weak_ptr<dae::GameObject> m_Player1{};
    std::weak_ptr<dae::GameObject> m_Player2{};

};

